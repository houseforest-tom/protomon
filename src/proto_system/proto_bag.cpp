#include "../../include/proto_system/proto_bag.h"

ushort ProtoBag::getItemQuantity(ushort item) const{

    ushort qtty = 0;
    const ProtoItem &itemRef = ProtoItemList::getItem(item);
    for(auto iter = m_contents[itemRef.type].begin(); iter != m_contents[itemRef.type].end(); ++iter){

        if((*iter).id == item){
            qtty += (*iter).count;
        }
    }

    return qtty;
}

const ProtoItemQuantity &ProtoBag::getElement(ubyte bag, ubyte slot) const{
    return m_contents[bag][slot];
}

ushort ProtoBag::getElementCount(ubyte bag) const{
    return m_contents[bag].size();
}

bool ProtoBag::addItem(ushort item){
    return addItemQuantity( { item, 1 } );
}

bool ProtoBag::addItemQuantity(const ProtoItemQuantity &itemQtty){

    ushort containedQtty = getItemQuantity(itemQtty.id);
    ubyte  subBag        = ProtoItemList::getItem(itemQtty.id).type;
    ushort slot          = findSlot(itemQtty.id);

    //Can't hold more than 999 of the same Item
    if(containedQtty + itemQtty.count > 999) return false;

    //No such item contained yet
    if(slot == m_contents[subBag].size()){
        m_contents[subBag].push_back(itemQtty);
        return true;
    }

    //Items Contained yet
    else if(containedQtty > 0){
        m_contents[subBag][slot].count += itemQtty.count;
        return true;
    }

    return true;
}

bool ProtoBag::discardItem(ushort item){
    discardItemQuantity( { item, 1 } );
}

bool ProtoBag::discardItemQuantity(const ProtoItemQuantity &itemQtty){

    ushort inBag = getItemQuantity(itemQtty.id);

    //Item Quantity not contained in Bag
    if(inBag < itemQtty.count){
        return false;
    }

    ushort slot = findSlot(itemQtty.id);
    ProtoItemQuantity &qtty = m_contents[ProtoItemList::getItem(itemQtty.id).type][slot];
    qtty.count -= itemQtty.count;
    if(qtty.count == 0){
        //Erase the Item Quantity as a whole
    }
}

ushort ProtoBag::findSlot(ushort item){

    const ProtoItem &itemRef = ProtoItemList::getItem(item);
    ushort i=0;

    for(; i<m_contents[itemRef.type].size(); ++i){
        if( m_contents[itemRef.type][i].id == item )
            return i;
    }

    return i;
}
