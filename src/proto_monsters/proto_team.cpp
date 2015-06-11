#include "../../include/proto_monsters/proto_team.h"

ProtoTeam::ProtoTeam(void){

    for(uint i=0; i<PROTO_TEAM_SIZE; ++i){
        m_members[i] = nullptr;
    }
}

void ProtoTeam::addMember(ProtoMonster *mon){

    uint i;
    for(i=0; i<PROTO_TEAM_SIZE; ++i){
        if(m_members[i] == nullptr){
            //Empty Slot found
            break;
        }
    }

    //Member can get added to the Team
    if(i < PROTO_TEAM_SIZE){
        m_members[i] = mon;
        return;
    }

    //Error - Team already fully occupied
    else{
        cout << "Error: Team already contains " << PROTO_TEAM_SIZE << " Members!" << endl;
    }
}

void ProtoTeam::setMember(ubyte slot, ProtoMonster *mon){

    if(slot < PROTO_TEAM_SIZE){
        //Slot already populated -> overwrite
        if(slot < getSize()){
            delete m_members[slot];
            m_members[slot] = mon;
        }
        //Empty Slot demanded -> write to first empty Slot in Team
        else{
            m_members[getSize()] = mon;
        }
    }
}

ProtoMonster *ProtoTeam::getMember(ubyte slot){

    return m_members[slot];
}

bool ProtoTeam::hasMemberInSlot(ubyte slot){

    return (m_members[slot] != nullptr);
}

ubyte ProtoTeam::getSize(void){

    for(uint i=0; i<PROTO_TEAM_SIZE; ++i){
        if(m_members[i] == nullptr)
            return i;
    }

    return PROTO_TEAM_SIZE;
}

//Free Mem
ProtoTeam::~ProtoTeam(void){

    for(uint i=0; i<PROTO_TEAM_SIZE; ++i){
        if(m_members[i] == nullptr)
            delete m_members[i];
    }
}
