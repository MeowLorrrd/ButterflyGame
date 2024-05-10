#ifndef _MATH_
#define _MATH_
#include <cmath>
#include <SFML/System/Vector2.hpp>
namespace Math
{
	static float Lerp(float a, float b, float c)
	{
		return a * (1.0f - c) + (b * c);
	}
	//"Clamps" a value between a minimum and maximum value
	//The value will never go over the limited values
	static float Clamp(float value, float minvalue, float maxvalue)
	{
		return (value < minvalue) ? minvalue : ((value > maxvalue) ? maxvalue : value);
	}
	//Returns a value that resets to a minimum value if the maximum has been reached
	template<typename T>
	static T ResetValue(T value, T minvalue, T maxvalue)
	{
		return (value < minvalue) ? maxvalue : ((value > maxvalue) ? minvalue : value);
	}

	//I did not know there was a standard lib for these functions...

	template<typename T>
	static T Min(T one, T two)
	{
		return (one < two) ? one : two;
	}
	template<typename T>
	static T Max(T one, T two)
	{
		return (one > two) ? one : two;
	}
	static float Sqrt(float x)
	{
		if (x <= 0.f) return 0.f;
		return pow(x, 0.5f);
	}
	static float Vec2Length(sf::Vector2f v2)
	{
		return Sqrt(v2.x * v2.x + v2.y * v2.y);
	}
	static float Vec2LengthSqrt(sf::Vector2f v2)
	{
		return v2.x * v2.x + v2.y * v2.y;
	}
	static float Vec2Distance(sf::Vector2f position_1, sf::Vector2f position_2)
	{
		return Sqrt(((position_1.x - position_2.x) * (position_1.x - position_2.x)) + ((position_1.y - position_2.y) * (position_1.y - position_2.y)));
	}
	static float Vec2DistanceSqrt(sf::Vector2f position_1, sf::Vector2f position_2)
	{
		return ((position_1.x - position_2.x) * (position_1.x - position_2.x)) + ((position_1.y - position_2.y) * (position_1.y - position_2.y));
	}
}
#endif
