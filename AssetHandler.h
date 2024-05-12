#ifndef _ASSETHANDLER_H
#define _ASSETHANDLER_H
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

using namespace sf;

class AssetHandler
{
public:
	AssetHandler();
	virtual ~AssetHandler();
	static Texture* GetTexture(AssetHandler* instance, int texture_type, int specific_type);
	static Text* GetText(AssetHandler instance);

	enum TextureTypes
	{
		Player,
		Butterflies,
		Backgrounds,
		Floors,
		UI
	};
	enum ButterflyTypes
	{
		Monarch,
		Golden,
		Nebula,
		Glass
	};
	enum BackgroundTypes
	{
		Normal
	};
	enum FloorTypes
	{
		Grass
	};
	enum UITypes
	{
		InventorySlot,
		InventorySlotSelected
	};
private:
	Font* font;
	Texture* player_texture;
	std::vector<Texture> butterfly_textures;
	Texture* background_textures[1];
	Texture* floor_textures[1];
	std::vector<Texture> ui_textures;
};
#endif
