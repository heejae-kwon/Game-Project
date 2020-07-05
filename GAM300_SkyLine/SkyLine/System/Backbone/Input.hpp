#pragma once

#include "MyInput.hpp"
#include <bitset>
#include <memory>

namespace Input
{

	class Keyboard
	{
	public:
		friend class Application; //for using SetKeyPressed

		static Keyboard* instance()  //!< Returns an instance of the class
		{
			static std::unique_ptr<Keyboard> instance(new Keyboard());
			return instance.get();
		}
		~Keyboard();
		//void Initialize();
		void Reset();

		//Check if a specific key is
		bool IsPressed(Key_Scancode key)const;
		bool IsTriggered(Key_Scancode key)const;
		bool IsReleased(Key_Scancode key)const;

		bool IsAnyPressed()const;
		bool IsAnyTriggered()const;
		bool IsAnyReleased()const;

	private:
		Keyboard();
		void SetKeyPressed(Key_Scancode key, Key_EventType keyStatus);

		//Sets pressed, triggered, released, or unpressed status of a key

		std::bitset<Key_NUM_SCANCODES> s_pressed;
		std::bitset<Key_NUM_SCANCODES> s_triggered;
		std::bitset<Key_NUM_SCANCODES> s_released;

	};

}

