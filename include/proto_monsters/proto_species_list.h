#pragma once

#include "proto_species.h"
#include <vector>
#include <fstream>

class ProtoSpeciesList{

private:
    //Vector of Species in successive Order by ID
    static vector<ProtoSpecies*> m_species;

public:
    //Construct an empty Species List
    static void init(void);

    //Add a new Species to the List
    static void addSpecies(ProtoSpecies *species);

    //Load Species into List from File
    static void loadFromFile(const string &file);

    //Return a readonly Reference to a Species
    static const ProtoSpecies &getSpecies(ushort id);

    //Return the Number of Species contained within the List
    static ushort getSpeciesCount(void);

    //Free Memory
    static void unload(void);
};
