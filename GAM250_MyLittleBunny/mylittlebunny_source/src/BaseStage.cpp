/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      BaseStage.cpp
Purpose:        All other stages inherit this class
Language:       C++
Project:        GAM250
Author:         Name : Stuart Sulaski
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/

#include <BaseStage.hpp>
#include <Core/Debugger.hpp>
#include <Components/Components.hh>
#include <Utilities/JsonReader.hh>
#include <Utilities/JsonWriter.hh>
#include <WIP/PropManager.hpp>

BE::Stage::BaseStage::BaseStage(std::string stageFileName_, BaseStage* previousStage_)
    : _stageLoadCoreConf({ false, false }), _stageFileName(stageFileName_), _previousStage(previousStage_)
{
}

BE::Stage::BaseStage::keepPrevActorsOnLoad&
BE::Stage::BaseStage::getCoreConfig()
{
    return _stageLoadCoreConf;
}

void
BE::Stage::BaseStage::loadProps(std::string fileName_)
{
    // Loading default err texture in case it hasn't already been
    {
        Json::Value data;
        if (JsonReader::readFile("./Data/Props/missingTex.png.prop", data))
        {
            BE::PropManager::instance()->createPropFromFile("missingTex.png.prop", data);
        }
        else
        {
            abort(); // If we are missing our err texture then something is very wrong
        }
    }

    // Loading Props
    Json::Value inData;
    fileName_ = (fileName_ == "") ? _stageFileName : fileName_;
    if (BE::JsonReader::readFile("./Data/" + fileName_, inData))
    {
        std::vector<std::string> propNames = BE::JsonReader::getArrayAsString(inData["PropList"]);

        for (auto& prop : propNames)
        {
            BE::Prop::BaseProp* tmpPropPtr;
            Json::Value data;
            if (JsonReader::readFile(formatPath("./Data/Props/" + prop), data))
            {
                if ((tmpPropPtr = PropManager::instance()->createPropFromFile(prop, data)) != nullptr)
                {
                    _propVec.push_back(tmpPropPtr);
                }
            }
            else
            {
                Core::Debugger::instance()->AddLog("[ERR][BaseStage::%s] [STAGE]: %s : %s file could not be created\n", __func__, fileName_.c_str(), prop.c_str());
            }
        }
    }
    else
    {
        Core::Debugger::instance()->AddLog("[ERR][BaseStage::%s] %s file could not be loaded\n", __func__, fileName_.c_str());
    }
}

void
BE::Stage::BaseStage::loadStageFile(std::string fileName_)
{
    fileName_ = (fileName_ == "") ? _stageFileName : fileName_;
    Json::Value inData;
    if (BE::JsonReader::readFile("./Data/" + fileName_, inData))
    {
        std::vector<std::string> actorNames = BE::JsonReader::getArrayAsString(inData["ActorList"]);
        for (auto& actor : actorNames)
        {
            Actor* newActor = Actor::createActor(actor, BE::JsonReader::getFieldAsBool(inData["Actors"][actor]["isActive"]), &inData);
            newActor->loadComponents(inData);
            newActor->_saveActor = true;
            addActor(newActor);
        }
    }
    else
    {
        Core::Debugger::instance()->AddLog("[ERR][BaseStage::%s] %s file could not be loaded\n", __func__, fileName_.c_str());
    }
}

void
BE::Stage::BaseStage::saveStageFile(std::string fileName_)
{
    Json::Value outData;

    for (size_t i = 0; i < _actorVec.size(); ++i)
    {
        if (_actorVec[i]->_saveActor)
        {
            _actorVec[i]->saveComponents(outData);
        }
    }
    std::vector<std::string> propStringArray;
    for (auto& prop : _propVec)
    {
        propStringArray.push_back(prop->fileName);
    }
    JsonWriter::addStringArray(outData["PropList"], propStringArray);

    JsonWriter::write(outData, fileName_);
}

BE::Actor*
BE::Stage::BaseStage::addActor(Actor * actor_)
{
    _actorVec.push_back(std::unique_ptr<Actor>(actor_));
    return (_actorVec.back().get());
}

void
BE::Stage::BaseStage::removeActor(Actor* actor_)
{
    int i = 0;

    for (auto& actor : _actorVec)
    {
        if (actor.get() == actor_)
        {
            std::swap(_actorVec[i], _actorVec.back());  // We move the pointer to the end of the vector
            _actorVec.pop_back();                   // and then remove it from the vector
            return;
        }
        ++i;
    }
}

void
BE::Stage::BaseStage::addProp(Prop::BaseProp* prop_)
{
    _propVec.push_back(prop_);
}

void
BE::Stage::BaseStage::removeProp(Prop::BaseProp* actor_)
{
    int i = 0;

    for (auto& prop : _propVec)
    {
        if (prop == actor_)
        {
            std::swap(_propVec[i], _propVec.back());  // We move the pointer to the end of the vector
            _propVec.pop_back();                   // and then remove it from the vector
            return;
        }
        ++i;
    }
}

std::string
BE::Stage::BaseStage::getStageFileName()
{
    return _stageFileName;
}

BE::Actor*
BE::Stage::BaseStage::getActor(std::string name_)
{
    for (auto & actor : _actorVec)
    {
        if (actor->_name == name_)
        {
            return actor.get();
        }
    }
    Core::Debugger::instance()->AddLog("[WARNING][%s::%s] Could not retrieve actor with the following name: %s\n", this->_stageFileName.c_str(), __func__,name_.c_str());
    return nullptr;
}
