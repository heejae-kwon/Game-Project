/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      PropManager.cpp
Purpose:        Handles the creation, destruction of Props. It also manages the correspondance table between props and their id name.
Language:       C++
Project:        GAM250
Author:         Name : Stuart Sulaski
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/

#include "PropManager.hpp"
#include <Utilities/JsonReader.hh>
#include <Core/Debugger.hpp>

BE::Prop::BaseProp*
BE::PropManager::createProp(std::string fileName_, Prop::Type propType_, std::string id_)
{
    Prop::BaseProp* newProp;

    for (auto & prop : _propVec) // This is so that we don't load the same file multiple times
    {
        if (prop->fileName == fileName_)
            return nullptr;
    }
    switch (propType_)
    {
    case (Prop::Type::IMAGE):
    {
        newProp = new Prop::Image(fileName_, id_);
        break;
    }
    case (Prop::Type::AUDIO):
    {
        newProp = new Prop::Audio(fileName_, id_);
        break;
    }
    case (Prop::Type::ANIMATION):
    {
        newProp = new Prop::Animation(fileName_, id_);
        break;
    }
    default:
    {
        return nullptr;
    }
    }
    addEntry(id_, newProp);        // Adding a simple pointer to the correspondance table

    return (_propVec.back().get());
}

BE::Prop::BaseProp*
BE::PropManager::createPropFromFile(std::string fileName_, Json::Value & data_)
{
    Prop::BaseProp* newProp;

    std::string typeStr = JsonReader::getFieldAsString(data_["Props"][fileName_]["type"]);
    Prop::Type type = Prop::stringToEnum(typeStr);

    for (auto & prop : _propVec) // This is so that we don't load the same file multiple times
    {
        if (prop->fileName == fileName_)
        {
            //Core::Debugger::instance()->AddLog("[WARNING][PropViewer::Draw()] trying to load [%s] but it seems to have already been loaded\n", prop->fileName.c_str());
            return prop.get();
        }
    }

    switch (type)
    {
    case (Prop::Type::IMAGE):
    {
        newProp = new Prop::Image(fileName_, "NO_VALUE");

        newProp->getData(data_);
        if (static_cast<Prop::Image*>(newProp)->textureIsLoaded() == false) // We check to see if the texture loading / creation was succesful
        {
            Core::Debugger::instance()->AddLog("[ERR][PropManager::%s] Failed to load texture\n", __func__);
            return nullptr;
        }

        break;
    }
    case (Prop::Type::AUDIO):
    {
        newProp = new Prop::Audio(fileName_, "NO_VALUE");

        newProp->getData(data_);
        if (static_cast<Prop::Audio*>(newProp)->soundIsLoaded() == false) // We check to see if the texture loading / creation was succesful
        {
            Core::Debugger::instance()->AddLog("[ERR][PropManager::%s] Failed to load audio\n", __func__);
            return nullptr;
        }

        break;
    }
    case (Prop::Type::ANIMATION):
    {
        newProp = new Prop::Animation(fileName_, "NO_VALUE");

        newProp->getData(data_);

        break;
    }
    default:
    {
        return nullptr;
    }
    }

    addEntry(newProp->id, newProp);        // Adding a simple pointer to the correspondance table

    return (_propVec.back().get());
}

BE::PropManager::propNamePair*
BE::PropManager::lookupValue(std::string id_)
{
    for (auto prop : _propCorrespondanceTable)
    {
        if (prop->first == id_)
        {
            return prop;
        }
    }
    _propCorrespondanceTable.push_back(new propNamePair(id_, lookupValue("err")->second));
    return lookupValue(id_);
}

BE::PropManager::propNamePairList&
BE::PropManager::getCorresTable()
{
    return _propCorrespondanceTable;
}

bool BE::PropManager::isFileLoaded(std::string filename_)
{
    for (auto prop : _propCorrespondanceTable)
    {
        if (prop->second->fileName == filename_)
        {
            return true;
        }
    }
    return false;
}

void
BE::PropManager::addEntry(std::string id_, Prop::BaseProp* newProp_)
{
    Prop::BaseProp* prop;
    _propVec.push_back(std::unique_ptr<Prop::BaseProp>(newProp_)); // Adding to the array of smart pointer
    prop = _propVec.back().get();
    _ordererPropVec.push_back(prop);
    updateOrder();

    for (size_t i = 0; i < _propCorrespondanceTable.size(); ++i)
    {
        if (_propCorrespondanceTable[i]->first == id_)
        {
            updateEntry(prop);
            return;
        }
    }
    _propCorrespondanceTable.push_back(new propNamePair(id_, prop));
}

void
BE::PropManager::updateEntry(Prop::BaseProp * prop_)
{
    propNamePair* src = nullptr;
    propNamePair* dest = nullptr;

    for (auto & pair : this->_propCorrespondanceTable)
    {
        if (pair->first == prop_->id)
        {
            dest = pair;
        }
        if (pair->second == prop_)
        {
            src = pair;
        }
    }
    if (dest == nullptr && src != nullptr)
    {
        addEntry(prop_->id, prop_);
        src->second = lookupValue("err")->second;
    }
    if (dest != nullptr)
    {
        dest->second = prop_;
        if (src != nullptr)
        {
            src->second = dest->second;
        }
    }
}

void
BE::PropManager::removeEntry(Prop::BaseProp* entry_)
{
    // Set the place where the prop was stored with a nullptr
    for (size_t i = 0; i < _propCorrespondanceTable.size(); ++i)
    {
        if (_propCorrespondanceTable[i]->second == entry_)
        {
            _propCorrespondanceTable[i]->second = lookupValue("err")->second;
            //            std::swap(_propCorrespondanceTable[i], _propCorrespondanceTable.back());  // We move the pointer to the end of the vector
            //            _propCorrespondanceTable.pop_back();                                      // and then remove it from the vector
        }
    }
    deleteEntry(entry_);
}

void
BE::PropManager::deleteEntry(Prop::BaseProp* entry_)
{
    // Fully remove the prop
    for (size_t i = 0; i < _propVec.size(); ++i)
    {
        if (_propVec[i].get() == entry_)
        {
            std::swap(_propVec[i], _propVec.back());    // We move the pointer to the end of the vector
            _propVec.pop_back();                        // and then remove it from the vector
        }
    }
    for (size_t i = 0; i < _ordererPropVec.size(); ++i)
    {
        if (_ordererPropVec[i] == entry_)
        {
            std::swap(_ordererPropVec[i], _ordererPropVec.back());  // We move the pointer to the end of the vector
            _ordererPropVec.pop_back();                             // and then remove it from the vector
        }
    }
}

std::vector<BE::Prop::BaseProp*>&
BE::PropManager::getProps()
{
    return _ordererPropVec;
}

void
BE::PropManager::updateOrder()
{
    for (uint32_t i = 0; i < _ordererPropVec.size(); ++i)
    {
        if (i != 0)
        {
            if (_ordererPropVec[i - 1]->id > _ordererPropVec[i]->id)
            {
                std::swap(_ordererPropVec[i - 1], _ordererPropVec[i]);
                i = 0;
            }
        }
    }
}
