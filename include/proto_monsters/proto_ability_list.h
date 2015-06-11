#pragma once

#include <vector>
#include <fstream>
#include "proto_ability.h"

class ProtoAbilityList{

private:
    //Vector of Abilities in successive Order by ID
    static vector<ProtoAbility> m_abilities;

public:
    //Construct an ampty Ability List
    static void init(void);

    //Add a new Ability to the List
    static void addAbility(const ProtoAbility &ability);

    //Load Abilities into List from File
    static void loadFromFile(const string &file);

    //Return a readonly Reference to an Ability
    static const ProtoAbility &getAbility(ushort id);

    //Return the Number of Abilities contained within the List
    static ushort getAbilityCount(void);
};
