#pragma once
#include "BaseComponent.hpp"
namespace Component
{
				class Logic : public BaseComponent
				{
				public:

								COMPONENT_HASH(Logic)	/*This MUST be exist in each Component 
																																For comparing component*/
								Logic(Actor* owner_ = nullptr);
								virtual ~Logic();

								virtual void Update(float dt)=0;

								//void    getData(Json::Value& data_)     final;
								//void    writeData(Json::Value& data_)   final;
								//	virtual void    drawData();
				};

}
