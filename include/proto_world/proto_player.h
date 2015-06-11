#pragma once

#include <NKeyboard.h>
#include "../proto_system/proto_bag.h"
#include "../proto_monsters/proto_team.h"
#include "proto_npc.h"

class ProtoPlayer : public ProtoNPC
{
private:
    const NKeyboard *m_pKeyboard = nullptr;
    const NRenderer *m_pRenderer = nullptr;

    bool m_frozen;

    ushort m_currentMapWidth     = 0;
    ushort m_currentMapHeight    = 0;

    ProtoBag  m_bag;
    ProtoTeam m_team;

public:
    ProtoPlayer(NTextureManager &texmgr, const NKeyboard &keyboard);

    void update(float dt);

    void draw(NRenderer &renderer);

    inline void setMapSize(ushort w, ushort h)
    {
        m_currentMapWidth = w;
        m_currentMapHeight = h;
    }

    inline bool isFrozen(void) const { return m_frozen; }
    inline void freeze(void) { m_frozen = true; }
    inline void unfreeze(void) { m_frozen = false; }

    inline ProtoBag  &getBag(void)  { return m_bag; }
    inline ProtoTeam &getTeam(void) { return m_team; }
};
