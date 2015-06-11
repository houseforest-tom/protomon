#pragma once

#include "../proto_system/proto_game_scene.h"
#include "../proto_battle/proto_battle.h"

class ProtoGScWildBattleItem : public ProtoGameScene{

private:
    //Accumulated Scene Duration
    float m_accumTime = 0;

    //Pointer to Parent Battle
    ProtoBattle *m_pBattle = nullptr;

    //Waiting for Input?
    bool m_waiting = true;

    //Current Menu Selection
    static const ubyte  BAG_BASIC   = 0,
                        BAG_BALLS   = 1;

    ubyte m_bagSelection  = BAG_BASIC;
    ubyte m_itemSelection = 0;

    //Item Strings
    const string m_bagNames[4] = { "BASIC", "BALLS", "BERRIES", "STUFF" };

    //Previous Scene Adress
    ProtoGameScene *prev = nullptr;

public:
    ProtoGScWildBattleItem(ProtoGameScene *prev, ProtoBattle *parent);

    void onEnter(ProtoGameScene *prev);

    void update(float dt);

    void draw(NRenderer &renderer);

    void onExit(void);

    //Dtor
    ~ProtoGScWildBattleItem(void);
};
