#pragma once

#include "Logic.hpp"


namespace Component
{
	class Chasing : public Logic
	{
	public:

		Chasing(Actor* owner_);
		~Chasing();

		void Update(float dt);
		void ChasingObj(float dt);
		void SetTarget(Actor* actor);


		void getData(Json::Value& data_)     final;
		void writeData(Json::Value& data_)   final;
		void drawData();

	private:
	Actor* target;

			bool isHit = false;
		bool isDetect;
		float misSpeed;
	
	};

}
