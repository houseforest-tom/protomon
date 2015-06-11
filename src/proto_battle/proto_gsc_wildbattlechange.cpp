#include "../../include/proto_battle/proto_gsc_wildbattlechange.h"

ProtoGScWildBattleChange::ProtoGScWildBattleChange(ProtoGameScene *prev, ProtoBattle *parent) : ProtoGameScene(prev), m_pBattle(parent){
    onEnter(prev);
}

void ProtoGScWildBattleChange::onEnter(ProtoGameScene *prev){

    //Store previous Scene (Main Menu)
    this->prev = prev;
}

void ProtoGScWildBattleChange::update(float dt){

    if(!hasFinished()){

        m_accumTime += dt;

        if(m_pBattle->getKeyboard().wasKeyPressed(sf::Keyboard::Escape)){
            m_pBattle->setBattleSceneAndDelete(prev, this); //Return to Main Scene
        }

        //Manouver one Item down
        if(m_pBattle->getKeyboard().wasKeyPressed(sf::Keyboard::S)){
            if(m_selection < m_pBattle->getPlayerTeam().getSize() - 1) m_selection++;
        }

        //Manouver one Item up
        if(m_pBattle->getKeyboard().wasKeyPressed(sf::Keyboard::W)){
            if(m_selection > 0) m_selection--;
        }

        //[SPACE] pressed -> Do something according to Selection
        if(m_pBattle->getKeyboard().wasKeyPressed(sf::Keyboard::Space)){
        }
    }
}

