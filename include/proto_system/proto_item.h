#pragma once

#include <NBase.h>
#include "../proto_system/proto_enums.h"

//Defines an Item
typedef struct protoitem_t{

    ushort id;          //Item Identifier
    string name;        //Item Name to be displayed
    ProtoItemType type; //Item Type
    bool battleOnly;    //Flag determining whether the Item is to be used during Battle only (X-ATK, ...)
    string description; //Descriptive Text

} ProtoItem;
