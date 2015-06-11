#pragma once
#include "../proto_system/proto_game_scene.h"
#include "../proto_battle/proto_battle.h"

class ProtoGScWildBattleChange : public ProtoGameScene{

private:
    //Accumulated Scene Duration
    float m_accumTime = 0;

    //Pointer to Parent Battle
    ProtoBattle *m_pBattle = nullptr;

    //Waiting for Input?
    bool m_waiting = true;

    //Current Menu Selection
    ubyte m_selection = 0;

    //Previous Scene Adress
    ProtoGameScene *prev = nullptr;

public:
    ProtoGScWildBattleChange(ProtoGameScene *prev, ProtoBattle *parent);

    void onEnter(ProtoGameScene *prev);

    void update(float dt);

    void draw(NRenderer &renderer);

    void onExit(void);

    //Dtor
    ~ProtoGScWildBattleChange(void);
};
