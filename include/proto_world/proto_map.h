#include <NBase.h>
#include <NDrawable.h>
#include <NField.h>
#include <NTextureManager.h>
#include "../proto_system/proto_enums.h"
#include "proto_npc.h"

#define PROTO_RENDER_MAP_COLLISION 0

//Basic tiled Map Entity
class ProtoMap : public NDrawable{

private:
    //Texture Manager Reference
    NTextureManager *m_pTextureMgr = nullptr;

    //Alias of Texture Asset to use as Tilesheet
    string m_tilesheet = "";

    //Position of Rendering Camera
    float m_cameraPosition[2];

    //Actual Tile Information
    NField<ubyte> m_layers[PROTO_TILE_LAYERS];
    NField<bool>  m_collision;

    //Objects on the Map
    map<string, ProtoMapObject*> m_objects;

public:
    //Default Ctor, w & h specify the Maps Width and Height
    ProtoMap(uint width, uint height, const string &tilesheet, NTextureManager &texmgr);

    //Update Rendering Camera Position
    inline void setCameraPosition(float x, float y){
        m_cameraPosition[0] = x;
        m_cameraPosition[1] = y;
    }

    //Get Map Dimensions
    inline uint getWidth (void){ return m_layers[0].getWidth(); }
    inline uint getHeight(void){ return m_layers[0].getHeight(); }

    //Get Camera Position
    inline float getCameraX(void) const { return m_cameraPosition[0]; }
    inline float getCameraY(void) const { return m_cameraPosition[1]; }

    //Draw Tiles & Objects
    void draw(NRenderer &renderer);

    //Update Objects
    void update(float dt);

    //Get Layer Reference
    inline NField<ubyte> &getLayer(ubyte layer){ return m_layers[(layer < PROTO_TILE_LAYERS ? layer : (PROTO_TILE_LAYERS - 1))]; };

    //Get Collision Data Reference
    inline NField<bool> &getCollisionData(void){ return m_collision; }

    //Get single Tile Collision
    inline bool collidesTile(uint x, uint y) const { return m_collision.getEntry(x, y); }

    //Check for Collision with an Object
    bool collidesObject(const string &host, uint x, uint y) const;

    //Add a new Map Object
    void addObject(ProtoMapObject *object, const string &name);

    //Remove an Object from the Map's Update and Draw Loop
    void removeObject(const string &name);

    //Delete a Map Object
    void deleteObject(const string &name);

    //Get a Reference to an Object on the Map
    ProtoMapObject &getObject(const string& name);

    //Default Dtor destroys all Objects on the Map
    ~ProtoMap(void);
};
