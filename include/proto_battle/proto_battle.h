#pragma once

#include <NObjectManager.h>
#include <NTextureManager.h>
#include <NFontManager.h>
#include <NKeyboard.h>
#include <NMouse.h>

#include "../proto_system/proto_game_scene.h"
#include "../proto_monsters/proto_team.h"
#include "../proto_monsters/proto_move_list.h"
#include "../proto_monsters/proto_species_list.h"
#include "../proto_system/proto_bag.h"
#include "../proto_monsters/proto_ability_list.h"
#include "../proto_system/proto_game_scene.h"

// ---Constants---

//Number of Battle Sceneries (Background Images in 'res/img/battlebg.png')
#define SCENERY_COUNT    11

//Dedicated Height of Text Box
#define TEXTBOX_H       100

//Text Size to use in Text Boxes
#define TEXTBOX_TS       20

// ---------------

class ProtoBattle : public NDrawable{

private:
    //Various self-explanatory Reference
    ProtoGameScene   *m_pBattleScene  = nullptr;
    ProtoTeam        *m_pPlayerTeam   = nullptr;
    ProtoTeam        *m_pEnemyTeam    = nullptr;
    ProtoBag         *m_pItemBag      = nullptr;
    NTextureManager  *m_pTextureMgr   = nullptr;
    NFontManager     *m_pFontMgr      = nullptr;
    NObjectManager   *m_pObjectMgr    = nullptr;
    NKeyboard        *m_pKeyboard     = nullptr;
    NMouse           *m_pMouse        = nullptr;

    //Battle Background (Scenery)
    ubyte m_scenery = 0;

    //Team Slots of currently fighting Pokemon
    //First Pokemon (slot 0) always starts off
    ubyte m_playerSlot = 0;
    ubyte m_enemySlot  = 0;

    //Flag determining whether currently the first part of a Battle Round is taking Place
    //or the Round is about to end after the current Action
    bool m_isFirstTurn = false;

    //Has the Battle ended?
    bool m_hasEnded = false;

public:
    //Construct new Battle
    ProtoBattle(NObjectManager &objmgr,
                NTextureManager &texmgr,
                NFontManager &fontmgr,
                NKeyboard &kb,
                NMouse &mouse,
                ProtoTeam &playerTeam,
                ProtoTeam &enemyTeam,
                ProtoBag &itemBag,
                ubyte scenery);

    //Update Battle Scene
    void update(float dt);

    //Render Battle Scene
    void draw(NRenderer &renderer);

    //End the Battle
    void end(void);

    //Unsubscribe from Object Manager and free Memory allocated for Scenes
    virtual ~ProtoBattle(void);

    //Calculate who is to attack first
    bool playerGoesFirst(void);

    //Calculate whether a Move is about to hit or miss
    bool moveWillHit(bool playerCasts, ushort moveID);

    //Getters
    inline ProtoTeam                &getPlayerTeam(void)        { return *m_pPlayerTeam; }
    inline ProtoTeam                &getEnemyTeam(void)         { return *m_pEnemyTeam; }
    inline ProtoMonster             &getPlayerMon(void)         { return *(m_pPlayerTeam->getMember(m_playerSlot)); }
    inline ProtoMonster             &getEnemyMon(void)          { return *(m_pEnemyTeam->getMember(m_enemySlot)); }
    inline ProtoBag                 &getItemBag(void)           { return *m_pItemBag; }
    inline NTextureManager          &getTexMgr(void)            { return *m_pTextureMgr; }
    inline NFontManager             &getFontMgr(void)     const { return *m_pFontMgr; }
    inline NObjectManager           &getObjMgr(void)            { return *m_pObjectMgr; }
    inline NKeyboard                &getKeyboard(void)    const { return *m_pKeyboard; }
    inline NMouse                   &getMouse(void)       const { return *m_pMouse; }
    inline ubyte                     getScenery(void)     const { return  m_scenery; }
    inline ubyte                     getPlayerSlot(void)  const { return  m_playerSlot; }
    inline ubyte                     getEnemySlot(void)   const { return  m_enemySlot; }
    inline bool                      isFirstTurn(void)    const { return  m_isFirstTurn; }
    inline bool                      hasEnded(void)       const { return  m_hasEnded; }

    //Setters
    inline void setPlayerSlot(ubyte slot)                { m_playerSlot = slot; }
    inline void setEnemySlot(ubyte slot)                 { m_enemySlot = slot; }
    inline void setScenery(ubyte scenery)                { m_scenery = scenery; }
    inline void setFirstTurn(bool first)                 { m_isFirstTurn = first; }
    inline void setBattleScene(ProtoGameScene *scene)    { m_pBattleScene = scene; }
    inline void setBattleSceneAndDelete(ProtoGameScene *scene, ProtoGameScene *oldScene) { delete oldScene; m_pBattleScene = scene; }
};
