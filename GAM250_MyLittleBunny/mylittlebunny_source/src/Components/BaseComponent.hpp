/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      BasicComponent.hpp
Purpose:        Components are what make up each Actor, this is the base component that all the others inherit from
Language:       C++
Project:        GAM250
Author:         Name : Stuart Sulaski
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/

#pragma once

#include <Utilities\crc32.hh> // For hashing purposes
#include <json\json.h>

namespace BE
{
class Actor; // Forward declaration of Actor class
namespace Component
{
    /** Component::Type
    *  A human readable way to discern component types.
    */
    enum Type
    {
        TRANSFORM,
        DISPLAY,
        CAMERA,
        RIGIDBODY,
		PARTICLEEMITTER,
        CIRCLE_COLLIDER,
        GAMEPLAY,
        TYPE_LENGTH //This enum represents the amount of component types we have
    };

    static const std::string TypeStr[] =
    {
        "TRANSFORM",
        "DISPLAY",
        "CAMERA",
        "RIGIDBODY",
		"PARTICLEEMITTER",
        "CIRCLE_COLLIDER",
        "GAMEPLAY"
    };

    #define COMPONENT_HASH(name) static constexpr unsigned int identifier = #name##_crc32;

    //!  BaseComponent class. 
    /*!
    The BaseComponent class is the base stucture that all future components will inherit from.
    It contains a hashId which is a hash of it's name that is determined during runtime. This let's us do type compares.
    Each component also has functions (getData(), writeData()) that let's it read and write itself from and into a .json file.
    They will also all have a drawData() function that tells ImGui how it should display and treat it's data. Again the component is responsible of this himself.
    */
    class BaseComponent
    {
    public:
        BaseComponent(unsigned int identifier_) : hashId(identifier_), type(Type::TYPE_LENGTH), owner(nullptr) {}
        virtual ~BaseComponent() = default;

        unsigned int    hashId;         /*!< This is used for the type comparison. */
        Type            type;           /*!< An enum representing the type of the component. */
        Actor*          owner;          /*!< A pointer to the Actor class that "owns" the component. */

        virtual void    getData(Json::Value& data_) = 0;    //!< Get's the necesarry data from the Json::Value object it receives.
        virtual void    writeData(Json::Value& data_) = 0;  //!< Writes all the necesarry data in the Json::Value object it receives.
        virtual void    drawData() = 0;                     //!< This function uses ImGui functions to render out component specific tools to edit it's variables.
    };
}
}