void ProtoGScWildBattleChange::draw(NRenderer &renderer){

    NTextBuffer<128> buf;
    const NFont &fnt = m_pBattle->getFontMgr().getAsset("default");
    float ww = renderer.getWindowWidth();
    float wh = renderer.getWindowHeight();
    float sz = 2.4f;

    const NTexture &currentPokeSpr = m_pBattle->getTexMgr().getAsset(m_pBattle->getPlayerTeam().getMember(m_selection)->getSpriteAssetName(true));

    float x = 256 + 10;
    float y = 256 + 10;

    ProtoMonster &mon = *(m_pBattle->getPlayerTeam().getMember(m_selection));

    //Render White BG Quad for Sprite Preview (+ Name)
    glColor3f(.95f, .95f, .95f);
    renderer.renderQuad(5, 5, 256, 256);
    renderer.renderTexQuad(currentPokeSpr, 130 - currentPokeSpr.getWidth() * sz / 2, 218 - currentPokeSpr.getHeight() * sz, currentPokeSpr.getWidth() * sz,  currentPokeSpr.getHeight() * sz);
    renderer.renderString(fnt, 20, 10, 10, 0x000000FF, ProtoSpeciesList::getSpecies(mon.getSpecies()).getName());
    sprintf(buf, "L%03u", mon.getLevel());
    renderer.renderString(fnt, 20, 205, 10, 0x000000FF, string(buf));


    //Render Type Emblems
    float v0 = (float)(ProtoSpeciesList::getSpecies(mon.getSpecies()).getType1() - 1)/(float)(ProtoTypes::COUNT-1);
    float v1 = v0 + 32.f / m_pBattle->getTexMgr().getAsset("typesheet").getHeight();

    //Only of one Type
    if(!ProtoSpeciesList::getSpecies(mon.getSpecies()).getType2()){
        glColor3f(0, 0, 0);
        renderer.renderCircle(256 - 34 + 17, 240, 17);
        glColor3f(1, 1, 1);
        renderer.renderSubtexQuad(m_pBattle->getTexMgr().getAsset("typesheet"), 256 - 33, 224, 32, 32, 0, v0, 1, v1);
    }

    //Has secondary Type
    else{
        glColor3f(0, 0, 0);
        renderer.renderCircle(256 - 34 - 36 + 17, 240, 17);
        renderer.renderCircle(256 - 34 + 17, 240, 17);

        glColor3f(1, 1, 1);
        renderer.renderSubtexQuad(m_pBattle->getTexMgr().getAsset("typesheet"), 256 - 33 - 36, 224, 32, 32, 0, v0, 1, v1);
        v0 = (float)(ProtoSpeciesList::getSpecies(mon.getSpecies()).getType2() - 1)/(float)(ProtoTypes::COUNT-1);
        v1 = v0 + 32.f / m_pBattle->getTexMgr().getAsset("typesheet").getHeight();
        renderer.renderSubtexQuad(m_pBattle->getTexMgr().getAsset("typesheet"), 256 - 33, 224, 32, 32, 0, v0, 1, v1);
    }


    //Render Stat Preview
    glColor3f(.95f, .95f, .95f);
    renderer.renderQuad(x, 5, ww - x - 5, 256);
    renderer.renderString(fnt, 20, x + 10, 10, 0x000000FF, "NICKNAME:");
    sprintf(buf, "\"%s\"", mon.getNickname().c_str());
    renderer.renderString(fnt, 20, x + 44, 30, 0x000000FF, string(buf));


    for(uint i=0; i<ProtoPrimStats::COUNT; ++i){
        sprintf(buf, "%s:", protoPrimStatToStr(i).c_str());
        renderer.renderString(fnt, 20, x + 10, 100 + i * 24, 0x000000FF, string(buf));
        sprintf(buf, "%03u/%03u", mon.getMaxStat(i), mon.getCurrentStat(i));
        renderer.renderString(fnt, 20, x + 94, 100 + i * 24, 0x000000FF, string(buf));
    }

    //Render Selection Menu
    glColor3f(.95f, .95f, .95f);
    renderer.renderQuad(5, y, 256, wh - y - 5);
    for(uint i=0; i<m_pBattle->getPlayerTeam().getSize(); ++i){
        sprintf(buf, "%s%s", (i == m_selection ? "> " : ""), m_pBattle->getPlayerTeam().getMember(i)->getNickname().c_str());
        renderer.renderString(fnt, 20, 32, y + 48 + i * 64, 0x000000FF, string(buf));
    }

    //Render Move Preview
    glColor3f(.95f, .95f, .95f);
    renderer.renderQuad(x, y, ww - x - 5, wh - y - 5);

    glColor3f(.85f, .85f, .85f);
    ProtoMoveset &moveset = mon.getMoveset();
    for(uint i=0; i<PROTO_MOVESET_SIZE; ++i){

        glColor3f(.85f, .85f, .85f);
        renderer.renderQuad(x + 10, y + 28 + i * 100, ww - x - 25, 90);

        float v0 = ((float)ProtoMoveList::getMove(moveset.getMove(i)).getType()-1) / (ProtoTypes::COUNT - 1);
        float v1 = ((float)ProtoMoveList::getMove(moveset.getMove(i)).getType()+0) / (ProtoTypes::COUNT - 1);

        if(moveset.isMoveInSlot(i)){

            sprintf(buf, "%02u/%02u", moveset.getLeftPP(i), moveset.getMaxPP(i));
            renderer.renderString(fnt, 20, x + 20,  y + 44 + i * 100, 0x000000FF, string(buf));
            renderer.renderString(fnt, 20, x + 140, y + 44 + i * 100, 0x000000FF, ProtoMoveList::getMove(moveset.getMove(i)).getName());
            renderer.renderString(fnt, 14, x + 20,  y + 88 + i * 100, 0x000000FF, ProtoMoveList::getMove(moveset.getMove(i)).getDescription());

            glColor3f(0, 0, 0);
            renderer.renderCircle(x + 400 + 16, y + 38 + 16 + i * 100, 17);
            renderer.renderCircle(x + 448 + 16, y + 38 + 16 + i * 100, 17);

            glColor3f(1, 1, 1);
            renderer.renderSubtexQuad(m_pBattle->getTexMgr().getAsset("typesheet"), x + 400, y + 38 + i * 100, 32, 32, 0, v0, 1, v1);

            v0 = ((float)ProtoMoveList::getMove(moveset.getMove(i)).getClass()+0) / (ProtoMoveClasses::COUNT);
            v1 = ((float)ProtoMoveList::getMove(moveset.getMove(i)).getClass()+1) / (ProtoMoveClasses::COUNT);

            renderer.renderSubtexQuad(m_pBattle->getTexMgr().getAsset("clssheet"), x + 448, y + 38 + i * 100, 32, 32, 0, v0, 1, v1);

            sprintf(buf, "%03u", (ushort)ProtoMoveList::getMove(moveset.getMove(i)).getPower());
            renderer.renderTexQuad(m_pBattle->getTexMgr().getAsset("pwr"), x + 580, y + 40 + i * 100, 32, 32);
            renderer.renderString(fnt, 20, x + 640, y + 44 + i * 100, 0x000000FF, string(buf));

            ushort acc = (ushort)ProtoMoveList::getMove(moveset.getMove(i)).getAccuracy();
            sprintf(buf, (acc == 0 ? "---" : "%03u%%"), acc);
            renderer.renderTexQuad(m_pBattle->getTexMgr().getAsset("acc"), x + 760, y + 40 + i * 100, 32, 32);
            renderer.renderString(fnt, 20, x + 820, y + 44 + i * 100, 0x000000FF, string(buf));
        }
    }
}

void ProtoGScWildBattleChange::onExit(void){
    //Do Nothing
}

//Dtor
ProtoGScWildBattleChange::~ProtoGScWildBattleChange(void){
    onExit();
}
