#ifndef NGINE_KEYBOARD_HDR
#define NGINE_KEYBOARD_HDR

/***************************************************************************************************************/
#include "NBase.h"
#include <SFML/System.hpp>
#include <SFML/Window/Keyboard.hpp>
/***************************************************************************************************************/


///Contains Information about Keys being currently held down and
///recently happened Key Press- / Release- Events
class NKeyboard{

private:
	///Keys currently pressed
	bool m_keysDown[256];

	///Keys pressed last Frame
	bool m_prevKeysDown[256];

public:
	///Initialize Keyboard
	void init(void);

	///Returns whether a Key is currently held down
	bool isKeyDown(sf::Keyboard::Key key) const;

	///Returns whether a Key is currently not pressed
	bool isKeyUp(sf::Keyboard::Key key) const;

	///Returns whether a Key was pressed this Frame
	bool wasKeyPressed(sf::Keyboard::Key key) const;

	///Returns whether a Key was released this Frame
	bool wasKeyReleased(sf::Keyboard::Key key) const;

	///Updates Keyboard State
	void update(void);
};

#endif // NGINE_KEYBOARD_HDR
