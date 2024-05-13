#include "Player.h"

Player::Player(AssetHandler* _ah)
{
	position = Vector2f(800.f, 450.f);
	width = DEFAULT_WIDTH;
	height = DEFAULT_HEIGHT / TOTAL_FRAMES;
	current_frame = 0;
	texture_rectangle = IntRect(0, 0, (int)width, (int)height);
	frame.setSize(Vector2f(width, height));
	frame.setOrigin(Vector2f(
		width / 2.0f,
		height / 2.0f));
	frame.setPosition(Vector2f(position));
	frame.setTexture(AssetHandler::GetTexture(_ah, AssetHandler::Player, 0));
	frame.setTextureRect(texture_rectangle);

	items = new Item(_ah);
	for (int i = 0u; i < INVENTORY_SIZE; i++)
	{
		inventory[i] = new Item(_ah);
	}
	Item::TurnItemToNewType(*inventory[0], Item::BasicBugnet);
	selected_item_slot = 0;
	can_jump = false;
	inventory_open = false;
}
Player::~Player()
{

}
//Draw animated player & item related content
void Player::Draw(RenderWindow& render_target, RenderStates render_states)
{
	window_borders = render_target.getSize();
#pragma region PLAYER
	texture_rectangle.top = current_frame * (int)(height);//Setting frame of 'animation'
	frame.setScale(Vector2f(2.f * (float)direction, 2.f));//Flipping sprite
	frame.setTextureRect(texture_rectangle);
	render_target.draw(this->frame, render_states);
#pragma endregion

#pragma region ITEMS
	//Draw Inventory (ALL ITEMS, if item type is Item::COUNT, draw empty slot
	for (int i = 0u; i < INVENTORY_SIZE; i++)
	{
		Item::DrawInventoryUI(render_target, render_states, *inventory[i], i, selected_item_slot, inventory_open);
	}
	for (int i = 0u; i < INVENTORY_SIZE; i++)
	{
		Item::DrawInventoryContents(render_target, render_states, *inventory[i], i, inventory_open);
	}
	if (Item::ItemIsUsed(*items))
		Item::DrawInWorld(render_target, render_states, *items, GetCenter());
#pragma endregion
}

void Player::Movement(Input* input)
{
	if (input->IsPressingKey(Keyboard::A))
	{
		direction = -1;
		if (velocity.x > RUN_SLOWDOWN)
		{
			velocity.x -= RUN_SLOWDOWN * (can_jump ? 1.0f : 0.25f);
		}
		velocity.x = Math::Clamp(velocity.x - RUN_ACCELERATION, -4.0f, 4.0f);
	}
	else if (input->IsPressingKey(Keyboard::D))
	{
		direction = 1;
		if (velocity.x < -RUN_SLOWDOWN)
		{
			velocity.x += RUN_SLOWDOWN * (can_jump ? 1.0f : 0.25f);
		}
		velocity.x = Math::Clamp(velocity.x + RUN_ACCELERATION, -4.0f, 4.0f);
	}
	else
	{
		velocity.x *= (can_jump ? 0.92f : 0.98f);
		// ^ more slowdown if player is floored
		if (velocity.x > -5e-1 && velocity.x < 5e-1) velocity.x = 0.0f;
		// ^ set x velocity to 0 if x velocity is very low
	}
	if (input->IsPressingKey(Keyboard::Space))
	{
		if (can_jump)
		{
			velocity.y = JUMP_POWER;
			can_jump = false;
		}
	}
	velocity.y += GRAVITY;
	position += velocity;//* deltaTime;

}
void Player::UseItem(Input* input, Butterfly* _gb[BUTTERFLY_LIMIT])
{
#ifndef DEBUG
	if (input->HasPressedKey(Keyboard::Numpad0))
	{
		Item::TurnItemToNewType(*inventory[0], 0);
	}
	else if (input->HasPressedKey(Keyboard::Numpad1))
	{
		Item::TurnItemToNewType(*inventory[1], 1);
	}
	else if (input->HasPressedKey(Keyboard::Numpad2))
	{
		Item::TurnItemToNewType(*inventory[2], 1);
	}
	else if (input->HasPressedKey(Keyboard::Numpad3))
	{
		Item::TurnItemToNewType(*inventory[3], 1);
	}
	else if (input->HasPressedKey(Keyboard::Numpad4))
	{
		Item::TurnItemToNewType(*inventory[4], 1);
	}
	else if (input->HasPressedKey(Keyboard::Numpad5))
	{
		Item::TurnItemToNewType(*inventory[5], 1);
	}
	else if (input->HasPressedKey(Keyboard::Numpad6))
	{
		Item::TurnItemToNewType(*inventory[6], 1);
	}
	else if (input->HasPressedKey(Keyboard::Numpad7))
	{
		Item::TurnItemToNewType(*inventory[7], 1);
	}
	else if (input->HasPressedKey(Keyboard::Numpad8))
	{
		Item::TurnItemToNewType(*inventory[8], 1);
	}
	else if (input->HasPressedKey(Keyboard::Numpad9))
	{
		Item::TurnItemToNewType(*inventory[9], 1);
	}
	else if (input->HasPressedKey(Keyboard::Add))
	{
		Item::TurnItemToNewType(*inventory[10], 1);
	}
	else if (input->HasPressedKey(Keyboard::F1))
	{
		Item::TurnItemToNewType(*inventory[11], 1);
	}
	else if (input->HasPressedKey(Keyboard::F2))
	{
		Item::TurnItemToNewType(*inventory[12], 1);
	}
	else if (input->HasPressedKey(Keyboard::F3))
	{
		Item::TurnItemToNewType(*inventory[13], 1);
	}
	else if (input->HasPressedKey(Keyboard::F4))
	{
		Item::TurnItemToNewType(*inventory[14], 1);
	}
#endif
#pragma region  ugly input stuff
	if (input->HasPressedKey(Keyboard::Left))
	{
		selected_item_slot--;
	}
	else if (input->HasPressedKey(Keyboard::Right))
	{
		selected_item_slot++;
	}
	if (input->HasPressedKey(Keyboard::Num1))
	{
		selected_item_slot = 0;
	}
	else if (input->HasPressedKey(Keyboard::Num2))
	{
		selected_item_slot = 1;
	}
	else if (input->HasPressedKey(Keyboard::Num3))
	{
		selected_item_slot = 2;
	}
	else if (input->HasPressedKey(Keyboard::Num4))
	{
		selected_item_slot = 3;
	}
	else if (input->HasPressedKey(Keyboard::Num5))
	{
		selected_item_slot = 4;
	}
	else if (input->HasPressedKey(Keyboard::Num6))
	{
		selected_item_slot = 5;
	}
	else if (input->HasPressedKey(Keyboard::Num7))
	{
		selected_item_slot = 6;
	}
	else if (input->HasPressedKey(Keyboard::Num8))
	{
		selected_item_slot = 7;
	}
	else if (input->HasPressedKey(Keyboard::Num9))
	{
		selected_item_slot = 8;
	}
#pragma endregion

	selected_item_slot = Math::Clamp(selected_item_slot, 0, 8);
	if (input->HasPressedKey(Keyboard::E))
		inventory_open = !inventory_open;
	if (input->HasPressedMouse(Mouse::Left) && !Item::ItemIsUsed(*items))
	{
		if (inventory[selected_item_slot]->type >= Item::ButterflyMonarch && inventory[selected_item_slot]->type <= Item::ButterflyGlass)
		{
			Butterfly::NewButterfly(GetCenter(), inventory[selected_item_slot]->type - 2, _gb);
			Item::ReduceStackSize(*inventory[selected_item_slot], 1);
		}
		else
		{
			Item::NewItem(GetCenter(), inventory[selected_item_slot]->type, *items);
		}
	}
}
void Player::Collision()
{
	if (position.x - width < 0.0f)
	{
		position.x = width;
		velocity.x = 0.0f;
	}

	else if (position.x + width > window_borders.x)
	{
		position.x = window_borders.x - width;
		velocity.x = 0.0f;
	}
	if (position.y + height > window_borders.y - 75.f) //75 is where the floor is at
	{
		position.y = window_borders.y - height - 75.f;
		can_jump = true;
		velocity.y = 0.0f;
	}
	frame.setPosition(position);
}
//TODO::
//Player stitching system, where different body parts can be animated, and stiched together
//Instead of having to re-draw the whole sprite

