/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      BaseProp.hpp
Purpose:        BaseProp is the interface that all other props inherit from
Language:       C++
Project:        GAM250
Author:         Name : Stuart Sulaski
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/

#pragma once

#include <Utilities\crc32.hh> // For hashing purposes
#include <json\json.h>

#include <memory>

static std::string formatPath(std::string filename_)
{
    return filename_;
    std::string documentpath = getenv("USERPROFILE");
    documentpath += "\\Documents\\MyLittleBunny\\Data\\";

    return documentpath + filename_;
}

namespace BE
{
namespace Prop
{
    /** Component::Type
    *  A human readable way to discern component types.
    */
    enum Type
    {
        IMAGE,
        AUDIO,
        ANIMATION,
        TYPE_LENGTH //This enum represents the amount of component types we have
    };

    Type stringToEnum(std::string& str_);

    #define PROP_HASH(name) static constexpr unsigned int identifier = #name##_crc32;

    //!  BaseProp class. 
    /*!
    The BaseProp class is the base stucture that all future components will inherit from.
    It contains a hashId which is a hash of it's name that is determined during runtime. This let's us do type compares.
    Each component also has functions (getData(), writeData()) that let's it read and write itself from and into a .json file.
    They will also all have a drawData() function that tells ImGui how it should display and treat it's data. Again the component is responsible of this himself.
    */
    class __declspec(dllexport) BaseProp
    {
    public:
        BaseProp(unsigned int identifier_, std::string fileName_, std::string id_) : hashId(identifier_), type(Type::TYPE_LENGTH), fileName(fileName_), id(id_) {}
        virtual ~BaseProp() = default;

        unsigned int    hashId;     /*!< This is used for the type comparison. */
        Type            type;       /*!< An enum representing the type of the component. */
        std::string     fileName;   /*!< The file that the prop will be loaded from (ex: music.mp3, picture.png). */
        std::string     id;         /*!< the name given to the prop as an id to be used by actors. */

        virtual void    getData(Json::Value& data_) = 0;    //!< Get's the necesarry data from the Json::Value object it receives.
        virtual void    loadData() = 0;                     //!< This is where you would place all the actual loading of assets (textures, sound files...);
        virtual void    writeData(Json::Value& data_) = 0;  //!< Writes all the necesarry data in the Json::Value object it receives.
        virtual void    drawData() = 0;                     //!< This function uses ImGui functions to render out prop specific tools to edit it's variables.
    };

    using BasePropSmartPtr = std::unique_ptr<Prop::BaseProp>;

    /**
    *This templated function is what lets us retrieve ASSETs from entities.
    *We compare the identifiers to find a match.
    *Identifiers are simply a hash of the ASSET's actual type.
    *
    *\return - A pointer to the templated type
    */
    template<typename PropType>
    PropType* getProp(BaseProp *prop)
    {
        if (prop && prop->hashId == PropType::identifier)
        {
            return static_cast<PropType*>(prop);
        }
        return nullptr;
    }

}
}
