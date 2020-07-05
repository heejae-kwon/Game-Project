/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      Display.cpp
Purpose:        Display component used by the Draw core
Language:       C++
Project:        GAM250
Author:         Name : Stuart Sulaski
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/

#include <Components/Display.hpp>
#include <Components/Transform.hpp>
#include <Core/Draw.hpp>
#include <Core/Debugger.hpp>
#include <Utilities/JsonReader.hh>
#include <Utilities/JsonWriter.hh>

#include <imgui\imgui.h>
#include <glm/glm.hpp>

BE::Component::Display::Display(Actor* owner_) :
    BaseComponent(identifier),
    drawType(DrawType::SPRITE),
    spriteIndex(0),
    textureId("err"),
    texture(nullptr),
    textureColor(1.f),
    animPlaying(false),
    animPaused(false),
    loopAnim(false),
    animationId("err"),
    animation(nullptr),
    zOffset(0.f),
    animTimer(0.f)
{
    type = Type::DISPLAY;
    owner = owner_;
    Core::Draw::instance()->registerActor(owner);

    texture = updateProp("err");
}

BE::Component::Display::~Display()
{
    Core::Draw::instance()->unregisterActor(owner);
}

void
BE::Component::Display::getData(Json::Value& data_)
{
    std::string componentField = BE::Component::TypeStr[BE::Component::DISPLAY];
    Json::Value componentData = data_["Actors"][owner->_name][componentField];

    drawType = stringToDrawEnum(JsonReader::getFieldAsString(componentData["drawType"]));
    ddType = static_cast<int>(drawType);
    spriteIndex = JsonReader::getFieldAsInt(componentData["spriteIndex"]);
    textureId = JsonReader::getFieldAsString(componentData["textureId"]);
    textureColor = JsonReader::getFieldAsVec4(componentData["textureColor"], 1.f);

    for (int i = 0; i < 4; ++i)
    {
        color[i] = textureColor[i];
    }

    animPlaying = JsonReader::getFieldAsBool(componentData["animPlaying"]);
    if (animPlaying == true)
    {
        animPaused = JsonReader::getFieldAsBool(componentData["animPaused"]);
        loopAnim = JsonReader::getFieldAsBool(componentData["loopAnim"]);
        animationId = JsonReader::getFieldAsString(componentData["animationId"]);
        playAnim(animationId);
    }

    setTextureId(textureId);
}

void
BE::Component::Display::writeData(Json::Value& data_)
{
    std::string componentField = BE::Component::TypeStr[BE::Component::DISPLAY];
    Json::Value& componentData = data_["Actors"][owner->_name][componentField];

    JsonWriter::addValue(componentData["drawType"], DrawTypeStr[drawType]);
    JsonWriter::addValue(componentData["spriteIndex"], spriteIndex);
    JsonWriter::addValue(componentData["textureId"], textureId);
    JsonWriter::addVec4(componentData["textureColor"], textureColor);

    JsonWriter::addValue(componentData["animPlaying"], animPlaying);
    if (animPlaying == true)
    {
        JsonWriter::addValue(componentData["animPaused"], animPaused);
        JsonWriter::addValue(componentData["loopAnim"], loopAnim);
        JsonWriter::addValue(componentData["animationId"], animationId);
    }
}

void
BE::Component::Display::drawData()
{
    if (ImGui::CollapsingHeader("Draw Component"))
    {
        // Modify texture id
        ImGui::PushItemWidth(160);
        {

            ImGui::Text("Texture Id name: %s\n", textureId.c_str());
            ImGui::PushID(1);
            {
                if (ImGui::InputText("", buf1, 64, ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CharsNoBlank))
                {
                    setTextureId(buf1);
                    buf1[0] = '\0';
                }
            }
            ImGui::PopID();
            // Modify draw type
            if (ImGui::Combo("Draw Type", &ddType, "SPRITE\0HUD\0\0"))
            {
                if (ddType == 0)
                {
                    drawType = DrawType::SPRITE;
                }
                else if (ddType == 1)
                {
                    drawType = DrawType::HUD;
                }
            }
            if (ImGui::InputInt("Sprite Index", &spriteIndex, 1))
            {
                if (spriteIndex < 0)
                {
                    spriteIndex = 0;
                }
                //            updateTexture();
            }
            {
                if (ImGui::InputFloat4("Texture Color", color, 1))
                {
                    textureColor.r = color[0];
                    textureColor.g = color[1];
                    textureColor.b = color[2];
                    textureColor.a = color[3];
                }
            }
            // Display selected texture
            ImGui::Indent();
            if (texture->second->type == Prop::IMAGE)
            {
                if (ImGui::CollapsingHeader("Texture Preview"))
                {
                    Prop::getProp<Prop::Image>(texture->second)->drawData();
                }
            }
            ImGui::Unindent();
            ImGui::Checkbox("Animation Is Playing", &animPlaying);
            if (animPlaying)
            {
                // Will the animation loop or not
                ImGui::Checkbox("Animation Loop", &loopAnim);
                ImGui::Checkbox("Animation Pause", &animPaused);
                // Modify animation id
                ImGui::PushID(2);
                {
                    ImGui::Text("Animation Id name: %s\n", animationId.c_str());
                    if (ImGui::InputText("", buf2, 64, ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CharsNoBlank))
                    {
                        animationId = buf2;
                        playAnim(animationId);
                        buf2[0] = '\0';
                    }
                }
                ImGui::PopID();
                ImGui::Text("Anim Timer: %.2f", animTimer);
            }
        }
        ImGui::PopItemWidth();
    }
}