void Player::SetFrame()
{
	current_frame = 0;
	if (velocity.y != 0.0f)
	{
		current_frame = 1;
	}
	else if (velocity.x != 0.0f)
	{
		animation_time += 3;
		current_frame = (animation_time % (int)(height * TOTAL_FRAMES) < height * TOTAL_FRAMES / 2.0f) ? 2 : 3;
	}
	else
	{
		animation_time--;
		current_frame = 0;
	}
	if (Item::ItemIsUsed(*items))
	{
		current_frame += 4;
	}
	animation_time = Math::ResetValue<int>(animation_time, 0, (int)(height * TOTAL_FRAMES));
}

void Player::Update(float deltaTime, Input* input, Butterfly* _gb[BUTTERFLY_LIMIT])
{
	Movement(input);
	UseItem(input, _gb);
	Collision();
	SetFrame();
	if (Item::ItemIsUsed(*items))
	{
		Item::Update(deltaTime, *items, GetCenter());
		items->dirX = this->direction;
	}
}

Vector2f Player::GetCenter()
{
	return Vector2f(position.x + width / 2.f, position.y + height / 2.f);
}
Vector2f Player::GetItemPosition(Player& player)
{
	if (Item::ItemIsUsed(*player.items))
		return Item::GetPosition(*player.items);
	return Vector2f(-500.f, -500.f);
}

bool Player::GetCollision(Player& p, FloatRect other)
{
	if (Item::ItemIsUsed(*p.items))
		return Item::GetCollision(*p.items, other);
	return false;
}

void Player::SetItem(Item* inventory[INVENTORY_SIZE], unsigned char item_type)
{
	if (item_type >= Item::COUNT)
	{
		printf("Tried setting unexisting item!\n");
		return;
	}
	for (int i = 0u; i < INVENTORY_SIZE; i++)
	{
		if (inventory[i]->type >= Item::ButterflyMonarch && inventory[i]->type <= Item::ButterflyGlass)
			inventory[i]->max_stack = 30;
		if (inventory[i]->type == item_type && inventory[i]->stack < inventory[i]->max_stack)
		{
			inventory[i]->stack++;
			return;
		}
		if (inventory[i]->type == Item::COUNT)
		{
			inventory[i]->type = item_type;
			if (inventory[i]->type >= Item::ButterflyMonarch && inventory[i]->type <= Item::ButterflyGlass)
			{
				inventory[i]->max_stack = 30;
			}
			inventory[i]->stack = 1;
			return;
		}
	}
}
