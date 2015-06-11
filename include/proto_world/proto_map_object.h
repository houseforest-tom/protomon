#pragma once

#include "../proto_system/proto_enums.h"
#include <NObjectManager.h>
#include <NTextureManager.h>

class ProtoMapObject : public NDrawable
{
private:
    //Position
    float m_position[2] = { 0, 0 };

    //Camera Position
    float m_cameraPosition[2] = { 0, 0 };

    //Name
    string m_name = "";

    //Texture Name
    string m_texture = "";

    //Texture Region
    float m_textureRegion[4] = { 0, 0, 1, 1 };

    //Draw Size
    ushort m_drawSizePx[2] = { PROTO_TILE_SIZE, PROTO_TILE_SIZE };

    //Texture Manager Reference
    NTextureManager *m_pTextureManager = nullptr;

    //Collides?
    bool m_collides = true;

public:
    //Default Ctor
    ProtoMapObject(NTextureManager &texmgr, const string &name) : NDrawable(), m_name(name), m_pTextureManager(&texmgr) { ;; }

    //Get Name
    inline const string &getName(void) const { return m_name; }

    //Set Name
    inline void setName(const string &name){ m_name.assign(name); }

    //Set Texture Name
    inline void setTexture(const string &textureName){ m_texture.assign(textureName); }

    //Set Texture Region
    inline void setTextureRegion(float u0, float v0, float u1, float v1)
    {
        m_textureRegion[0] = u0;
        m_textureRegion[1] = v0;
        m_textureRegion[2] = u1;
        m_textureRegion[3] = v1;
    }

    inline void setTextureRegion(const float uvs[4])
    {
        memcpy(m_textureRegion, uvs, sizeof(float) * 4);
    }

    //Set Draw Size
    inline void setDrawSize(float xsz, float ysz){ m_drawSizePx[0] = xsz; m_drawSizePx[1] = ysz; }

    //Get Position Information
    inline float  getX(void) const { return m_position[0]; }
    inline float  getY(void) const { return m_position[1]; }
    inline ushort getTileX(void) const { return (ushort)(m_position[0] / PROTO_TILE_SIZE); }
    inline ushort getTileY(void) const { return (ushort)(m_position[1] / PROTO_TILE_SIZE); }

    //Change the Object's Position
    inline void setX(float x){ m_position[0] = x; }
    inline void setY(float y){ m_position[1] = y; }
    inline void setTileX(ushort x){ m_position[0] = (float)(x * PROTO_TILE_SIZE); }
    inline void setTileY(ushort y){ m_position[1] = (float)(y * PROTO_TILE_SIZE); }
    inline void moveX(float dx){ m_position[0] += dx; }
    inline void moveY(float dy){ m_position[1] += dy; }
    inline void moveTileX(ushort dx){ m_position[0] += (float)(dx * PROTO_TILE_SIZE); }
    inline void moveTileY(ushort dy){ m_position[1] += (float)(dy * PROTO_TILE_SIZE); }

    inline bool hasCollision(void) const { return m_collides; }
    inline void setCollision(bool c) { m_collides = c; }

    //Set the Camera Position for Rendering
    inline void setCameraPosition(float camx, float camy)
    {
        m_cameraPosition[0] = camx;
        m_cameraPosition[1] = camy;
    }

    //Draw the specified Subregion of the attached Texture
    virtual void draw(NRenderer &renderer);

    //Update Movement etc.
    virtual void update(float dt){ ;; }

    //Dtor
    virtual ~ProtoMapObject(void) { ;; }
};
