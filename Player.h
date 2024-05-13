#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "Math.cpp"
#include "Item.h"
#include "Input.h"

using namespace sf;

class Player
{
public:
	Player(AssetHandler* asset_handler);
	virtual ~Player();
	void Draw(RenderWindow& render_window, RenderStates render_states);
	void Update(float deltaTime, Input* input);
	Vector2f GetCenter();

	Item* inventory[INVENTORY_SIZE];
	float width, height;
	static Vector2f GetItemPosition(Player& player);
	static bool GetCollision(Player& player, FloatRect other);
	static void SetItem(Item* inventory[INVENTORY_SIZE], unsigned char item_type);
private:
	const float
		RUN_SLOWDOWN = 0.6f,
		RUN_ACCELERATION = 0.06f,
		JUMP_POWER = -11.8f,
		GRAVITY = 0.34f,
		DEFAULT_WIDTH = 24.0f,
		DEFAULT_HEIGHT = 256.0f;
	const Uint8 TOTAL_FRAMES = 8U;

	Vector2u window_borders;

	Vector2f velocity;
	Vector2f position;

	bool can_jump;

	bool inventory_open;

	Uint8 current_frame, animation_time;
	Int8 direction = 1;
	int selected_item_slot;

	RectangleShape frame = RectangleShape();
	IntRect texture_rectangle = IntRect();
	Item* items;

	void Collision();
	void UseItem(Input* input);
	void SetFrame();
	void Movement(Input* input);
};

#endif