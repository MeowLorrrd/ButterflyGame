#ifndef GAME_H_
#define GAME_H_
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "Math.cpp"
#include "Player.h"
#include "Butterfly.h"
#include "Background.h"
#include "Random.cpp"
#include "Input.h"
#include "AssetHandler.h"

using namespace sf;

class Game
{
private:
	RenderWindow* render_window;
	VideoMode video_mode;
	Event sf_event;
	RenderStates render_states;
	Keyboard keyboard;
	Input input;
	AssetHandler* asset_handler;

	void SetupGameWindow();
	void UpdateInput();
public:
	Game();
	~Game();
	void Update(float deltaTime);
	void Draw();
	//Returns true if window is open, game will exit otherwise
	const bool WindowIsActive() const;
	//Returns true if window is currently focussed, game is paused otherwise
	const bool WindowHasFocus() const;

	Player* my_player;
	Butterfly* butterflies[BUTTERFLY_LIMIT];
	Background background = Background();
};
#endif
