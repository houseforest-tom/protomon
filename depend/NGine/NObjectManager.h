#pragma once

#include "NDrawable.h"

//Manager Class for Game Objects
//Once an Object is added to the Manager's Pool, it will be automatically updated and / or drawn.
//The Manager will free all Memory allocated by Objects inside its Pool automatically in its Destructor.
//By Default, all Game Object Instances should be added to the Manager
class NObjectManager{

private:
    //Pool of managed Objects
    map<string, NGameObject*> m_objectPool;

public:
    //Default Ctor
    NObjectManager(void){ }

    //Add a new (heap-allocated) Object to the Manager's Pool
    //Returns false if the Name was already taken or the Pointer was invalid
    bool subscribe(NGameObject *obj, const string &name);

    //Remove an Object from the Manager's Pool by Address
    //This will NOT free the Memory allocated for the Object, thus it stays in a usable State
    //Returns false if the Pointer was invalid
    bool unsubscribe(NGameObject *obj);

    //Remove an Object from the Manager's Pool by Alias
    //This will NOT free the Memory allocated for the Object, thus it stays in a usable State
    //Returns false if the Name wasn't found
    bool unsubscribe(const string &name);

    //Destroy an Object, erasing it from the Manager's Pool and freeing its Memory
    //Returns false if the Name wasn't found
    bool destroy(const string &name);

    //Destroy an Object, erasing it from the Manager's Pool and freeing its Memory
    //Returns false if the Pointer was invalid
    bool destroy(NGameObject *obj);

    //Return whether the Object (designated by given Address) is in the Manager's Pool
    bool manages(const NGameObject *obj) const;

    //Return whether the Object called 'name' is in the Manager's Pool
    bool manages(const string &name) const;

    //Returns a Reference to an Object casted to needed Type
    template<typename T>
    T &getRefAs(const string &name){
        return *(dynamic_cast<T*>(m_objectPool.at(name)));
    }

    //Returns a Pointer to an Object
    template<typename T>
    T *getPtrAs(const string &name){
        return dynamic_cast<T*>(m_objectPool.at(name));
    }

    //Handles all Transform Updates
    void update(float dt);

    //Handles all Drawables' Rendering Routines
    void draw(NRenderer &renderer);

    //Return Number of currently managed Objects
    uint getObjectCount(void) const;

    //Default Dtor
    //Frees the Memory used by all Game Objects currently residing inside the Manager's Pool
    ~NObjectManager(void);
};
