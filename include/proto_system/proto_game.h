#pragma once

#include <NBase.h>
#include <NRenderer.h>
#include <NObjectManager.h>
#include <NMouse.h>
#include <NKeyboard.h>
#include <NFontManager.h>
#include <NTextureManager.h>

#include <stdlib.h>
#include <time.h>
#include <fstream>

#include "../../include/proto_world/proto_map.h"
#include "../../include/proto_system/proto_game_scene.h"
#include "../../include/proto_system/proto_enums.h"
#include "../../include/proto_monsters/proto_species.h"
#include "../../include/proto_monsters/proto_monster.h"
#include "../../include/proto_monsters/proto_move.h"
#include "../../include/proto_monsters/proto_moveset.h"
#include "../../include/proto_monsters/proto_species_list.h"
#include "../../include/proto_monsters/proto_move_list.h"
#include "../../include/proto_monsters/proto_ability_list.h"
#include "../../include/proto_system/proto_item_list.h"
#include "../../include/proto_battle/proto_battle.h"
#include "../../include/proto_system/proto_bag.h"
#include "../proto_world/proto_player.h"
#include "../../include/proto_system/proto_lua_handler.h"

enum ProtoGameState
{
    WORLD,              //Move around
    MENU,               //Menu opened
    MENU_LEXICON,       //Lexicon Menu Option selected
    MENU_TEAM,          //Team Menu Option selected
    MENU_BAG,           //Bag Menu Option selected
    MENU_SETTINGS,      //Settings Menu Option selected
    BATTLE_WILD,        //In a wild Battle
    BATTLE_TRAINER      //In a Trainer Battle
};

class ProtoGame{

private:
    ularge          m_lastFrameTime     = 0ul;
    ularge          m_currentFrameTime  = 0ul;
    float           m_frameDeltaTime    = .0f;
    ProtoGameState  m_gameState         = ProtoGameState::WORLD;

    ProtoMap       *m_pMap              = nullptr;
    ProtoPlayer    *m_pPlayer           = nullptr;
    ProtoBattle    *m_pBattle           = nullptr;

    NRenderer       m_renderer;
    NMouse          m_mouse;
    NKeyboard       m_keyboard;
    NObjectManager  m_objectMgr;
    NTextureManager m_textureMgr;
    NFontManager    m_fontMgr;

    //Load Resources
    void loadSpeciesSprites(void);
    void loadMoveAnims(void);
    void loadItemSprites(void);
    void loadObjectSprites(void);
    void initGameLogic(void);

    //Update Camera
    void determineCameraPos(void);

    //Draw Overlay Text / HUD
    void drawOverlay(void);

public:
    ProtoGame(void);
    ~ProtoGame(void);

    inline NRenderer &getRenderer(void){ return m_renderer; }
    inline const NMouse &getMouse(void) const { return m_mouse; }
    inline const NKeyboard &getKeyboard(void) const { return m_keyboard; }
    inline NObjectManager &getObjectMgr(void){ return m_objectMgr; }
    inline const NTextureManager &getTextureMgr(void) const { return m_textureMgr; }
    inline const NFontManager &getFontMgr(void) const { return m_fontMgr; }
};
