#pragma once
#include <math.h>
#include "../proto_system/proto_game_scene.h"
#include "proto_gsc_wildbattlecast.h"
#include "../proto_battle/proto_battle.h"

class ProtoGScWildBattleFight : public ProtoGameScene{

private:
    //Accumulated Scene Duration
    float m_accumTime = 0;

    //Pointer to Parent Battle
    ProtoBattle *m_pBattle = nullptr;

    //Render Battle Textbox
    void renderTextbox(NRenderer &renderer);

    //Waiting for Input?
    bool m_waiting = true;

    //Current Move Selection
    ubyte m_selection = 0;

    //Previous Scene
    ProtoGameScene *prev = nullptr;

    //Reference to Type Spritesheet
    const NTexture *m_pTypesheetSpr = nullptr;

public:
    ProtoGScWildBattleFight(ProtoGameScene *prev, ProtoBattle *parent);

    inline ushort getUsedMoveID(void) const { return m_pBattle->getPlayerMon().getMoveset().getMove(m_selection); }

    void onEnter(ProtoGameScene *prev);

    void update(float dt);

    void draw(NRenderer &renderer);

    void onExit(void);

    //Dtor
    ~ProtoGScWildBattleFight(void);
};
