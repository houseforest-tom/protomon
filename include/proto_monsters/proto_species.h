#pragma once

#include "../proto_system/proto_enums.h"
#include <vector>
#include <NIGenString.h>
#include <sstream>

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

//Proto Species Evolution Information
typedef struct protoevoinfo_t{

    ushort              targetSpeciesID; //Monster to evolve to
    ProtoEvoCondition   condition;       //Condition Type to fulfill (LVL, ITEM..)
    ushort              conditionValue;  //Required Value for to meet the Condition
} ProtoEvoInfo;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

 //Proto Move Learn Information
 typedef struct protomvlearn_t{

    ushort moveToLearn;     //What Move to learn
    ushort requiredLevel;   //At which Level to learn the Move
 } ProtoMoveLearnInfo;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

//Represents one Species a Proto Creature can be of
class ProtoSpecies : public NIGenString{

private:
    ushort                       m_id                                  = 0;                                      //Specific Species Identifier
    string                       m_name                                = "MISSINGNO";                            //Species Name
    ProtoType                    m_type1                               = ProtoTypes::NORMAL;                     //Primary Type
    ProtoType                    m_type2                               = ProtoTypes::NONE;                       //Secondary Type (optional)
    ProtoExpModel                m_expModel                            = ProtoExpModels::AVERAGE;                //Experience Curve- / Model
    ProtoGenderSplit             m_genderSplit                         = ProtoGenderSplits::EVEN;                //Gender Distribution
    ProtoCatchDiff               m_catchDiff                           = ProtoCatchDiffs::AVERAGE;               //Catching Difficulty

    ubyte                        m_baseStats[ProtoPrimStats::COUNT]    = { 25, 25, 25, 25, 25, 25 };             //Base Stats
    ubyte                        m_evYield[ProtoPrimStats::COUNT]      = { 0, 0, 0, 0, 0, 0 };                   //Effort Value Points yielded upon killing a Creature of this Species
    ushort                       m_expYield                            = 10;                                     //Base Experience yielded upon killing a Creature of this Species

    vector<ProtoMoveLearnInfo>   m_movesToLearn;                                                                 //Moves to be learnt by Creatures of this Species
    vector<ushort>               m_learnableTMs;                                                                 //TMs learnable by Creatures of this Species
    vector<ProtoEvoInfo>         m_evolutions;                                                                   //Information about this Species' Evolutions (+ their Conditions)
    vector<ubyte>                m_abilities;                                                                    //Possible Abilities

public:
    //Create a Species with the given Properties
    ProtoSpecies(
                 ushort id,
                 const string &name,
                 ProtoType t1,
                 ProtoType t2,
                 ProtoExpModel xpmdl,
                 ProtoGenderSplit gsplit,
                 ProtoCatchDiff cdiff,
                 ushort xpyield,
                 ubyte base[ProtoPrimStats::COUNT],
                 ubyte evyield[ProtoPrimStats::COUNT] );

    //Getters
    inline ushort getID(void) const{ return m_id; }
    inline const string &getName(void) const{ return m_name; }
    inline ProtoType getType1(void) const{ return m_type1; }
    inline ProtoType getType2(void) const{ return m_type2; }
    inline ProtoExpModel getExpModel(void) const{ return m_expModel; }
    inline ProtoGenderSplit getGenderSplit(void) const{ return m_genderSplit; }
    inline ProtoCatchDiff getCatchDiff(void) const{ return m_catchDiff; }
    inline ushort getExpYield(void) const{ return m_expYield; }
    inline ubyte getBaseStat(ProtoPrimStat stat) const{ return m_baseStats[stat]; }
    inline ubyte getEvYield(ProtoPrimStat stat) const{ return m_evYield[stat]; }
    inline const vector<ProtoMoveLearnInfo> &getMoveLearnInfo(void) const{ return m_movesToLearn; }
    inline const vector<ushort> &getLearnableTMs(void) const{ return m_learnableTMs; }
    inline const vector<ProtoEvoInfo> &getEvolutionInfo(void) const{ return m_evolutions; }

    //Add a Move to the List of Moves to learn
    void addMoveToLearn(const ProtoMoveLearnInfo &learn);

    //Add a TM to the List of learnable TMs
    void addLearnableTM(ushort TM);

    //Add a new Evolution Stage
    void addEvolution(const ProtoEvoInfo &evolution);

    //Add a learnable Ability
    void addAbility(ubyte ability);

    //Generate String Information
    string genString(void) const;

    //Write to File
    void writeToFile(const string &file) const;

    ~ProtoSpecies(void){}
};

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
