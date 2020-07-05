#pragma once

#include "MyInput.hpp"

#include "glm\glm.hpp"
#include <bitset>
#include <memory>

namespace Input {
	// Class for LT RT buttons
	class Trigger
	{
	public:
		Trigger();
		~Trigger();
		
		void Reset(void);
		void setTrigger(void);

		float triggerValue; // Check how much they pressed
		bool isTriggered;    // Just check Triggered - Bool
	private:

	};

	// Class for Left Right Sticks
	class Stick
	{
	public:
		Stick();
		~Stick();
		void Update(void);
		void stickAngleUpdate(void);
		void stickDirUpdate(void);

		glm::vec2 GetStickDir(void); // get stick x, y as vec2

		// Booleans for LRUD check
		bool LEFT;
		bool RIGHT;
		bool UP;
		bool DOWN;

		// Angle informations of stick with every 45 degree.
		double stickAngle;
		float xValue; // Check how much they pressed
		float yValue; // Check how much they pressed
		glm::vec2 stickDir;
		bool isMove;
	private:
	};

	// Class for actual GAMEPAD
	class Gamepad
	{
	public:
		friend class Application; //for using SetKeyPressed

		static Gamepad* instance()  //!< Returns an instance of the class
		{
			static std::unique_ptr<Gamepad> instance(new Gamepad());
			return instance.get();
		}
		~Gamepad();

		void Reset();

		//Check if a specific key is
		bool IsPressed(Key_GameControllerButton button) const;
		bool IsTriggered(Key_GameControllerButton button) const;
		bool IsReleased(Key_GameControllerButton button) const;

		bool IsAnyPressed()const;
		bool IsAnyTriggered()const;
		bool IsAnyReleased()const;
		
		void stickUpdate(void);

		// two sticks and LT RT
		Stick leftStick;
		Stick rightStick;
		Trigger LT;
		Trigger RT;
	private:
		Gamepad();
		void SetButtonPressed(Key_GameControllerButton button, Key_EventType keyStatus);
		void SetAxisDirection(char axis, int value);

		//Sets pressed, triggered, released, or unpressed status of a key

		std::bitset<Key_CONTROLLER_BUTTON_MAX> s_pressed;
		std::bitset<Key_CONTROLLER_BUTTON_MAX> s_triggered;
		std::bitset<Key_CONTROLLER_BUTTON_MAX> s_released;
	};
}