/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      BaseProp.cpp
Purpose:        BaseProp is the interface that all other props inherit from
Language:       C++
Project:        GAM250
Author:         Name : Stuart Sulaski
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/

#include <Props\BaseProp.hpp>

BE::Prop::Type
BE::Prop::stringToEnum(std::string& str_)
{
    if (str_ == "IMAGE")
    {
        return IMAGE;
    }
    else if (str_ == "AUDIO")
    {
        return AUDIO;
    }
    else if (str_ == "ANIMATION")
    {
        return ANIMATION;
    }
    return TYPE_LENGTH;
}
