#include "LogicCore.hpp"
#include <Actor.hpp>
#include <memory>

LogicCore * LogicCore::instance()
{
	static std::unique_ptr<LogicCore> instance(new LogicCore());
	return instance.get();
}

LogicCore::~LogicCore()
{
}

void LogicCore::Update(float dt)
{
		std::vector<Actor*> actorVec = getRegisteredActors();
		for (auto& actor : actorVec){
				if (actor->isActive == true && actor->isPaused == false) {
						Component::Logic* plogic = actor->getComponent<Component::Logic>();
						if (plogic->m_isActive == true) {
								plogic->Update(dt);
						}
				}
		}
}

LogicCore::LogicCore()
{
}
