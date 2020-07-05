#pragma once

#include "Logic.hpp"

namespace Component
{
	class PlayerController : public Logic
	{
	public:

		PlayerController(Actor* owner_);
		~PlayerController();

		void Update(float dt);
		void gamepadControl(float dt);
		void keyboardControl(float dt);

        void    getData(Json::Value& data_)     final;
        void    writeData(Json::Value& data_)   final;

		void    drawData();

	private:
		float moveSpeed_;

		float pitchSpeed_;


		float yawSpeed_;
		float rollSpeed_;

		float actMovSpeed;
		float actPitchSpeed;
		float actYawSpeed;
		float actRollSpeed;

		float acceleration;
		float b;
		float a;
		float v;
		float v_default;
	

		// v = vdef + dt*a -bv
	};

}
