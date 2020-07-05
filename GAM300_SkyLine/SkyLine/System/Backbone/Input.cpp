#include <Input.hpp>

#include "Input.hpp"


namespace {
	std::bitset<Key_NUM_SCANCODES> s_pressed;	//Container of keys pressed this frame
	std::bitset<Key_NUM_SCANCODES> s_triggered;	//Container of keys pressed this frame
	std::bitset<Key_NUM_SCANCODES> s_released;	//Container of keys pressed this frame
}
namespace Input{
Keyboard::Keyboard()
{
			for (int i = 0; i < Key_NUM_SCANCODES; ++i){
								s_pressed[i] = s_triggered[i] = s_released[i] = false;
				}
}

Keyboard::~Keyboard()
{
}


void Keyboard::Reset()
{
			for (int i = 0; i < Key_NUM_SCANCODES; ++i){
								s_triggered[i] = s_released[i] = false;
				}
}

void Keyboard::SetKeyPressed(Key_Scancode key_, Key_EventType keyStatus_)
{
				if (keyStatus_ == Key_KEYDOWN) {
								s_pressed[key_] = true;
								s_triggered[key_] = true;
				}
				else if (keyStatus_ == Key_KEYUP) {
								s_released[key_] = true;
								s_pressed[key_] = false;
				}
}

bool Keyboard::IsPressed(Key_Scancode key_)const
{
				return s_pressed[key_];
}

bool Keyboard::IsTriggered(Key_Scancode key_)const
{
				return s_triggered[key_];
}
	
bool Keyboard::IsReleased(Key_Scancode key_)const
{
				return s_released[key_];
}

bool Keyboard::IsAnyPressed()const
{
				return s_pressed.any();
}

bool Keyboard::IsAnyTriggered()const
{
				return s_triggered.any();
}

bool Keyboard::IsAnyReleased()const
{
				return s_released.any();
}

}
