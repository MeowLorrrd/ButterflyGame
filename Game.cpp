#include "Game.h"

Game::Game()
{
	SetupGameWindow();
	for (int i = 0u; i < BUTTERFLY_LIMIT; i++)
	{
		butterflies[i] = new Butterfly(1);
	}
}
Game::~Game()
{
	delete this->render_window;
}
void Game::SetupGameWindow()
{
	const std::string rand_name[3] = { "Now in 4K!", "New release on PC 2!", "The Game!" };
	const std::string display_name = "Butterfly: " + rand_name[Random::NextInt(0, sizeof(rand_name) / sizeof(*rand_name))];

	this->video_mode.width = 1600u;
	this->video_mode.height = 900u;

	this->render_window = new RenderWindow(video_mode, display_name, Style::Titlebar | Style::Close);
	this->render_window->setFramerateLimit(60);
}
void Game::Update(float _deltaTime)
{
	UpdateInput();
	my_player->Update(_deltaTime, &input);
	for (int i = 0u; i < BUTTERFLY_LIMIT; i++)
	{
		if (butterflies[i]->is_active)
			//continue;
		{
			printf("[xy]:\t[%f, %f]\n", Butterfly::GetPosition(*butterflies[0]).x, Butterfly::GetPosition(*butterflies[0]).y);

			Butterfly::Update(_deltaTime, *butterflies[i]);
			if (Player::GetCollision(*my_player, Butterfly::GetGlobalBounds(*butterflies[i])))
			{
				//TODO:: 
				//	Give player butterfly item												[DONE]
				//	Kill butterfly															[50%]
				//	Set butterfly array to  i (instead of 0)								[DONE]
				Player::SetItem(my_player->inventory, Butterfly::GetItemType(*butterflies[i]));
				Butterfly::KillButterfly(butterflies, i);
			}
		}
	}
	Butterfly::SpawnButterflyNatural(60, butterflies);
}
void Game::UpdateInput()
{
	for (int i = 0u; i < sizeof(input.mouseState) / sizeof(*input.mouseState); i++) input.oldMouseState[i] = input.mouseState[i];
	for (int i = 0u; i < sizeof(input.keyState) / sizeof(*input.keyState); i++) input.oldKeyState[i] = input.keyState[i];

	if (render_window->pollEvent(sf_event)) //Update once (for input)
	{
		if (sf_event.type == Event::Closed) render_window->close();

		for (int i = 0u; i < sizeof(input.mouseState) / sizeof(*input.mouseState); i++) input.mouseState[i] = false;
		for (int i = 0u; i < sizeof(input.keyState) / sizeof(*input.keyState); i++) input.keyState[i] = false;
		if (sf_event.type == Event::KeyPressed)
		{
			input.keyState[sf_event.key.code] = true;
		}
		if (sf_event.type == Event::MouseButtonPressed)
		{
			input.mouseState[sf_event.mouseButton.button] = true;
		}
	}
	if (input.HasPressedKey(Keyboard::Escape)) render_window->close();
#ifndef DEBUG
	if (input.HasPressedKey(Keyboard::N)) Butterfly::NewButterfly(Vector2f(800.f, 450.f), 0u, butterflies);
#endif
}

void Game::Draw()
{
	render_window->clear();
	background.Draw(*render_window, render_states);
	for (int i = 0u; i < BUTTERFLY_LIMIT; i++)
	{
		if (butterflies[i]->is_active)
			//continue;
			Butterfly::Draw(*render_window, render_states, *butterflies[i]);
	}
	my_player->Draw(*render_window, render_states);
	render_window->display();
}
const bool Game::WindowIsActive() const
{
	return this->render_window->isOpen();
}
const bool Game::WindowHasFocus() const
{
	return this->render_window->hasFocus();
}
