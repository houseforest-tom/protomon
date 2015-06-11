#ifndef NGINE_TEXTURE_HDR
#define NGINE_TEXTURE_HDR

#include "NBase.h"
#include <GL/gl.h>
#include <SFML/Graphics.hpp>

class NTexture{
    friend class NRenderer;
    friend class NTextureManager;

private:
    //Underlying Texture Object
    sf::Texture *m_texture = nullptr;

    //OpenGL Texture ID
    GLint m_openGLId = (uint)(-1);

public:
    //Return the Texture's Width
    inline ushort getWidth(void) const { return m_texture->getSize().x; }

    //Return the Texture's Height
    inline ushort getHeight(void) const { return m_texture->getSize().y; }

    inline void findGLId(void){
        sf::Texture::bind(m_texture);
        glGetIntegerv(GL_TEXTURE_BINDING_2D, &m_openGLId);
    }

    //Bind GL Texture
    inline bool bind(void) const {

        //Only Bind to Texture Object State if not already active

        //OpenGL ID wasn't retrieved earlier by call to findGLId()
        if(m_openGLId == (uint)(-1))
        {
            sf::Texture::bind(m_texture);
            return true;
        }
        else //OpenGL ID was retrieved earlier -> use for early cancellation check
        {
            GLint currentTexture = 0;
            glGetIntegerv(GL_TEXTURE_BINDING_2D, &currentTexture);
            if(m_openGLId != currentTexture)
            {
                sf::Texture::bind(m_texture);
                return true;
            }

            return false;
        }

        return false;
    }

    //Clean up
    inline void unloadTexture(void){ del(m_texture); }
};

#endif // NGINE_TEXTURE_HDR
