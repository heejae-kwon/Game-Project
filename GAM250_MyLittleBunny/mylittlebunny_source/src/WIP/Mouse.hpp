/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      Mouse.hpp
Purpose:        Handles state of the mouse
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

    //!  The Mouse class. 
    /*!
    The Mouse class stores the state of our mouse.
    */
    class Mouse
    {
        // All type redefinitions go here
    protected:
        using MouseSmartPtr = std::unique_ptr<Mouse>;

    public:
        static Mouse*        instance()  //!< Returns an instance of the class
        {
            static MouseSmartPtr instance(new Mouse());
            return instance.get();
        }
        ~Mouse() = default;

        void        turnonKey(int key);
        void        turnoffKey(int key);
        void        setMousePosition(int x, int y);
        glm::vec2   getMousePosition();
        bool        IsPressed(MS::KeyCode key);
        bool        IsTriggered(MS::KeyCode key);
        void        clearTrigger();
    protected:
        //
    private:
        Mouse();   //!< Mouse's constructor is private as it is a Singleton and should only be accessed through the instance() function

    public:
        int nbrOfMouseScrolls;
    protected:
        //
    private:
        static const int arraySize = 2; // The size of our input arrays
        std::vector<MS::KeyCode>    keyIsPressed;
        std::vector<MS::KeyCode>    keyIsTriggered;
        glm::ivec2                  mousePos;
    };
}
}