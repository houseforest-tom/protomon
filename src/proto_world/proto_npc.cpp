#include "../../include/proto_world/proto_npc.h"

ProtoNPC::ProtoNPC(NTextureManager &texmgr, const string &name, ushort type)
    :ProtoMapObject(texmgr, name), m_npcType(type)
{
    setTexture("npc_sheet");
    adjustTextureRegion();
}

void ProtoNPC::walk(ubyte steps)
{
    //Must not be walking atm
    if(!m_isWalking)
    {
        m_isWalking = true;
        m_walkStepsLeft = steps;

        if(m_direction == ProtoDirections::LEFT || m_direction == ProtoDirections::RIGHT)
            m_walkStartCoord = getTileX();
        else
            m_walkStartCoord = getTileY();
    }
}

void ProtoNPC::adjustTextureRegion(void)
{
    ubyte textureSnippetV = m_npcType;
    ubyte textureSnippetH = 0;
    bool  mirrored = false;

    //Determine Direction-dependent Texture Snippet to use
    switch(m_direction)
    {
        case ProtoDirections::UP:    textureSnippetH = 1; break;
        case ProtoDirections::LEFT:  textureSnippetH = 2; break;
        case ProtoDirections::RIGHT: textureSnippetH = 2; mirrored = true; break;
        case ProtoDirections::DOWN:  textureSnippetH = 0; break;
        default: break;
    }

    //Use Walking Animation
    if(m_isWalking)
    {
        //First Step of Walking Animation
        if(m_walkAnimStep == 0)
        {
            textureSnippetH += 3;
        }
        //Second Step of Walking Animation
        else if(m_walkAnimStep == 1)
        {
            ;; //leave unchanged (idle sprite)
        }
        //Third Step of Walking Animation
        else
        {
            if(m_direction == ProtoDirections::LEFT || m_direction == ProtoDirections::RIGHT)
            {
                textureSnippetH += 4;
            }

            else
            {
                //Use mirrored Texture Region for Up and Down Movement
                textureSnippetH += 3;
                mirrored = !mirrored;
            }
        }
    }

    //Calculate Texture Coordinates
    float sheetWidth  = NPC_TEXSNIPPET_W * 7;
    float sheetHeight = NPC_TEXSNIPPET_H * MAX_NPC_TYPES;
    float u0 = (textureSnippetH * NPC_TEXSNIPPET_W) / sheetWidth;
    float v0 = (1 + textureSnippetV * NPC_TEXSNIPPET_H) / sheetHeight;
    float u1 = ((textureSnippetH + 1) * NPC_TEXSNIPPET_W) / sheetWidth;
    float v1 = ((textureSnippetV + 1) * NPC_TEXSNIPPET_H) / sheetHeight;

    //Swap u0 & u1 if mirrored Drawing is needed
    if(mirrored)
    {
        float tmp = u0;
        u0 = u1;
        u1 = tmp;
    }

    setTextureRegion(u0, v0, u1, v1);
}

void ProtoNPC::update(float dt)
{
    if(m_isWalking)
    {
        //Last Step was done
        if(m_walkStepsLeft == 0)
        {
            m_isWalking = false;
            adjustTextureRegion();
        }

        //Still walking
        else
        {
            //Distance to move this Frame
            float distance = PROTO_TILE_SIZE * m_walkSpeed * dt;

            switch(m_direction)
            {
                case ProtoDirections::UP:    moveY(-distance); break;
                case ProtoDirections::LEFT:  moveX(-distance); break;
                case ProtoDirections::RIGHT: moveX( distance); break;
                case ProtoDirections::DOWN:  moveY( distance); break;
                default: break;
            }

            m_walkedDistance += distance;

            //Tile was walked completely
            if( m_walkedDistance >= PROTO_TILE_SIZE )
            {
                m_walkedDistance = 0.0f;
                m_walkStepsLeft--;
                setTileX((ushort)roundf(getX() / PROTO_TILE_SIZE));
                setTileY((ushort)roundf(getY() / PROTO_TILE_SIZE));
                m_walkAnimStep = 0;
            }
            //66% of Tile were walked -> use 3rd Animation Step
            else if(m_walkedDistance >= PROTO_TILE_SIZE / 3 * 2)
            {
                m_walkAnimStep = 2;
            }
            //33% of Tile were walked -> use 2nd Animation Step
            else if(m_walkedDistance >= PROTO_TILE_SIZE / 3 * 1)
            {
                m_walkAnimStep = 1;
            }
            //<33% of Tile walked
            else m_walkAnimStep = 0;

            //Animate walk
            adjustTextureRegion();
        }
    }
}

void ProtoNPC::interruptWalk(void)
{
    if(m_isWalking)
    {
        m_isWalking = false;

        if(m_direction == ProtoDirections::LEFT || m_direction == ProtoDirections::RIGHT)
        {
            setTileX(m_walkStartCoord);
        }
        else
        {
            setTileY(m_walkStartCoord);
        }

        m_walkedDistance = 0.0f;
        m_walkStepsLeft = 0;
        m_walkAnimStep = 0;

        adjustTextureRegion();
    }
}
