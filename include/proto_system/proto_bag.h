#pragma once

#include "proto_enums.h"
#include "proto_item.h"
#include "proto_item_list.h"

#include <vector>


//Bundles an Item ID w/ a Quantity
typedef struct protoitemquantity_t{

    ushort id;      //Item ID
    ushort count;   //Item Count

} ProtoItemQuantity;


//Describes the Player's Bag
class ProtoBag{

private:
    //Contained Elements per Sub-Bag
    vector<ProtoItemQuantity> m_contents[ProtoItemTypes::COUNT];

    //Find Slot the Item is contained in
    ushort findSlot(ushort item);

public:
    //Returns the Quantity of the specified Item inside the Bag
    ushort getItemQuantity(ushort item) const;

    //Retrieve a readonly Reference to the Element contained in Sub-Bag 'bag' in the given Slot
    const ProtoItemQuantity &getElement(ubyte bag, ubyte slot) const;

    //Return the Number of Items (different IDs) contained in a Sub-Bag
    ushort getElementCount(ubyte bag) const;

    //Add one Instance of an Item to the Bag
    bool addItem(ushort item);

    //Add a specific Amount of Instances of an Item to the Bag
    bool addItemQuantity(const ProtoItemQuantity &itemQtty);

    //Discard one Instance of an Item from the Bag
    bool discardItem(ushort item);

    //Discard a specific Amount of Instances of an Item from the Bag
    bool discardItemQuantity(const ProtoItemQuantity &itemQtty);
};
