#include "Input.h"
Input::Input()
{
	keyboard = Keyboard();
	mouse = Mouse();

	for (int i = 0u; i < sizeof(mouseState) / sizeof(*mouseState); i++) mouseState[i] = false;
	for (int i = 0u; i < sizeof(oldMouseState) / sizeof(*oldMouseState); i++) oldMouseState[i] = false;
	
	for (int i = 0u; i < sizeof(keyState) / sizeof(*keyState); i++) keyState[i] = false;
	for (int i = 0u; i < sizeof(oldKeyState) / sizeof(*oldKeyState); i++) oldKeyState[i] = false;
}
Input::~Input()
{

}
bool Input::IsPressingKey(Keyboard::Key kb) const
{
	return keyboard.isKeyPressed(kb);
}
bool Input::HasPressedKey(Keyboard::Key kb) const
{
	return keyState[kb] && !oldKeyState[kb];
}
bool Input::IsPressingMouse(Mouse::Button m) const
{
	return mouse.isButtonPressed(m);
}
bool Input::HasPressedMouse(Mouse::Button m) const
{
	return mouseState[m] && !oldMouseState[m];
}