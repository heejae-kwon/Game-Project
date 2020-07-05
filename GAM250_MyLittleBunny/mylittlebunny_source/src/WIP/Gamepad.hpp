/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      Gamepad.hpp
Purpose:        Handles state of the gamepad
Language:       C++
Project:        GAM200
Author:         Name : Stuart Sulaski
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/

#pragma once
#include <WIP/keycode.hh>

#include <glm\glm.hpp>

#include <vector>
#include <memory> //smart_ptr

namespace BE
{
    namespace Input
    {

        //!  The Gamepad class. 
        /*!
        The Gamepad class stores the state of our Gamepad.
        */
        class Gamepad
        {
            // All type redefinitions go here
        protected:
            using GamepadSmartPtr = std::unique_ptr<Gamepad>;

        public:
            static Gamepad*        instance()  //!< Returns an instance of the class
            {
                static GamepadSmartPtr instance(new Gamepad());
                return instance.get();
            }
            ~Gamepad() = default;

            void        turnonKey(int key);
            void        turnoffKey(int key);
            void        setXValue(float value_);
            void        setYValue(float value_);
            glm::vec2   getLeftStick();
            glm::vec2   getRightStick();
            bool        IsPressed(GP::KeyCode key);
            bool        IsTriggered(GP::KeyCode key);
            void        clearTrigger();
            void        update();
        protected:
            //
        private:
            Gamepad();   //!< Gamepad's constructor is private as it is a Singleton and should only be accessed through the instance() function

        public:
            //
        protected:
            //
        private:
            static const int arraySize = 15; // The size of our input arrays
            std::vector<GP::KeyCode>    keyIsPressed;
            std::vector<GP::KeyCode>    keyIsTriggered;
            // isPressed
            bool up;
            bool down;
            bool left;
            bool right;
            bool start;
            bool back;
            bool leftShoulder;
            bool rightShoulder;
            bool buttonA;
            bool buttonB;
            bool buttonX;
            bool buttonY;
            // isTriggered
            bool trigUp;
            bool trigDown;
            bool trigLeft;
            bool trigRight;
            bool trigStart;
            bool trigBack;
            bool trigLeftShoulder;
            bool trigRightShoulder;
            bool trigButtonA;
            bool trigButtonB;
            bool trigButtonX;
            bool trigButtonY;

            glm::vec2 leftStick;
            glm::vec2 rightStick;
        };
    }
}