#pragma once

#include "../proto_system/proto_enums.h"

class ProtoMapEvent
{
private:
    //Upper Left Corner of the Event Area
    ushort m_tileX = 0, m_tileY = 0;

    //Size of Event Area
    ushort m_width = 1, m_height = 1;

    //Internal Event State
    ubyte m_state = 0;

public:
    //Default Ctor
    ProtoMapEvent(void);

    //Return the Event's Position & Size
    inline ushort getTileX(void)  const { return m_tileX;  }
    inline ushort getTileY(void)  const { return m_tileY;  }
    inline ushort getWidth(void)  const { return m_width;  }
    inline ushort getHeight(void) const { return m_height; }

    //Set the Event's Area
    inline void setArea(ushort x, ushort y, ushort w = 1, ushort h = 1)
    {
        m_tileX  = x;
        m_tileY  = y;
        m_width  = w;
        m_height = h;
    }

    //Return the current Event State
    inline ubyte getState(void) const { return m_state; }

    //Routine to call upon Map Initialization
    virtual void setup(void){ ;; }

    //Routine to call upon Interaction e.g. by Action Button
    virtual void interact(void){ ;; }

    //Routine to call once the Player enters the Event Area
    virtual void enter(void){ ;; }

    //Routine to call once the Player leaves the Event Area
    virtual void leave(void){ ;; }

    //Default Dtor
    virtual ~ProtoMapEvent(void);
};
