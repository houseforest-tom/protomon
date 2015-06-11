#pragma once

#include "proto_monster.h"

#define PROTO_TEAM_SIZE 6

class ProtoTeam{

private:
    ProtoMonster *m_members[PROTO_TEAM_SIZE];

public:
    ProtoTeam(void);
    void addMember(ProtoMonster *mon);
    void setMember(ubyte slot, ProtoMonster *mon);
    ProtoMonster *getMember(ubyte slot);
    bool hasMemberInSlot(ubyte slot);
    ubyte getSize(void);
    ~ProtoTeam(void);
};
