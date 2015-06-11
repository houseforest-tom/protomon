#include "../../include/proto_monsters/proto_ability_list.h"

void ProtoAbilityList::init(void){ }

void ProtoAbilityList::addAbility(const ProtoAbility &ability){
    m_abilities.push_back(ability);
}

void ProtoAbilityList::loadFromFile(const string &file){

    //Open File
    ifstream fstr(file);

    string buf;

    ubyte id=0;
    string name="";
    string info="";

    //Still a Line left?
    while(getline(fstr, buf)){

        //Find ID - Part of the String
        uint place = 0;
        for(uint i=0; i<buf.length(); ++i){

            //ID Found
            if(buf[i] == ' '){
                id = atoi( buf.substr(0, i).c_str() );
                place = i;
                break;
            }
        }

        //Find Name - Part of the String
        for(uint i=place+1; i<buf.length(); ++i){

            //Name Found
            if(buf[i] == ' '){
                name = buf.substr(place+1, i-(place+1));
                place = i;
                break;
            }
        }

        //Rest of String is Information Text
        info.assign(buf.substr(place+1, buf.length()-(place+1)));

        m_abilities.push_back( { id, name, info } );
    }

    //Close File
    fstr.close();
}

const ProtoAbility &ProtoAbilityList::getAbility(ushort id){
    return m_abilities[id];
}

ushort ProtoAbilityList::getAbilityCount(void){
    return m_abilities.size();
}

vector<ProtoAbility> ProtoAbilityList::m_abilities;
