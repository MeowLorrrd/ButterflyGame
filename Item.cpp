#include "Item.h"

Item::Item(AssetHandler* _ah)
{
	asset_handler = _ah;

	inventory_sprite.setTexture(*AssetHandler::GetTexture(_ah, AssetHandler::UI, AssetHandler::UITypes::InventorySlot));
	inventory_sprite.setScale(Vector2f(2.5f, 2.5f));
	inventory_sprite_s.setTexture(*AssetHandler::GetTexture(_ah, AssetHandler::UI, AssetHandler::UITypes::InventorySlotSelected));
	inventory_sprite_s.setScale(Vector2f(2.51f, 2.51f));

	type = COUNT;
	item_use_delay = 0;
	item_use_offset = Vector2f();
	item_use_type = 0;
	position = Vector2f();
	rotation = 0.f;
	dirX = 1;
	width = 0.0f;
	height = 0.0f;
	scale = 0.0f;
	stack = 0;
	max_stack = 1;
	inventory_stack_text.setFont(*AssetHandler::GetFont(asset_handler));
}
Item::~Item()
{
	
}

void Item::DrawInventoryUI(RenderWindow& render_window, RenderStates render_states, Item& _inv, unsigned int slot_type, unsigned int s_item, bool full_ui)
{
	float x = 84.f * (slot_type % 9) + 28.f;
	float y = 84.f * (slot_type % 4) + 28.f;
	_inv.inventory_sprite.setPosition(Vector2f(x, y));
	if (slot_type % 4 == 0)
	{
		_inv.inventory_sprite.setColor(Color::Color(0, 175, 175));
	}
	if (full_ui)
		render_window.draw(_inv.inventory_sprite, render_states);
	else if (slot_type % 4 == 0)
		render_window.draw(_inv.inventory_sprite, render_states);
	x = 84.f * static_cast<int>(s_item % 9) + 28.f;
	y = 84.f * static_cast<int>(s_item / 9.f) + 28.f;
	_inv.inventory_sprite_s.setTexture(*AssetHandler::GetTexture(_inv.asset_handler, AssetHandler::UI, AssetHandler::UITypes::InventorySlotSelected));
	_inv.inventory_sprite_s.setPosition(Vector2f(x, y));
	render_window.draw(_inv.inventory_sprite_s, render_states);
}
void Item::DrawInventoryContents(RenderWindow& render_window, RenderStates render_states, Item& _inv, unsigned int slot_type, bool full_ui)
{
	if (_inv.type >= 0 && _inv.type < COUNT)
	{
		_inv.frame.setTexture(AssetHandler::GetTexture(_inv.asset_handler, AssetHandler::Items, _inv.type));
		_inv.frame.setSize(Vector2f(56.f, 56.f));
		float x = 84.f * static_cast<int>(slot_type % 9) + 40.f;
		float y = 84.f * static_cast<int>(slot_type / 9.f) + 40.f;
		_inv.frame.setPosition(Vector2f(x, y));
		if (_inv.max_stack != 1)
		{
			std::string stacksize = std::to_string(_inv.stack);
			_inv.inventory_stack_text.setString(stacksize);
			_inv.inventory_stack_text.setCharacterSize(36u);
			_inv.inventory_stack_text.setPosition(x + 24.0f, y + 18.0f);
		}
		if (full_ui)
		{
			render_window.draw(_inv.frame, render_states);
			render_window.draw(_inv.inventory_stack_text, render_states);
		}

		else if (slot_type < 9)
		{
			render_window.draw(_inv.frame, render_states);
			render_window.draw(_inv.inventory_stack_text, render_states);
		}
	}
}
void Item::DrawInWorld(RenderWindow& render_window, RenderStates render_states, Item& _item, Vector2f xy)
{
	if (_item.type >= 0 && _item.type < COUNT)
	{
		_item.frame.setPosition(_item.position);
		_item.frame.setRotation(_item.rotation);
		_item.frame.setScale(Vector2f(_item.dirX, 1.f));

		_item.frame.setOutlineColor(Color::Color(255, 0, 0, 255));
		_item.frame.setOutlineThickness(1.f);
		render_window.draw(_item.frame, render_states);
	}
}

void Item::Update(float deltaTime, Item& _item, Vector2f xy)
{
	_item.item_use_delay--;
	if (_item.item_use_delay < 1)
		return;
	_item.position = Vector2f(
		_item.dirX == 1 ?
		xy.x - _item.item_use_offset.x :
		xy.x - _item.item_use_offset.x * 2.f,
		xy.y - _item.item_use_offset.y);
	switch (_item.type)
	{
	case BASICBUGNET:
		_item.rotation = (360.f * sin(-(float)_item.item_use_delay / 90.f) + 90.f) * (float)_item.dirX;
		break;
	}
}
void Item::NewItem(Vector2f xy, Uint8 _type, Item& _item)
{
	_item.type = _type;
	_item.position = xy;
	_item.rotation = -40.0f;
	_item.frame.setTexture(AssetHandler::GetTexture(_item.asset_handler, AssetHandler::Items, _item.type));
	switch (_item.type)
	{
	case BASICBUGNET:
		_item.item_use_delay = 30;
		_item.item_use_offset = Vector2f(8.5f, 44.f);
		_item.width = 64.f;
		_item.height = 64.f;
		_item.scale = 1.0f;
		_item.frame.setOrigin(Vector2f(0.f, _item.height));
		_item.frame.setSize(Vector2f(_item.width, _item.height));
		break;
	case NETBOMB:
		break;
	case BUTTERFLYMONARCH:
		//spawn butterfly manually
		break;
	};
}
void Item::TurnItemToNewType(Item& old, unsigned short new_type)
{
	old.type = (new_type < COUNT) ? new_type : 0;
	if (old.type >= Item::BUTTERFLYMONARCH && old.type <= Item::BUTTERFLYGLASS) old.max_stack = 30;
	old.frame.setTexture(AssetHandler::GetTexture(old.asset_handler, AssetHandler::Items, old.type));
}

Vector2f Item::GetPosition(Item& item)
{
	return Vector2f(item.position);
}

Vector2f Item::GetSize(Item& item)
{
	return Vector2f(item.width * item.scale, item.height * item.scale);
}

bool Item::GetCollision(Item& item, FloatRect other)
{
	return item.frame.getGlobalBounds().intersects(other);
}

bool Item::ItemIsUsed(Item& item)
{
	return item.item_use_delay > 0;
}
