#ifndef _BASE_BUTTERFLY_H
#define _BASE_BUTTERFLY_H
// Maximum amount of Butterflies that can exist at once
constexpr unsigned short BUTTERFLY_LIMIT = 30u;

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Math.cpp"
#include "Random.cpp"
#include "Collision.cpp"
#include "Player.h"
#include <memory>

using namespace sf;

class Butterfly
{
public:
	Butterfly(AssetHandler* asset_handler);
	virtual ~Butterfly();
	bool is_active;
	static void Draw(RenderWindow& render_target, RenderStates render_states, Butterfly& butterfly);
	static void Update(float deltaTime, Butterfly& butterfly);
	//Spawning function for new butterflies
	//The returned integer can be used to directly modify the butterfly
	//Example: 
	//	int temp = NewButterfly(...);
	//	Butterflies[temp]->... = ...;
	static int NewButterfly(Vector2f start_pos, unsigned char type, Butterfly* butterflies[BUTTERFLY_LIMIT]);

	//Let the game randomly spawn a butterfly
	//'chance' sets the spawn chance, so chance = 60 would spawn every 60 frames on average
	static void SpawnButterflyNatural(int chance, Butterfly* butterflies[BUTTERFLY_LIMIT]);
	//'Kills' a butterfly, rendering it inactive and freeing a slot
	static void KillButterfly(Butterfly* butterflies[BUTTERFLY_LIMIT], unsigned char unique_id);
	//Types of butterflies
	const enum TYPES
	{
		Monarch = 0,
		Golden = 1,
		Nebula = 2,
		Glasswing = 3,
		COUNT = 4
	};
	//Returns center of the butterfly
	static Vector2f GetCenter(Butterfly& butterfly);
	//Returns width and height, multiplied by scale
	static Vector2f GetSize(Butterfly& butterfly);
	//Returns the top-left position of the butterfly
	static Vector2f GetPosition(Butterfly& butterfly);
	static FloatRect GetGlobalBounds(Butterfly& butterfly);
	static unsigned char GetItemType(Butterfly& butterfly);
private:
	Vector2f velocity, old_velocity;
	Vector2f position;
	std::vector<Texture> textures; // Access textures with Butterfly [TYPES]
	RectangleShape frame; //Frame that is drawn to window
	IntRect animated_frame; //Current frame that will be drawn
	AssetHandler* asset_handler;

	unsigned char type; //Type of butterfly
	unsigned char item_type; //Item type that butterfly converts into
	unsigned int current_frame,
		alive_timer,
		animation_timer;
	unsigned char unique_id; //Ranges from 0 through 29. Only 1 number can be in use

	float custom_ai[2]; //Used for type-specific actions
	float width; //Width of butterfly
	float height; //Height of butterfly
	float scale; //Scale of butterfly

	float rotation,
		newX,
		newY;
	//Used for flipping Butterfly horizontally or vertically
	//Values should either be 1 or -1
	Int8 dirX, dirY;
	static void AI(Butterfly& butterfly);
	static void Movement(float deltaTime, Butterfly& butterfly);
	static void UpdateFrame(Butterfly& butterfly);
};
#endif

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// https://leafyplace.com/types-of-butterflies/  //
// Link to list of real-life butterflies         //
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
