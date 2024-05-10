#ifndef _INPUT_H
#define _INPUT_H
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
using namespace sf;
class Input
{
public:
	Input();
	virtual ~Input();
	bool IsPressingKey(Keyboard::Key key) const;
	bool HasPressedKey(Keyboard::Key key) const;
	bool IsPressingMouse(Mouse::Button button) const;
	bool HasPressedMouse(Mouse::Button button) const;
	bool mouseState[Mouse::ButtonCount];
	bool oldMouseState[Mouse::ButtonCount];
	bool keyState[Keyboard::KeyCount];
	bool oldKeyState[Keyboard::KeyCount];
private:
	Keyboard keyboard;
	Mouse mouse;
};
#endif // !_INPUT_H
