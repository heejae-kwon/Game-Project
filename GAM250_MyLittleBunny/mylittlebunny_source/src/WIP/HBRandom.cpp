/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:		HBRandom.cpp
Language:		C++
Project:			GAM250
Author:			Name : HeeJae Kwon
Email:				sfhy33@gmail.com
Creation date:	2017.06.16
----------------------------------------------------------------------------*/
#include <WIP/HBRandom.hpp>
#include <cstdlib>
#include <ctime>

void BE::HBRandom::Seed(unsigned seed) {
	srand(seed);
}

void BE::HBRandom::Seed(void) {
	srand(static_cast<unsigned int>(time(NULL)));
}

const int BE::HBRandom::GetInt(void) {
	return static_cast<int>(rand());
}

const int BE::HBRandom::GetInt(int min, int max) {
	int range = max - min + 1;
	return static_cast<int>((rand() % range) + min);
}

const float BE::HBRandom::GetFloat(void) {
	return static_cast<float>(rand());
}

const float BE::HBRandom::GetFloat(float min, float max) {
	int range = static_cast<int>(max - min + 1);
	return static_cast<float>((rand() % range) + min);
}
