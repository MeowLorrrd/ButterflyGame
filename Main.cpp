#include "Game.h"

int main()
{
	float deltaTime = 0.0f;
	Clock clock;
	Game game;
	while (game.WindowIsActive())
	{
		if (game.WindowHasFocus())
		{
			deltaTime = clock.restart().asSeconds();
			game.Update(deltaTime);
			game.Draw();
		}
	}
	return EXIT_SUCCESS;
}