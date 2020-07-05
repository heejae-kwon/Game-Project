/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      JsonReader.hh
Purpose:        Our abstraction of Jsoncpp used for reading in json files
Language:       C++
Project:        GAM250
Author:         Name : Stuart Sulaski
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/

#pragma once

#include <Props/Props.hh>

#include <json/json.h>
#include <json/json-forwards.h>
#include <glm/glm.hpp>

namespace BE
{
namespace JsonReader
{
    bool                        readFile(const std::string& filepath_, Json::Value& data_);
    bool                        fileExists(std::string filepath_);

    std::list<Prop::Animation::keyFrame>    getListAsKeyFrame(const Json::Value& data_);

    std::vector<Json::Value>    getArrayAsValue(const Json::Value& data_);
    std::vector<std::string>    getArrayAsString(const Json::Value& data_);
    std::vector<glm::vec2>      getArrayAsVec2(const Json::Value& data_);
    std::vector<glm::vec3>      getArrayAsVec3(const Json::Value& data_);
    std::vector<glm::vec4>      getArrayAsVec4(const Json::Value& data_);

    int         getFieldAsInt(const Json::Value& data_);
    float       getFieldAsFloat(const Json::Value& data_);
    std::string getFieldAsString(const Json::Value& data_);
    bool        getFieldAsBool(const Json::Value& data_);
    glm::vec2   getFieldAsVec2(const Json::Value& data_);
    glm::ivec2  getFieldAsIVec2(const Json::Value& data_);
    glm::vec3   getFieldAsVec3(const Json::Value& data_);
    glm::ivec3  getFieldAsIVec3(const Json::Value& data_);
    glm::vec4   getFieldAsVec4(const Json::Value& data_, const float defaultValue_ = 0.f);
    glm::ivec4  getFieldAsIVec4(const Json::Value& data_);
}
}
