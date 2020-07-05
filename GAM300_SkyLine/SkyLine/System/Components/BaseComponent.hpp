#pragma once
#include <string>
#include <json.h>
#include "ComponentType.hh"
#include "crc32.hh"
class Actor;
namespace Component 
{


#define COMPONENT_HASH(name) static constexpr unsigned int identifier = #name##_crc32;
	class BaseComponent
	{
	public:
					BaseComponent(Actor* onwner_ = nullptr);
					virtual ~BaseComponent() = default;

					virtual void Update(float dt) = 0; /*This should be deleted later*/

					unsigned int    m_hashId;         /*!< This is used for the type comparison. */
					Type            m_type;           /*!< An enum representing the type of the component. */
					Actor*          m_owner;          /*!< A pointer to the Actor class that "owns" the component. */
					bool											 m_isActive;       /*!< A bool to control component's active status*/

					virtual void    getData(Json::Value& data_) = 0;    //!< Get's the necesarry data from the Json::Value object it receives.
					virtual void    writeData(Json::Value& data_) = 0;  //!< Writes all the necesarry data in the Json::Value object it receives.
					virtual void    drawData() = 0;                     //!< This function uses ImGui functions to render out component specific tools to edit it's variables.
	};
}