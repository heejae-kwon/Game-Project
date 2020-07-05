/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      Keyboard.hpp
Purpose:        Handles state of the keyboard
Language:       C++
Project:        GAM200
Author:         Name : Stuart Sulaski
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/

#pragma once
#include <WIP/keycode.hh>

#include <vector>
#include <memory> //smart_ptr

namespace BE
{
namespace Input
{

    //!  The Keyboard class. 
    /*!
    The Keyboard class stores the key states of our keyboard
    */
    class Keyboard
    {
        // All type redefinitions go here
    protected:
        using KeyboardSmartPtr = std::unique_ptr<Keyboard>;

    public:
        static Keyboard*        instance()  //!< Returns an instance of the class
        {
            static KeyboardSmartPtr instance(new Keyboard());
            return instance.get();
        }
        ~Keyboard() = default;

        void    turnonKey(int key);
        void    turnoffKey(int key);
        bool    IsPressed(KB::KeyCode key);
        bool    IsTriggered(KB::KeyCode key);
        void    clearTrigger();
    protected:
        //
    private:
        Keyboard();   //!< Keyboard's constructor is private as it is a Singleton and should only be accessed through the instance() function

    public:
        //
    protected:
        //
    private:
        static const int arraySize = 10; // The size of our input arrays
        std::vector<KB::KeyCode> keyIsPressed;
        std::vector<KB::KeyCode> keyIsTriggered;
    };
}
}