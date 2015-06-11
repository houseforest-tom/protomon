#pragma once

#include <NBase.h>
#include "proto_move_list.h"

class ProtoMoveset{

#define PROTO_MOVESET_SIZE 4
private:
    ushort m_moves      [PROTO_MOVESET_SIZE];
    ubyte  m_maxPPs     [PROTO_MOVESET_SIZE];
    ubyte  m_currentPPs [PROTO_MOVESET_SIZE];

public:
    //Default Ctor initializes Moves to '0' (empty)
    ProtoMoveset(void);

    //Getters
    inline bool   isMoveInSlot(ubyte slot) const{ return m_moves[slot] > 0; }
    inline ushort getMove(ubyte slot) const{ return m_moves[slot]; }
           bool   setMove(ubyte slot, ushort move);
    inline ubyte  getMaxPP(ubyte slot) const{ return m_maxPPs[slot]; }
    inline ubyte  getLeftPP(ubyte slot) const{ return m_currentPPs[slot]; }
    inline void   setMaxPP(ubyte slot, ubyte pp){ m_maxPPs[slot] = pp; }
    inline void   setLeftPP(ubyte slot, ubyte pp){ m_currentPPs[slot] = pp; }

    //Add a Move to the Moveset if it isn't full
    bool addMove(ushort move);
};
