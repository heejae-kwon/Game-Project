#include "BaseCore.hpp"

void BaseCore::Initialize(void)
{
}

void BaseCore::registerActor(Actor * actor)
{
	_actorVec.push_back(actor);
}

void BaseCore::unregisterActor(Actor * actor)
{
	// scan actorVec
		for (int i = 0; i < _actorVec.size(); ++i)
		{
			if (actor == _actorVec[i])  // find actor
				{
					// to use pop_back, actor needs to be on the back
					if (_actorVec[i] != _actorVec.back())
					{
						std::swap(_actorVec[i], _actorVec.back());
					}
					_actorVec.pop_back(); // use pop back
					return;
				}
		}
}

std::vector<Actor*>& BaseCore::getRegisteredActors()
{
	return _actorVec;
}

