#ifndef _RANDOM_
#define _RANDOM_
#include "Math.cpp"
#include <stdexcept>
#include <random>
//Randomizer class
namespace Random
{
	//Returns an unseeded random integer, based on input, with the max-range input being 1 lower in the returned value
	//	Ex:	Random::NextInt(4, 9) returns a value between 4 and 8
	//		Random::NextInt(-9, 4) returns a value between -9 and 3
	static int NextInt(int min_value, int max_value)
	{
		if (min_value >= max_value) throw std::invalid_argument("Minimal value should be higher than maximum value");
		return (std::rand() % (max_value - min_value)) + min_value;
	}
	//Unseeded random boolean based on chance ( 1 / input )
	//	Example: Random::NextBool(2) returns true with a 1/2 chance
	static bool NextBool(int chance)
	{
		chance = Math::Max(chance, 0); //Making sure that 'chance' can never be lower than zero
		return std::rand() % chance == 0;
	}
	/*
	static int NextOfArray(int value[])
	{
		return value[std::rand() % (sizeof(value) / sizeof(*value))];
	}
	static float NextOfArray(float value[])
	{
		return value[std::rand() % (sizeof(value) / sizeof(*value))];
	}
	*/
	// ^^ this does not work... yet
	// But arr[sizeof(...)/sizeof(*...)] can be used anyway
}
#endif // ! _RANDOM_
