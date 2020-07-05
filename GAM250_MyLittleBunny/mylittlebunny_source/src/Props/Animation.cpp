/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      Animation.cpp
Purpose:        Animation prop is the object that contains all the animation data for the animations in the engine
Language:       C++
Project:        GAM250
Author:         Name : Stuart Sulaski, Wonjae Jung
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/

#include <Props\Animation.hpp>
#include <Core/Debugger.hpp>
#include <Utilities/JsonWriter.hh>
#include <Utilities/JsonReader.hh>

BE::Prop::Animation::Animation(std::string fileName_, std::string id_) :
    BaseProp(identifier, fileName_, id_),
    spriteOverride(false),
    colorOverride(false),
    colorInterpolate(false),
    transformOverride(false),
    transformInterpolate(false),
    textureId("err"),
    fullTime(0.f),
    loop(true)
{
    type = Type::ANIMATION;
}

void
BE::Prop::Animation::getData(Json::Value & data_)
{
    Json::Value propData = data_["Props"][fileName];

    id = JsonReader::getFieldAsString(propData["id"]);
    spriteOverride = JsonReader::getFieldAsBool(propData["spriteOverride"]);
    if (spriteOverride)
    {
        textureId = JsonReader::getFieldAsString(propData["textureId"]);
    }
    colorOverride = JsonReader::getFieldAsBool(propData["colorOverride"]);
    if (colorOverride)
    {
        colorInterpolate = JsonReader::getFieldAsBool(propData["colorInterpolate"]);
    }
    transformOverride = JsonReader::getFieldAsBool(propData["transformOverride"]);
    if (transformOverride)
    {
        transformInterpolate = JsonReader::getFieldAsBool(propData["transformInterpolate"]);
    }
    frameList = JsonReader::getListAsKeyFrame(propData["keyFrames"]);

    setTextureId(textureId);
    updateFullTime();
}

void
BE::Prop::Animation::loadData()
{
}

void
BE::Prop::Animation::writeData(Json::Value & data_)
{
    JsonWriter::addValue(data_["Props"][fileName]["type"], "ANIMATION");
    JsonWriter::addValue(data_["Props"][fileName]["id"], id);
    JsonWriter::addValue(data_["Props"][fileName]["spriteOverride"], spriteOverride);
    if (spriteOverride)
    {
        JsonWriter::addValue(data_["Props"][fileName]["textureId"], textureId);
    }
    JsonWriter::addValue(data_["Props"][fileName]["colorOverride"], colorOverride);
    if (colorOverride)
    {
        JsonWriter::addValue(data_["Props"][fileName]["colorInterpolate"], colorInterpolate);
    }
    JsonWriter::addValue(data_["Props"][fileName]["transformOverride"], transformOverride);
    if (transformOverride)
    {
        JsonWriter::addValue(data_["Props"][fileName]["transformInterpolate"], transformInterpolate);
    }
    JsonWriter::addKeyFrameList(data_["Props"][fileName]["keyFrames"], frameList);
}

void
BE::Prop::Animation::drawData()
{

    ImGui::Checkbox("Animation Loop", &loop);
    ImGui::Checkbox("Sprite", &spriteOverride);
    if (spriteOverride)
    {
        ImGui::Indent();
        {
            static char buf1[32] = "";
            // Modify texture id
            ImGui::PushItemWidth(160);
            {
                ImGui::Text("Texture Id name: %s\n", textureId.c_str());
                if (ImGui::InputText("##texture id", buf1, 32, ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CharsNoBlank))
                {
                    textureId = buf1;
                    setTextureId(textureId);
                    buf1[0] = '\0';
                }
            }
            ImGui::PopItemWidth();
        }
        ImGui::Unindent();
    }
    ImGui::Checkbox("Color", &colorOverride);
    if (colorOverride)
    {
        ImGui::Indent();
        {
            ImGui::Checkbox("Color Interpolate", &colorInterpolate);
        }
        ImGui::Unindent();
    }
    ImGui::Checkbox("Transform", &transformOverride);
    if (transformOverride)
    {
        ImGui::Indent();
        {
            ImGui::Checkbox("Transform Interpolate", &transformInterpolate);
        }
        ImGui::Unindent();
    }

    size_t i = 0;
    ImGui::Indent();
    {
        ImGui::PushItemWidth(100);
        {
            for (auto it = frameList.begin(); i < frameList.size() && it != frameList.end(); ++it)
            {
                ImGui::PushID(static_cast<int>(i));
                {
                    if (ImGui::Button("+"))
                    {
                        frameList.insert(it, keyFrame(*it));
                        updateFullTime();
                    }
                    ImGui::SameLine();
                    if (ImGui::Button("-"))
                    {
                        frameList.erase(it);
                        updateFullTime();
                        ImGui::PopID();
                        break;
                    }
                    ImGui::Indent();
                    {
                        if (spriteOverride)
                        {
                            if (ImGui::InputInt("sprite index", &(it->spriteIndex), 1, 1))
                            {
                                if (it->spriteIndex < 0)
                                {
                                    it->spriteIndex = 0;
                                }
                            }
                        }
                        if (colorOverride)
                        {
                            ImGui::PushItemWidth(160);
                            ImGui::InputFloat4("Color", it->color, 1);
                            ImGui::PopItemWidth();
                        }
                        if (transformOverride)
                        {
                            ImGui::PushItemWidth(160);
                            {
                                ImGui::InputFloat3("Pos Offset", it->transform, 2);
                                ImGui::InputFloat2("Scale Offset", it->scale, 2);
                            }
                            ImGui::PopItemWidth();
                            if (ImGui::InputInt("Rotation", &it->rotation, 1, 5))
                            {
                                if (it->rotation > 360)
                                {
                                    it->rotation %= it->rotation;
                                }
                                else if (it->rotation < 0)
                                {
                                    it->rotation = 360 + it->rotation;
                                }
                            }
                        }

                    }
                }
                ImGui::Unindent();
                if (ImGui::InputFloat("duration", &(it->duration), 0.001f, 0.01f, 3))
                {
                    if (it->duration < 0)
                    {
                        it->duration = 0;
                    }
                    updateFullTime();
                }
                ImGui::PopID();
                ++i;
            }
        }
        ImGui::PopItemWidth();
    }
    ImGui::Unindent();
    ImGui::Separator();
    if (ImGui::Button("+"))
    {
        frameList.push_back(keyFrame());
        updateFullTime();
    }
}

