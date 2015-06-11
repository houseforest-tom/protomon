#include "../../include/proto_monsters/proto_moveset.h"

ProtoMoveset::ProtoMoveset(void)
    :m_moves        {0, 0, 0, 0},
     m_maxPPs       {0, 0, 0, 0},
     m_currentPPs   {0, 0, 0, 0}{

}

bool ProtoMoveset::addMove(ushort move){

    ubyte slot = 0;

    for(; slot<PROTO_MOVESET_SIZE; slot++){
        if(m_moves[slot] == move) return false; //Already knows Move
        if(!isMoveInSlot(slot)) break;
    }

    //Can still learn a move
    if(slot < PROTO_MOVESET_SIZE){
        m_moves[slot] = move;
        m_currentPPs[slot] = m_maxPPs[slot] = ProtoMoveList::getMove(move).getPP();
        return true;
    }

    //All Moveset Slots already occupied
    return false;
}

bool ProtoMoveset::setMove(ubyte slot, ushort move){

    for(ubyte s=0; s<PROTO_MOVESET_SIZE; s++){
        if(s != slot && m_moves[s] == move) return false; //Already knows Move
    }

    m_moves[slot] = move;
    m_currentPPs[slot] = m_maxPPs[slot] = ProtoMoveList::getMove(move).getPP();
    return true;
}
