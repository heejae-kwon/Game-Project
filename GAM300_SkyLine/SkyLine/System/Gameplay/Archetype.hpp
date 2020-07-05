#pragma once

#include <string>

class Actor; // Predeclaration

class Archetype
{
public:
	Archetype();
	~Archetype();

	Actor* GetActor(void);
	std::string a_name;

private:
	//std::string a_name; // name of Archetype
	Actor* a_actor;        // saved with informations for this Archetype
};

