#pragma once

#include "Logic.hpp"

namespace Component
{
	class MissileShooter : public Logic
	{
	public:
		COMPONENT_HASH(MissileShooter)

			MissileShooter(Actor* owner_);
		~MissileShooter();

		void Update(float dt);
		void    getData(Json::Value& data_)     final;
		void    writeData(Json::Value& data_)   final;

		void    drawData();

	private:
		float coolDown;
		int maximumMissile;
	};

}
