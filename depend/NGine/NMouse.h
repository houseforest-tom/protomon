#ifndef NGINE_MOUSE_HDR
#define NGINE_MOUSE_HDR

/***************************************************************************************************************/
#include "NBase.h"
#include "NRenderer.h"
/***************************************************************************************************************/


///Provides Information about Mouse Location & Movement
class NMouse{

private:
	///Real Window Dimensions
	ushort m_windowSize[2] = { 800, 600 };

	///Current Location of the Mouse Pointer (Virtual Coordinates)
	ushort m_locationX = 800;
	ushort m_locationY = 450;

	///Mouse Movement since last Frame
	ushort m_deltaX = 0;
	ushort m_deltaY = 0;

public:
	///Initialize Mouse
	void init(ushort windowWidth, ushort windowHeight);

	///Update Cursor Location and Movement
	void update(const NRenderer &gfx);

	///Returns the current Location of the Mouse
	ushort getX(void) const;
	ushort getY(void) const;
	void getLocation(ushort &x, ushort &y) const;

	///Returns the Movement of the Mouse since the last Frame
	ushort getDeltaX(void) const;
	ushort getDeltaY(void) const;
	void getDelta(ushort &x, ushort &y) const;
};

#endif // NGINE_MOUSE_HDR
