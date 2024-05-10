#ifndef _BACKGROUND_H
#define _BACKGROUND_H

#include "math.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

using namespace sf;

class Background
{
public:
	Background();
	virtual ~Background();
	const enum BGTYPES
	{
		CLOUDYDAY = 0
	};
	const enum FLOORTYPES
	{
		DIRTY = 0
	};
	//The current active background
	unsigned short BG_Active;
	//Used for parallex background effect (UNFINISHED)
	void Update(float deltaTime, RenderWindow& render_window);
	void Draw(RenderWindow& render_target, RenderStates render_states) const;
private:
	//All the textures for the backgrounds
	//Only 1 texture instance can exist, as only 1 background can exist
	Texture* background_textures[1];
	Texture* floor_textures[1];

	RectangleShape background, floor;
};
#endif
