#pragma once
#include <string>
		//Order is important. Please be careful about the order
		//when you add Components
namespace Component {
		enum Type
		{
				TRANSFORM,
				RENDERABLE,
				CAMERA,
				RIGIDBODY,
				LOGIC,
				PLAYERCONTROLLER,
				BULLET,
				CHASING,
				MISSILEEXPLODE,
				MISSILESHOOTER,


				TYPE_LENGTH //This enum represents the amount of component types we have
		};

		static const std::string TypeStr[] =
		{
						"TRANSFORM",
						"RENDERABLE",
						"CAMERA",
						"RIGIDBODY",
				"LOGIC",
				"PLAYERCONTROLLER",
				"BULLET",
				"CHASING",
			"MISSILEEXPLODE",
			"MISSILESHOOTER",

		};
}

