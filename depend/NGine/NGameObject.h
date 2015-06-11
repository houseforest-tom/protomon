#pragma once

#include "NTransform2D.h"

//Basic Representation of a Game Object
class NGameObject : public NIGenString{

private:
    //The Object's Taransformation Detail
    NTransform2D m_transform;

public:
    //Default Ctor
    NGameObject(void){ }

    //Return a Read / Write Reference to the Object's Transform
    inline NTransform2D &getTransform(void){ return m_transform; }

    //Update the Transform
    virtual void update(float dt){ m_transform.update(dt); }

    //Generate a Debug String or such
    virtual string genString(void) const { return m_transform.genString(); }
};
