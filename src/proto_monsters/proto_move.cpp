#include "../../include/proto_monsters/proto_move.h"

ProtoMove::ProtoMove(
                     ushort id,
                     const string &name,
                     ubyte power,
                     ubyte pp,
                     ubyte acc,
                     ProtoType type,
                     int8_t prio,
                     ProtoMoveClass cls,
                     ushort effect,
                     ubyte effectChance,
                     bool flags[ProtoMoveFlags::COUNT],
                     const string &desc)

            //Initializer List
            :m_id(id), m_name(name), m_power(power), m_pp(pp),
             m_accuracy(acc), m_type(type), m_priority(prio),
             m_class(cls), m_effect(effect), m_effectChance(effectChance){

    m_desc.assign(desc);

    for(uint i=0; i<ProtoMoveFlags::COUNT; ++i){
        m_flags[i] = flags[i];

    }
}

string ProtoMove::genString(void) const{

    stringstream ss;

    ss  << "<ProtoMove> ID: "   <<  m_id
        << ", Name: "           <<  m_name
        << ", Power: "          << (ushort)m_power
        << ", PP: "             << (ushort)m_pp
        << ", Acc: "            << (ushort)m_accuracy
        << ", Type: "           <<  protoTypeToStr(m_type)
        << ", Prio: "           << (short)m_priority
        << ", Class: "          <<  protoMoveClassToStr(m_class)
        << ", Effect: "         <<  m_effect
        << ", Description: "    <<  m_desc;

    return ss.str();
}
