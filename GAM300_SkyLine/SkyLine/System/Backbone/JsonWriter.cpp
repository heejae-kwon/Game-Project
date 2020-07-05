/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      JsonWriter.cpp
Purpose:        Our abstraction of Jsoncpp used for writing in json files
Language:       C++
Project:        GAM250
Author:         Name : Stuart Sulaski
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/

#include "JsonWriter.hh"

#include <fstream>

void
JsonWriter::write(const Json::Value& buffer_, const std::string & outputFile_)
{
    std::ofstream fileData;
    fileData.open(outputFile_, std::ios_base::out);
    if (fileData.is_open())
    {
        fileData << buffer_;
        fileData.close();
    }
}

void
JsonWriter::addValue(Json::Value & buffer_, const Json::Value & value_)
{
    buffer_ = value_;
}


void
JsonWriter::appendValue(Json::Value & array, const Json::Value & value_)
{
    array.append(value_);
}

void JsonWriter::addVec2(Json::Value & buffer_, const glm::vec2 value_)
{
    Json::Value array(Json::arrayValue);

    array.append(value_.x);
    array.append(value_.y);

    addValue(buffer_, array);
}

void JsonWriter::addVec3(Json::Value & buffer_, const glm::vec3 value_)
{
    Json::Value array(Json::arrayValue);

    array.append(value_.x);
    array.append(value_.y);
    array.append(value_.z);

    addValue(buffer_, array);
}

void
JsonWriter::addVec4(Json::Value & buffer_, const glm::vec4 value_)
{
    Json::Value array(Json::arrayValue);

    array.append(value_.r);
    array.append(value_.g);
    array.append(value_.b);
    array.append(value_.a);

    addValue(buffer_, array);
}

//void
//JsonWriter::addKeyFrame(Json::Value& buffer_, const Prop::Animation::keyFrame& value_)
//{
//    Json::Value value;
//
//    value["duration"] = value_.duration;
//    value["spriteIndex"] = value_.spriteIndex;
//    glm::vec4 color = glm::vec4(value_.color[0], value_.color[1], value_.color[2], value_.color[3]);
//    glm::vec3 transform = glm::vec3(value_.transform[0], value_.transform[1], value_.transform[2]);
//    glm::vec2 scale = glm::vec2(value_.scale[0], value_.scale[1]);
//    addVec4(value["color"], color);
//    addVec3(value["transform"], transform);
//    addVec2(value["scale"], scale);
//    value["rotation"] = value_.rotation;
//
//    buffer_.append(value);
//}

void JsonWriter::addBoolArray(Json::Value & buffer_, const std::vector<bool>& arrayValue_)
{
    Json::Value array(Json::arrayValue);

    for (auto value_ : arrayValue_) // Generates the list of entities to load
    {
        array.append(value_);
    }
    addValue(buffer_, array);
}

void
JsonWriter::addStringArray(Json::Value & buffer_, const std::vector<std::string>& arrayValue_)
{
    Json::Value array(Json::arrayValue);

    for (auto value_ : arrayValue_) // Generates the list of entities to load
    {
        array.append(value_);
    }
    addValue(buffer_, array);
}

void
JsonWriter::addIntArray(Json::Value & buffer_, const std::vector<int>& arrayValue_)
{
    Json::Value array(Json::arrayValue);

    for (auto value_ : arrayValue_) // Generates the list of entities to load
    {
        array.append(value_);
    }
    addValue(buffer_, array);
}

void
JsonWriter::addFloatArray(Json::Value & buffer_, const std::vector<float>& arrayValue_)
{
    Json::Value array(Json::arrayValue);

    for (auto value_ : arrayValue_) // Generates the list of entities to load
    {
        array.append(value_);
    }
    addValue(buffer_, array);
}

void
JsonWriter::addVec2Array(Json::Value & buffer_, const std::vector<glm::vec2>& arrayValue_)
{
    Json::Value array(Json::arrayValue);

    for (auto value_ : arrayValue_) // Generates the list of entities to load
    {
        array.append(value_.x);
        array.append(value_.y);
    }
    addValue(buffer_, array);
}

void JsonWriter::addVec3Array(Json::Value & buffer_, const std::vector<glm::vec3>& arrayValue_)
{
    Json::Value array(Json::arrayValue);

    for (auto value_ : arrayValue_) // Generates the list of entities to load
    {
        array.append(value_.x);
        array.append(value_.y);
        array.append(value_.z);
    }
    addValue(buffer_, array);
}

void JsonWriter::addVec4Array(Json::Value & buffer_, const std::vector<glm::vec4>& arrayValue_)
{
    Json::Value array(Json::arrayValue);

    for (auto value_ : arrayValue_) // Generates the list of entities to load
    {
        array.append(value_.r);
        array.append(value_.g);
        array.append(value_.b);
        array.append(value_.a);
    }
    addValue(buffer_, array);
}

//void JsonWriter::addKeyFrameList(Json::Value& buffer_, const std::list<Prop::Animation::keyFrame>& listValue_)
//{
//    Json::Value array(Json::arrayValue);
//
//    for (auto value : listValue_) // Generates the list of entities to load
//    {
//        addKeyFrame(buffer_, value);
//    }
//    //    addValue(buffer_, array);
//}

