#include "NObjectManager.h"

bool NObjectManager::subscribe(NGameObject *obj, const string &name){

    //Name already taken
    if(manages(name)) return false;

    m_objectPool.insert(make_pair(name, obj));
}

bool NObjectManager::unsubscribe(NGameObject *obj){

    auto iter = m_objectPool.begin();

    for(; iter != m_objectPool.end(); ++iter){
        if(iter->second == obj) break;
    }

    //Object was found inside Pool
    if(iter != m_objectPool.end()){
        if(m_objectPool.erase(iter->first) > 0){
            return true;
        }
    }

    return false;
}

bool NObjectManager::unsubscribe(const string &name){

    //Try and erase Object by Key
    if(m_objectPool.erase(name)){
        return true;
    }

    return false;
}

bool NObjectManager::destroy(const string &name){

    if(!manages(name)) return false;

    NGameObject *object = m_objectPool.at(name);
    unsubscribe(name);
    delete object;
    return true;
}

bool NObjectManager::destroy(NGameObject *obj){

    if(obj == nullptr || !manages(obj)) return false;

    unsubscribe(obj);
    delete obj;
    return true;
}

bool NObjectManager::manages(const NGameObject *obj) const{

    auto iter = m_objectPool.begin();

    for(; iter != m_objectPool.end(); ++iter){
        if(iter->second == obj) break;
    }

    return (iter != m_objectPool.end());
}

bool NObjectManager::manages(const string &name) const{

    return m_objectPool.count(name);
}

void NObjectManager::update(float dt){
    for(auto iter = m_objectPool.begin(); iter != m_objectPool.end(); ++iter){
        iter->second->update(dt);
    }
}

void NObjectManager::draw(NRenderer &renderer){

    NDrawable *drawPtr = nullptr;
    for(auto iter = m_objectPool.begin(); iter != m_objectPool.end(); ++iter){
        if( (drawPtr = dynamic_cast<NDrawable*>(iter->second)) != nullptr ){
                drawPtr->draw(renderer);
        }
    }
}

uint NObjectManager::getObjectCount(void) const{

    return m_objectPool.size();
}

NObjectManager::~NObjectManager(void){

    //Free all Objects
    for(auto iter = m_objectPool.begin(); iter != m_objectPool.end(); ++iter){
        destroy(iter->first);
    }
}
