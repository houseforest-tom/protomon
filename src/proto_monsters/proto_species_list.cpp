#include "../../include/proto_monsters/proto_species_list.h"
#include "../../include/proto_monsters/proto_monster.h"

void ProtoSpeciesList::init(void){

    ubyte base[ProtoPrimStats::COUNT] = { }, yield[ProtoPrimStats::COUNT] = { };
    m_species.push_back(
                        new ProtoSpecies(0, "MISSIGNO", ProtoTypes::NORMAL, 0, 0, 0, 0, 0, base, yield)
                        );
}

void ProtoSpeciesList::addSpecies(ProtoSpecies *species){
    m_species.push_back(species);
}

void ProtoSpeciesList::loadFromFile(const string &file){

    ifstream fstr(file);
    string valueBuf;
    string values[8 + 2 * ProtoPrimStats::COUNT];
    vector<ProtoMoveLearnInfo> moves;
    vector<ProtoEvoInfo> evos;
    vector<ushort> tms;
    vector<ubyte> abilities;

    uint x=0;
    while( getline(fstr, valueBuf) ){

        //Read an empty Line -> construct Species from Values read in earlier
        if(valueBuf == ""){

            ubyte ubYield[ProtoPrimStats::COUNT], ubBase[ProtoPrimStats::COUNT];

            for(uint i=0; i<sizeof(ubBase); ++i){

                ubBase[i]  = static_cast<ubyte>(atoi(values[8 + i].c_str()));
                ubYield[i] = static_cast<ubyte>(atoi(values[8 + ProtoPrimStats::COUNT + i].c_str()));
            }

            ProtoSpecies *s = new ProtoSpecies(
                                (ushort)atoi(values[0].c_str()),
                                 values[1],
                                (ProtoType)atoi(values[2].c_str()),
                                (ProtoType)atoi(values[3].c_str()),
                                (ProtoExpModel)atoi(values[4].c_str()),
                                (ProtoGenderSplit)atoi(values[5].c_str()),
                                (ProtoCatchDiff)atoi(values[6].c_str()),
                                (ushort)atoi(values[7].c_str()),
                                 ubBase,
                                 ubYield
                               );


            //Add possible Abilities
            for(auto iter = abilities.begin(); iter != abilities.end(); ++iter)
                s->addAbility(*iter);

            //Add learnable Moves
            for(auto iter = moves.begin(); iter != moves.end(); ++iter){
                s->addMoveToLearn(*iter);
            }

            //Add learnable TMs
            for(auto iter = tms.begin(); iter != tms.end(); ++iter)
                s->addLearnableTM(*iter);

            //Add Evolutions
            for(auto iter = evos.begin(); iter != evos.end(); ++iter)
                s->addEvolution(*iter);

            addSpecies(s);

            moves.clear(); tms.clear(); evos.clear(); abilities.clear();
            x = 0;

        //Line is not empty
        } else {

            //There are still constant length fields left to read
            if(x < 8 + 2 * ProtoPrimStats::COUNT){
                //Read a Value
                values[x++].assign(valueBuf);
            }

            //Read dynamic length fields
            else{
                //Read Abilities to possibly have
                uint num = atoi(valueBuf.c_str());
                if(num){ for(uint i=0; i<num; ++i){
                    getline(fstr, valueBuf);
                    abilities.push_back( atoi(valueBuf.c_str()) );
                } }

                //Read Moves to learn
                //Number of Moves to learn is already in Buffer
                getline(fstr, valueBuf);
                num = atoi(valueBuf.c_str());
                ushort id, lvl;
                if(num) { for(uint i=0; i<num; ++i){
                    getline(fstr, valueBuf);
                    id = atoi(valueBuf.c_str());    //Move ID
                    getline(fstr, valueBuf);
                    lvl = atoi(valueBuf.c_str());   //Required Level
                    moves.push_back( { id, lvl } );
                } }

                //Read learnable TM Indices
                getline(fstr, valueBuf);    //Retrieve Number of learnable TMs
                num = atoi(valueBuf.c_str());
                if(num) { for(uint i=0; i<num; ++i){
                    getline(fstr, valueBuf);
                    tms.push_back( atoi(valueBuf.c_str()) );
                } }

                //Read Evolution Information
                getline(fstr, valueBuf);    //Retrieve Number of Evolutions
                num = atoi(valueBuf.c_str());
                ushort species, ctype, cval;

                if(num) { for(uint i=0; i<num; ++i){
                    getline(fstr, valueBuf);
                    species = atoi(valueBuf.c_str());   //Target Species ID
                    getline(fstr, valueBuf);
                    ctype = atoi(valueBuf.c_str());     //Condition Type
                    getline(fstr, valueBuf);
                    cval = atoi(valueBuf.c_str());      //Condition Value
                    evos.push_back( { species, (ProtoEvoCondition)ctype, cval } );
                } }
            }
        }
    }

    fstr.close();
}

const ProtoSpecies &ProtoSpeciesList::getSpecies(ushort id){
    return *m_species[id];
}

ushort ProtoSpeciesList::getSpeciesCount(void){
    return m_species.size()-1; //ignore Missigno Entry
}

void ProtoSpeciesList::unload(void){
    for(auto iter = m_species.begin(); iter != m_species.end(); ++iter){
        delete *iter;
        *iter = nullptr;
    }
    m_species.clear();
}

vector<ProtoSpecies*> ProtoSpeciesList::m_species;
