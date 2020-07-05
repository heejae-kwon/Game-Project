#include <Gamepad.hpp>

#include "Gamepad.hpp"
#include <cmath>
#include <iostream>

//Analog joystick dead zone
const int JOYSTICK_DEAD_ZONE = 8000;
const float TRIGGER_DEAD_ZONE = 30000.f;
const float JOYSTICK_MAX_ZONE = 32500.f;
const double PI = 3.141592653;


namespace {
	std::bitset<Key_CONTROLLER_BUTTON_MAX> s_pressed;	//Container of keys pressed this frame
	std::bitset<Key_CONTROLLER_BUTTON_MAX> s_triggered;	//Container of keys pressed this frame
	std::bitset<Key_CONTROLLER_BUTTON_MAX> s_released;	//Container of keys pressed this frame
}
namespace Input {

	Gamepad::Gamepad()
	{
		for (int i = 0; i < Key_CONTROLLER_BUTTON_MAX; ++i) {
			s_pressed[i] = s_triggered[i] = s_released[i] = false;
		}
		leftStick.xValue = leftStick.yValue = 0;
		rightStick.xValue = rightStick.yValue = 0;
		LT.triggerValue = 0;
		RT.triggerValue = 0;

	}

	Gamepad::~Gamepad()
	{
	}


	void Gamepad::Reset(void)
	{
		for (int i = 0; i < Key_CONTROLLER_BUTTON_MAX; ++i) {
			s_triggered[i] = s_released[i] = false;
		}

	}

	void Gamepad::SetButtonPressed(Key_GameControllerButton button, Key_EventType keyStatus)
	{
		switch (keyStatus)
		{
		case Key_CONTROLLERBUTTONDOWN: {
			s_pressed[button] = true;
			s_triggered[button] = true;
		}break;
		case Key_CONTROLLERBUTTONUP: {
			s_released[button] = true;
			s_pressed[button] = false;
		}break;
		default:
			break;
		}
	}

	void Gamepad::SetAxisDirection(char axis, int value)
	{
		// Axis 0 and 1 is Left Stick
		if (axis == 0) // X axis motion
		{
			// value of X with int
			if (value < -JOYSTICK_DEAD_ZONE) // left
			{
				// value of xValue with float
				if (value < -JOYSTICK_MAX_ZONE) // left stick go over max zone
				{
					leftStick.xValue = -1.f;
				}
				else
				{
					leftStick.xValue = value / JOYSTICK_MAX_ZONE;
				}
			}
			else if (value > JOYSTICK_DEAD_ZONE) // right
			{
				// value of xValue with float
				if (value > JOYSTICK_MAX_ZONE) // left stick go over max zone
				{
					leftStick.xValue = 1.f;
				}
				else
				{
					leftStick.xValue = value / JOYSTICK_MAX_ZONE;
				}
			}
			else
			{
				leftStick.xValue =  0;
			}
		}
		else if (axis == 1) // Y axis motion
		{
			// value of Y with int
			if (value < -JOYSTICK_DEAD_ZONE) // down
			{
				// value of yValue with float
				if (value < -JOYSTICK_MAX_ZONE) // left
				{
					leftStick.yValue = 1.f;
				}
				else
				{
					leftStick.yValue = -value / JOYSTICK_MAX_ZONE;
				}
			}
			else if (value > JOYSTICK_DEAD_ZONE) // up
			{
				// value of yValue with float
				if (value > JOYSTICK_MAX_ZONE) // left stick go over max zone
				{
					leftStick.yValue = -1.f;
				}
				else
				{
					leftStick.yValue = -value / JOYSTICK_MAX_ZONE;
				}
			}
			else
			{
				leftStick.yValue = 0;
			}
		}

		// Axis 2 and 3 is Right Stick
		if (axis == 2) // X axis motion
		{
			if (value < -JOYSTICK_DEAD_ZONE) // left
			{
				// value of xValue with float
				if (value < -JOYSTICK_MAX_ZONE) // left stick go over max zone
				{
					rightStick.xValue = -1.f;
				}
				else
				{
					rightStick.xValue = value / JOYSTICK_MAX_ZONE;
				}
			}
			else if (value > JOYSTICK_DEAD_ZONE) // right
			{
				if (value > JOYSTICK_MAX_ZONE) // left stick go over max zone
				{
					rightStick.xValue = 1.f;
				}
				else
				{
					rightStick.xValue = value / JOYSTICK_MAX_ZONE;
				}
			}
			else
			{
				rightStick.xValue = 0;
			}
		}
		else if (axis == 3) // Y axis motion
		{
			// value of Y with int
			if (value < -JOYSTICK_DEAD_ZONE) // down
			{
				// value of xValue with float
				if (value < -JOYSTICK_MAX_ZONE) // left stick go over max zone
				{
					rightStick.yValue = 1.f;
				}
				else
				{
					rightStick.yValue = -value / JOYSTICK_MAX_ZONE;
				}
			}
			else if (value > JOYSTICK_DEAD_ZONE) // up
			{
				// value of yValue with float
				if (value > JOYSTICK_MAX_ZONE) // left stick go over max zone
				{
					rightStick.yValue = -1.f;
				}
				else
				{
					rightStick.yValue = -value / JOYSTICK_MAX_ZONE;
				}
			}
			else
			{
				rightStick.yValue =  0;
			}
		}

		// LT
		if (axis == 4) // X axis motion
		{
			if (value <= TRIGGER_DEAD_ZONE)
			{
				LT.triggerValue = value / TRIGGER_DEAD_ZONE;
			}
			else if (value > TRIGGER_DEAD_ZONE)
			{
				LT.triggerValue = 1.f;
			}
			else
			{
				LT.triggerValue = 0.f;
			}
		}

		if (axis == 5) // X axis motion
		{
			if (value <= TRIGGER_DEAD_ZONE)
			{
				RT.triggerValue = value / TRIGGER_DEAD_ZONE;
			}
			else if (value > TRIGGER_DEAD_ZONE)
			{
				RT.triggerValue = 1.f;
			}
			else
			{
				RT.triggerValue = 0.f;
			}
		}
	}
	void Gamepad::stickUpdate(void)
	{
		leftStick.Update();
		rightStick.Update();
		LT.setTrigger();
		RT.setTrigger();
	}
	bool Gamepad::IsPressed(Key_GameControllerButton button)const
	{
		return s_pressed[button];
	}

