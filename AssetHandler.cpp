#include "AssetHandler.h"

// Could go 2 ways with this:::
// a)
//	Instantiate all assets, and have getters return an asset
//	Good bc all assets can be accessed quickly
//	Bad because (video) memory
// b)
//	Load assets as needed, and discard if not in use 
//	Good because less memory overhead
//	Bad because could increase stuttering and memory leaks





AssetHandler::AssetHandler()
{
	std::string texture_path = "Assets/Text/BRADHITC.TTF";
	font = new Font();
	if (!font->loadFromFile(texture_path))
	{
		printf("Could not load font!\nMissing file:\n\t[%s]\n", texture_path.c_str());
	}
	player_texture = new Texture();
	texture_path = "Assets/Player_Frog.png";
	if (!player_texture->loadFromFile(texture_path))
	{
		printf("Could not load file!\nMissing file:\n\t[%s]\n", texture_path.c_str());
	}
	butterfly_textures.clear();
	for (int i = 0u; i < 4u; i++)
	{
		texture_path = "Assets/Butterfly_" + std::to_string(i) + ".png";
		Texture _t = Texture();
		if (!_t.loadFromFile(texture_path))
		{
			printf("Could not load file!\nMissing file:\n\t[%s]", texture_path.c_str());
		}
		butterfly_textures.push_back(_t);
	}
	for (int i = 0u; i < (sizeof(background_textures) / sizeof(*background_textures)); i++)
	{
		texture_path = "Assets/Background_" + std::to_string(i) + ".png";
		background_textures[i] = new Texture();
		if (!background_textures[i]->loadFromFile(texture_path))
		{
			printf("Could not load file!\nMissing file:\n\t[%s]", texture_path.c_str());
		}
	}
	for (int i = 0u; i < (sizeof(floor_textures) / sizeof(*floor_textures)); i++)
	{
		texture_path = "Assets/Floor_" + std::to_string(i) + ".png";
		floor_textures[i] = new Texture();
		if (!floor_textures[i]->loadFromFile(texture_path))
		{
			printf("Could not load file!\nMissing file:\n\t[%s]", texture_path.c_str());
		}
	}
	ui_textures.clear();
	for (int i = 0u; i < 2; i++)
	{
		texture_path = "Assets/UI_" + std::to_string(i) + ".png";
		Texture _t = Texture();
		if (!_t.loadFromFile(texture_path))
		{
			printf("Could not load file!\nMissing file:\n\t[%s]", texture_path.c_str());
		}
		ui_textures.push_back(_t);
	}
}

AssetHandler::~AssetHandler()
{
	delete font;
	delete player_texture;
	butterfly_textures.clear();
	ui_textures.clear();

	delete[] & butterfly_textures;
	for (int i = 0u; i < (sizeof(background_textures) / sizeof(*background_textures)); i++)
	{
		delete background_textures[i];
	}
	delete[] & background_textures;
	for (int i = 0u; i < (sizeof(floor_textures) / sizeof(*floor_textures)); i++)
	{
		delete floor_textures[i];
	}
	delete[] & floor_textures;

}

Texture* AssetHandler::GetTexture(AssetHandler* instance, int type, int _st = 0)
{
	switch (type)
	{
	case TextureTypes::Player:
		return instance->player_texture;
	case TextureTypes::Butterflies:
		return (_st >= 0 && _st <= instance->butterfly_textures.size()) ? &instance->butterfly_textures.at(_st) : &instance->butterfly_textures.at(_st);
	case TextureTypes::Backgrounds:
		return (_st >= 0 && _st <= (sizeof(background_textures) / sizeof(*background_textures))) ? instance->background_textures[_st] : instance->background_textures[0];
	case TextureTypes::Floors:
		return (_st >= 0 && _st <= (sizeof(floor_textures) / sizeof(*floor_textures))) ? instance->floor_textures[_st] : instance->floor_textures[0];
	case TextureTypes::UI:
		return (_st >= 0 && _st <= instance->ui_textures.size()) ? &instance->ui_textures.at(_st) : &instance->ui_textures.at(0);
	}
	return new Texture();
}
