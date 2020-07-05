#include "ObjectManager.hpp"
#include "Actor.hpp"
#include "Archetype.hpp"

ObjectManager * ObjectManager::instance()
{
		static std::unique_ptr<ObjectManager> instance(new ObjectManager());
	return instance.get();
}

ObjectManager::ObjectManager()
{
}

//ObjectManager * ObjectManager::instance()
//{
//	static std::unique_ptr<ObjectManager> instance(new ObjectManager());
//	return instance.get();
//}

ObjectManager::~ObjectManager()
{
	Reset();
}

Actor * ObjectManager::CreateActorwithArchetype(std::string archName)
{
	 Archetype* archeType = FindArchetypebyName(archName);
	Actor* newActor = CreateActor(archName,true);
	newActor = archeType->GetActor();

	return newActor;
}

Archetype * ObjectManager::FindArchetypebyName(std::string archName)
{
	for (auto & archeType : m_archVec)
	{
		if (archeType->a_name == archName)
		{
			return archeType.get();
		}
	}
	return nullptr;
}

Actor * ObjectManager::CreateActor(std::string name, bool isActive, Json::Value* data_)
{
	Actor* newActor = Actor::CreateActor(name, isActive , data_);
	m_actorVec.push_back(newActor);

	return newActor;
}

std::vector<Actor*>& ObjectManager::getActorVec(void)
{
	return m_actorVec;
}

void ObjectManager::Reset() {
		if (m_actorVec.size() != 0) {
				for (auto& actor : m_actorVec) {
						delete actor;
						actor = nullptr;
				}
				m_actorVec.clear();
				m_archVec.clear();
		}
}

Actor * ObjectManager::FindActorbyName(std::string actorName)
{
	for (auto & archeType : m_actorVec)
	{
		if (archeType->name == actorName)
		{
			return archeType;
		}
	}
	return nullptr;
}
