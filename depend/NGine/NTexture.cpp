#include "NTexture.h"

/***************************************************************************************************************/
void NTexture::fromSource(const sf::Texture &texture){

	ubyte 	 bpp 	= 4;

    if(bpp < 4) { cerr << "Unsupported Image Format\nShould be 32Bit True Color!" << endl; return; }

	glGenTextures(1, &m_glIndex);
	glBindTexture(GL_TEXTURE_2D, m_glIndex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(
                    GL_TEXTURE_2D,
                    0,
                    4,
                    texture.getSize().x,
                    texture.getSize().y,
                    0,
                    GL_RGBA,
                    GL_UNSIGNED_BYTE,
                    texture.Pixels
	);

	m_width = texture.getSize().x;
	m_height = texture.getSize().y;
}
/***************************************************************************************************************/
