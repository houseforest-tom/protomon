#include "../../include/proto_battle/proto_gsc_wildbattleenemy.h"

ProtoGScWildBattleEnemy::ProtoGScWildBattleEnemy(ProtoGameScene *prev, ProtoBattle *parent) : ProtoGameScene(prev), m_pBattle(parent){

    //Player just chose his Move, but Enemy goes first -> get Move ID the Player used
    if(m_pBattle->isFirstTurn())
        m_usedPlayerMove = ((ProtoGScWildBattleFight*)prev)->getUsedMoveID();

    onEnter(prev);

    //Randomly select Move to cast
    while( !m_pBattle->getEnemyMon().getMoveset().isMoveInSlot( (m_usedMove = rand() % PROTO_MOVESET_SIZE) ) );
    m_usedMove = m_pBattle->getEnemyMon().getMoveset().getMove(m_usedMove); //<- Transform Moveset Array Index to actual Move Index
}

void ProtoGScWildBattleEnemy::onEnter(ProtoGameScene *prev){

    //'prev' should be the Move Selection Scene in this Case!
    delete prev;
}

void ProtoGScWildBattleEnemy::update(float dt){

    if(!hasFinished() || !m_moveDrawDone || !m_effectDrawDone || !m_effectUpdateDone){

        //Wait for Move Animation to finish
        if( m_moveDrawDone ){

            //Animation Scene done -> apply Move Effect
            if( !m_effectUpdateDone ){

                m_effectUpdateDone = protoUpdateMoveEffect(m_usedMove, *m_pBattle, 1);

            }else{ //Done

                finish();
            }
        }
    }

    else{
        //Player still has to do his Turn
        if(m_pBattle->isFirstTurn()){
            m_pBattle->setFirstTurn(false);
            m_pBattle->setBattleScene(new ProtoGScWildBattleCast(this, m_pBattle, m_usedPlayerMove));
        }

        //Player already did his Turn -> end Round
        else m_pBattle->setBattleScene(new ProtoGScWildBattleMain(this, m_pBattle));
    }

    m_accumTime += dt;
}

void ProtoGScWildBattleEnemy::draw(NRenderer &renderer){

    float baseY = renderer.getWindowHeight() - TEXTBOX_H,
          w     = renderer.getWindowWidth(),
          h     = renderer.getWindowHeight() - TEXTBOX_H;

    NTextBuffer<128> buf;
    const NFont &fnt = m_pBattle->getFontMgr().getAsset("default");

    //Get Reference to Player Monster Sprite (Back)
    const NTexture &playerMonSpr = m_pBattle->getTexMgr().getAsset(m_pBattle->getPlayerMon().getSpriteAssetName(false));

    //Get Reference to Enemy Monster Sprite  (Front)
    const NTexture &enemyMonSpr  = m_pBattle->getTexMgr().getAsset(m_pBattle->getEnemyMon().getSpriteAssetName(true));

    ubyte bb = m_pBattle->getScenery();

    //------

    //Always Render Battle Backdrop
    renderer.renderSubtexQuad(m_pBattle->getTexMgr().getAsset("battlebg"), 0, 0, w, h, .001f + (1.0f / 3) * (bb % 3), .001f + (1.0f / 4) * (bb / 3), -.001f + (1.0f / 3) * (bb % 3 + 1), -.001f + (1.0f / 4) * (bb / 3 + 1));

    //Render Enemy Monster Front Sprite
    renderer.renderTexQuad(enemyMonSpr, w - (320 + enemyMonSpr.getWidth() * 1.5), 390 - enemyMonSpr.getHeight() * 3, enemyMonSpr.getWidth() * 3, enemyMonSpr.getHeight() * 3);

    //Render Player Monster Back Sprite
    renderer.renderTexQuad(playerMonSpr, 300 - playerMonSpr.getWidth() * 1.5, h - playerMonSpr.getHeight() * 3, playerMonSpr.getWidth() * 3, playerMonSpr.getHeight() * 3);

    //Show & update the Move Animation
    if(!hasFinished() || !m_effectDrawDone || !m_effectUpdateDone){

        //First do the Animation of the Move itself
        if(m_accumTime < 1){

            //Somewhat fake Move Animation here by doing fancy Fade-Effects with a white Overlay
            glColor4f(1, 1, 1, 1 - m_accumTime);

            NTextBuffer<128> alias;
            sprintf(alias, "move_particle_%u", (ushort)ProtoMoveList::getMove(m_usedMove).getType());

            uint particles = rand() % 24;
            for(uint i=0; i<particles; ++i)
                renderer.renderTexQuad(m_pBattle->getTexMgr().getAsset(alias), 256 + rand() % 256, h - rand() % 256, 64, 64);

            /* TO BE REPLACED W/ MOVE ANIMATION */
        }

        //After Move Animation is done and Move Effect was updated -> draw Effect Animation
        else{
            m_moveDrawDone = true;

            if(m_effectUpdateDone && !m_effectDrawDone){

                //Show the Move's Effect Animation
                m_effectDrawDone = protoDrawMoveEffect(m_usedMove, *m_pBattle, 1);
            }
        }
    }

    //------

    //Render Textbox
    renderTextbox(renderer);
}

void ProtoGScWildBattleEnemy::onExit(void){
    //Do Nothing
}

//Dtor
ProtoGScWildBattleEnemy::~ProtoGScWildBattleEnemy(void){
    onExit();
}

void ProtoGScWildBattleEnemy::renderTextbox(NRenderer &renderer){

    NTextBuffer<128> buf;

    float baseY = renderer.getWindowHeight() - TEXTBOX_H,
          w     = renderer.getWindowWidth();

    //Render black Border
    glColor3f(0, 0, 0);
    renderer.renderQuad(0, baseY, w, TEXTBOX_H);

    sprintf(buf, "%s uses %s!", m_pBattle->getEnemyMon().getNickname().c_str(), ProtoMoveList::getMove(m_usedMove).getName().c_str());

    //Render white Text Field
    glColor3f(.95f, .95f, .95f);
    renderer.renderQuad(5, baseY + 5, w - 10, TEXTBOX_H - 10);
    renderer.renderString(m_pBattle->getFontMgr().getAsset("default"), TEXTBOX_TS, 20, baseY + 20, renderer.packRGB(0, 0, 0), string(buf));
}
