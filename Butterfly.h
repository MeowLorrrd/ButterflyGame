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

using namespace sf;

class Butterfly
{
public:
	Butterfly(bool first_init);
	virtual ~Butterfly();
	static void Draw(RenderWindow& render_target, RenderStates render_states, Butterfly& butterfly);
	static void Update(float deltaTime, Butterfly& butterfly);
	//Spawning function for new butterflies
	//The returned integer can be used to directly modify the butterfly
	//Example: 
	//	int temp = NewButterfly(...);
	//	Butterflies[temp]->... = ...;
	static int NewButterfly(Vector2f start_pos, unsigned short type, Butterfly* butterflies[BUTTERFLY_LIMIT]);

	static void SpawnButterflyNatural(int chance, Butterfly* butterflies[BUTTERFLY_LIMIT]);

	const enum TOITEMTYPE //TODO:: Add items that the Butterflies can convert into upon being caught by the Player
	{

	};
	//Types of butterflies
	const enum TYPES
	{
		MONARCH = 0,
		GOLDEN = 1,
		NEBULA = 2,
		GLASSWING = 3
	};
	bool is_active;
	//Returns center of the butterfly
	static Vector2f GetCenter(Butterfly& butterfly);
	//Returns width and height, multiplied by scale
	static Vector2f GetSize(Butterfly& butterfly);
	//Returns the top-left position of the butterfly
	static Vector2f GetPosition(Butterfly& butterfly);
	static FloatRect GetGlobalBounds(Butterfly& butterfly);
private:
	Vector2f velocity, old_velocity;
	Vector2f position;
	Texture* textures[2]; // Access textures with Butterfly [TYPES]
	RectangleShape frame; //Frame that is drawn to window
	IntRect animated_frame; //Current frame that will be drawn

	Uint16 type; 
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
