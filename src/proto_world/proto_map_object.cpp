#include "../../include/proto_world/proto_map_object.h"

void ProtoMapObject::draw(NRenderer &renderer)
{
    renderer.renderSubtexQuad(  m_pTextureManager->getAsset(m_texture),
                                m_position[0] - m_cameraPosition[0] - (m_drawSizePx[0] - PROTO_TILE_SIZE),
                                m_position[1] - m_cameraPosition[1] - (m_drawSizePx[1] - PROTO_TILE_SIZE),
                                (float)m_drawSizePx[0],
                                (float)m_drawSizePx[1],
                                m_textureRegion[0],
                                m_textureRegion[1],
                                m_textureRegion[2],
                                m_textureRegion[3]                   );
}
