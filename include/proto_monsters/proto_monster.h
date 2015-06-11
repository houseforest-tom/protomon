#pragma once

#include "proto_species.h"
#include "proto_moveset.h"
#include "proto_species_list.h"
#include "proto_move_list.h"
#include <time.h>

#define IV_MAX 31
#define EV_MAX 255

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

class ProtoMonster{

private:

    ushort                  m_speciesID                                 = 0;                        //Species Index
    ProtoGender             m_gender                                    = ProtoGenders::MALE;       //Gender of the Monster
    string                  m_nickname                                  = "MISSINGNO";              //Nickname given to the Monster
    ubyte                   m_level                                     = 1;                        //Level
    ushort                  m_maxStats[ProtoPrimStats::COUNT]           = { 0 };                    //Maximum Stats
    int8_t                  m_statStages[7]                             = { 0 };                    //Stat Stages of all primary and secondary Stats besides HP [-6...0...+6]
    ushort                  m_hpLost                                    = 0;                        //Amount of HP Lost
    ProtoNature             m_nature                                    = ProtoNatures::SERIOUS;    //The Monster's Nature
    uint                    m_wrappedExp                                = 0;                        //Accumulated Experience since last Level Up
    ubyte                   m_individualValues[ProtoPrimStats::COUNT]   = { 0 };                    //Individiual Values [0...31]
    ubyte                   m_effortValues[ProtoPrimStats::COUNT]       = { 0 };                    //Effort Values [0...255]
    ushort                  m_heldItem                                  = 0;                        //Item held by the Monster, 0 if none
    ProtoMoveset            m_knownMoves;                                                           //Known Moveset
    ProtoStatus             m_mainStatus                                = ProtoStatuses::OK;        //Primary Status
    ProtoBtlStatus          m_secStatus                                 = ProtoBtlStatuses::OK;     //Volatile Battle Status (will be reset to OK after each Battle)
    bool                    m_shiny                                     = false;                    //Flag determining whether the Monster is shiny

    // ! - Possibly add Identifier of Ball caught with here - ! //

    //(Re-)calculate the current & Maximum Stats, e.g. upon Modification of IV / EV or Level
    void calcStats(void);

public:
    //Default Ctor creates an unidentified Proto Monster
    ProtoMonster(void){ }

    //Ctor creates a Monster of the given Species at the Level specfied (1 by Default)
    ProtoMonster(ushort species, ushort level = 1);

    //Getters
    inline ushort           getSpecies(void) const{ return m_speciesID; }
    inline ProtoGender      getGender(void) const{ return m_gender; }
    inline const string    &getNickname(void) const{ return m_nickname; }
    inline ubyte            getLevel(void) const{ return m_level; }
    inline ubyte            getIV(ProtoPrimStat stat){ return m_individualValues[stat]; }
    inline ubyte            getEV(ProtoPrimStat stat){ return m_effortValues[stat]; }
    inline ushort           getMaxStat(ProtoPrimStat stat){ return m_maxStats[stat]; }
           ushort           getCurrentStat(ProtoPrimStat mainStatID);
           ushort           getCurrentSecStat(ProtoSecStat secStatID);
    inline int8_t           getStatStage(ubyte stat){ return m_statStages[stat]; }
    inline bool             isShiny(void) const{ return m_shiny; }
    inline ProtoMoveset    &getMoveset(void){ return m_knownMoves; }

    //Setters
    inline void setNickname(const string &nick){ m_nickname.assign(nick); }
    inline void setGender(ProtoGender gender){ m_gender = gender; }
    inline void setLevel(ubyte level){ m_level = level; calcStats(); }
    inline void setIV(ProtoPrimStat stat, ubyte iv){ m_individualValues[stat] = iv % (IV_MAX + 1); calcStats(); }
    inline void setEV(ProtoPrimStat stat, ubyte ev){ m_effortValues[stat] = ev % (EV_MAX + 1); calcStats(); }
    inline void setShiny(bool shiny){ m_shiny = shiny; }

    //Generate a String based on Species and Shinyness that specifies the Name of the Sprite Resource
    string getSpriteAssetName(bool isFrontSpr);
};

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
