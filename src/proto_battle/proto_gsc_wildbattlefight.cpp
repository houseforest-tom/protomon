#include "../../include/proto_battle/proto_gsc_wildbattlefight.h"
#include "../../include/proto_battle/proto_gsc_wildbattleenemy.h"

ProtoGScWildBattleFight::ProtoGScWildBattleFight(ProtoGameScene *prev, ProtoBattle *parent) : ProtoGameScene(prev), m_pBattle(parent){
    onEnter(prev);
}

void ProtoGScWildBattleFight::onEnter(ProtoGameScene *prev){

    //Store Main Menu Scene
    this->prev = prev;

    //Get Reference to Spritesheet Sprite
    m_pTypesheetSpr = &(m_pBattle->getTexMgr().getAsset("typesheet"));
}

void ProtoGScWildBattleFight::update(float dt){

    if(!hasFinished()){

        m_accumTime += dt;

        //Return to Main Menu
        if(m_pBattle->getKeyboard().wasKeyPressed(sf::Keyboard::Escape)){
            m_pBattle->setBattleSceneAndDelete(prev, this);
        }

        if(m_pBattle->getKeyboard().wasKeyPressed(sf::Keyboard::Space)){
            //Player goes first
            if(m_pBattle->playerGoesFirst())
                m_pBattle->setBattleSceneAndDelete(new ProtoGScWildBattleCast(this, m_pBattle, m_pBattle->getPlayerMon().getMoveset().getMove(m_selection)), prev);
            //Enemy goes first
            else  m_pBattle->setBattleSceneAndDelete(new ProtoGScWildBattleEnemy(this, m_pBattle), prev);
        }

        ProtoMoveset &moveset = m_pBattle->getPlayerMon().getMoveset();

        //Manage Menu Item Selection
        if(m_pBattle->getKeyboard().wasKeyPressed(sf::Keyboard::S)){
            if(m_selection == 0 && moveset.isMoveInSlot(2)) m_selection = 2;
            if(m_selection == 1 && moveset.isMoveInSlot(3)) m_selection = 3;
        }

        // ---
        if(m_pBattle->getKeyboard().wasKeyPressed(sf::Keyboard::W)){
            if(m_selection == 2 && moveset.isMoveInSlot(0)) m_selection = 0;
            if(m_selection == 3 && moveset.isMoveInSlot(1)) m_selection = 1;
        }

        // ---
        if(m_pBattle->getKeyboard().wasKeyPressed(sf::Keyboard::D)){
            if(m_selection == 2 && moveset.isMoveInSlot(3)) m_selection = 3;
            if(m_selection == 0 && moveset.isMoveInSlot(1)) m_selection = 1;
        }

        // ---
        if(m_pBattle->getKeyboard().wasKeyPressed(sf::Keyboard::A)){
            if(m_selection == 1 && moveset.isMoveInSlot(0)) m_selection = 0;
            if(m_selection == 3 && moveset.isMoveInSlot(2)) m_selection = 2;
        }
    }else{
        m_pBattle->end();
    }
}

void ProtoGScWildBattleFight::draw(NRenderer &renderer){

    //Get Reference to Player Monster Sprite (Back)
    const NTexture &playerMonSpr = m_pBattle->getTexMgr().getAsset(m_pBattle->getPlayerMon().getSpriteAssetName(false));

    //Get Reference to Enemy Monster Sprite  (Front)
    const NTexture &enemyMonSpr  = m_pBattle->getTexMgr().getAsset(m_pBattle->getEnemyMon().getSpriteAssetName(true));

    float w = renderer.getWindowWidth();
    float h = renderer.getWindowHeight() - TEXTBOX_H;
    ubyte bb = m_pBattle->getScenery();

    //------

    //Always Render Battle Backdrop
    renderer.renderSubtexQuad(m_pBattle->getTexMgr().getAsset("battlebg"), 0, 0, w, h, .001f + (1.0f / 3) * (bb % 3), .001f + (1.0f / 4) * (bb / 3), -.001f + (1.0f / 3) * (bb % 3 + 1), -.001f + (1.0f / 4) * (bb / 3 + 1));

    //Render Enemy Monster Front Sprite
    renderer.renderTexQuad(enemyMonSpr, w - (320 + enemyMonSpr.getWidth() * 1.5), 390 - enemyMonSpr.getHeight() * 3, enemyMonSpr.getWidth() * 3, enemyMonSpr.getHeight() * 3);

    //Render Player Monster Back Sprite
    renderer.renderTexQuad(playerMonSpr, 300 - playerMonSpr.getWidth() * 1.5, h - playerMonSpr.getHeight() * 3, playerMonSpr.getWidth() * 3, playerMonSpr.getHeight() * 3);

    //Render Menu
    renderTextbox(renderer);
}

