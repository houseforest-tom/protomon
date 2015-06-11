#pragma once

#include "proto_move.h"

#include <vector>
#include <fstream>

class ProtoMoveList{

private:
    //Vector of Moves in successive Order by ID
    static vector<ProtoMove*> m_moves;

public:
    //Construct an ampty Move List
    static void init(void);

    //Add a new Move to the List
    static void addMove(ProtoMove *move);

    //Load Moves into List from File
    static void loadFromFile(const string &file);

    //Return a readonly Reference to a Move
    static const ProtoMove &getMove(ushort id);

    //Return the Number of Moves contained within the List
    static ushort getMoveCount(void);

    //Free Memory
    static void unload(void);
};

