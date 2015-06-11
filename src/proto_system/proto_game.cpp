#include "../../include/proto_system/proto_game.h"
#include "../../include/proto_system/proto_dialog_system.h"

ProtoGame::ProtoGame(void){

    srand(time(nullptr));

    //Initialize Window & Renderer
    m_renderer.init(PROTO_SCREEN_W, PROTO_SCREEN_H, false);
    glEnable(GL_TEXTURE_2D);

    //Initialize Handlers for User Peripherals
    m_keyboard.init();

    //Timer Variables [in µs]
    m_lastFrameTime    = m_renderer.getElapsedTime();
    m_currentFrameTime = m_renderer.getElapsedTime();
    m_frameDeltaTime   = 0.0f; //Time passed since last Frame in sec

    //Load Font(s)
    m_fontMgr.setErrorKey("default");
    m_fontMgr.loadAsset("default", "res/fnt/default.ttf");

    //Load Texture(s)
    m_textureMgr.setErrorKey("error");
    m_textureMgr.loadAsset("error",     "res/img/error.png");
    m_textureMgr.loadAsset("typesheet", "res/img/types.png");
    m_textureMgr.loadAsset("bag",       "res/img/backpack.png");
    m_textureMgr.loadAsset("battlebg",  "res/img/battlebg.png");
    m_textureMgr.loadAsset("clssheet",  "res/img/classes.png");
    m_textureMgr.loadAsset("textbox",   "res/img/textbox.png");
    m_textureMgr.loadAsset("pwr",       "res/img/pwr.png");
    m_textureMgr.loadAsset("acc",       "res/img/acc.png");

    NTextBuffer<128> alias, src;
    for(uint t=1; t<ProtoTypes::COUNT; t++){

        sprintf(alias, "move_particle_%u", t);
        sprintf(src, "res/img/move_particles/move%u.png", t);
        m_textureMgr.loadAsset(alias, src);
    }


    //Load Species from File
    ProtoSpeciesList::init();
    ProtoSpeciesList::loadFromFile("res/dat/species.dat");
    loadSpeciesSprites();

    //Load Moves from File
    ProtoMoveList::init();
    ProtoMoveList::loadFromFile("res/dat/moves.dat");

    //Load Abilities from File
    ProtoAbilityList::init();
    ProtoAbilityList::loadFromFile("res/dat/abilities.dat");

    //Load Items from File
    ProtoItemList::init();
    ProtoItemList::loadFromFile("res/dat/items.dat");
    loadItemSprites();
    loadObjectSprites();

    ProtoLuaHandler::init();
    ProtoLuaHandler::executeFile("res/scr/test.lua");

    //Setup the Game Logic / Testbed Code
    initGameLogic();

    //Loop until Window was closed by clicking the [X] Icon or the [F1] Key was pressed
    while(!m_renderer.wasWindowClosed() && !PROTOKEYPR(m_keyboard, F1))
    {
        //Handle System-side Events
        m_renderer.handleEvents();

        //Update Peripherals
        m_keyboard.update();
        m_mouse.update(m_renderer);

        //Clear the Screen
        m_renderer.clearScreen(0, 0, 0);
        glColor3f(1, 1, 1);

        //Update Map independent Game Objects
        m_objectMgr.update(m_frameDeltaTime);

        switch(m_gameState)
        {

        case ProtoGameState::WORLD:

            //Determine Camera Position
            determineCameraPos();

            //Draw Tilemap and Map Objects
            m_pMap->draw(m_renderer);

            if(ProtoDialogSystem::isActive())
            {
                bool playerFrozenBefore = m_pPlayer->isFrozen();
                if(!playerFrozenBefore) m_pPlayer->freeze();

                ProtoDialogSystem::dispatch(*this, m_frameDeltaTime);
                ProtoDialogSystem::draw(*this);

                if(!ProtoDialogSystem::isActive() && playerFrozenBefore)
                {
                    m_pPlayer->unfreeze();
                }
            }

            //Update Map Objects
            m_pMap->update(m_frameDeltaTime);

            //Initiate wild Battle
            if(PROTOKEYPR(m_keyboard, Return) && !m_pPlayer->isWalking())
            {
                m_gameState = ProtoGameState::BATTLE_WILD;
                ProtoTeam enemyTeam;
                enemyTeam.addMember(new ProtoMonster( 1 + (rand() % ProtoSpeciesList::getSpeciesCount()), 25));
                m_pBattle = new ProtoBattle(m_objectMgr, m_textureMgr, m_fontMgr, m_keyboard, m_mouse, m_pPlayer->getTeam(), enemyTeam, m_pPlayer->getBag(), 0);
            }

        break;

        case ProtoGameState::BATTLE_WILD:

            if(m_pBattle->hasEnded())
            {
                delete m_pBattle;
                m_pBattle = nullptr;
                m_gameState = ProtoGameState::WORLD;
            }

        break;

        }

        //Draw Map independent Objects
        m_objectMgr.draw(m_renderer);

        //Draw Overlay
        drawOverlay();

        //Swap Back Buffers to present Frame
        m_renderer.present();

        //Handle Timing Issues
        m_frameDeltaTime = (m_currentFrameTime - m_lastFrameTime) / 1E6;
        m_lastFrameTime = m_currentFrameTime;
        m_currentFrameTime = m_renderer.getElapsedTime();
    }
}

