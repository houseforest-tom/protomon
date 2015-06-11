#pragma once
#include <math.h>
#include "proto_gsc_wildbattlemain.h"
#include "proto_gsc_wildbattlecast.h"
#include "../proto_battle/proto_battle.h"
#include "../proto_monsters/proto_move_effects.h"

class ProtoGScWildBattleEnemy : public ProtoGameScene{

private:
    const float ANIM_DURATION = 1.0f;

    //Accumulated Scene Duration
    float m_accumTime = 0;

    //Move Effect applied yet?
    bool m_effectUpdateDone = false;

    //Move Animation finished yet?
    bool m_moveDrawDone = false;

    //Move Effect Animation finsihed yet?
    bool m_effectDrawDone = false;

    //Pointer to Parent Battle
    ProtoBattle *m_pBattle = nullptr;

    //Render Battle Textbox
    void renderTextbox(NRenderer &renderer);

    //Move Index used
    ushort m_usedMove = 0;

    //Move Index used by Player if Player went first
    ushort m_usedPlayerMove = 0;

public:
    ProtoGScWildBattleEnemy(ProtoGameScene *prev, ProtoBattle *parent);

    void onEnter(ProtoGameScene *prev);

    void update(float dt);

    void draw(NRenderer &renderer);

    void onExit(void);

    //Dtor
    ~ProtoGScWildBattleEnemy(void);
};

