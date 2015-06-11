#include "../../include/proto_monsters/proto_move_list.h"
#include "../../include/proto_monsters/proto_monster.h"

void ProtoMoveList::init(void){

    bool flags[ProtoMoveFlags::COUNT] = { 0 };

    m_moves.push_back(new ProtoMove(
                                    0,
                                    "DESPERATION",
                                    10,
                                    0,
                                    100,
                                    ProtoTypes::NORMAL,
                                    0,
                                    ProtoMoveClasses::PHYSICAL,
                                    0,
                                    100,
                                    flags,
                                    "Used as last Way out when no PP of any other Move are left."
                                    ));
}

void ProtoMoveList::addMove(ProtoMove *move){

    m_moves.push_back(move);
}

void ProtoMoveList::loadFromFile(const string &file){

    const ubyte cnt = 11;
    ifstream fstr(file);
    string values[cnt];
    uint x = 0;

    while( x < cnt && getline(fstr, values[x++]) ){

        if( x == cnt ){

            bool flags[ProtoMoveFlags::COUNT] = { 0 };
            uint z = 0;
            for(uint i=0; i<values[9].length(); ++i){
                if(values[9][i] == ','){
                    flags[z++] = atoi( values[9].substr(i-1, 1).c_str() );
                }
            }

            addMove(new ProtoMove(
                                  atoi(values[0].c_str()),
                                  values[1],
                                  atoi(values[2].c_str()),
                                  atoi(values[3].c_str()),
                                  atoi(values[4].c_str()),
                                  atoi(values[5].c_str()),
                                  atoi(values[6].c_str()),
                                  atoi(values[7].c_str()),
                                  atoi(values[8].c_str()),
                                  100, //Cheat Effect Chance FOR NOW!
                                  flags,
                                  values[10]
                                  )
                    );
            x = 0;

            getline(fstr, values[0]);
        }
    }

    fstr.close();
}

const ProtoMove &ProtoMoveList::getMove(ushort id){

    return *m_moves[id];
}

ushort ProtoMoveList::getMoveCount(void){

    return m_moves.size()-1; //Ignore Desperation
}

void ProtoMoveList::unload(void){

    for(auto iter = m_moves.begin(); iter != m_moves.end(); ++iter){
        delete *iter;
        *iter = nullptr;
    }

    m_moves.clear();
}

vector<ProtoMove*> ProtoMoveList::m_moves;