ProtoGame::~ProtoGame(void)
{
    ProtoLuaHandler::destroy();

    //Delete Map
    delete m_pMap;

    //Unload Lists
    ProtoSpeciesList::unload();
    ProtoMoveList::unload();
    ProtoItemList::unload();
}

void ProtoGame::initGameLogic(void)
{
    //Create Map
    m_pMap = new ProtoMap(32, 24, "blackvolution", m_textureMgr);
    ubyte tmpMapEntryID;
    bool  tmpMapEntryColl;
    ubyte possibleTiles[] = { /* 0, */ 1, 4, 5, 8, 9, 10, 18 };
    for(ubyte l=0; l<PROTO_TILE_LAYERS; ++l){
        for(uint x=0; x<m_pMap->getWidth(); ++x){
            for(uint y=0; y<m_pMap->getHeight(); ++y){
                tmpMapEntryID = possibleTiles[ rand() % sizeof(possibleTiles) ];
                tmpMapEntryColl = (tmpMapEntryID == 5);
                m_pMap->getLayer(l).setEntry(x, y, tmpMapEntryID);
                m_pMap->getCollisionData().setEntry(x, y, tmpMapEntryColl);
            }
        }
    }

    //Create Player
    m_pPlayer = new ProtoPlayer(m_textureMgr, m_keyboard);
    m_pPlayer->setMapSize(m_pMap->getWidth(), m_pMap->getHeight());
    m_pMap->addObject(m_pPlayer, "player");

    //Create Random NPCs on Map
    NTextBuffer<32> name;
    for(uint i=0; i<20; i++)
    {
        sprintf(name, "Proto-NPC-%02u", i);
        m_pMap->addObject(new ProtoNPC(m_textureMgr, name, i % 7), name);
        auto& npc = *dynamic_cast<ProtoNPC*>(&m_pMap->getObject(name));
        npc.setTileX(rand() % m_pMap->getWidth());
        npc.setTileY(rand() % m_pMap->getHeight());
        npc.setDrawSize(PROTO_TILE_SIZE, PROTO_TILE_SIZE / 4 * 5);
        npc.setDirection(rand() % 4);
    }
}

void ProtoGame::loadSpeciesSprites(void)
{

    NTextBuffer<128> aliasBuf, pathBuf;

    for(uint species = 1; species <= ProtoSpeciesList::getSpeciesCount(); species++){

        //Back Sprite
        sprintf(aliasBuf, "b_%u", species);
        sprintf(pathBuf,  "res/img/monsters/back_male/%u.tga", species);
        if(!m_textureMgr.loadAsset(aliasBuf, pathBuf)){
            sprintf(pathBuf,  "res/img/monsters/back_female/%u.tga", species);
            m_textureMgr.loadAsset(aliasBuf, pathBuf);
        }

        //Back Sprite (Shiny)
        sprintf(aliasBuf, "b_s_%u", species);
        sprintf(pathBuf,  "res/img/monsters/back_male_shiny/%u.tga", species);
        if(!m_textureMgr.loadAsset(aliasBuf, pathBuf)){
            sprintf(pathBuf,  "res/img/monsters/back_female_shiny/%u.tga", species);
            m_textureMgr.loadAsset(aliasBuf, pathBuf);
        }

        //Front Sprite (1)
        sprintf(aliasBuf, "f_%u", species);
        sprintf(pathBuf,  "res/img/monsters/male_1/%u.tga", species);
        if(!m_textureMgr.loadAsset(aliasBuf, pathBuf)){
            sprintf(pathBuf,  "res/img/monsters/female_1/%u.tga", species);
            m_textureMgr.loadAsset(aliasBuf, pathBuf);
        }

        //Front Sprite (1, Shiny)
        sprintf(aliasBuf, "f_s_%u", species);
        sprintf(pathBuf,  "res/img/monsters/male_1_shiny/%u.tga", species);
        if(!m_textureMgr.loadAsset(aliasBuf, pathBuf)){
            sprintf(pathBuf,  "res/img/monsters/female_1_shiny/%u.tga", species);
            m_textureMgr.loadAsset(aliasBuf, pathBuf);
        }

        //Front Sprite (2)
        sprintf(aliasBuf, "f2_%u", species);
        sprintf(pathBuf,  "res/img/monsters/male_2/%u.tga", species);
        if(!m_textureMgr.loadAsset(aliasBuf, pathBuf)){
            sprintf(pathBuf,  "res/img/monsters/female_2/%u.tga", species);
            m_textureMgr.loadAsset(aliasBuf, pathBuf);
        }

        //Front Sprite (2, Shiny)
        sprintf(aliasBuf, "f2_s_%u", species);
        sprintf(pathBuf,  "res/img/monsters/male_2_shiny/%u.tga", species);
        if(!m_textureMgr.loadAsset(aliasBuf, pathBuf)){
            sprintf(pathBuf,  "res/img/monsters/female_2_shiny/%u.tga", species);
            m_textureMgr.loadAsset(aliasBuf, pathBuf);
        }

        //Icons
        sprintf(aliasBuf, "i%u", species);
        sprintf(pathBuf,  "res/img/monsters/icons/%u.png", species);
        m_textureMgr.loadAsset(aliasBuf, pathBuf);
    }
}

