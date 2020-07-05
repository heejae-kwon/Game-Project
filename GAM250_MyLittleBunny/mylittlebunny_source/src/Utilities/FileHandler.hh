/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      FileHandler.hh
Purpose:        Functions used to retrieve files
Language:       C++
Project:        GAM250
Author:         Name : Stuart Sulaski
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/

#pragma once

#include <dirent\dirent.h>

#include <vector>

namespace BE
{
    std::vector<std::string>    getFilesFromDir(const std::string& dir_);
    std::vector<std::string>    getFilesFromDirByType(const std::string& dir_, std::string& fileType_);
    std::vector<std::string>    getFilesFromDirByTypeList(const std::string& dir_, std::vector<std::string>& fileTypeList_);
    std::vector<std::string>    getDirsFromDir(const std::string& dir_);
    bool                        checkFileType(const std::string& file_, const std::string& fileType_);
}
