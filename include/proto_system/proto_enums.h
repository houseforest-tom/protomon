#pragma once

#define PROTO_SCREEN_W 1280 //Screen Width  [px]
#define PROTO_SCREEN_H  720 //Screen Height [px]

#define PROTO_TILE_SIZE              32 //DST
#define PROTO_TILESHEET_TILE_SIZE    16 //SRC
#define PROTO_TILE_LAYERS             4 //Count of usable Tile Layers
#define PROTO_VISIBLE_TILES_H        (PROTO_SCREEN_W / PROTO_TILE_SIZE + 2) //Maximum visible Tiles on the horizontal Axis
#define PROTO_VISIBLE_TILES_V        (PROTO_SCREEN_H / PROTO_TILE_SIZE + 2) //Maximum visible Tiles on the vertical Axis

//Convenience Keyboard Macros (to be moved over to Engine)
#define PROTOKEYPR(KEYBOARD, KEY) (KEYBOARD).wasKeyPressed(sf::Keyboard::KEY)
#define PROTOKEYDN(KEYBOARD, KEY) (KEYBOARD).isKeyDown(sf::Keyboard::KEY)

#include <NBase.h>
#include <sstream>
#include <NRenderer.h>
#include <NTextureManager.h>

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

//Enumeration of Creature Types
using ProtoType = ubyte;
typedef struct{
static const ProtoType

    NONE        = 0x00,
    NORMAL      = 0x01,
    FIRE        = 0x02,
    WATER       = 0x03,
    GRASS       = 0x04,
    FLYING      = 0x05,
    ELECTRIC    = 0x06,
    FIGHTING    = 0x07,
    GROUND      = 0x08,
    ROCK        = 0x09,
    BUG         = 0x0A,
    ICE         = 0x0B,
    PSYCHIC     = 0x0C,
    POISON      = 0x0D,
    DARK        = 0x0E,
    GHOST       = 0x0F,
    STEEL       = 0x10,
    DRAGON      = 0x11,
    FAIRY       = 0x12,

    COUNT       = 0x13;
} ProtoTypes;

inline string protoTypeToStr(ProtoType type){
    stringstream ss;
    switch(type){
        case ProtoTypes::NONE:      return "NONE";
        case ProtoTypes::NORMAL:    return "NORMAL";
        case ProtoTypes::FIRE:      return "FIRE";
        case ProtoTypes::WATER:     return "WATER";
        case ProtoTypes::GRASS:     return "GRASS";
        case ProtoTypes::FLYING:    return "FLYING";
        case ProtoTypes::ELECTRIC:  return "ELECTRIC";
        case ProtoTypes::FIGHTING:  return "FIGHTING";
        case ProtoTypes::GROUND:    return "GROUND";
        case ProtoTypes::ROCK:      return "ROCK";
        case ProtoTypes::BUG:       return "BUG";
        case ProtoTypes::ICE:       return "ICE";
        case ProtoTypes::PSYCHIC:   return "PSYCHIC";
        case ProtoTypes::POISON:    return "POISON";
        case ProtoTypes::DARK:      return "DARK";
        case ProtoTypes::GHOST:     return "GHOST";
        case ProtoTypes::STEEL:     return "STEEL";
        case ProtoTypes::DRAGON:    return "DRAGON";
        case ProtoTypes::FAIRY:     return "FAIRY";

        case ProtoTypes::COUNT:
            ss << static_cast<ushort>(ProtoTypes::COUNT);
        return ss.str();

        default: return "";
    }
}

//Calculate Type Effectiveness
float protoGetTypeEff(ProtoType src, ProtoType dst);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

//Enumeration of Experience Models
using ProtoExpModel = ubyte;
typedef struct{
static const ProtoExpModel

    SLOWEST = 0,
    SLOWER  = 1,
    SLOW    = 2,
    AVERAGE = 3,
    FAST    = 4,
    FASTER  = 5,
    FASTEST = 6,

    COUNT   = 7;
}ProtoExpModels;

