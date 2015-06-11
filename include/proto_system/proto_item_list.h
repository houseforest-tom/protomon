#pragma once

#include "proto_item.h"
#include <vector>
#include <fstream>

class ProtoItemList{

private:
    //Vector of Items in successive Order by ID
    static vector<ProtoItem> m_items;

public:
    //Construct an empty Items List
    static void init(void);

    //Add a new Item to the List
    static void addItem(const ProtoItem &item);

    //Load Items into List from File
    static void loadFromFile(const string &file);

    //Return a readonly Reference to a Item
    static const ProtoItem &getItem(ushort id);

    //Return the Number of Items contained within the List
    static ushort getItemCount(void);

    //Free Memory
    static void unload(void);
};
