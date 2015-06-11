#ifndef NGINE_TRANSFORM2D_HDR
#define NGINE_TRANSFORM2D_HDR

#include "NBase.h"
#include "NIGenString.h"

//Describes a Transformation State in 2-dimensional Space (translatory & rotational Movement)
class NTransform2D : public NIGenString{

public:
    //Position
    float x  = 0, y  = 0;

    //Velocity
    float vx = 0, vy = 0;

    //Acceleration
    float ax = 0, ay = 0;

    //Angle of Rotation (in Degrees)
    float rotation = 0;

private:
    //Collision Flag
    bool  m_collidable = true;

public:
    //Default Ctor
    NTransform2D(void) { }

    //Update the Transform
    virtual void update(float dt);

    //Get / Set Collision Flag
    inline void setCollidable(bool coll){ m_collidable = coll; }
    inline bool isCollidable(void) const{ return m_collidable; }

    //Generate Debug String
    virtual string genString(void) const;
};

#endif // NGINE_TRANSFORM2D_HDR
