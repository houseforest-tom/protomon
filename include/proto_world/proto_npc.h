#pragma once

#include "proto_map_object.h"

//Number of NPC Spritesheet Slots
#define MAX_NPC_TYPES    30
//Texture Snippet Dimensions
#define NPC_TEXSNIPPET_W 16
#define NPC_TEXSNIPPET_H 22

class ProtoNPC : public ProtoMapObject
{
private:
    //NPC Type used to determine Sprite to draw
    ubyte m_npcType = 0;

    //Facing Direction
    ProtoDirection m_direction = ProtoDirections::DOWN;

    //Currently Walking
    float m_isWalking = false;

    //Coordinate the NPC was at (X or Y) when his Movement started
    ushort m_walkStartCoord = 0;

    //Steps left of current Walk
    ubyte m_walkStepsLeft = 0;

    //Distance walked yet (temporary)
    float m_walkedDistance = 0.0f;

    //Movement Speed
    float m_walkSpeed = 1.0f;

    //Current Walking Animation Step
    ubyte m_walkAnimStep = 0;

public:
    //Ctor contructs NPC of given Type
    ProtoNPC(NTextureManager &texmgr, const string &name, ushort type);

    //Calculate current Texture Coordinates
    void adjustTextureRegion(void);

    //Is the Object currently walking?
    inline bool isWalking(void) const { return m_isWalking; }

    //Return the Coordinates the NPC started its Walk
    inline ushort getWalkStartCoord(void) const { return m_walkStartCoord; }

    //Set the Object's Walking Speed
    inline void setWalkSpeed(float speed){ m_walkSpeed = speed; }

    //Set Facing Direction
    inline void setDirection(ProtoDirection dir){ m_direction = dir; adjustTextureRegion(); }

    //Get Facing Direction
    inline ProtoDirection getDirection(void) const { return m_direction; }

    //Get NPC Type
    inline ubyte getNPCType(void) const { return m_npcType; }

    //Set NPC Type
    inline void setNPCType(ubyte type){ m_npcType = type; }

    //Initiate Movement of Number of Steps in faced Direction
    void walk(ubyte steps);

    //Interrupt the Walk if e.g. Collision was spotted
    void interruptWalk(void);

    //NPC Update Method
    virtual void update(float dt);

    //Dtor
    virtual ~ProtoNPC(void) { ;; }
};
