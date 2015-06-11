#include "../../include/proto_battle/proto_gsc_wildbattlemain.h"

ProtoGScWildBattleMain::ProtoGScWildBattleMain(ProtoGameScene *prev, ProtoBattle *parent) : ProtoGameScene(prev), m_pBattle(parent){
    onEnter(prev);
}

void ProtoGScWildBattleMain::onEnter(ProtoGameScene *prev){

    //'prev' should be the Initialization Scene
    if(prev != nullptr) delete prev;

    //Reset to first Part of Turn
    m_pBattle->setFirstTurn(true);
}

void ProtoGScWildBattleMain::update(float dt){

    if(!hasFinished()){

        m_accumTime += dt;

        if(m_pBattle->getKeyboard().wasKeyPressed(sf::Keyboard::Escape)){
            m_selection = SELECTION_RUN;
        }

        if(m_pBattle->getKeyboard().wasKeyPressed(sf::Keyboard::Space)){

            switch(m_selection){
                case SELECTION_FIGHT:  m_pBattle->setBattleScene(new ProtoGScWildBattleFight(this, m_pBattle)); break;
                case SELECTION_ITEM:   m_pBattle->setBattleScene(new ProtoGScWildBattleItem(this, m_pBattle)); break;
                case SELECTION_CHANGE: m_pBattle->setBattleScene(new ProtoGScWildBattleChange(this, m_pBattle)); break;
                case SELECTION_RUN:    m_pBattle->end();
                default: break; //<- You fucked up!
            }
        }

        //Manage Menu Item Selection
        if(m_pBattle->getKeyboard().wasKeyPressed(sf::Keyboard::S)){
            if(m_selection == 0) m_selection = 2;
            if(m_selection == 1) m_selection = 3;
        }

        // ---
        if(m_pBattle->getKeyboard().wasKeyPressed(sf::Keyboard::W)){
            if(m_selection == 2) m_selection = 0;
            if(m_selection == 3) m_selection = 1;
        }

        // ---
        if(m_pBattle->getKeyboard().wasKeyPressed(sf::Keyboard::D)){
            if(m_selection == 2) m_selection = 3;
            if(m_selection == 0) m_selection = 1;
        }

        // ---
        if(m_pBattle->getKeyboard().wasKeyPressed(sf::Keyboard::A)){
            if(m_selection == 1) m_selection = 0;
            if(m_selection == 3) m_selection = 2;
        }
    }else{
        m_pBattle->end();
    }
}

void ProtoGScWildBattleMain::draw(NRenderer &renderer){

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

void ProtoGScWildBattleMain::onExit(void){
    //Do Nothing
}

//Dtor
ProtoGScWildBattleMain::~ProtoGScWildBattleMain(void){
    onExit();
}

void ProtoGScWildBattleMain::renderTextbox(NRenderer &renderer){

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

        glColor3f(0, 0, 0);
        renderer.renderQuad(xCoord, yCoord, w / 4 - 6, TEXTBOX_H / 2 - 14);
        glColor3f(.95f, .95f, .95f);
        protoRenderTextbox(renderer, m_pBattle->getTexMgr(), xCoord + 2, yCoord + 2, w / 4 - 10, TEXTBOX_H / 2 - 18);
        renderer.renderString(m_pBattle->getFontMgr().getAsset("default"), TEXTBOX_TS, xCoord + 46 + (i == m_selection ? ABS(sinf(m_accumTime * 10)) * 16 : 0), yCoord + 4, (i == m_selection ? 0x888888FF : 0x000000FF), m_menuItemStrings[i]);
    }
}
