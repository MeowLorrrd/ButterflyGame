#include "Item.h"

Item::Item()
{
	std::string asset_path;
	for (int i = 0u; i < sizeof(textures) / sizeof(*textures); i++)
	{
		asset_path = "Assets/Item_" + std::to_string(i) + ".png";
		textures[i] = new Texture();
		if (!textures[i]->loadFromFile(asset_path))
			printf("Could not load texture!\nMissing texture: [Item_%i.png]", i);
	}
	inv_texture = new Texture();
	if (!inv_texture->loadFromFile("Assets/Inventory_Slot.png"))
		printf("Could not load texture!\nMissing texture: [Inventory_Slot.png]");
	inventory_frame.setTexture(inv_texture);
	inv_texture_s = new Texture();
	if (!inv_texture_s->loadFromFile("Assets/Inventory_Slot_Selected.png"))
		printf("Could not load texture!\nMissing texture: [Inventory_Slot_Selected.png]");

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
}
Item::~Item()
{
	for (int i = 0u; i < sizeof(textures) / sizeof(*textures); i++)
	{
		delete textures[i];
	}
	delete[] & textures;
	delete inv_texture;
	delete inv_texture_s;
}

void Item::DrawInventoryUI(RenderWindow& render_window, RenderStates render_states, Item& _inv, unsigned int slot_type, unsigned int s_item)
{
	float x = 68.f * (slot_type % 5) + 24.f;
	float y = 68.f * (slot_type % 3) + 24.f;
	_inv.inventory_frame.setTexture(_inv.inv_texture);
	_inv.inventory_frame.setSize(Vector2f(64.f, 64.f));
	_inv.inventory_frame.setPosition(Vector2f(x, y));
	render_window.draw(_inv.inventory_frame, render_states);
	x = 68.f * static_cast<int>(s_item % 5) + 24.f;
	y = 68.f * static_cast<int>(s_item / 5.f) + 24.f;
	_inv.inventory_frame.setTexture(_inv.inv_texture_s);
	_inv.inventory_frame.setPosition(Vector2f(x, y));
	render_window.draw(_inv.inventory_frame, render_states);
}
void Item::DrawInventoryContents(RenderWindow& render_window, RenderStates render_states, Item& _inv, unsigned int slot_type)
{
	if (_inv.type >= 0 && _inv.type < COUNT)
	{
		_inv.frame.setTexture(_inv.textures[_inv.type]);
		_inv.frame.setSize(Vector2f(44.f, 44.f));
		float x = 68.f * static_cast<int>(slot_type % 5) + 34.f;
		float y = 68.f * static_cast<int>(slot_type / 5.f) + 34.f;
		_inv.frame.setPosition(Vector2f(x, y));
		render_window.draw(_inv.frame, render_states);
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
	_item.frame.setTexture(_item.textures[_item.type]);
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
	};
}
void Item::TurnItemToNewType(Item& old, unsigned short new_type)
{
	old.type = (new_type < COUNT) ? new_type : 0;
	if (old.type >= Item::BUTTERFLYMONARCH && old.type <= Item::BUTTERFLYGLASS) old.max_stack = 30;
	old.frame.setTexture(old.textures[old.type]);
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
