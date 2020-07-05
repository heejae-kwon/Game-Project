/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      JsonReader.cpp
Purpose:        Our abstraction of Jsoncpp used for reading in json files
Language:       C++
Project:        GAM250
Author:         Name : Stuart Sulaski
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/

#include "JsonReader.hh"

#include <fstream>

bool
JsonReader::readFile(const std::string& filePath_, Json::Value& data_)
{
    if (fileExists(filePath_) == true)
    {
        //std::ifstream fileData;
        //fileData.open(filePath_, std::ifstream::in);
        //if (fileData.is_open())
        //{
        //    fileData >> data_;
        //    fileData.close();
        //}
					Json::Reader reader;
					reader.parse(filePath_, data_);
        return true;
    }

    return false;
}

bool
JsonReader::fileExists(std::string filepath_)
{
    struct stat buffer;
    return (stat(filepath_.c_str(), &buffer) == 0);

}

//std::list<Prop::Animation::keyFrame>
//JsonReader::getListAsKeyFrame(const Json::Value & data_)
//{
//    std::list<Prop::Animation::keyFrame> retVal;
//
//    Json::Value element = data_;
//    for (unsigned int index = 0; index < element.size(); ++index)  // Iterates over the sequence elements.
//    {
//        Prop::Animation::keyFrame newKeyFrame;
//
//        newKeyFrame.duration = getFieldAsFloat(element[index]["duration"]);
//        newKeyFrame.spriteIndex = getFieldAsInt(element[index]["spriteIndex"]);
//        glm::vec4 color = getFieldAsVec4(element[index]["color"], 1.f);
//        glm::vec3 transform = getFieldAsVec3(element[index]["transform"]);
//        glm::vec2 scale = getFieldAsVec2(element[index]["scale"]);
//        for (int i = 0; i < 4; ++i)
//        {
//            newKeyFrame.color[i] = color[i];
//        }
//        for (int i = 0; i < 3; ++i)
//        {
//            newKeyFrame.transform[i] = transform[i];
//        }
//        for (int i = 0; i < 2; ++i)
//        {
//            newKeyFrame.scale[i] = scale[i];
//        }
//        newKeyFrame.rotation = getFieldAsInt(element[index]["rotation"]);
//        retVal.push_back(newKeyFrame);
//    }
//
//    return retVal;
//}

std::vector<Json::Value>
JsonReader::getArrayAsValue(const Json::Value& data_)
{
    std::vector<Json::Value> retVal;

    Json::Value element = data_;
    for (unsigned int index = 0; index < element.size(); ++index)  // Iterates over the sequence elements.
    {
        retVal.push_back(element[index]);
    }

    return retVal;
}

std::vector<std::string>
JsonReader::getArrayAsString(const Json::Value& data_)
{
    std::vector<std::string> retVal;

    Json::Value element = data_;
    for (unsigned int index = 0; index < element.size(); ++index)  // Iterates over the sequence elements.
    {
        retVal.push_back(getFieldAsString(element[index]));
    }

    return retVal;
}

std::vector<glm::vec2>
JsonReader::getArrayAsVec2(const Json::Value& data_)
{
    std::vector<glm::vec2> retVal;

    Json::Value element = data_;
    for (unsigned int index = 0; index < element.size(); ++index)  // Iterates over the sequence elements.
    {
        retVal.push_back(getFieldAsVec2(element[index]));
    }

    return retVal;
}

std::vector<glm::vec3>
JsonReader::getArrayAsVec3(const Json::Value& data_)
{
    std::vector<glm::vec3> retVal;

    Json::Value element = data_;
    for (unsigned int index = 0; index < element.size(); ++index)  // Iterates over the sequence elements.
    {
        retVal.push_back(getFieldAsVec3(element[index]));
    }

    return retVal;
}

std::vector<glm::vec4>
JsonReader::getArrayAsVec4(const Json::Value& data_)
{
    std::vector<glm::vec4> retVal;

    Json::Value element = data_;
    for (unsigned int index = 0; index < element.size(); ++index)  // Iterates over the sequence elements.
    {
        retVal.push_back(getFieldAsVec4(element[index]));
    }

    return retVal;
}

int
JsonReader::getFieldAsInt(const Json::Value& data_)
{
    int retVal = 0;

    retVal = data_.asInt();

    return retVal;
}

float
JsonReader::getFieldAsFloat(const Json::Value& data_)
{
    float retVal = 0.0f;

    retVal = data_.asFloat();

    return retVal;
}

std::string
JsonReader::getFieldAsString(const Json::Value& data_)
{
    std::string retVal = "NO_VALUE";

    std::string result = data_.asString();
    retVal = (result == "") ? retVal : result;

    return retVal;
}

bool
JsonReader::getFieldAsBool(const Json::Value& data_)
{
    bool retVal = false;

    retVal = data_.asBool();

    return retVal;
}

glm::vec2
JsonReader::getFieldAsVec2(const Json::Value& data_)
{
    glm::vec2 retVal = { 0.f, 0.f };

    Json::Value element = data_;
    if (element.size() >= 2)
    {
        retVal.x = element[0].asFloat();
        retVal.y = element[1].asFloat();
    }

    return retVal;
}

glm::ivec2
JsonReader::getFieldAsIVec2(const Json::Value& data_)
{
    glm::ivec2 retVal = { 0, 0 };

    Json::Value element = data_;
    if (element.size() >= 2)
    {
        retVal.x = element[0].asInt();
        retVal.y = element[1].asInt();
    }

    return retVal;
}

glm::vec3
JsonReader::getFieldAsVec3(const Json::Value& data_)
{
    glm::vec3 retVal = { 0.f, 0.f, 0.f };

    Json::Value element = data_;
    if (element.size() >= 3)
    {
        retVal.x = element[0].asFloat();
        retVal.y = element[1].asFloat();
        retVal.z = element[2].asFloat();
    }

    return retVal;
}

glm::ivec3
JsonReader::getFieldAsIVec3(const Json::Value& data_)
{
    glm::ivec3 retVal = { 0, 0, 0 };

    Json::Value element = data_;
    if (element.size() >= 3)
    {
        retVal.x = element[0].asInt();
        retVal.y = element[1].asInt();
        retVal.y = element[2].asInt();
    }

    return retVal;
}

glm::vec4
JsonReader::getFieldAsVec4(const Json::Value & data_, const float defaultValue_)
{
    glm::vec4 retVal(defaultValue_);

    Json::Value element = data_;
    if (element.size() >= 4)
    {
        retVal.r = element[0].asFloat();
        retVal.g = element[1].asFloat();
        retVal.b = element[2].asFloat();
        retVal.a = element[3].asFloat();
    }

    return retVal;
}

glm::ivec4
JsonReader::getFieldAsIVec4(const Json::Value & data_)
{
    glm::ivec4 retVal = { 0, 0, 0, 0 };

    Json::Value element = data_;
    if (element.size() >= 4)
    {
        retVal.r = element[0].asInt();
        retVal.g = element[1].asInt();
        retVal.b = element[2].asInt();
        retVal.a = element[2].asInt();
    }

    return retVal;
}
