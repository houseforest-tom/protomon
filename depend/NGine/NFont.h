#ifndef NGINE_FONT_HDR
#define NGINE_FONT_HDR

#include "NBase.h"
#include <SFML/Graphics/Font.hpp>

///Wraps a True Type Font
class NFont{
    friend class NRenderer;
    friend class NFontManager;

private:
    ///Internal Font Data
    sf::Font *m_font = nullptr;

public:
    ///Free Memory used by Font
    inline void unloadTTF(void){ del(m_font); }
};

#endif // NGINE_FONT_HDR
