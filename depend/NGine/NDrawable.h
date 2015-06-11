#pragma once

#include "NRenderer.h"
#include "NTransform2D.h"
#include "NGameObject.h"

class NDrawable : public NGameObject{

private:

public:
    NDrawable(void) { }
    virtual void draw(NRenderer &renderer) = 0;
    virtual void update(float dt){ NGameObject::update(dt); }
    virtual ~NDrawable(void) { }
};
