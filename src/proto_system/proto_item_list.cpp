#include "../../include/proto_system/proto_item_list.h"

void ProtoItemList::init(void){
}

void ProtoItemList::addItem(const ProtoItem &item){
    m_items.push_back(item);
}

void ProtoItemList::loadFromFile(const string &file){

    ifstream fstr(file);
    string buf;

    ushort id;
    string name;
    ProtoItemType type;
    bool battle;
    string desc;

    //Still a Line left to read
    while(getline(fstr, buf)){

        id = atoi( buf.c_str() );
        getline(fstr, buf);
        name.assign(buf);
        getline(fstr, buf);
        type = atoi( buf.c_str() );
        getline(fstr, buf);
        battle = atoi( buf.c_str() );
        getline(fstr, buf);
        desc.assign(buf);

        addItem( { id, name, type, battle, desc } );
        getline(fstr, buf);
    }

    fstr.close();
}

const ProtoItem &ProtoItemList::getItem(ushort id){
    return m_items[id-1];
}

ushort ProtoItemList::getItemCount(void){
    return m_items.size();
}

void ProtoItemList::unload(void){
    m_items.clear();
}

vector<ProtoItem> ProtoItemList::m_items;
