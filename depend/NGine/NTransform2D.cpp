#include "NTransform2D.h"

//Update the Transform
void NTransform2D::update(float dt){

    //Accelerate
    vx += ax * dt;
    vy += ay * dt;

    //Move
    x += vx * dt;
    y += vy * dt;
}

//Generate Debug string
string NTransform2D::genString(void) const{

    NTextBuffer<1024> buffer;

    sprintf(buffer, "NTransform2D::toString()\n\tPosition = {%0.2f|%0.2f};\n\tVelocity = {%0.2f|%0.2f};\n\tAcceleration = {%0.2f|%0.2f};\n\tRotation = {%0.2f};\n",
            x, y, vx, vy, ax, ay, rotation);

    return string(buffer);
}
