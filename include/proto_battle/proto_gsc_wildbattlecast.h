#pragma once
#include <math.h>
#include "proto_gsc_wildbattlemain.h"
#include "proto_gsc_wildbattlecast.h"
#include "../proto_battle/proto_battle.h"
#include "../proto_monsters/proto_move_effects.h"

class ProtoGScWildBattleCast : public ProtoGameScene{

private:
    //Accumulated Scene Duration
    float m_accumTime = 0;

    //Move Effect applied yet?
    bool m_effectUpdateDone = false;

    //Move Animation finished yet?
    bool m_moveDrawDone = false;

    //Move Effect Animation finished yet?
    bool m_effectDrawDone = false;

    //Pointer to Parent Battle
    ProtoBattle *m_pBattle = nullptr;

    //Render Battle Textbox
    void renderTextbox(NRenderer &renderer);

    //Move Index used
    ushort m_usedMove = 0;

public:
    ProtoGScWildBattleCast(ProtoGameScene *prev, ProtoBattle *parent, ushort usedMove);

    void onEnter(ProtoGameScene *prev);

    void update(float dt);

    void draw(NRenderer &renderer);

    void onExit(void);

    //Dtor
    ~ProtoGScWildBattleCast(void);
};

