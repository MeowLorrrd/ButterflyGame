#ifndef _ITEM_H_
#define _ITEM_H_

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "Math.cpp"
#include "AssetHandler.h"
#include <SFML/Graphics/Sprite.hpp>
constexpr auto INVENTORY_SIZE = 37U;

using namespace sf;

class Item
{
public:
	Item(AssetHandler* asset_handler);
	virtual ~Item();
	//Draws Inventory UI
	//Will only draw top row (hotbar) if inventory is closed
	static void DrawInventoryUI(RenderWindow& render_window, RenderStates render_states, Item& inv, unsigned int slot_type, unsigned int s_item, bool inventory_open);
	//Draws Inventory contents
	//Will only draw top row (hotbar) if inventory is closed
	static void DrawInventoryContents(RenderWindow& render_window, RenderStates render_states, Item& inv, unsigned int slot_type, bool inventory_open);
	//Draws Items used by the player
	//Should not be called if item is not used
	//Usage: Item::DrawInWorld(render_window, render_states, *item, Vector2f(..., ...));
	static void DrawInWorld(RenderWindow& render_window, RenderStates render_states, Item& item, Vector2f player_position);
	//Updates logic of an used item
	//Should not be called if item is not used
	//Usage: Item::Update(deltaTime, *item, Vector2f(..., ...));
	static void Update(float deltaTime, Item& item, Vector2f player_position);
	//Spawns a new item in the world, relative to the owner (player)
	//Usage: Item::NewItem(Vector2f(..., ...), (*inventory[selected_item_slot]).type, *item);
	static void NewItem(Vector2f new_position, Uint8 type, Item& item);
	//Static function that changes an item in an inventory slot to a new type
	//Usage: Item::TurnItemToNewType(*inventory[slot_id], new_type);
	static void TurnItemToNewType(Item& old_item, unsigned short new_type);
	//Type of item
	//Defines behavior and sprite
	Uint8 type;
	const enum Types
	{
		BASICBUGNET = 0,
		NETBOMB = 1,
		BUTTERFLYMONARCH = 2,
		BUTTERFLYGOLDEN = 3,
		BUTTERFLYNEBULA = 4,
		BUTTERFLYGLASS = 5,
		COUNT = 6 //Amount of current items
	};
	//Current stack size of inventory slot
	unsigned int stack;
	//Maximum stack size of inventory slot
	unsigned int max_stack;
	
	//Used for flipping the sprite horizontally
	//Value should either be 1 or -1
	signed char dirX;
	//Returns top-left position of the item
	static Vector2f GetPosition(Item& item);
	//Returns size of item, with scale factored in
	static Vector2f GetSize(Item& item);
	static bool GetCollision(Item& item, FloatRect other);
	static bool ItemIsUsed(Item& item);

private:
	//Frame for drawing items in the inventory and in the world (if active)
	RectangleShape frame;
	Sprite inventory_sprite;
	Sprite inventory_sprite_s;

	AssetHandler* asset_handler;

	//Position for used item
	Vector2f position;
	//Offset for the used item, relative to the player's center
	Vector2f item_use_offset;
	//The way an item is used (ex: swung over player, thrown)
	Uint8 item_use_type;
	const enum USETYPES
	{
		SWING = 0,
		THROWN = 1
	};

	//Rotating the sprite
	//Value should be between 0.0f and 360.0f
	float rotation;

	float width;
	float height;
	float scale;

	//How quick another item can be used
	//Value is in frames, so item_use_delay = 60 would be 1 second
	//A value of 0 means that the item is not in use
	unsigned short item_use_delay;
};
#endif
