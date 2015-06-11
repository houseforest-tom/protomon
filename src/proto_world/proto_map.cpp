#include "../../include/proto_world/proto_map.h"


ProtoMap::ProtoMap(uint w, uint h, const string &tilesheet, NTextureManager &texmgr):
    m_pTextureMgr(&texmgr),
    m_tilesheet(tilesheet){

    m_collision.resize(w, h);
    for(ubyte l=0; l<PROTO_TILE_LAYERS; ++l){
        m_layers[l].resize(w, h);
    }
}

void ProtoMap::update(float dt)
{
    for(auto iter = m_objects.begin(); iter != m_objects.end(); ++iter)
    {
        iter->second->update(dt);

        auto *npc = dynamic_cast<ProtoNPC*>(iter->second);
        if(npc != nullptr)
        {
            //Check for Collision when NPC is moving
            if(npc->isWalking())
            {
                ProtoDirection dir = npc->getDirection();

                uint x, y;

                if( dir == ProtoDirections::LEFT || dir == ProtoDirections::RIGHT )
                {
                    x = npc->getWalkStartCoord();
                    y = npc->getTileY();
                }
                else
                {
                    x = npc->getTileX();
                    y = npc->getWalkStartCoord();
                }

                if(        ( dir == ProtoDirections::DOWN  && (collidesTile(x, y + 1) || collidesObject(npc->getName(), x, y + 1)) )
                        || ( dir == ProtoDirections::UP    && (collidesTile(x, y - 1) || collidesObject(npc->getName(), x, y - 1)) )
                        || ( dir == ProtoDirections::LEFT  && (collidesTile(x - 1, y) || collidesObject(npc->getName(), x - 1, y)) )
                        || ( dir == ProtoDirections::RIGHT && (collidesTile(x + 1, y) || collidesObject(npc->getName(), x + 1, y)) ) )
                {
                    //Collision detected!
                    npc->interruptWalk();

                    //const CBusinessEngineExpenseMaintenanceFactorySingletonInstance *m_pCrudelyPaintedNotSoFunnyPlywoodCutoutFolkart = nullptr;
                }
            }
        }
    }
}

void ProtoMap::draw(NRenderer &renderer){

    static NTextBuffer<128> alias, path;
    sprintf(alias, "tilesheet_%s", m_tilesheet.c_str());
    sprintf(path, "res/img/tilesheets/%s.png", m_tilesheet.c_str());

    if(!m_pTextureMgr->containsAsset(string(alias))){
        m_pTextureMgr->loadAsset(string(alias), path);
    }

    const NTexture &ssheet = m_pTextureMgr->getAsset(string(alias));
    const ushort ssheetw = ssheet.getWidth();
    const ushort ssheeth = ssheet.getHeight();
    const ushort tilesPerRow = ssheetw / PROTO_TILESHEET_TILE_SIZE;

    static uint x=0, y=0, l=0;

    //Determine starting Tile Positions
    uint x0 = max(0, min((int)getWidth(),  (int)(m_cameraPosition[0] / PROTO_TILE_SIZE))),
         y0 = max(0, min((int)getHeight(), (int)(m_cameraPosition[1] / PROTO_TILE_SIZE)));

    for(l = 0; l < PROTO_TILE_LAYERS; ++l){
        for(y = y0; y < getHeight() && y < y0 + PROTO_VISIBLE_TILES_V; ++y){
            for(x = x0; x < getWidth() && x < x0 + PROTO_VISIBLE_TILES_H; ++x){

                ubyte tile = m_layers[l].getEntry(x, y);

                //Skip Air Tiles
                if(tile == 0) continue;
                renderer.renderSubtexQuad(
                                            ssheet,
                                            (float)(int)roundf( (x * PROTO_TILE_SIZE - m_cameraPosition[0]) ),
                                            (float)(int)roundf( (y * PROTO_TILE_SIZE - m_cameraPosition[1]) ),
                                            PROTO_TILE_SIZE,
                                            PROTO_TILE_SIZE,
                                            ((tile % tilesPerRow) * PROTO_TILESHEET_TILE_SIZE) / (float)ssheetw,
                                            ((tile / tilesPerRow) * PROTO_TILESHEET_TILE_SIZE) / (float)ssheeth,
                                            ((tile % tilesPerRow + 1) * PROTO_TILESHEET_TILE_SIZE) / (float)ssheetw,
                                            ((tile / tilesPerRow + 1) * PROTO_TILESHEET_TILE_SIZE) / (float)ssheeth,
                                            0.0f
                                         );
            }
        }
    }

    for(auto iter = m_objects.begin(); iter != m_objects.end(); ++iter)
    {
        iter->second->setCameraPosition(m_cameraPosition[0], m_cameraPosition[1]);
        iter->second->draw(renderer);
    }

    //Render Tiles' Collision if desired
    if( PROTO_RENDER_MAP_COLLISION )
    {
        glDisable(GL_TEXTURE_2D);
        glColor4f(1, 0, 0, .56f);

        for(y = y0; y < getHeight() && y < y0 + PROTO_VISIBLE_TILES_V; ++y){
            for(x = x0; x < getWidth() && x < x0 + PROTO_VISIBLE_TILES_H; ++x){
                if(!collidesTile(x, y)) continue;
                renderer.renderQuad(
                                                (float)(int)roundf( (x * PROTO_TILE_SIZE - m_cameraPosition[0]) ),
                                                (float)(int)roundf( (y * PROTO_TILE_SIZE - m_cameraPosition[1]) ),
                                                PROTO_TILE_SIZE,
                                                PROTO_TILE_SIZE
                                    );

            }
        }

        glEnable(GL_TEXTURE_2D);
        glColor4f(1, 1, 1, 1);
    }
}

//Add a new Map Object
void ProtoMap::addObject(ProtoMapObject *object, const string &name)
{
    m_objects.insert(std::make_pair(name, object));
}

//Remove an Object from the Map's Update and Draw Loop
void ProtoMap::removeObject(const string &name)
{
    m_objects.erase(name);
}

//Delete a Map Object
void ProtoMap::deleteObject(const string &name)
{
    delete m_objects[name];
    m_objects.erase(name);
}

//Get a Reference to an Object on the Map
ProtoMapObject &ProtoMap::getObject(const string& name)
{
   return *m_objects[name];
}

bool ProtoMap::collidesObject(const string &host, uint x, uint y) const
{
    for(auto iter = m_objects.begin(); iter != m_objects.end(); ++iter)
    {
        if(iter->second->getName() != host && iter->second->getTileX() == x && iter->second->getTileY() == y && iter->second->hasCollision())
        {
            return true;
        }
    }

    return false;
}

ProtoMap::~ProtoMap(void)
{
    for(auto iter = m_objects.begin(); iter != m_objects.end(); ++iter)
        delete iter->second;
    m_objects.clear();
    cout << "ProtoMap::~ProtoMap(void) called!" << endl;
}
