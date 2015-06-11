#include "../../include/proto_monsters/proto_species.h"
#include <fstream>

ProtoSpecies::ProtoSpecies(
                 ushort id,
                 const string &name,
                 ProtoType t1,
                 ProtoType t2,
                 ProtoExpModel xpmdl,
                 ProtoGenderSplit gsplit,
                 ProtoCatchDiff cdiff,
                 ushort xpyield,
                 ubyte base[ProtoPrimStats::COUNT],
                 ubyte evyield[ProtoPrimStats::COUNT] )

    //Initializer List
    : m_id(id), m_name(name), m_type1(t1), m_type2(t2),
      m_expModel(xpmdl), m_genderSplit(gsplit),
      m_catchDiff(cdiff), m_expYield(xpyield){

    //Copy Array Entries
    for(uint i=0; i<ProtoPrimStats::COUNT; ++i){
        m_baseStats[i]  = base[i];
        m_evYield[i]    = evyield[i];
    }
}

void ProtoSpecies::addMoveToLearn(const ProtoMoveLearnInfo &learn){

    m_movesToLearn.push_back(learn);
}

void ProtoSpecies::addLearnableTM(ushort TM){

    m_learnableTMs.push_back(TM);
}

void ProtoSpecies::addEvolution(const ProtoEvoInfo &evolution){

    m_evolutions.push_back(evolution);
}

void ProtoSpecies::addAbility(ubyte ability){

    m_abilities.push_back(ability);
}

string ProtoSpecies::genString(void) const{

    string BLANK = "-------------------------------";

    NTextBuffer<4> fmtID;
    sprintf(fmtID, "%03u", m_id);

    NTextBuffer<16> buf;
    string evoString;
    for(uint i=0; i<m_evolutions.size(); ++i){
        evoString.append("\tTo Species ").append(itoa(m_evolutions[i].targetSpeciesID, buf, 10)).append("\n");
        evoString.append("\t\tCondition: ").append(itoa(m_evolutions[i].condition, buf, 10)).append("\n");
        evoString.append("\t\tValue:     ").append(itoa(m_evolutions[i].conditionValue, buf, 10));
    }

    stringstream ss;
    ss  << BLANK << "\n"
        << "ProtoSpecies Entity" << "\n"
        << BLANK << "\n"
        << "ID:\t\t" << fmtID << "\n"
        << "Name:\t\t" << m_name << "\n"
        << "Type:\t\t" << protoTypeToStr(m_type1) << " | " << protoTypeToStr(m_type2) << "\n"
        << "EXP-Model:\t" << protoExpModelToStr(m_expModel) << "\n"
        << "Gender-Split:\t" << protoGenderSplitToStr(m_genderSplit) << "\n"
        << "Catch-Diffic.:\t" << protoCatchDiffToStr(m_catchDiff) << "\n"
        << "EXP-Yield:\t" << m_expYield << "\n"
        << BLANK << "\n"
        << "Base-Stats:" << "\n"
        << "\t\tHP:\t" << (ushort)m_baseStats[ProtoPrimStats::HP] << "\n"
        << "\t\tATK:\t" << (ushort)m_baseStats[ProtoPrimStats::ATK] << "\n"
        << "\t\tDEF:\t" << (ushort)m_baseStats[ProtoPrimStats::DEF] << "\n"
        << "\t\tSPATK:\t" << (ushort)m_baseStats[ProtoPrimStats::SPATK] << "\n"
        << "\t\tSPDEF:\t" << (ushort)m_baseStats[ProtoPrimStats::SPDEF] << "\n"
        << "\t\tINIT:\t" << (ushort)m_baseStats[ProtoPrimStats::INIT] << "\n"
        << BLANK << "\n"
        << "EV-Yields:" << "\n"
        << "\t\tHP:\t" << (ushort)m_evYield[ProtoPrimStats::HP] << "\n"
        << "\t\tATK:\t" << (ushort)m_evYield[ProtoPrimStats::ATK] << "\n"
        << "\t\tDEF:\t" << (ushort)m_evYield[ProtoPrimStats::DEF] << "\n"
        << "\t\tSPATK:\t" << (ushort)m_evYield[ProtoPrimStats::SPATK] << "\n"
        << "\t\tSPDEF:\t" << (ushort)m_evYield[ProtoPrimStats::SPDEF] << "\n"
        << "\t\tINIT:\t" << (ushort)m_evYield[ProtoPrimStats::INIT] << "\n"
        << BLANK << "\n"
        << "Move-Info:" << "\n"
        << "\t\tLearns " << m_movesToLearn.size() << " Moves" << "\n"
        << "\t\tCan learn " << m_learnableTMs.size() << " TMs" << "\n"
        << BLANK << "\n" << "\n"
        << "Evolutions:" << "\n"
        << evoString << "\n" << BLANK << "\n\n";

    return ss.str();
}

void ProtoSpecies::writeToFile(const string &file) const{

    ofstream fstr(file, ios::app);
    fstr << m_id << endl;
    fstr << m_name << endl;
    fstr << (ushort)m_type1 << endl;
    fstr << (ushort)m_type2 << endl;
    fstr << (ushort)m_expModel << endl;
    fstr << (ushort)m_genderSplit << endl;
    fstr << (ushort)m_catchDiff << endl;
    fstr << m_expYield << endl;

    for(uint i=0; i<ProtoPrimStats::COUNT; ++i){
        fstr << (ushort)m_baseStats[i] << endl;
    }

    for(uint i=0; i<ProtoPrimStats::COUNT; ++i){
        fstr << (ushort)m_evYield[i] << endl;
    }

    fstr << m_abilities.size() << endl;
    for(uint i=0; i<m_abilities.size(); ++i){
        fstr << (ushort)m_abilities[i] << endl;
    }

    fstr << m_movesToLearn.size() << endl;
    for(uint i=0; i<m_movesToLearn.size(); ++i){
        fstr << m_movesToLearn[i].moveToLearn << endl;
        fstr << (ushort)m_movesToLearn[i].requiredLevel << endl;
    }

    fstr << m_learnableTMs.size() << endl;
    for(uint i=0; i<m_learnableTMs.size(); ++i){
        fstr << m_learnableTMs[i] << endl;
    }

    fstr << m_evolutions.size() << endl;
    for(uint i=0; i<m_evolutions.size(); ++i){
        fstr << m_evolutions[i].targetSpeciesID << endl;
        fstr << (ushort)m_evolutions[i].condition << endl;
        fstr << m_evolutions[i].conditionValue << endl;
    }

    fstr << endl;

    fstr.close();
}
