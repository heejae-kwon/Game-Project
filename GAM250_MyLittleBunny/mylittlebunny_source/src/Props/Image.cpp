/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      Audio.cpp
Purpose:        Audio prop is the object that contains the data of the texture files we load in
Language:       C++
Project:        GAM250
Author:         Name : Stuart Sulaski, Wonjae Jung
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/

#include <Props/Image.hpp>
#include <Core/Debugger.hpp>
#include <Abstractions/RenderAbst.hpp>
#include <Utilities/JsonWriter.hh>
#include <Utilities/JsonReader.hh>

BE::Prop::Image::Image(std::string fileName_, std::string id_)
    : BaseProp(identifier, fileName_, id_), imageFile(""), texData(nullptr), spriteDm(1.f, 1.f), spriteCoord()
{
    type = Type::IMAGE;
}

void
BE::Prop::Image::getData(Json::Value& data_)
{
    Json::Value propData = data_["Props"][fileName];

    id = JsonReader::getFieldAsString(propData["id"]);
    imageFile = JsonReader::getFieldAsString(propData["imageFile"]);
    spriteDm = JsonReader::getFieldAsVec2(propData["spriteDm"]);
    if (spriteDm.x == 0.f && spriteDm.y == 0.f)
    {
        spriteDm.x = 1.f;
        spriteDm.y = 1.f;
    }
    loadData();
}

void
BE::Prop::Image::loadData()
{
    if ((texData = RenderAbst::instance()->createTexture(formatPath("./Data/Textures/" + imageFile).c_str(), true)) == nullptr)
    {
        Core::Debugger::instance()->AddLog("[ERR][Image::%s] Failed to create texture\n", __func__);
        return;
    }

    calculateSpriteCoord();
}

void
BE::Prop::Image::writeData(Json::Value& data_)
{
    JsonWriter::addValue(data_["Props"][fileName]["type"], "IMAGE");
    JsonWriter::addValue(data_["Props"][fileName]["id"], id);
    JsonWriter::addValue(data_["Props"][fileName]["imageFile"], imageFile);
    JsonWriter::addVec2(data_["Props"][fileName]["spriteDm"], spriteDm);
}

void
BE::Prop::Image::drawData()
{
    float sizeDiffPer = (100.f * 100.f) / static_cast<float>(texData->size.y);
    float newWidth = (static_cast<float>(texData->size.x) * sizeDiffPer) / 100;

    unsigned __int64 _64bitId = texData->ID; // To is to solve the typecast err when casting from uint to void* in 64bit
    ImGui::Image(reinterpret_cast<ImTextureID>(_64bitId), ImVec2(newWidth, 100.f), ImVec2(0, 0), ImVec2(1, 1), ImVec4(1.f, 1.f, 1.f, 1.f));

    float textWidth = 100;
    ImGui::PushItemWidth(textWidth);
    if (ImGui::InputFloat("sprite width", &spriteDm.x, 0.05f, 0.1f, 2))
    {
        spriteDm.x = glm::clamp(spriteDm.x, 0.f, 1.f);
        calculateSpriteCoord();
    }
    if (ImGui::InputFloat("sprite height", &spriteDm.y, 0.05f, 0.1f, 2))
    {
        spriteDm.y = glm::clamp(spriteDm.y, 0.f, 1.f);
        calculateSpriteCoord();
    }
    ImGui::PopItemWidth();
}

BE::Texture*
BE::Prop::Image::getSprite(size_t index)
{
    if (index > spriteCoord.size() || index == 0)
    {
        texData->spriteCoord = glm::vec2(1.f, 1.f);
        texData->spriteSize = glm::vec2(1.f, 1.f);
    }
    else
    {
        texData->spriteCoord = spriteCoord[index - 1];
        texData->spriteSize = spriteDm;
    }
    return texData;
}

bool
BE::Prop::Image::textureIsLoaded()
{
    return (texData != nullptr) ? true : false;
}

void
BE::Prop::Image::calculateSpriteCoord()
{
    if (spriteDm.x <= 0.f || spriteDm.y <= 0.f)
    {
        return;
    }
    spriteCoord.resize(0);

    for (float height = 0.f + spriteDm.y; height <= 1.f; height += spriteDm.y)
    {
        for (float width = 0.f; width < 1.f; width += spriteDm.x)
        {
            spriteCoord.push_back(glm::vec2(width, height));
        }
    }
}
