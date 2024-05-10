#ifndef _COLLISION_
#define _COLLISION_
#include <SFML/System/Vector2.hpp>
#include <stdio.h>

using namespace sf;
//
namespace Collision
{
	//Checks if two targets are colliding
	//Scale should be factored in width and height
	[[deprecated("Use GetGlobalBounds() instead.")]]
	static bool IsColliding(Vector2f source, float source_width, float source_height, Vector2f target, float target_width, float target_height)
	{
		bool a = target.x > source.x;
		bool b = target.x < source.x + source_width;
		bool c = target.x + target_width > source.x;
		bool d = target.x + target_width < source.x + source_width;
		bool e = target.y > source.y;
		bool f = target.y < source.y + source_height;
		bool g = target.y + target_height > source.y;
		bool h = target.y + target_height < source.y + source_height;
		//printf("\n\na:\t%i\nb:\t%i\nc:\t%i\nd:\t%i\ne:\t%i\nf:\t%i\ng:\t%i\nh:\t%i\n", a, b, c, d, e, f, g, h);
		return ((a && b) || (c && d)) && ((e && f) || (g && h));
	}
	//Checks if two targets are colliding
	//[...]_size should be factored with scale
	static bool IsColliding(Vector2f source, Vector2f source_size, Vector2f target, Vector2f target_size)
	{
		bool a = target.x > source.x;
		bool b = target.x < source.x + source_size.x;
		bool c = target.x + target_size.x > source.x;
		bool d = target.x + target_size.x < source.x + source_size.x;
		bool e = target.y > source.y;
		bool f = target.y < source.y + source_size.y;
		bool g = target.y + target_size.y > source.y;
		bool h = target.y + target_size.y < source.y + source_size.y;
		//printf("\n\na:\t%i\nb:\t%i\nc:\t%i\nd:\t%i\ne:\t%i\nf:\t%i\ng:\t%i\nh:\t%i\n", a, b, c, d, e, f, g, h);
		return ((a && b) || (c && d)) && ((e && f) || (g && h));
	}
}
#endif