	bool Gamepad::IsTriggered(Key_GameControllerButton button)const
	{
		return s_triggered[button];
	}

	bool Gamepad::IsReleased(Key_GameControllerButton button)const
	{
		return s_released[button];
	}

	bool Gamepad::IsAnyPressed(void) const
	{
		return s_pressed.any();
	}

	bool Gamepad::IsAnyTriggered(void) const
	{
		return s_triggered.any();
	}

	bool Gamepad::IsAnyReleased(void) const
	{
		return s_released.any();
	}

	// Functions for Sticks
	Stick::Stick()
	{
		// Booleans for LRUD check
		LEFT = RIGHT = UP = DOWN = false;

		// Angle informations of stick with every 45 degree.
		stickAngle = 0.0;
		xValue = 0.f; // Check how much they pressed
		yValue = 0.f; // Check how much they pressed
		stickDir = { 0.0f, 0.0f };
	}

	Stick::~Stick()
	{
	}

	void Stick::Update(void)
	{
		stickDirUpdate();
		stickAngleUpdate();
	}

	void Stick::stickAngleUpdate(void)
	{
		stickAngle = atan2((double)yValue, (double)xValue) * (180.0 / PI);
	}

	void Stick::stickDirUpdate(void)
	{
		// set stick dir with x,y value
		stickDir = { xValue, yValue };
		stickDir = glm::normalize(stickDir);

		if (stickDir.x > 0.0f)
			RIGHT = true;
		else if (stickDir.x < 0.0f)
			LEFT = true;
		else
			RIGHT = LEFT = false;

		if (stickDir.y > 0.0f)
			UP = true;
		else if (stickDir.y < 0.0f)
			DOWN = true;
		else
			UP = DOWN = false;
	}

	glm::vec2 Stick::GetStickDir(void)
	{
		return stickDir;
	}

	Trigger::Trigger()
	{
	}

	Trigger::~Trigger()
	{
	}

	void Trigger::Reset(void)
	{
		isTriggered = false;
		triggerValue = 0.f;
	}

	void Trigger::setTrigger(void)
	{
		if (triggerValue > 0)
			isTriggered = true;
	}

}