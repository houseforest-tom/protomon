#include "../../include/proto_battle/proto_battle.h"
#include "../../include/proto_battle/proto_gsc_wildbattleinit.h"

ProtoBattle::ProtoBattle(
                NObjectManager &objmgr,
                NTextureManager &texmgr,
                NFontManager &fontmgr,
                NKeyboard &kb,
                NMouse &mouse,
                ProtoTeam &playerTeam,
                ProtoTeam &enemyTeam,
                ProtoBag &itemBag,
                ubyte scenery)

    //Initializer List
    :   m_pPlayerTeam(&playerTeam),
        m_pEnemyTeam(&enemyTeam),
        m_pItemBag(&itemBag),
        m_pTextureMgr(&texmgr),
        m_pFontMgr(&fontmgr),
        m_pObjectMgr(&objmgr),
        m_pKeyboard(&kb),
        m_pMouse(&mouse),
        m_playerSlot(0),
        m_enemySlot(0),
        m_scenery(scenery){

        m_pBattleScene = new ProtoGScWildBattleInit(nullptr, this);
        m_pObjectMgr->subscribe(this, "Battle");
}

bool ProtoBattle::playerGoesFirst(void){
    return false;
}

bool ProtoBattle::moveWillHit(bool playerCasts, ushort moveID){

    //Determine Caster and Target Monster
    ProtoMonster &caster = playerCasts ? getPlayerMon() : getEnemyMon(),
                 &target = playerCasts ? getEnemyMon()  : getPlayerMon();

    //Get Move Information
    const ProtoMove &move = ProtoMoveList::getMove(moveID);
    ubyte base = move.getAccuracy();

    //In Case of Accuracy 0 (which means Infinity) skip Calculation
    if(base == 0) return true;

    //Calculate current Accuracy Modifier (in %)
    ushort acc = caster.getCurrentSecStat(ProtoSecStats::ACC);

    //Calculate current Target Evasion Modifier (in %)
    ushort eva = caster.getCurrentSecStat(ProtoSecStats::EVA);

    //Calculate combined Hit Chance Percentage
    //and cap it at 1/3 of the Move's Base Accuracy
    ushort percentage = acc * eva / 100;
    percentage = min( percentage, (ushort)100 );
    percentage = max( (ubyte)percentage, (ubyte)(base / 3) );

    if(percentage >= 100) return true;          //Hits anyway
    else return ((rand() % 100) < percentage);  //Check against Percentage
}

void ProtoBattle::update(float dt){
    m_pBattleScene->update(dt);
}

void ProtoBattle::draw(NRenderer &renderer){
    m_pBattleScene->draw(renderer);
}

void ProtoBattle::end(void){

    cout << "Battle ended!" << endl;

    if(m_pObjectMgr != nullptr){
        if(m_pObjectMgr->manages(this)){
            m_pObjectMgr->unsubscribe(this);
            m_pObjectMgr = nullptr;
        }
    }

    if(m_pBattleScene != nullptr){
        delete m_pBattleScene;
        m_pBattleScene = nullptr;
    }

    m_hasEnded = true;
}

ProtoBattle::~ProtoBattle(void){
    end();
}
