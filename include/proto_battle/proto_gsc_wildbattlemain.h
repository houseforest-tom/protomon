#pragma once

#include "proto_gsc_wildbattlefight.h"
#include "proto_gsc_wildbattleitem.h"
#include "proto_gsc_wildbattlechange.h"

class ProtoGScWildBattleMain : public ProtoGameScene{

private:
    //Accumulated Scene Duration
    float m_accumTime = 0;

    //Pointer to Parent Battle
    ProtoBattle *m_pBattle = nullptr;

    //Render Battle Textbox
    void renderTextbox(NRenderer &renderer);

    //Waiting for Input?
    bool m_waiting = true;

    //Current Menu Selection
    ubyte m_selection = SELECTION_FIGHT;
    static const ubyte SELECTION_FIGHT  = 0,
                       SELECTION_ITEM   = 1,
                       SELECTION_CHANGE = 2,
                       SELECTION_RUN    = 3;

    //Item Strings
    const string m_menuItemStrings[4] = { "FIGHT", "ITEM", "CHANGE", "RUN" };

public:
    ProtoGScWildBattleMain(ProtoGameScene *prev, ProtoBattle *parent);

    void onEnter(ProtoGameScene *prev);

    void update(float dt);

    void draw(NRenderer &renderer);

    void onExit(void);

    //Dtor
    ~ProtoGScWildBattleMain(void);
};
