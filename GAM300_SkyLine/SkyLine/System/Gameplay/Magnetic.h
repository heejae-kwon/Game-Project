#pragma once

#include "Logic.hpp"

namespace Component
{
	class Magnetic : public Logic
	{
	public:
		COMPONENT_HASH(Magnetic)

			Magnetic(Actor* owner_);
		~Magnetic();

		void Update(float dt);
		void    getData(Json::Value& data_)     final;
		void    writeData(Json::Value& data_)   final;

		void    drawData();

	private:
		// v = vdef + dt*a -bv
	};

}
