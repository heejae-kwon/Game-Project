/* ---------------------------------------------------------------------------
Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:      FileHandler.cpp
Purpose:        Functions used to retrieve files
Language:       C++
Project:        GAM250
Author:         Name : Stuart Sulaski
Email:          stuartsulaski@gmail.com
Creation date:  2017.06.12
----------------------------------------------------------------------------*/

#include "FileHandler.hh"

std::vector<std::string>
BE::getFilesFromDir(const std::string & dir_)
{
    DIR*dir;
    char buffer[PATH_MAX + 2];
    char*p = buffer;
    const char*src = dir_.c_str();
    char*end = &buffer[PATH_MAX];
    int ok;
    std::vector<std::string> fileList;

    /* Copy directory name to buffer*/
    while (p < end  && *src != '\0') {
        *p++ = *src++;
    }
    *p = '\0';

    /* Open directory stream*/
    dir = opendir(dir_.c_str());
    if (dir != NULL)
    {
        struct dirent*ent;

        /* Print all files and directories within the directory*/
        while ((ent = readdir(dir)) != NULL) {
            char*q = p;
            char c;

            /* Get final character of directory name*/
            if (buffer < q) {
                c = q[-1];
            }
            else {
                c = ':';
            }

            /* Append directory separator if not already there*/
            if (c != ':'  &&  c != '/'  &&  c != '\\') {
                *q++ = '/';
            }

            /* Append file name*/
            src = ent->d_name;
            while (q < end  && *src != '\0') {
                *q++ = *src++;
            }
            *q = '\0';

            /* Decide what to do with the directory entry*/
            switch (ent->d_type) {
            case DT_LNK:
            case DT_REG:
                fileList.push_back(buffer);
                break;

            case DT_DIR:
                //          /* Scan sub-directory recursively*/
                //          if (strcmp(ent->d_name, ".") != 0
                //              && strcmp(ent->d_name, "..") != 0) {
                //              getFilesFromDir(buffer);
                //          }
                break;

            default:
                /* Ignore device entries*/
                /*NOP*/;
            }
        }
        closedir(dir);
        ok = 1;

    }
    else {
        /* Could not open directory*/
        printf("## Cannot open directory %s\n", dir_.c_str());
        ok = 0;
    }
    return fileList;
}

std::vector<std::string>
BE::getFilesFromDirByType(const std::string & dir_, std::string & fileType_)
{
    DIR*dir;
    char buffer[PATH_MAX + 2];
    char*p = buffer;
    const char*src = dir_.c_str();
    char*end = &buffer[PATH_MAX];
    int ok;
    std::vector<std::string> fileList;

    /* Copy directory name to buffer*/
    while (p < end  && *src != '\0') {
        *p++ = *src++;
    }
    *p = '\0';

    /* Open directory stream*/
    dir = opendir(dir_.c_str());
    if (dir != NULL)
    {
        struct dirent*ent;

        /* Print all files and directories within the directory*/
        while ((ent = readdir(dir)) != NULL) {
            char*q = p;
            char c;

            /* Get final character of directory name*/
            if (buffer < q) {
                c = q[-1];
            }
            else {
                c = ':';
            }

            /* Append directory separator if not already there*/
            if (c != ':'  &&  c != '/'  &&  c != '\\') {
                *q++ = '/';
            }

            /* Append file name*/
            src = ent->d_name;
            while (q < end  && *src != '\0') {
                *q++ = *src++;
            }
            *q = '\0';

            /* Decide what to do with the directory entry*/
            switch (ent->d_type) {
            case DT_LNK:
            case DT_REG:
                /* Output file name with directory*/
                if (checkFileType(buffer, fileType_) == true)
                {
                    std::string fn(buffer);

                    fileList.push_back(fn.substr(fn.find_last_of("/") + 1));
                }
                break;

            case DT_DIR:
                //      /* Scan sub-directory recursively*/
                //      if (strcmp(ent->d_name, ".") != 0
                //          && strcmp(ent->d_name, "..") != 0) {
                //          getFilesFromDir(buffer);
                //      }
                break;

            default:
                /* Ignore device entries*/
                /*NOP*/;
            }
        }
        closedir(dir);
        ok = 1;

    }
    else {
        /* Could not open directory*/
        printf("## Cannot open directory %s\n", dir_.c_str());
        ok = 0;
    }
    return fileList;
}