void ProtoGScWildBattleFight::onExit(void){
    //Do Nothing
}

//Dtor
ProtoGScWildBattleFight::~ProtoGScWildBattleFight(void){
    onExit();
}

void ProtoGScWildBattleFight::renderTextbox(NRenderer &renderer){

    float baseY = renderer.getWindowHeight() - TEXTBOX_H,
          w     = renderer.getWindowWidth();

    NTextBuffer<128> buf;
    sprintf(buf, "What should %s do?", m_pBattle->getPlayerMon().getNickname().c_str());

    //Render black Border
    glColor3f(0, 0, 0);
    renderer.renderQuad(0, baseY, w, TEXTBOX_H);

    //Render white Text Field
    glColor3f(.95f, .95f, .95f);
    protoRenderTextbox(renderer, m_pBattle->getTexMgr(), 5, baseY + 5, w - 10, TEXTBOX_H - 10);
    renderer.renderString(m_pBattle->getFontMgr().getAsset("default"), TEXTBOX_TS, 46, baseY + 20, renderer.packRGB(0, 0, 0), string(buf));

    //Render Box and Text for each Menu Choice
    for(uint i=0; i<4; ++i){

        float xCoord = w / 2.5f + w / 4 * (i % 2);
        float yCoord = baseY + (TEXTBOX_H / 2 - 12) * (i / 2) + 13;
        bool moveInSlot = (m_pBattle->getPlayerMon().getMoveset().isMoveInSlot(i));

        glColor3f(0, 0, 0);
        renderer.renderQuad(xCoord, yCoord, w / 4 - 6, TEXTBOX_H / 2 - 14);
        glColor3f(.95f, .95f, .95f);
        protoRenderTextbox(renderer, m_pBattle->getTexMgr(), xCoord + 2, yCoord + 2, w / 4 - 10, TEXTBOX_H / 2 - 18);

        renderer.renderString(m_pBattle->getFontMgr().getAsset("default"),
                              TEXTBOX_TS,
                              xCoord + 46 + (i == m_selection ? 36 + ABS(sinf(m_accumTime * 10)) * 16 : 0),
                              yCoord + 4, (i == m_selection ? 0x888888FF : 0x000000FF),
                             (moveInSlot ? ProtoMoveList::getMove( m_pBattle->getPlayerMon().getMoveset().getMove(i) ).getName() : "")
        );
    }

    //Render selected Move Information
    const ProtoMove &move = ProtoMoveList::getMove( m_pBattle->getPlayerMon().getMoveset().getMove(m_selection) );
    ProtoMoveset &mset = m_pBattle->getPlayerMon().getMoveset();

    sprintf(buf, "PP: %02u/%02u", mset.getLeftPP(m_selection), mset.getMaxPP(m_selection));

    renderer.renderString(m_pBattle->getFontMgr().getAsset("default"),
                          TEXTBOX_TS,
                          w / 4 - 50,
                          baseY + 56,
                          renderer.packRGB(0, 0, 0),
                          string(buf));


    //Render the Move's Type Icon
    float xCoord = w / 2.5f + w / 4 * (m_selection % 2);
    float yCoord = baseY + (TEXTBOX_H / 2 - 12) * (m_selection / 2) + 13;
    float v0 = (float)(move.getType()-1)/(float)(ProtoTypes::COUNT-1);
    float v1 = v0 + 32.f / m_pTypesheetSpr->getHeight();

    glColor3f(0, 0, 0);
    renderer.renderCircle(xCoord + 22 + TEXTBOX_H / 9.0f, yCoord + 7 + TEXTBOX_H / 9.0f, TEXTBOX_H / 8.2f);
    renderer.renderCircle(xCoord + 22 + TEXTBOX_H / 4.5f + 8 + TEXTBOX_H / 9.0f, yCoord + 7 + TEXTBOX_H / 9.0f, TEXTBOX_H / 8.2f);
    glColor3f(1, 1, 1);
    renderer.renderSubtexQuad(*m_pTypesheetSpr, xCoord + 22, yCoord + 7, TEXTBOX_H / 4.5f, TEXTBOX_H / 4.5f, 0, v0, 1, v1);

    //Render the Move's Class Icon
    v0 = ((float)move.getClass()+0) / (ProtoMoveClasses::COUNT);
    v1 = ((float)move.getClass()+1) / (ProtoMoveClasses::COUNT);

    renderer.renderSubtexQuad(m_pBattle->getTexMgr().getAsset("clssheet"), xCoord + 22 + TEXTBOX_H / 4.5f + 8, yCoord + 7, TEXTBOX_H / 4.5f, TEXTBOX_H / 4.5f, 0, v0, 1, v1);
}
