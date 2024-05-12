#include "Butterfly.h"

Butterfly::Butterfly(AssetHandler* _ah)
{
	std::string texture_path;
	//for (int i = 0u; i < _textures->size(); i++)
	//{
	//	//texture_path = "Assets/Butterfly_" + std::to_string(i) + ".png";
	//	//textures.resize(_textures.max_size());
	//	textures.assign(0, _textures->at(i));
	//	//textures[i] = std::unique_ptr<Texture>(&_textures.at(i));
	//	//if (!textures[i]->loadFromFile(texture_path))
	//	//	printf("Could not load texture!\nMissing texture: [Butterfly_%i.png]", i);
	//}
	asset_handler = _ah;
	position = Vector2f();
	is_active = false;
	unique_id = 0;
	dirX = 1;
	dirY = 1;
	type = 0;
	newX = 800.f;
	newY = 450.f;
	custom_ai[0] = 0.0f;
	custom_ai[1] = 0.0f;
	//animation_timer_speed = 1.0f;
	animation_timer = 0;
}

Butterfly::~Butterfly()
{
	//for (int i = 0u; i < sizeof(textures) / sizeof(*textures); i++)
	{
		//textures.clear();
	}
	//delete[] & textures;
}
//Drawing all active Butterflies to screen
void Butterfly::Draw(RenderWindow& render_target, RenderStates render_states, Butterfly& butterfly)
{
	butterfly.UpdateFrame(butterfly);
	render_target.draw(butterfly.frame, render_states);
}
void Butterfly::UpdateFrame(Butterfly& butterfly)
{
	switch (butterfly.type)
	{
	case MONARCH:
	case GOLDEN:
	case NEBULA:
	case GLASSWING:
		butterfly.animation_timer = Math::ResetValue<int>(butterfly.animation_timer + 1, 0, 9);
		if (butterfly.animation_timer > 8)
		{
			butterfly.current_frame = Math::ResetValue<int>(butterfly.current_frame + 1, 0, 2);
		}
		break;
	}
	butterfly.animated_frame.top = butterfly.current_frame * static_cast<int>(butterfly.height);
	butterfly.frame.setTextureRect(butterfly.animated_frame);
	butterfly.frame.setScale(butterfly.scale * butterfly.dirX, butterfly.scale * butterfly.dirY);
	butterfly.frame.setRotation(butterfly.rotation);
}

void Butterfly::Update(float deltaTime, Butterfly& butterfly)
{
	Butterfly::AI(butterfly);
	Butterfly::Movement(deltaTime, butterfly);
}
void Butterfly::AI(Butterfly& butterfly)
{
	butterfly.alive_timer++;
}
//Movement system, moves butterflies. Butterflies are moved in here
void Butterfly::Movement(float dt, Butterfly& butterfly)
{
	butterfly.old_velocity = butterfly.velocity;
	//Timer for idle butterflies, they continue roaming if timer reaches limit
	float idle_time = 6.f * 60.f;

	if (butterfly.unique_id == 0)
	{
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
		butterfly.frame.setOutlineColor(Color::Color(255, 0, 0, 255));			//
		butterfly.frame.setOutlineThickness(2.f);								//
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
	}

	switch (butterfly.type)
	{
	case MONARCH:
	case GOLDEN:
	case NEBULA:
	case GLASSWING:
		idle_time = Random::NextInt(6, 11) * 60.f;
		if (butterfly.custom_ai[0] >= idle_time || butterfly.alive_timer == 1)
		{
			butterfly.newX = (float)Random::NextInt(10, 1590);
			butterfly.newY = (float)Random::NextInt(750, 800);
			butterfly.custom_ai[0] = 0.0f;
		}
		else if (Math::Vec2Distance(butterfly.GetCenter(butterfly), Vector2f(butterfly.newX, butterfly.newY)) < 200.f)
		{
			butterfly.custom_ai[0]++;
		}
		if (Math::Vec2Distance(butterfly.GetCenter(butterfly), Vector2f(butterfly.newX, butterfly.newY)) > 200.f && Math::Vec2Length(butterfly.velocity) < 240.f)
		{
			butterfly.velocity.x += 3.2f * (butterfly.newX > butterfly.GetCenter(butterfly).x ? 1 : -1);
			butterfly.velocity.y += 1.5f * (butterfly.newY > butterfly.GetCenter(butterfly).y ? 1 : -1);
			//butterfly.animation_timer_speed += 0.2f;
		}
		else
		{
			butterfly.velocity *= 0.9f;
			//butterfly.animation_timer_speed = 1.0f;
		}
		break;
	}
	butterfly.position += butterfly.velocity * dt;
	butterfly.dirX = (butterfly.velocity.x > 0.0f) ? 1 : -1;
	butterfly.frame.setPosition(butterfly.position);
}
int Butterfly::NewButterfly(Vector2f xy, unsigned char type, Butterfly* butterflies[BUTTERFLY_LIMIT])
{
	int new_id = -1;
	for (int i = 0u; i < BUTTERFLY_LIMIT; i++)
	{
		if (!butterflies[i]->is_active)
		{
			new_id = i;
			break;
		}
	}
	if (new_id > -1)
	{
		butterflies[new_id]->unique_id = new_id;

		butterflies[new_id]->newX = 800.f;
		butterflies[new_id]->newY = 450.f;
		butterflies[new_id]->custom_ai[0] = 0.0f;
		butterflies[new_id]->custom_ai[1] = 0.0f;
		butterflies[new_id]->animation_timer = 0;
		butterflies[new_id]->type = type;
		butterflies[new_id]->is_active = true;
		butterflies[new_id]->position = xy;
		butterflies[new_id]->dirX = 1;
		butterflies[new_id]->dirY = 1;
		butterflies[new_id]->alive_timer = 0;
		butterflies[new_id]->frame.setTexture(AssetHandler::GetTexture(butterflies[new_id]->asset_handler, AssetHandler::Butterflies, type));
		butterflies[new_id]->current_frame = 0;
		butterflies[new_id]->width = 12.f;
		butterflies[new_id]->height = 36.f / 3.f;
		butterflies[new_id]->scale = 1.f + (Random::NextInt(75, 200) / 100.f);

		switch (butterflies[new_id]->type)
		{
		case MONARCH:
			butterflies[new_id]->item_type = 2;
			break;
		case GOLDEN:
			butterflies[new_id]->scale = 1.f + (Random::NextInt(50, 175) / 100.f);
			butterflies[new_id]->item_type = 3;
			break;
		case NEBULA:
			butterflies[new_id]->item_type = 4;
			break;
		case GLASSWING:
			butterflies[new_id]->item_type = 5;
			break;
		}

		butterflies[new_id]->animated_frame = IntRect(0, butterflies[new_id]->current_frame, (int)butterflies[new_id]->width, (int)butterflies[new_id]->height);
		butterflies[new_id]->frame.setSize(Vector2f(butterflies[new_id]->width, butterflies[new_id]->height));
		butterflies[new_id]->frame.setOrigin(butterflies[new_id]->width / 2.0f, butterflies[new_id]->height / 2.0f);
		butterflies[new_id]->frame.setTextureRect(butterflies[new_id]->animated_frame);
		butterflies[new_id]->frame.setScale(butterflies[new_id]->scale * butterflies[new_id]->dirX, butterflies[new_id]->scale * butterflies[new_id]->dirY);
		return butterflies[new_id]->unique_id;
	}
	return BUTTERFLY_LIMIT;
}

