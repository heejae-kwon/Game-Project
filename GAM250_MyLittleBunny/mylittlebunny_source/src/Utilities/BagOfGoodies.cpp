/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      BagOfGoodies.cpp
Purpose:        A collection of useful functions that can be used anywhere in the engine
Language:       C++
Project:        GAM250
Author:         Name : Stuart Sulaski
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/

#include <Utilities\BagOfGoodies.hh>

#include <WIP/Mouse.hpp> // realMouseCoord()
#include <Abstractions\WindowAbst.hpp> // realMouseCoord()
#include <Abstractions\RenderAbst.hpp> // realMouseCoord()
#include <Core/Draw.hpp> // realMouseCoord()

#include <iostream> // emergencyMessageLogger()
#include <fstream>  // emergencyMessageLogger()

void
BE::BoG::emergencyMessageLogger(std::string errorMsg_)
{
    std::ofstream errorFile;
    errorFile.open("BE_ErrorLog.txt", std::ofstream::app);
    errorFile << "[EMERGENCY][ERROR] : " << errorMsg_ << '\n';
    errorFile.close();
}

glm::vec4
BE::BoG::getMouseCoord()
{
    glm::vec4 retVal;

    glm::vec2 mousePos = BE::Input::Mouse::instance()->getMousePosition();
    glm::vec2 viewportSize = RenderAbst::instance()->viewport;
    glm::ivec2 windowSize = BE::WindowAbst::instance()->_windowSize;

    // The ratio fix
    {
        float targetAspectRatio = viewportSize.x / viewportSize.y;

        // figure out the largest area that fits in this resolution at the desired aspect ratio
        int width = windowSize.x;
        int height = (int)(width / targetAspectRatio + 0.5f);

        if (height > windowSize.y)
        {
            //It doesn't fit our height, we must switch to pillarbox then
            height = windowSize.y;
            width = (int)(height * targetAspectRatio + 0.5f);
        }
        viewportSize.x += windowSize.x - width;
        viewportSize.y += windowSize.y - height;
    }

    mousePos = { (((mousePos.x * 100.f) / static_cast<float>(windowSize.x)) * viewportSize.x) / 100.f, (((mousePos.y * 100.f) / static_cast<float>(windowSize.y)) * viewportSize.y) / 100.f };
    viewportSize /= 2.f;
    glm::vec2 cameraOffset = BE::Core::Draw::instance()->getCurrentCamera()->getComponent<BE::Component::Transform>()->position;
    float zoomModifier = BE::Core::Draw::instance()->getCurrentCamera()->getComponent<BE::Component::Camera>()->zoom;


    {
        mousePos -= viewportSize;
        retVal[0] = mousePos.x;
        retVal[1] = -mousePos.y; // invert the y axis
    }
    {
        mousePos *= zoomModifier;
        cameraOffset.y *= -1; // Fixed mouse select bug because the camera's y is inversed from the normal axis
        mousePos -= cameraOffset;
        retVal[2] = mousePos.x;
        retVal[3] = -mousePos.y; // invert the y axis
    }

    return retVal;
}
