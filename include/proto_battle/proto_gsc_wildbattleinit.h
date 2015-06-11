#pragma once

#include "../proto_system/proto_game_scene.h"
#include "../proto_monsters/proto_monster.h"
#include "proto_gsc_wildbattlemain.h"

class ProtoGScWildBattleInit : public ProtoGameScene{

private:
    //Timing Constants
    const float         ENEMY_APPEAR_TIME        = 2,
                        BALL_THROW_TIME          = 1.7,
                        PLAYER_GROW_TIME         = 0.5;

    //Accumulated Scene Duration
    float m_accumTime = 0;

    //Pointer to Parent Battle
    ProtoBattle *m_pBattle = nullptr;

    //Render Battle Textboc
    void renderTextbox(NRenderer &renderer);

    //Still waiting for Input?
    bool m_waiting = false;

    const NTexture *m_pPokeballSpr = nullptr;

public:
    ProtoGScWildBattleInit(ProtoGameScene *prev, ProtoBattle *parent);

    void onEnter(ProtoGameScene *prev);

    void update(float dt);

    void draw(NRenderer &renderer);

    void onExit(void);

    //Dtor
    ~ProtoGScWildBattleInit(void);
};