//(Unfinished) NPC spawner
//Spawns a new Butterfly outside of the screen
//
//	TODO::
//	-Make Butterflies have different spawn conditions, based on time, weather and Player progression
//	-Make Butterflies spawn in different positions, rather than a fixed position outside the screen
void Butterfly::SpawnButterflyNatural(int chance, Butterfly* butterflies[BUTTERFLY_LIMIT])
{
	if (chance < 1) return; // Disable spawning
	if (Random::NextBool(chance))
	{
		if (Random::NextBool(50))
			NewButterfly(Vector2f(-100.f, 500.f), GOLDEN, butterflies);
		else if (Random::NextBool(3))
			NewButterfly(Vector2f(-100.f, 500.f), MONARCH, butterflies);
		else if (Random::NextBool(2))
			NewButterfly(Vector2f(-100.f, 500.f), NEBULA, butterflies);
		else
			NewButterfly(Vector2f(-100.f, 500.f), GLASSWING, butterflies);
	}
}
void Butterfly::KillButterfly(Butterfly* butterflies[BUTTERFLY_LIMIT], unsigned char _id)
{
	butterflies[_id]->type = Butterfly::TYPES::COUNT;
	butterflies[_id]->is_active = false;

	/*Butterfly* _butterfly[BUTTERFLY_LIMIT]{};
	for (int i = 0u; i < BUTTERFLY_LIMIT; i++)
	{
		_butterfly[i] = butterflies[i];
	}

	for (int i = _id + 1; i < BUTTERFLY_LIMIT; i++)
	{
		if (!_butterfly[i]->is_active)
			return;
		butterflies[_id] = _butterfly[i];
	}*/

}
Vector2f Butterfly::GetCenter(Butterfly& butterfly)
{
	return Vector2f(butterfly.position.x + butterfly.width / butterfly.scale / 2.f, butterfly.position.y + butterfly.height / butterfly.scale / 2.f);
}
Vector2f Butterfly::GetSize(Butterfly& butterfly)
{
	return Vector2f(butterfly.width * butterfly.scale, butterfly.height * butterfly.scale);
}
Vector2f Butterfly::GetPosition(Butterfly& butterfly)
{
	return Vector2f(butterfly.position);
}
FloatRect Butterfly::GetGlobalBounds(Butterfly& butterfly)
{
	return FloatRect(butterfly.frame.getGlobalBounds());
}
unsigned char Butterfly::GetItemType(Butterfly& butterfly)
{
	return (unsigned char)butterfly.item_type;
}