std::vector<std::string>
BE::getFilesFromDirByTypeList(const std::string & dir_, std::vector<std::string>& fileTypeList_)
{
    DIR*dir;
    char buffer[PATH_MAX + 2];
    char*p = buffer;
    const char*src;
    char*end = &buffer[PATH_MAX];
    int ok;
    std::vector<std::string> fileList;

    /* Copy directory name to buffer*/
    src = dir_.c_str();
    while (p < end  && *src != '\0') {
        *p++ = *src++;
    }
    *p = '\0';

    /* Open directory stream*/
    dir = opendir(dir_.c_str());
    if (dir != NULL)
    {
        struct dirent*ent;

        /* Print all files and directories within the directory*/
        while ((ent = readdir(dir)) != NULL) {
            char*q = p;
            char c;

            /* Get final character of directory name*/
            if (buffer < q) {
                c = q[-1];
            }
            else {
                c = ':';
            }

            /* Append directory separator if not already there*/
            if (c != ':'  &&  c != '/'  &&  c != '\\') {
                *q++ = '/';
            }

            /* Append file name*/
            src = ent->d_name;
            while (q < end  && *src != '\0') {
                *q++ = *src++;
            }
            *q = '\0';

            /* Decide what to do with the directory entry*/
            switch (ent->d_type) {
            case DT_LNK:
            case DT_REG:
                /* Output file name with directory*/
                for (auto fileType : fileTypeList_)
                {
                    if (checkFileType(buffer, fileType) == true)
                    {
                        fileList.push_back(buffer);
                    }
                }
                break;

            case DT_DIR:
                //				/* Scan sub-directory recursively*/
                //				if (strcmp(ent->d_name, ".") != 0
                //					&& strcmp(ent->d_name, "..") != 0) {
                //					getFilesFromDir(buffer);
                //				}
                break;

            default:
                /* Ignore device entries*/
                /*NOP*/;
            }
        }
        closedir(dir);
        ok = 1;

    }
    else {
        /* Could not open directory*/
        printf("## Cannot open directory %s\n", dir_.c_str());
        ok = 0;
    }
    return fileList;
}

std::vector<std::string>
BE::getDirsFromDir(const std::string & dir_)
{
    DIR*dir;
    char buffer[PATH_MAX + 2];
    char*p = buffer;
    const char*src = dir_.c_str();
    char*end = &buffer[PATH_MAX];
    int ok;
    std::vector<std::string> dirList;

    /* Copy directory name to buffer*/
    while (p < end  && *src != '\0') {
        *p++ = *src++;
    }
    *p = '\0';

    /* Open directory stream*/
    dir = opendir(dir_.c_str());
    if (dir != NULL)
    {
        struct dirent*ent;

        /* Print all files and directories within the directory*/
        while ((ent = readdir(dir)) != NULL) {
            char*q = p;
            char c;

            /* Get final character of directory name*/
            if (buffer < q) {
                c = q[-1];
            }
            else {
                c = ':';
            }

            /* Append directory separator if not already there*/
            if (c != ':'  &&  c != '/'  &&  c != '\\') {
                *q++ = '/';
            }

            /* Append file name*/
            src = ent->d_name;
            while (q < end  && *src != '\0') {
                *q++ = *src++;
            }
            *q = '\0';

            /* Decide what to do with the directory entry*/
            switch (ent->d_type) {
            case DT_LNK:
            case DT_REG:
                break;

            case DT_DIR:
                dirList.push_back(buffer);
                break;

            default:
                /* Ignore device entries*/
                /*NOP*/;
            }
        }
        closedir(dir);
        ok = 1;

    }
    else {
        /* Could not open directory*/
        printf("## Cannot open directory %s\n", dir_.c_str());
        ok = 0;
    }
    return dirList;
}

bool
BE::checkFileType(const std::string & file_, const std::string & fileType_)
{
    bool ret = false;

    std::string fn = file_;
    if (fn.substr(fn.find_last_of(".") + 1) == fileType_)
    {
        ret = true;
    }
    else
    {
        ret = false;
    }
    return (ret);
}