BE::Prop::Image::imageData
BE::Prop::Animation::getFrame(float elapsedTime_, bool loop_)
{
    Image::imageData retVal;
    float totalTime = 0.f;

    if (loop_)
    {
        if (elapsedTime_ > fullTime)
        {
            elapsedTime_ -= fullTime * static_cast<int>(elapsedTime_ / fullTime);
        }
    }
    else
    {
        if (elapsedTime_ > fullTime)
        {
            elapsedTime_ = fullTime;
        }
    }

    // Default values
    {
        retVal.spriteIndex = 0;
        retVal.texture = nullptr;
        retVal.spriteSize = { 0.f, 0.f };
        retVal.posOffest = { 0.f, 0.f, 0.f };
        retVal.scaleOffest = { 0.f, 0.f };
        retVal.color = { -1.f, -1.f, -1.f, -1.f };
        retVal.rotation = 0;
    }
    for (auto it = frameList.begin(); it != frameList.end(); ++it)
    {
        if (elapsedTime_ >= totalTime && elapsedTime_ <= totalTime + it->duration)
        {
            if (spriteOverride)
            {
                retVal.spriteIndex = it->spriteIndex;
                retVal.texture = getTexture()->getSprite(retVal.spriteIndex);
                retVal.spriteSize = retVal.texture->getSize();
            }

            if (colorOverride)
            {
                auto prevFrame = it;
                if (colorInterpolate)
                {
                    // The following block is all about frame interpolation
                    auto nextFrame = prevFrame;
                    nextFrame = (++nextFrame == frameList.end()) ? ((loop_) ? frameList.begin() : prevFrame) : nextFrame;
                    {
                        float duration = prevFrame->duration;
                        float currentDuration = elapsedTime_ - totalTime;

                        float percent = ((currentDuration * 100) / duration) / 100;

                        for (int i = 0; i < 4; ++i)
                        {
                            retVal.color[i] = prevFrame->color[i] * (1.f - percent) + nextFrame->color[i] * percent;
                        }
                    }
                    // -
                }
                else
                {
                    for (int i = 0; i < 4; ++i)
                    {
                        retVal.color[i] = it->color[i];
                    }
                }
            }

            if (transformOverride)
            {
                auto prevFrame = it;
                if (transformInterpolate)
                {
                    // The following block is all about frame interpolation
                    auto nextFrame = prevFrame;
                    nextFrame = (++nextFrame == frameList.end()) ? ((loop_) ? frameList.begin() : prevFrame) : nextFrame;
                    {
                        float duration = prevFrame->duration;
                        float currentDuration = elapsedTime_ - totalTime;

                        float percent = ((currentDuration * 100) / duration) / 100;

                        for (int i = 0; i < 3; ++i)
                        {
                            if (i < 2)
                            {
                                retVal.scaleOffest[i] = prevFrame->scale[i] * (1.f - percent) + nextFrame->scale[i] * percent;
                            }
                            retVal.posOffest[i] = prevFrame->transform[i] * (1.f - percent) + nextFrame->transform[i] * percent;
                        }

                        retVal.rotation = prevFrame->rotation * (1 - percent) + nextFrame->rotation * percent;
                    }
                    // -
                }
                else
                {
                    for (int i = 0; i < 3; ++i)
                    {
                        if (i < 2)
                        {
                            retVal.scaleOffest[i] = prevFrame->scale[i];
                        }
                        retVal.posOffest[i] = prevFrame->transform[i];
                    }
                    retVal.rotation = static_cast<float>(prevFrame->rotation);
                }
            }
        }
        totalTime += it->duration;
    }
    return retVal;
}

std::pair<std::string, BE::Prop::BaseProp*>*
BE::Prop::Animation::updateProp(std::string propId_)
{
    std::pair<std::string, BE::Prop::BaseProp*>* retVal;
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

BE::Prop::Image*
BE::Prop::Animation::getTexture()
{
    return static_cast<Prop::Image*>(texture->second);
}

void
BE::Prop::Animation::setTextureId(std::string propId_)
{
    textureId = propId_;
    texture = updateProp(textureId);
    if (texture->second->hashId != Prop::Image::identifier)
    {
        Core::Debugger::instance()->AddLog("[WARNING][Display::%s] Only IMAGE type props may be assigned with this function\n", __func__);
        textureId = "err";
        texture = updateProp(textureId);
    }
}

void BE::Prop::Animation::updateFullTime()
{
    fullTime = 0.f;
    for (auto it = frameList.begin(); it != frameList.end(); ++it)
    {
        fullTime += it->duration;
    }
}
