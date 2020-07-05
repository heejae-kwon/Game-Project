#pragma once

#include <vector>
#include <string>
#include <json.h> 

class Actor;
class Archetype;

class ObjectManager
{
public:
	static ObjectManager* instance();
//	ObjectManager();
	~ObjectManager();

	using ArchetyperSmartPtr = std::unique_ptr<Archetype>;

	Actor* CreateActorwithArchetype(std::string archName);

	Actor* FindActorbyName(std::string actorName);
	Archetype* FindArchetypebyName(std::string archName);
	Actor * CreateActor(std::string name, bool isActive = true, Json::Value * data_ = nullptr);
	std::vector<Actor*>& getActorVec(void);
	void Reset();

private:
	ObjectManager();

	std::vector<Actor*>		 m_actorVec;
	std::vector<ArchetyperSmartPtr>  m_archVec;
};