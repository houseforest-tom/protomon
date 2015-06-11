#include "../../include/proto_system/proto_enums.h"

float protoGetTypeEff(ProtoType src, ProtoType dst){

    static const float NUL = 0.0f, HLF = 0.5f, ONE = 1.0f, DBL = 2.0f;

    //Skip undefined Case
    if(src == ProtoTypes::NONE || src == ProtoTypes::NONE)          return ONE;

    //Normal Attacks
    if(src == ProtoTypes::NORMAL && dst == ProtoTypes::ROCK)        return HLF;
    if(src == ProtoTypes::NORMAL && dst == ProtoTypes::STEEL)       return HLF;
    if(src == ProtoTypes::NORMAL && dst == ProtoTypes::GHOST)       return NUL;

    //Fire Attacks
    if(src == ProtoTypes::FIRE && dst == ProtoTypes::GRASS)         return DBL;
    if(src == ProtoTypes::FIRE && dst == ProtoTypes::ICE)           return DBL;
    if(src == ProtoTypes::FIRE && dst == ProtoTypes::STEEL)         return DBL;
    if(src == ProtoTypes::FIRE && dst == ProtoTypes::BUG)           return DBL;
    if(src == ProtoTypes::FIRE && dst == ProtoTypes::FIRE)          return HLF;
    if(src == ProtoTypes::FIRE && dst == ProtoTypes::WATER)         return HLF;
    if(src == ProtoTypes::FIRE && dst == ProtoTypes::ROCK)          return HLF;
    if(src == ProtoTypes::FIRE && dst == ProtoTypes::DRAGON)        return HLF;

    //Water Attacks
    if(src == ProtoTypes::WATER && dst == ProtoTypes::FIRE)         return DBL;
    if(src == ProtoTypes::WATER && dst == ProtoTypes::GROUND)       return DBL;
    if(src == ProtoTypes::WATER && dst == ProtoTypes::ROCK)         return DBL;
    if(src == ProtoTypes::WATER && dst == ProtoTypes::WATER)        return HLF;
    if(src == ProtoTypes::WATER && dst == ProtoTypes::GRASS)        return HLF;
    if(src == ProtoTypes::WATER && dst == ProtoTypes::DRAGON)       return HLF;

    //Electric Attacks
    if(src == ProtoTypes::ELECTRIC && dst == ProtoTypes::WATER)     return DBL;
    if(src == ProtoTypes::ELECTRIC && dst == ProtoTypes::FLYING)    return DBL;
    if(src == ProtoTypes::ELECTRIC && dst == ProtoTypes::DRAGON)    return HLF;
    if(src == ProtoTypes::ELECTRIC && dst == ProtoTypes::GRASS)     return HLF;
    if(src == ProtoTypes::ELECTRIC && dst == ProtoTypes::ELECTRIC)  return HLF;
    if(src == ProtoTypes::ELECTRIC && dst == ProtoTypes::GROUND)    return NUL;

    //Grass Attacks
    if(src == ProtoTypes::GRASS && dst == ProtoTypes::ROCK)         return DBL;
    if(src == ProtoTypes::GRASS && dst == ProtoTypes::WATER)        return DBL;
    if(src == ProtoTypes::GRASS && dst == ProtoTypes::GROUND)       return DBL;
    if(src == ProtoTypes::GRASS && dst == ProtoTypes::FIRE)         return HLF;
    if(src == ProtoTypes::GRASS && dst == ProtoTypes::GRASS)        return HLF;
    if(src == ProtoTypes::GRASS && dst == ProtoTypes::POISON)       return HLF;
    if(src == ProtoTypes::GRASS && dst == ProtoTypes::FLYING)       return HLF;
    if(src == ProtoTypes::GRASS && dst == ProtoTypes::BUG)          return HLF;
    if(src == ProtoTypes::GRASS && dst == ProtoTypes::DRAGON)       return HLF;
    if(src == ProtoTypes::GRASS && dst == ProtoTypes::STEEL)        return HLF;

    //Ice Attacks
    if(src == ProtoTypes::ICE && dst == ProtoTypes::GRASS)          return DBL;
    if(src == ProtoTypes::ICE && dst == ProtoTypes::GROUND)         return DBL;
    if(src == ProtoTypes::ICE && dst == ProtoTypes::FLYING)         return DBL;
    if(src == ProtoTypes::ICE && dst == ProtoTypes::DRAGON)         return DBL;
    if(src == ProtoTypes::ICE && dst == ProtoTypes::FIRE)           return HLF;
    if(src == ProtoTypes::ICE && dst == ProtoTypes::WATER)          return HLF;
    if(src == ProtoTypes::ICE && dst == ProtoTypes::ICE)            return HLF;
    if(src == ProtoTypes::ICE && dst == ProtoTypes::STEEL)          return HLF;

    //Fighting Attacks
    if(src == ProtoTypes::FIGHTING && dst == ProtoTypes::NORMAL)    return DBL;
    if(src == ProtoTypes::FIGHTING && dst == ProtoTypes::ICE)       return DBL;
    if(src == ProtoTypes::FIGHTING && dst == ProtoTypes::ROCK)      return DBL;
    if(src == ProtoTypes::FIGHTING && dst == ProtoTypes::DARK)      return DBL;
    if(src == ProtoTypes::FIGHTING && dst == ProtoTypes::STEEL)     return DBL;
    if(src == ProtoTypes::FIGHTING && dst == ProtoTypes::POISON)    return HLF;
    if(src == ProtoTypes::FIGHTING && dst == ProtoTypes::FLYING)    return HLF;
    if(src == ProtoTypes::FIGHTING && dst == ProtoTypes::PSYCHIC)   return HLF;
    if(src == ProtoTypes::FIGHTING && dst == ProtoTypes::BUG)       return HLF;
    if(src == ProtoTypes::FIGHTING && dst == ProtoTypes::FAIRY)     return HLF;
    if(src == ProtoTypes::FIGHTING && dst == ProtoTypes::NORMAL)    return NUL;

    //Poison Attacks
    if(src == ProtoTypes::POISON && dst == ProtoTypes::GRASS)       return DBL;
    if(src == ProtoTypes::POISON && dst == ProtoTypes::FAIRY)       return DBL;
    if(src == ProtoTypes::POISON && dst == ProtoTypes::POISON)      return HLF;
    if(src == ProtoTypes::POISON && dst == ProtoTypes::GROUND)      return HLF;
    if(src == ProtoTypes::POISON && dst == ProtoTypes::ROCK)        return HLF;
    if(src == ProtoTypes::POISON && dst == ProtoTypes::GHOST)       return HLF;
    if(src == ProtoTypes::POISON && dst == ProtoTypes::STEEL)       return NUL;

    //Ground Attacks
    if(src == ProtoTypes::GROUND && dst == ProtoTypes::FIRE)        return DBL;
    if(src == ProtoTypes::GROUND && dst == ProtoTypes::ELECTRIC)    return DBL;
    if(src == ProtoTypes::GROUND && dst == ProtoTypes::POISON)      return DBL;
    if(src == ProtoTypes::GROUND && dst == ProtoTypes::ROCK)        return DBL;
    if(src == ProtoTypes::GROUND && dst == ProtoTypes::STEEL)       return DBL;
    if(src == ProtoTypes::GROUND && dst == ProtoTypes::GRASS)       return HLF;
    if(src == ProtoTypes::GROUND && dst == ProtoTypes::BUG)         return HLF;
    if(src == ProtoTypes::GROUND && dst == ProtoTypes::FLYING)      return NUL;

    //Flying Attacks
    if(src == ProtoTypes::FLYING && dst == ProtoTypes::GRASS)       return DBL;
    if(src == ProtoTypes::FLYING && dst == ProtoTypes::FIGHTING)    return DBL;
    if(src == ProtoTypes::FLYING && dst == ProtoTypes::BUG)         return DBL;
    if(src == ProtoTypes::FLYING && dst == ProtoTypes::ELECTRIC)    return HLF;
    if(src == ProtoTypes::FLYING && dst == ProtoTypes::ROCK)        return HLF;
    if(src == ProtoTypes::FLYING && dst == ProtoTypes::STEEL)       return HLF;
    if(src == ProtoTypes::FLYING && dst == ProtoTypes::GROUND)      return NUL;

    //Psychic Attacks
    if(src == ProtoTypes::PSYCHIC && dst == ProtoTypes::FIGHTING)   return DBL;
    if(src == ProtoTypes::PSYCHIC && dst == ProtoTypes::POISON)     return DBL;
    if(src == ProtoTypes::PSYCHIC && dst == ProtoTypes::PSYCHIC)    return HLF;
    if(src == ProtoTypes::PSYCHIC && dst == ProtoTypes::STEEL)      return HLF;
    if(src == ProtoTypes::PSYCHIC && dst == ProtoTypes::DARK)       return NUL;

    //Bug Attacks
    if(src == ProtoTypes::BUG && dst == ProtoTypes::GRASS)          return DBL;
    if(src == ProtoTypes::BUG && dst == ProtoTypes::PSYCHIC)        return DBL;
    if(src == ProtoTypes::BUG && dst == ProtoTypes::DARK)           return DBL;
    if(src == ProtoTypes::BUG && dst == ProtoTypes::FIRE)           return HLF;
    if(src == ProtoTypes::BUG && dst == ProtoTypes::FIGHTING)       return HLF;
    if(src == ProtoTypes::BUG && dst == ProtoTypes::POISON)         return HLF;
    if(src == ProtoTypes::BUG && dst == ProtoTypes::FLYING)         return HLF;
    if(src == ProtoTypes::BUG && dst == ProtoTypes::GHOST)          return HLF;
    if(src == ProtoTypes::BUG && dst == ProtoTypes::STEEL)          return HLF;
    if(src == ProtoTypes::BUG && dst == ProtoTypes::FAIRY)          return HLF;

    //Rock Attacks
    if(src == ProtoTypes::ROCK && dst == ProtoTypes::FIRE)          return DBL;
    if(src == ProtoTypes::ROCK && dst == ProtoTypes::ICE)           return DBL;
    if(src == ProtoTypes::ROCK && dst == ProtoTypes::FLYING)        return DBL;
    if(src == ProtoTypes::ROCK && dst == ProtoTypes::BUG)           return DBL;
    if(src == ProtoTypes::ROCK && dst == ProtoTypes::FIGHTING)      return HLF;
    if(src == ProtoTypes::ROCK && dst == ProtoTypes::GROUND)        return HLF;
    if(src == ProtoTypes::ROCK && dst == ProtoTypes::STEEL)         return HLF;

    //Ghost Attacks
    if(src == ProtoTypes::GHOST && dst == ProtoTypes::PSYCHIC)      return DBL;
    if(src == ProtoTypes::GHOST && dst == ProtoTypes::GHOST)        return DBL;
    if(src == ProtoTypes::GHOST && dst == ProtoTypes::DARK)         return HLF;
    if(src == ProtoTypes::GHOST && dst == ProtoTypes::NORMAL)       return NUL;

    //Dragon Attacks
    if(src == ProtoTypes::DRAGON && dst == ProtoTypes::DRAGON)      return DBL;
    if(src == ProtoTypes::DRAGON && dst == ProtoTypes::STEEL)       return HLF;
    if(src == ProtoTypes::DRAGON && dst == ProtoTypes::FAIRY)       return NUL;

    //Dark Attacks
    if(src == ProtoTypes::DARK && dst == ProtoTypes::PSYCHIC)       return DBL;
    if(src == ProtoTypes::DARK && dst == ProtoTypes::GHOST)         return DBL;
    if(src == ProtoTypes::DARK && dst == ProtoTypes::FIGHTING)      return HLF;
    if(src == ProtoTypes::DARK && dst == ProtoTypes::DARK)          return HLF;
    if(src == ProtoTypes::DARK && dst == ProtoTypes::FAIRY)         return HLF;

    //Steel Attacks
    if(src == ProtoTypes::STEEL && dst == ProtoTypes::ICE)          return DBL;
    if(src == ProtoTypes::STEEL && dst == ProtoTypes::ROCK)         return DBL;
    if(src == ProtoTypes::STEEL && dst == ProtoTypes::FAIRY)        return DBL;
    if(src == ProtoTypes::STEEL && dst == ProtoTypes::FIRE)         return HLF;
    if(src == ProtoTypes::STEEL && dst == ProtoTypes::WATER)        return HLF;
    if(src == ProtoTypes::STEEL && dst == ProtoTypes::ELECTRIC)     return HLF;
    if(src == ProtoTypes::STEEL && dst == ProtoTypes::STEEL)        return HLF;

    //Fairy Attacks
    if(src == ProtoTypes::FAIRY && dst == ProtoTypes::FIGHTING)     return DBL;
    if(src == ProtoTypes::FAIRY && dst == ProtoTypes::DRAGON)       return DBL;
    if(src == ProtoTypes::FAIRY && dst == ProtoTypes::DARK)         return DBL;
    if(src == ProtoTypes::FAIRY && dst == ProtoTypes::FIRE)         return HLF;
    if(src == ProtoTypes::FAIRY && dst == ProtoTypes::POISON)       return HLF;
    if(src == ProtoTypes::FAIRY && dst == ProtoTypes::STEEL)        return HLF;

    return ONE;
}
