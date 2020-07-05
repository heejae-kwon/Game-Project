#include "BaseLevel.hpp"
#include "ObjectManager.hpp"
#include "Actor.hpp"


Level::BaseLevel::BaseLevel(std::string name):m_numberOfActor(0) {
						m_levelFileName = name;
						m_obj = ObjectManager::instance();
}

void Level::BaseLevel::LoadLevelFile(std::string fileName_)
{
			//  fileName_ = (fileName_ == "") ? _stageFileName : fileName_;
	Json::Value inData;
	if (JsonReader::readFile("./Data/" + fileName_, inData))
	{
		std::vector<std::string> actorNames = JsonReader::getArrayAsString(inData["ActorList"]);
		for (auto& actor : actorNames)
		{
		Actor* newActor = m_obj->CreateActor(actor, JsonReader::getFieldAsBool(inData["Actors"][actor]["isActive"]), &inData);
			newActor->LoadComponents(inData);
		}
	}
	else
	{
		//   Core::Debugger::instance()->AddLog("[ERR][BaseStage::%s] %s file could not be loaded\n", __func__, fileName_.c_str());
	}
}

void Level::BaseLevel::SaveLevelFile(std::string fileName_)
{
			Json::Value outData;

	for (auto& actor : m_obj->getActorVec())
	{
		if (actor->saveActor)
		{
			actor->SaveComponents(outData);
		}
	}
	//std::vector<std::string> propStringArray;
	//for (auto& prop : _propVec)
	//{
	//	propStringArray.push_back(prop->fileName);
	//}
//	JsonWriter::addStringArray(outData["PropList"], propStringArray);
	JsonWriter::write(outData, fileName_);
}

void Level::BaseLevel::Resume() {
		std::vector<Actor*>& actorVec = m_obj->getActorVec();
		while (actorVec.size() != m_numberOfActor){
				delete actorVec.back();
				actorVec.pop_back();
		}
			for (auto&actor:actorVec)
			{
					actor->isPaused = false;
			}
}

 void Level::BaseLevel::Pause() {
		std::vector<Actor*>& actorVec = m_obj->getActorVec();
		m_numberOfActor = static_cast<int>(actorVec.size());
			for (auto&actor:actorVec)
			{
					actor->isPaused = true;
			}
}
