/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      JsonWriter.hh
Purpose:        Our abstraction of Jsoncpp used for writing in json files
Language:       C++
Project:        GAM250
Author:         Name : Stuart Sulaski
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/

#pragma once

#include <Props\Props.hh>

#include <json/json.h>
#include <json/json-forwards.h>
#include <glm/glm.hpp>

namespace BE
{
namespace JsonWriter
{
    void    write(const Json::Value& buffer_, const std::string& outputFile_);

    void    addValue(Json::Value& buffer_, const Json::Value& value_);
    void    appendValue(Json::Value& array, const Json::Value& value_);

    void    addVec2(Json::Value& buffer_, const glm::vec2 value_);
    void    addVec3(Json::Value& buffer_, const glm::vec3 value_);
    void    addVec4(Json::Value& buffer_, const glm::vec4 value_);
    void    addKeyFrame(Json::Value& buffer_, const Prop::Animation::keyFrame& value_);

    void    addStringArray(Json::Value& buffer_, const std::vector<std::string>& arrayValue_);
    void    addIntArray(Json::Value& buffer_, const std::vector<int>& arrayValue_);
    void    addFloatArray(Json::Value& buffer_, const std::vector<float>& arrayValue_);
    void    addVec2Array(Json::Value& buffer_, const std::vector<glm::vec2>& arrayValue_);
    void    addVec3Array(Json::Value& buffer_, const std::vector<glm::vec3>& arrayValue_);
    void    addVec4Array(Json::Value& buffer_, const std::vector<glm::vec4>& arrayValue_);
    void    addKeyFrameList(Json::Value& buffer_, const std::list<Prop::Animation::keyFrame>& listValue_);
}
}
