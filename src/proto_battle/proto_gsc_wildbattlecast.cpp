#include "../../include/proto_battle/proto_gsc_wildbattlecast.h"
#include "../../include/proto_battle/proto_gsc_wildbattleenemy.h"

ProtoGScWildBattleCast::ProtoGScWildBattleCast(ProtoGameScene *prev, ProtoBattle *parent, ushort usedMove) : ProtoGameScene(prev), m_pBattle(parent){

    onEnter(prev);
    m_usedMove = usedMove;
}

void ProtoGScWildBattleCast::onEnter(ProtoGameScene *prev){

    //'prev' should be the Move Selection Scene in this Case!
    delete prev;
}

void ProtoGScWildBattleCast::update(float dt){

    if(!hasFinished() || !m_moveDrawDone || !m_effectDrawDone || !m_effectUpdateDone){

        //Wait for Move Animation to finish
        if( m_moveDrawDone ){

            //Animation Scene done -> apply Move Effect
            if( !m_effectUpdateDone ){

                m_effectUpdateDone = protoUpdateMoveEffect(m_usedMove, *m_pBattle, 0);

            }else{ //Done

                finish();
            }
        }
    }

    else{
        //Enemy still has to do his Turn
        if( m_pBattle->isFirstTurn() )
            m_pBattle->setBattleScene(new ProtoGScWildBattleEnemy(this, m_pBattle));

        //Enemy went first, end Round after Player's Move
        else{
            m_pBattle->setFirstTurn(false);
            m_pBattle->setBattleScene(new ProtoGScWildBattleMain(this, m_pBattle));
        }
    }

    m_accumTime += dt;
}

void ProtoGScWildBattleCast::draw(NRenderer &renderer){

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

            //Somewhat fake Move Animation here by doing fancy Effects
            glColor4f(1, 1, 1, 1 - m_accumTime);

            NTextBuffer<128> alias;
            sprintf(alias, "move_particle_%u", (ushort)ProtoMoveList::getMove(m_usedMove).getType());

            uint particles = rand() % 24;
            for(uint i=0; i<particles; ++i)
                renderer.renderTexQuad(m_pBattle->getTexMgr().getAsset(alias), w - 512 + rand() % 256, rand() % 256, 64, 64);

            /* TO BE REPLACED W/ MOVE ANIMATION */
        }

        //After Move Animation is done and Move Effect was updated -> draw Effect Animation
        else{
            m_moveDrawDone = true;

            if(m_effectUpdateDone && !m_effectDrawDone){

                //Show the Move's Effect Animation
                m_effectDrawDone = protoDrawMoveEffect(m_usedMove, *m_pBattle, 0);
            }
        }
    }

    //------

    //Render Textbox
    renderTextbox(renderer);
}

void ProtoGScWildBattleCast::onExit(void){
    //Do Nothing
}

//Dtor
ProtoGScWildBattleCast::~ProtoGScWildBattleCast(void){
    onExit();
}

void ProtoGScWildBattleCast::renderTextbox(NRenderer &renderer){

    NTextBuffer<128> buf;

    float baseY = renderer.getWindowHeight() - TEXTBOX_H,
          w     = renderer.getWindowWidth();


    //Render black Border
    glColor4f(0, 0, 0, 1);
    renderer.renderQuad(0, baseY, w, TEXTBOX_H);

    sprintf(buf, "%s uses %s!", m_pBattle->getPlayerMon().getNickname().c_str(), ProtoMoveList::getMove(m_usedMove).getName().c_str());

    //Render white Text Field
    glColor3f(.95f, .95f, .95f);
    renderer.renderQuad(5, baseY + 5, w - 10, TEXTBOX_H - 10);
    renderer.renderString(m_pBattle->getFontMgr().getAsset("default"), TEXTBOX_TS, 20, baseY + 20, renderer.packRGB(0, 0, 0), string(buf));
}
