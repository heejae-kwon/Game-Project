/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      Display.hpp
Purpose:        Display component used by the Draw core
Language:       C++
Project:        GAM250
Author:         Name : Stuart Sulaski
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/

#pragma once

#include <Components/BaseComponent.hpp>
#include <WIP/PropManager.hpp>

#include <glm\glm.hpp>
#include <json\json.h>

namespace BE
{
namespace Component
{

    static const std::string DrawTypeStr[] =
    {
        "SPRITE",
        "HUD"
    };

    static const std::string ClampModeStr[] =
    {
        "NONE",
        "TOP",
        "BOTTOM",
        "LEFT",
        "RIGHT"
    };

    class Display : public BaseComponent
    {
    public:
        enum DrawType
        {
            SPRITE,
            HUD,
            TYPE_LENGTH //This enum represents the amount of component types we have
        };

    public:
        COMPONENT_HASH(Display)
        Display(Actor* owner_);
        ~Display();

        void    getData(Json::Value& data_)     final;
        void    writeData(Json::Value& data_)   final;
        void    drawData()                      final;

        PropManager::propNamePair*  updateProp(std::string propId_);
        Prop::Image::imageData      getTexture(float dt_);
        std::string                 getTextureId();
        void                        setTextureId(std::string propId_, int spriteIndex_ = -1);
        void                        playAnim(std::string propId_, bool loopAnim_ = true, float startTime_ = 0.0f);
        void                        pauseAnim();
        void                        resumeAnim();
        void                        stopAnim();
    private:
        DrawType    stringToDrawEnum(std::string str_);

    public:
        // Saved data
        DrawType    drawType;   /*!< The type of the texture we are drawing (this will determin how we draw it)*/
		//// Texture specific
		int                         spriteIndex;    /*!< The index of the sprite we want to display;*/

        // Temporary data
        float   zOffset = .0f;    /*!< Used to make sure that 2 actors NEVER have the exact same Z value*/
		bool	animPlaying;    /*!< Bool that is set to true if an animation is playing*/

    private:
        // Saved data

        std::string                 textureId;      /*!< The id of the texture we are using*/
        PropManager::propNamePair*  texture;        /*!< Pointer to a prop pair that contains a texture*/
    public:
        glm::vec4                   textureColor;   /*!< A color modifier for the texture*/

    private:
        //// Animation specific
        bool                        animPaused;     /*!< Bool set to true if the animation is paused*/
        bool                        loopAnim;       /*!< Bool set to true if we wish the animation to loop*/
        std::string                 animationId;    /*!< The id of the texture we are using*/
        PropManager::propNamePair*  animation;      /*!< Pointer to a prop pair that contains a texture*/

        // Temporary data
        float   animTimer = .0f;  /*!< Used for the animation*/

        // Temporary data
        char buf1[64] = "";     /*!< Buffer for Texture prop id*/
        char buf2[64] = "";     /*!< Buffer for Actor name*/
        int ddType = 0;         /*!< DropDown Type*/
        float color[4];         /*!< Array used to store the color values*/

    };

}
}
