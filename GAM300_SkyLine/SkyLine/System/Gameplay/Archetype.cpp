#include "Archetype.hpp"
#include "Actor.hpp"

Archetype::Archetype()
{
}

Archetype::~Archetype()
{
}

Actor* Archetype::GetActor(void)
{
	return a_actor;
}