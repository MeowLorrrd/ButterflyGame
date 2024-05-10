#include "Player.h"

Player::Player()
{
	position = Vector2f(800.f, 450.f);
	if (!texture.loadFromFile("Assets/Player_Frog.png"))
		printf("Could not load player file!\n");
	width = DEFAULT_WIDTH;
	height = DEFAULT_HEIGHT / TOTAL_FRAMES;
	current_frame = 0;
	texture_rectangle = IntRect(0, 0, (int)width, (int)height);
	frame.setSize(Vector2f(width, height));
	frame.setOrigin(Vector2f(
		width / 2.0f,
		height / 2.0f));
	frame.setPosition(Vector2f(position));
	frame.setTexture(&texture);
	frame.setTextureRect(texture_rectangle);

	items = new Item();
	for (int i = 0u; i < INVENTORY_SIZE; i++)
	{
		inventory[i] = new Item();
	}
	selected_item_slot = 0;
	can_jump = false;
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
	//Draw Inventory (ALL ITEMS, if item type is Item::COUNT, draw emty slot
	for (int i = 0u; i < INVENTORY_SIZE; i++)
	{
		Item::DrawInventoryUI(render_target, render_states, *inventory[i], i, selected_item_slot);
	}
	for (int i = 0u; i < INVENTORY_SIZE; i++)
	{
		Item::DrawInventoryContents(render_target, render_states, *inventory[i], i);
	}
	if (items->item_use_delay > 0)
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
		if (velocity.x > -5e-2 && velocity.x < 5e-2) velocity.x = 0.0f;
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
void Player::UseItem(Input* input)
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
	if (input->HasPressedKey(Keyboard::Up))
	{
		selected_item_slot -= 5;
	}
	else if (input->HasPressedKey(Keyboard::Down))
	{
		selected_item_slot += 5;
	}
	else if (input->HasPressedKey(Keyboard::Left))
	{
		selected_item_slot--;
	}
	else if (input->HasPressedKey(Keyboard::Right))
	{
		selected_item_slot++;
	}
	if (selected_item_slot > 14)
	{
		selected_item_slot -= 15;
	}
	else if (selected_item_slot < 0)
	{
		selected_item_slot += 15;
	}
	if (input->HasPressedMouse(Mouse::Left))
	{
		if (items->item_use_delay > 0)//Can't use item if an item already exists
			return;
		Item::NewItem(GetCenter(), (Uint8)inventory[selected_item_slot]->type, *items);
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
	if (velocity.y != 0.0f)
	{
		current_frame = 1;
	}

	else if (items->item_use_delay > 0)
	{
		current_frame = 4;
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
	animation_time = Math::ResetValue<int>(animation_time, 0, (int)(height * TOTAL_FRAMES));
}

void Player::Update(float deltaTime, Input* input)
{
	Movement(input);
	UseItem(input);
	Collision();
	SetFrame();
	if (items->item_use_delay > 0)
	{
		Item::Update(deltaTime, *items, GetCenter());
		items->dirX = this->direction;
	}
}

Vector2f Player::GetCenter()
{
	return Vector2f(position.x + width / 2.f, position.y + height / 2.f);
}
Item* Player::GetItem(Player& player)
{
	return player.items;
}
Vector2f Player::GetItemPosition(Player& player)
{
	Item* item = GetItem(player);
	if (item->item_use_delay > 0)
		return Item::GetPosition(*item);
	return Vector2f(-500.f, -500.f);
}

Vector2f Player::GetItemSize(Player& player)
{
	Item* item = GetItem(player);
	if (item->item_use_delay > 0)
		return Item::GetSize(*item);
	return Vector2f(0.0f, 0.0f);
}
bool Player::GetCollision(Player& p, FloatRect other)
{
	Item* item = GetItem(p);
	if (item->item_use_delay > 0)
		return Item::GetCollision(*item, other);
	return false;
}