#include "Actor.hpp"

Actor::Actor():isActive(true), isPaused(false), saveActor(true)
{
}

/** A static factory function to create Actors.
* Takes a string (name) and boolean (isActive) as params
THIS SHOULD BE ALWAYS UPDATED WHEN NEW COMPONET IS ADDED
*/

Actor * Actor::CreateActor(std::string name_, bool isActive_, Json::Value * data_)
{
		Actor* newActor = new Actor();

		newActor->name = name_;
		newActor->isActive = isActive_;
		newActor->saveActor = true;
		if (data_ != nullptr)
		{

				Json::Value actorData = (*data_)["Actors"][name_];
				std::vector<std::string> componentArray = JsonReader::getArrayAsString(actorData["Components"]);

				for (auto & component : componentArray)
				{
						if (component == Component::TypeStr[Component::TRANSFORM])
						{
								newActor->addComponent<Component::Transform>();
						}
						else if (component == Component::TypeStr[Component::RENDERABLE])
						{
								newActor->addComponent<Component::Renderable>();
						}
						else if (component == Component::TypeStr[Component::PLAYERCONTROLLER])
						{
								newActor->addComponent<Component::PlayerController>();
						}
						else if (component == Component::TypeStr[Component::RIGIDBODY])
						{
								newActor->addComponent<Component::Rigidbody>();
						}
						else if (component == Component::TypeStr[Component::CHASING])
						{
								newActor->addComponent<Component::Chasing>();
						}
						else if (component == Component::TypeStr[Component::MISSILEEXPLODE])
						{
								newActor->addComponent<Component::MissileExplode>();
						}
						else if (component == Component::TypeStr[Component::MISSILESHOOTER])
						{
								newActor->addComponent<Component::MissileShooter>();
						}
			else if (component == Component::TypeStr[Component::BULLET])
						{
								newActor->addComponent<Component::Bullet>();
						}



				}
		}

		return newActor;
}

void Actor::LoadComponents(Json::Value & data_)
{
	for (auto& component : componentVec)
	{
			component->getData(data_);
	}
}

void Actor::SaveComponents(Json::Value & data_)
{
	    JsonWriter::appendValue(data_["ActorList"], name);
    JsonWriter::addValue(data_["Actors"][name]["isActive"], isActive);
    std::vector<std::string> componentStringArray;
    for (auto & component : componentVec)
    {
        componentStringArray.push_back(Component::TypeStr[component->m_type]);
        component->writeData(data_);
    }
    JsonWriter::addStringArray(data_["Actors"][name]["Components"], componentStringArray);
}

void Actor::drawComponentData(void)
{
	for (auto & component : componentVec)
	{
		component->drawData();
	}
}