BE::PropManager::propNamePair*
BE::Component::Display::updateProp(std::string propId_)
{
    BE::PropManager::propNamePair* retVal;
    if ((retVal = PropManager::instance()->lookupValue(propId_)) == nullptr)
    {
        if ((retVal = PropManager::instance()->lookupValue("err")) == nullptr)
        {
            Core::Debugger::instance()->AddLog("[ERR][Display::%s] Unable to retrieve default \"error\" texture\n", __func__);
            return retVal;
        }
    }
    return retVal;
}

BE::Prop::Image::imageData
BE::Component::Display::getTexture(float dt_)
{
    Prop::Image::imageData retVal{ 0, nullptr, {0.f, 0.f} };

    if (texture != nullptr)
    {
        retVal.spriteIndex = spriteIndex;
        retVal.texture = static_cast<Prop::Image*>(texture->second)->getSprite(retVal.spriteIndex);
        retVal.spriteSize = retVal.texture->getSize();
        retVal.posOffest = { 0.f, 0.f, 0.f };
        retVal.color = textureColor;
        if (animPlaying && animation != nullptr && animation->second->type == Prop::ANIMATION)
        {
            if (!animPaused)
            {
                animTimer += dt_;
            }
            retVal = static_cast<Prop::Animation*>(animation->second)->getFrame(animTimer, loopAnim);
            if (!loopAnim && animTimer >= static_cast<Prop::Animation*>(animation->second)->fullTime)
            {
                animPlaying = false;
            }
        }
    }
    return retVal;
}

std::string
BE::Component::Display::getTextureId()
{
    return textureId;
}

void
BE::Component::Display::setTextureId(std::string propId_, int spriteIndex_)
{
    textureId = propId_;
    texture = updateProp(textureId);
    if (texture->second->hashId != Prop::Image::identifier)
    {
        Core::Debugger::instance()->AddLog("[WARNING][Display::%s] Only IMAGE type props may be assigned with this function\n", __func__);
        textureId = "err";
        texture = updateProp(textureId);
    }

    if (spriteIndex_ != -1)
    {
        spriteIndex = spriteIndex_; // Setting the sprite index for the texture we just assigned
    }
}

void
BE::Component::Display::playAnim(std::string propId_, bool loopAnim_, float startTime_)
{
    if (animation != nullptr && propId_ == animation->first && animPlaying == true)
    {
        return;
    }
    animationId = propId_;
    animation = updateProp(animationId);
    //    if (animation->second->hashId != Prop::Animation::identifier)
    //    {
    //        Core::Debugger::instance()->AddLog("[WARNING][Display::%s] Only ANIMATION type props may be assigned with this function\n", __func__);
    //        animationId = "err";
    //        animation = updateProp(textureId);
    //        return;
    //    }
    animTimer = startTime_;
    animPlaying = true;
    animPaused = false;
    loopAnim = loopAnim_;
}

void
BE::Component::Display::pauseAnim()
{
    animPaused = true;
}

void
BE::Component::Display::resumeAnim()
{
    if (texture != nullptr && animTimer != 0.f && animPaused == true)
    {
        animPaused = false;
    }
}

void
BE::Component::Display::stopAnim()
{
    animTimer = 0.f;
    animPlaying = false;
}

BE::Component::Display::DrawType
BE::Component::Display::stringToDrawEnum(std::string str_)
{
    if (str_ == "SPRITE")
    {
        return DrawType::SPRITE;
    }
    else if (str_ == "HUD")
    {
        return DrawType::HUD;
    }
    else
    {
        return DrawType::SPRITE;
    }
}
