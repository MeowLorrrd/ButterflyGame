#include "Background.h"

Background::Background()
{
	for (int i = 0u; i < (sizeof(background_textures) / sizeof(*background_textures)); i++)
	{
		background_textures[i] = new Texture();
	}
	for (int i = 0u; i < (sizeof(floor_textures) / sizeof(*floor_textures)); i++)
	{
		floor_textures[i] = new Texture();
	}
	if (!background_textures[CLOUDYDAY]->loadFromFile("Assets/Background_0.png"))
	{
		printf("Could not load all Backgrounds!\n");
	}
	else if (!floor_textures[DIRTY]->loadFromFile("Assets/Floor_0.png"))
	{
		printf("Could not load all Floors!\n");
	}
	BG_Active = CLOUDYDAY;
	background.setSize(Vector2f(1600.f, 900.f));
	background.setOrigin(800, 450);
	background.setPosition(800, 450);
	background.setTexture(background_textures[BGTYPES::CLOUDYDAY]);

	floor.setSize(Vector2f(1600.f, 75.f));
	floor.setOrigin(800, 0);
	floor.setPosition(800, 825);
	floor.setTexture(floor_textures[FLOORTYPES::DIRTY]);
}
Background::~Background()
{
}
// TODO:: Add a parallex effect with a nicer looking background
void Background::Update(float deltaTime, RenderWindow& render_window)
{
}

void Background::Draw(RenderWindow& render_target, RenderStates render_states) const
{
	if (BG_Active < 0 || BG_Active >(sizeof(background_textures) / sizeof(*background_textures)))
	{
		throw "Tried drawing an unexisting background!";
	}
	render_target.draw(this->background, render_states);
	//Currently only 1 floor can exist, might implement a system where the game can have more floors and/or platforms
	render_target.draw(this->floor, render_states);
}