void ProtoGame::loadItemSprites(void)
{

    NTextBuffer<128> pathBuf, aliasBuf;

    for(ushort item = 1; item <= ProtoItemList::getItemCount(); ++item){

        sprintf(aliasBuf, "item_%u", item);
        sprintf(pathBuf,  "res/img/items/%u.png", item);

        m_textureMgr.loadAsset(aliasBuf, pathBuf);
    }
}

void ProtoGame::loadObjectSprites(void)
{
    m_textureMgr.loadAsset("rarrow", "res/img/rarrow.png");
    m_textureMgr.loadAsset("npc_sheet", "res/img/objects/npc.png");
}

void ProtoGame::determineCameraPos(void)
{
    int widthPx        = m_pMap->getWidth()  * PROTO_TILE_SIZE;
    int heightPx       = m_pMap->getHeight() * PROTO_TILE_SIZE;
    int visiblePxHor   = PROTO_SCREEN_W;
    int visiblePxVer   = PROTO_SCREEN_H;

    //Drawing Offset
    float camx = roundf(m_pPlayer->getX() - visiblePxHor / 2);
    float camy = roundf(m_pPlayer->getY() - visiblePxVer / 2);

    if(camx < 0) camx = 0;
    if(camy < 0) camy = 0;

    //Map is wider than one Screen can fit
    if(widthPx > visiblePxHor)
    {
        if(camx > widthPx - visiblePxHor)
        {
            camx = widthPx - visiblePxHor;
        }
    }
    else
    {
        camx = 0;
    }

    //Map is higher than one Screen can fit
    if(heightPx > visiblePxVer)
    {
        if(camy > heightPx - visiblePxVer)
        {
            camy = heightPx - visiblePxVer;
        }
    }
    else
    {
        camy = 0;
    }

    //Add Screen Padding on the Horizontal for small Maps
    if(widthPx < visiblePxHor)
        camx -= (visiblePxHor - widthPx) / 2.f;

    //Add Screen Padding on the Vertical for small Maps
    if(heightPx < visiblePxVer)
        camy -= (visiblePxVer - heightPx) / 2.f;

    m_pMap->setCameraPosition(camx, camy);
    m_pPlayer->setCameraPosition(camx, camy);
}

void ProtoGame::drawOverlay(void)
{
    NTextBuffer<128> buf;

    sprintf(buf, "FPS: %03u {%02u ms}", m_renderer.getFPS(), (uint)(m_frameDeltaTime * 1000.f));
    m_renderer.renderString(m_fontMgr.getAsset("default"), 13, 10, 10, 0xFFFFFFFF, buf);

    sprintf(buf, "Vertices: %05u", (uint)m_renderer.dbg_verticesRendered);
    m_renderer.renderString(m_fontMgr.getAsset("default"), 13, 10, 26, 0xFFFFFFFF, buf);

    sprintf(buf, "Camera: {x: %d y: %d}", (int)m_pMap->getCameraX(), (int)m_pMap->getCameraY());
    m_renderer.renderString(m_fontMgr.getAsset("default"), 13, 10, 42, 0xFFFFFFFF, buf);

    sprintf(buf, "Player: {x: %d [%02u] y: %d [%02u]", (int)m_pPlayer->getX(), m_pPlayer->getTileX(), (int)m_pPlayer->getY(), m_pPlayer->getTileY());
    m_renderer.renderString(m_fontMgr.getAsset("default"), 13, 10, 58, 0xFFFFFFFF, buf);
}
