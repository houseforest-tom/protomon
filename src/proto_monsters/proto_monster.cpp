#include "../../include/proto_monsters/proto_monster.h"

ProtoMonster::ProtoMonster(ushort species, ushort level){

    //Assign passed Parameters
    m_speciesID = species;
    m_level     = level;

    //Assign Species Name
    m_nickname.assign(ProtoSpeciesList::getSpecies(species).getName());

    //Determine Gender
    m_gender = ProtoGenders::MALE;
    switch(ProtoSpeciesList::getSpecies(species).getGenderSplit()){

        case ProtoGenderSplits::ALWAYS_F:   m_gender = ProtoGenders::FEMALE;   break;
        case ProtoGenderSplits::ALWAYS_N:   m_gender = ProtoGenders::NEUTRAL;  break;
        case ProtoGenderSplits::RATE_1M_3F: m_gender = (((rand() % 1000) < 250) ? ProtoGenders::MALE      : ProtoGenders::FEMALE);    break;
        case ProtoGenderSplits::RATE_3M_1F: m_gender = (((rand() % 1000) < 250) ? ProtoGenders::FEMALE    : ProtoGenders::MALE);      break;
        case ProtoGenderSplits::RATE_7M_1F: m_gender = (((rand() % 1000) < 125) ? ProtoGenders::FEMALE    : ProtoGenders::MALE);      break;
        case ProtoGenderSplits::EVEN:       m_gender = (((rand() % 1000) < 500) ? ProtoGenders::FEMALE    : ProtoGenders::MALE);      break;
    }

    //Generate random IVs
    for(uint i=0; i<ProtoPrimStats::COUNT; ++i){
        m_individualValues[i] = rand() % 32;
    }

    //Calculate Stats
    calcStats();

    //Learn Moves
    auto moveInfo = ProtoSpeciesList::getSpecies(species).getMoveLearnInfo();
    ubyte slot = 0;
    for(uint i=0; i<moveInfo.size(); ++i){
        if(m_level >= moveInfo[i].requiredLevel){
            //Already knows 4 Moves
            if(!m_knownMoves.addMove(moveInfo[i].moveToLearn)){
                m_knownMoves.setMove(slot % PROTO_MOVESET_SIZE, moveInfo[i].moveToLearn);
                slot++;
            }
        }
    }
}

string ProtoMonster::getSpriteAssetName(bool isFrontSpr){

    NTextBuffer<128> buf;
    sprintf(buf, "%s_%s%u", (isFrontSpr ? "f" : "b"), (m_shiny ? "s_" : ""), m_speciesID);
    return string(buf);
}

ushort ProtoMonster::getCurrentStat(ProtoPrimStat mainStatID){

    ushort alteredStat = m_maxStats[mainStatID];
    int8_t stage = m_statStages[mainStatID - 1];

    if(stage == 0) return alteredStat;
    if(stage <  0) return alteredStat * (2.0f / (-stage + 2));
    if(stage >  0) return alteredStat * ((stage + 2) / 2.0f);

    return 0;
}

ushort ProtoMonster::getCurrentSecStat(ProtoSecStat secStatID){

    ubyte alteredStat = 100; //Default Value for ACC & EVA
    int8_t stage = m_statStages[secStatID + (ProtoPrimStats::COUNT - 1)];

    if(stage == 0) return alteredStat;
    if(stage <  0) return alteredStat * (3.0f / (-stage + 3));
    if(stage >  0) return alteredStat * ((stage + 3) / 3.0f);

    return 0;
}

void ProtoMonster::calcStats(void){

    //Calculate Maximum Stats
    m_maxStats[0] = (m_individualValues[0] + 2.f * ProtoSpeciesList::getSpecies(m_speciesID).getBaseStat(0) + m_effortValues[0] / 4.f + 100) * m_level / 100.f + 10.f;
    for(uint i=1; i<ProtoPrimStats::COUNT; ++i){
        m_maxStats[i] = (m_individualValues[i] + 2.f * ProtoSpeciesList::getSpecies(m_speciesID).getBaseStat(i) + m_effortValues[i] / 4.f) * m_level / 100.f + 5.f;
    }
}
