#pragma once

#include "../proto_system/proto_enums.h"
#include <NIGenString.h>
#include <fstream>

using ProtoMoveFlag = ubyte;
typedef struct{
static const ProtoMoveFlag

    CONTACT                 = 0,
    CHARGETURN              = 1,
    MUSTRECHARGE            = 2,
    DETECTABLEPROTECTABLE   = 3,
    REFLECTABLE             = 4,
    SNATCHABLE              = 5,
    COPIEDBYMIRRORMOVE      = 6,
    PUNCHBASED              = 7,
    SOUNDBASED              = 8,
    UNUSABLEDURINGGRAVITY   = 9,
    DEFROSTSWHENUSED        = 10,
    AFFECTEDBYKINGSTONE     = 11,
    HEALS                   = 12,
    IGNORESSUBSTITUTE       = 13,
    POWDERBASED             = 14,
    JAWBASED                = 15,
    PULSEBASED              = 16,
    BALLISTICSBASED         = 17,
    MENTALEFFECTS           = 18,
    USABLEOUTSIDEOFBATTLE   = 19,

    COUNT                   = 20;

} ProtoMoveFlags;

class ProtoMove : public NIGenString{

private:
    ushort          m_id        = 0;                                //Move ID
    string          m_name      = "EMPTY";                          //Displayed Name
    ubyte           m_power     = 0;                                //Base Power [0...255]
    ubyte           m_pp        = 5;                                //Base PP (typically [5...40])
    ubyte           m_accuracy  = 100;                              //Base Accuracy in Percent [0...100]
    ProtoType       m_type      = ProtoTypes::NORMAL;               //Move Element Type
    int8_t          m_priority  = 0;                                //Move Priority [-7...+7]
    ProtoMoveClass  m_class     = ProtoMoveClasses::PHYSICAL;       //Move Class [Physical / Special / Status]
    ushort          m_effect    = 0;                                //Function Code of Effect to apply upon Cast
    ubyte           m_effectChance = 100;                           //Chance of the Effect to trigger upon Cast
    bool            m_flags[ProtoMoveFlags::COUNT] = { 0 };         //Move Flags e.g. does the Move create Contact w/ the Enemy, etc.
    string          m_desc      = "Describe the Move w/ this Text"; //Descriptive Text

public:

    //Construct a new Move with the given Properties
    ProtoMove(
              ushort id,
              const string &name,
              ubyte power,
              ubyte pp,
              ubyte acc,
              ProtoType type,
              int8_t prio,
              ProtoMoveClass cls,
              ushort effect,
              ubyte effectChance,
              bool flags[ProtoMoveFlags::COUNT],
              const string &desc);

    //Getters
    inline ushort getID(void) const{ return m_id; }
    inline const string &getName(void) const{ return m_name; }
    inline ubyte getPower(void) const{ return m_power; }
    inline ubyte getPP(void) const{ return m_pp; }
    inline ProtoType getType(void) const{ return m_type; }
    inline int8_t getPriority(void) const{ return m_priority; }
    inline ProtoMoveClass getClass(void) const{ return m_class; }
    inline ubyte getAccuracy(void) const{ return m_accuracy; }
    inline ushort getEffect(void) const{ return m_effect; }
    inline bool isFlagSet(ProtoMoveFlag flag) const{ return m_flags[flag]; }
    inline const string &getDescription(void) const{ return m_desc; }

    //Generate Debug String
    string genString(void) const;

};
