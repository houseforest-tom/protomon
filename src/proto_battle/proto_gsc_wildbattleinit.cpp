#include "../../include/proto_battle/proto_gsc_wildbattleinit.h"

ProtoGScWildBattleInit::ProtoGScWildBattleInit(ProtoGameScene *prev, ProtoBattle *parent) : ProtoGameScene(prev), m_pBattle(parent){
    onEnter(prev);
}

void ProtoGScWildBattleInit::onEnter(ProtoGameScene *prev){

    //'prev' should be nullptr as this is the Initialization Scene
    if(prev != nullptr) delete prev;

    NTextBuffer<128> buf;
    sprintf(buf, "item_%u", 24);
    m_pPokeballSpr = &m_pBattle->getTexMgr().getAsset(buf);
}

void ProtoGScWildBattleInit::update(float dt){

    if(!hasFinished()){

        m_accumTime += dt;

        //When in idle Scene, wait for User Input to procede
        if(m_accumTime > ENEMY_APPEAR_TIME + BALL_THROW_TIME + PLAYER_GROW_TIME){
            m_waiting = true;

            if(m_pBattle->getKeyboard().wasKeyPressed(sf::Keyboard::Space)){
                finish();
            }
        }
    }else{
        m_pBattle->setBattleScene(new ProtoGScWildBattleMain(this, m_pBattle));
    }
}

void ProtoGScWildBattleInit::draw(NRenderer &renderer){

    //Get Reference to Player Monster Sprite (Back)
    const NTexture &playerMonSpr = m_pBattle->getTexMgr().getAsset(m_pBattle->getPlayerMon().getSpriteAssetName(false));

    //Get Reference to Enemy Monster Sprite  (Front)
    const NTexture &enemyMonSpr  = m_pBattle->getTexMgr().getAsset(m_pBattle->getEnemyMon().getSpriteAssetName(true)),
                    enemyMonSpr2 = m_pBattle->getTexMgr().getAsset(m_pBattle->getEnemyMon().getSpriteAssetName(true).replace(0, 1, "f2"));

    //Relative Time
    float t;

    float w = renderer.getWindowWidth();
    float h = renderer.getWindowHeight() - TEXTBOX_H;
    ubyte bb = m_pBattle->getScenery();

    //------

    //Always Render Battle Backdrop
    renderer.renderSubtexQuad(m_pBattle->getTexMgr().getAsset("battlebg"), 0, 0, w, h, .001f + (1.0f / 3) * (bb % 3), .001f + (1.0f / 4) * (bb / 3), -.001f + (1.0f / 3) * (bb % 3 + 1), -.001f + (1.0f / 4) * (bb / 3 + 1));

    //Animate Enemy Appearance
    if((t = m_accumTime) < ENEMY_APPEAR_TIME){

        //Render Enemy Monster Front Sprite
        renderer.renderTexQuad(enemyMonSpr, w - (320 + enemyMonSpr.getWidth() * 1.5) + 500 * (ENEMY_APPEAR_TIME - m_accumTime), 390 - enemyMonSpr.getHeight() * 3, enemyMonSpr.getWidth() * 3, enemyMonSpr.getHeight() * 3);
    }

    //Animate Pokeball Throw
    else if((t = m_accumTime - ENEMY_APPEAR_TIME) < BALL_THROW_TIME){

        //Render Enemy Monster Front Sprite Animation
        renderer.renderTexQuad(
                               (m_accumTime - ENEMY_APPEAR_TIME < BALL_THROW_TIME / 2 || m_accumTime - ENEMY_APPEAR_TIME > BALL_THROW_TIME / 3 * 2 ? enemyMonSpr2 : enemyMonSpr),
                               w - (320 + enemyMonSpr.getWidth() * 1.5),
                               390 - enemyMonSpr.getHeight() * 3,
                               enemyMonSpr.getWidth() * 3,
                               enemyMonSpr.getHeight() * 3);

        //Render thrown Pokeball 24.94-48.118
        renderer.renderTexQuad(  *m_pPokeballSpr,
                                  -48 + 250 * t,
                                  h - 500 + SQR(15 * t),
                                  48, 48,
                                  2.f * m_accumTime * 360.f);
    }

    //Player Sprite Growing Scene
    else if((t = m_accumTime - ENEMY_APPEAR_TIME - BALL_THROW_TIME) < PLAYER_GROW_TIME){

        //Render Enemy Monster Front Sprite
        renderer.renderTexQuad(enemyMonSpr, w - (320 + enemyMonSpr.getWidth() * 1.5), 390 - enemyMonSpr.getHeight() * 3, enemyMonSpr.getWidth() * 3, enemyMonSpr.getHeight() * 3);

        //Render Player Monster Back Sprite
        renderer.renderTexQuad(playerMonSpr, 300 - playerMonSpr.getWidth() * 1.5 * (t / PLAYER_GROW_TIME),
                                             h - playerMonSpr.getHeight() * 3 * (t / PLAYER_GROW_TIME),
                                             playerMonSpr.getWidth() * 3 * (t / PLAYER_GROW_TIME),
                                             playerMonSpr.getHeight() * 3 * (t / PLAYER_GROW_TIME)
                               );
    }

    //Idle Scene
    else{
        //Render Enemy Monster Front Sprite
        renderer.renderTexQuad(enemyMonSpr, w - (320 + enemyMonSpr.getWidth() * 1.5), 390 - enemyMonSpr.getHeight() * 3, enemyMonSpr.getWidth() * 3, enemyMonSpr.getHeight() * 3);

        //Render Player Monster Back Sprite
        renderer.renderTexQuad(playerMonSpr, 300 - playerMonSpr.getWidth() * 1.5, h - playerMonSpr.getHeight() * 3, playerMonSpr.getWidth() * 3, playerMonSpr.getHeight() * 3);
    }

    //Render Textbox
    renderTextbox(renderer);
}

void ProtoGScWildBattleInit::onExit(void){
    //Do Nothing
}

//Dtor
ProtoGScWildBattleInit::~ProtoGScWildBattleInit(void){
    onExit();
}

void ProtoGScWildBattleInit::renderTextbox(NRenderer &renderer){

    float baseY = renderer.getWindowHeight() - TEXTBOX_H,
          w     = renderer.getWindowWidth();

    NTextBuffer<128> buf;
    if(m_accumTime < ENEMY_APPEAR_TIME){
        sprintf(buf, "All of a sudden, a wild %s is attacking you!", m_pBattle->getEnemyMon().getNickname().c_str());
    } else{
        sprintf(buf, "Go for it, %s!", m_pBattle->getPlayerMon().getNickname().c_str());
    }

    //Render black Border
    glColor3f(0, 0, 0);
    renderer.renderQuad(0, baseY, w, TEXTBOX_H);

    //Render white Text Field
    glColor3f(.95f, .95f, .95f);
    protoRenderTextbox(renderer, m_pBattle->getTexMgr(), 5, baseY + 5, w - 10, TEXTBOX_H - 10);
    renderer.renderString(m_pBattle->getFontMgr().getAsset("default"), TEXTBOX_TS, 46, baseY + 20, renderer.packRGB(0, 0, 0), string(buf));
}