inline string protoExpModelToStr(ProtoExpModel xpmdl){
    stringstream ss;
    switch(xpmdl){
        case ProtoExpModels::SLOWEST:   return "SLOWEST";
        case ProtoExpModels::SLOWER:    return "SLOWER";
        case ProtoExpModels::SLOW:      return "SLOW";
        case ProtoExpModels::AVERAGE:   return "AVERAGE";
        case ProtoExpModels::FAST:      return "FAST";
        case ProtoExpModels::FASTER:    return "FASTER";
        case ProtoExpModels::FASTEST:   return "FASTEST";

        case ProtoExpModels::COUNT:
            ss << static_cast<ushort>(xpmdl);
        return ss.str();

        default: return "";
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

//Enumeration of Proto Creature Genders
using ProtoGender = ubyte;
typedef struct{
static const ProtoGender

    MALE    = 0,
    FEMALE  = 1,
    NEUTRAL = 2,

    COUNT   = 3;
} ProtoGenders;

inline string protoGenderToStr(ProtoGender gender){
    stringstream ss;
    switch(gender){
        case ProtoGenders::MALE:    return "MALE";
        case ProtoGenders::FEMALE:  return "FEMALE";
        case ProtoGenders::NEUTRAL: return "NEUTRAL";
        case ProtoGenders::COUNT:
            ss << static_cast<ushort>(gender);
        return ss.str();
        default: return "";
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

//Enumeration of Gender Distribution Possibilities
using ProtoGenderSplit = ubyte;
typedef struct{
static const ProtoGenderSplit

    EVEN        = 0,          //Evenly distributed (50% Male, 50% Female)
    ALWAYS_M    = 1,          //100% Male
    ALWAYS_F    = 2,          //100% Female
    ALWAYS_N    = 3,          //100% Neutral
    RATE_7M_1F  = 4,          //7 times as many Males as Females
    RATE_3M_1F  = 5,          //3 times as many Males as Females
    RATE_1M_3F  = 6,          //3 times as many Females as Males

    COUNT       = 7;
} ProtoGenderSplits;

inline string protoGenderSplitToStr(ProtoGenderSplit gsplit){
    stringstream ss;
    switch(gsplit){
        case ProtoGenderSplits::EVEN:           return "EVEN";
        case ProtoGenderSplits::ALWAYS_M:       return "ALWAYS_M";
        case ProtoGenderSplits::ALWAYS_F:       return "ALWAYS_F";
        case ProtoGenderSplits::ALWAYS_N:       return "ALWAYS_N";
        case ProtoGenderSplits::RATE_7M_1F:     return "RATE_7M_1F";
        case ProtoGenderSplits::RATE_3M_1F:     return "RATE_3M_1F";
        case ProtoGenderSplits::RATE_1M_3F:     return "RATE_1M_3F";

        case ProtoGenderSplits::COUNT:
            ss << static_cast<ushort>(gsplit);
        return ss.str();

        default: return "";
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

//Enumeration of Catching Difficulties
using ProtoCatchDiff = ubyte;
typedef struct{
static const ProtoCatchDiff

    IMPOSSIBLE  = 0,    //Uncatchable for whatever Reason
    TRIVIAL     = 1,    //Super easy to catch
    EASY        = 2,    //Rather easy to catch
    AVERAGE     = 3,    //Normally difficult to catch
    DIFFICULT   = 4,    //Rather difficult to catch
    CHALLENGING = 5,    //Super difficult to catch
    LEGENDARY   = 6,    //Specific Catch Rate used for legendary Encounters

    COUNT       = 7;
} ProtoCatchDiffs;

inline string protoCatchDiffToStr(ProtoCatchDiff cdiff){
    stringstream ss;
    switch(cdiff){
        case ProtoCatchDiffs::IMPOSSIBLE:    return "IMPOSSIBLE";
        case ProtoCatchDiffs::TRIVIAL:       return "TRIVIAL";
        case ProtoCatchDiffs::EASY:          return "EASY";
        case ProtoCatchDiffs::AVERAGE:       return "AVERAGE";
        case ProtoCatchDiffs::DIFFICULT:     return "DIFFICULT";
        case ProtoCatchDiffs::CHALLENGING:   return "CHALLENGING";
        case ProtoCatchDiffs::LEGENDARY:     return "LEGENDARY";

        case ProtoCatchDiffs::COUNT:
            ss << static_cast<ushort>(cdiff);
        return ss.str();

        default: return "";
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

//Enumeration of Proto Creature Primary Stats
using ProtoPrimStat = ubyte;
typedef struct{
static const ProtoPrimStat

    HP      = 0,
    ATK     = 1,
    DEF     = 2,
    SPATK   = 3,
    SPDEF   = 4,
    INIT    = 5,
    COUNT   = 6;
} ProtoPrimStats;

inline string protoPrimStatToStr(ProtoPrimStat stat){

    NTextBuffer<16> buf;
    switch(stat){
        case ProtoPrimStats::HP:    return "HP";
        case ProtoPrimStats::ATK:   return "ATK";
        case ProtoPrimStats::DEF:   return "DEF";
        case ProtoPrimStats::SPATK: return "SPATK";
        case ProtoPrimStats::SPDEF: return "SPDEF";
        case ProtoPrimStats::INIT:  return "INIT";

        case ProtoPrimStats::COUNT: return itoa(ProtoPrimStats::COUNT, buf, 10);
        default: return "";
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

//Enumeration of Proto Creature Secondary Stats
using ProtoSecStat = ubyte;
typedef struct{
static const ProtoSecStat

    ACC     = 0,    //Accuracy
    EVA     = 1,    //Evasiveness
    COUNT   = 2;
} ProtoSecStats;

inline string protoSecStatToStr(ProtoSecStat stat){

    NTextBuffer<16> buf;
    switch(stat){
        case ProtoSecStats::ACC:  return "ACC";
        case ProtoSecStats::EVA:  return "EVA";

        case ProtoSecStats::COUNT: return itoa(ProtoSecStats::COUNT, buf, 10);
        default: return "";
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

//Enumeration of possible Evolution Conditions
using ProtoEvoCondition = ubyte;
typedef struct{
static const ProtoEvoCondition

    LEVEL       = 0,
    HOLDITEM    = 1,
    USEITEM     = 2,
    COUNT       = 3;
} ProtoEvoConditions;

inline string protoEvoConditionToStr(ProtoEvoCondition econd){

    NTextBuffer<16> buf;
    switch(econd){
        case ProtoEvoConditions::LEVEL:      return "LEVEL";
        case ProtoEvoConditions::HOLDITEM:   return "HOLDITEM";
        case ProtoEvoConditions::USEITEM:    return "USEITEM";

        case ProtoEvoConditions::COUNT: return itoa(ProtoEvoConditions::COUNT, buf, 10);
        default: return "";
    }
}

 /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

//Enumeration of Protomon Natures
using ProtoNature = ubyte;
typedef struct{
static const ProtoNature

    //No Change to Stats
    SERIOUS = 0x00,
    QUIRKY  = 0x01,
    HARDY   = 0x02,
    DOCILE  = 0x03,
    BASHFUL = 0x04,

    //Lowered ATK
    BOLD    = 0x05,     //DEF+
    MODEST  = 0x06,     //SPATK+
    CALM    = 0x07,     //SPDEF+
    TIMID   = 0x08,     //INIT+

    //Lowered DEF
    LONELY  = 0x09,     //ATK+
    MILD    = 0x0A,     //SPATK+
    GENTLE  = 0x0B,     //SPDEF+
    HASTY   = 0x0C,     //INIT+

    //Lowered SPATK
    ADAMANT = 0x0D,     //ATK+
    IMPISH  = 0x0E,     //DEF+
    CAREFUL = 0x0F,     //SPDEF+
    JOLLY   = 0x10,     //INIT+

    //Lowered SPDEF
    NAUGHTY = 0x11,     //ATK+
    LAX     = 0x12,     //DEF+
    RASH    = 0x13,     //SPATK+
    NAIVE   = 0x14,     //INIT+

    //Lowered INIT
    BRAVE   = 0x15,     //ATK+
    RELAXED = 0x16,     //DEF+
    QUIET   = 0x17,     //SPATK+
    SASSY   = 0x18,     //SPDEF+

    COUNT   = 0x19;
} ProtoNatures;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

//Enumeration of primary Proto Monster Statuses
using ProtoStatus = ubyte;
typedef struct{
static const ProtoStatus

    OK          = 0,
    POISONED    = 1,
    PARALYZED   = 2,
    BURNED      = 3,
    ASLEEP      = 4,
    FROZEN      = 5,
    BADLYPSN    = 6,
    FAINTED     = 7,
    COUNT       = 8;
} ProtoStatuses;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

//Enumeration of volatile (infight) Proto Monster Statuses
using ProtoBtlStatus = ubyte;
typedef struct{
static const ProtoBtlStatus

    OK                  = 0x01,
    CONFUSION           = 0x02,
    CURSE               = 0x03,
    EMBARGO             = 0x04,
    ENCORE              = 0x05,
    FLINCH              = 0x06,
    HEALBLOCK           = 0x07,
    IDENTIFICATION      = 0x08,
    INFATUATION         = 0x09,
    NIGHTMARE           = 0x0A,
    PARTIALLYTRPD       = 0x0B,
    PERISHSONG          = 0x0C,
    SEEDING             = 0x0D,
    TAUNT               = 0x0E,
    TELELEVITATION      = 0x0F,
    TORMENT             = 0x10,
    TRAPPED             = 0x11,
    AQUARING            = 0x12,
    BRACING             = 0x13,
    ATTENTION           = 0x14,
    DEFENSECURL         = 0x15,
    GLOWING             = 0x16,
    ROOTING             = 0x17,
    MAGICCOAT           = 0x18,
    MAGNLEVITATION      = 0x19,
    MINIMIZE            = 0x1A,
    PROTECTION          = 0x1B,
    RECHARGING          = 0x1C,
    SEMIINVULNERABLE    = 0x1D,
    SUBSTITUTE          = 0x1E,
    TAKINGAIM           = 0x1F,
    TAKINGINSUN         = 0x20,
    WITHDRAWING         = 0x21,
    WHIRLWIND           = 0x22,

    COUNT               = 0x23;
} ProtoBtlStatuses;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

using ProtoMoveClass = ubyte;
typedef struct{
static const ProtoMoveClass

    PHYSICAL = 0,
    SPECIAL  = 1,
    STATUS   = 2,

    COUNT    = 3;

} ProtoMoveClasses;

inline string protoMoveClassToStr(ProtoMoveClass mcls){

    NTextBuffer<16> buf;
    switch(mcls){
        case ProtoMoveClasses::PHYSICAL: return "PHYSICAL";
        case ProtoMoveClasses::SPECIAL:  return "SPECIAL";
        case ProtoMoveClasses::STATUS:   return "STATUS";
        case ProtoMoveClasses::COUNT:    return itoa(ProtoMoveClasses::COUNT, buf, 10);
        default: return "";
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

using ProtoItemType = ubyte;
typedef struct{
static const ProtoItemType

    BASIC       = 0, //Potions etc.
    BALLS       = 1, //Pokéballs
    BERRIES     = 2, //Berries
    STUFF       = 3, //Important (Story-relevant,...) Items
    COUNT       = 4;
} ProtoItemTypes;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

using ProtoDirection = ubyte;
typedef struct{
static const ProtoDirection

    DOWN   = 0,
    LEFT   = 1,
    RIGHT  = 2,
    UP     = 3;
} ProtoDirections;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

//Helper Function for rendering a Textbox's Sprite
inline void protoRenderTextbox(NRenderer &renderer, const NTextureManager &texmgr, ushort x, ushort y, ushort w, ushort h){

    renderer.renderSubtexQuad(texmgr.getAsset("textbox"), x, y, 16, h, 0, 0, .1f, 1);
    renderer.renderSubtexQuad(texmgr.getAsset("textbox"), x + 16, y, w - 16, h, .1f, 0, .9f, 1);
    renderer.renderSubtexQuad(texmgr.getAsset("textbox"), x + w - 16, y, 16, h, .9f, 0, 1, 1);
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
