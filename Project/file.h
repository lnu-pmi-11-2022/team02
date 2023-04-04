#pragma once

#include <iostream>
#include <string>
#include <stdio.h>
#include <cstring>
#include <filesystem>
#include <fstream>

using namespace std;

class File
{
public:

    friend ostream& operator<<(ostream& os, File& file)
    {
        os << file.filePath;
        return os;
    }
    bool operator==(File& file)
    {
        string temp1;
        string temp2;
        for (int i = 0; i < fileContent.size(); i++)
        {
            if (i % 10 != 0 || i == 0)
            {
                temp1 += this->fileContent[i];
                temp2 += file.fileContent[i];
            }
            else
            {
                if (temp1 != temp2)
                {
                    return false;
                }
                temp1 = "";
                temp2 = "";
            }

        }
        return true;
    }
    string getContent(string file)
    {
        ifstream ifs("myFile.txt");
        string content((istreambuf_iterator<char>(ifs)), (istreambuf_iterator<char>()));
        return content;
    }
    void setPath(string FP)
    {
        this->filePath = FP;
    }
    string getPath()
    {
        return filePath;
    }
    void setContent(string fileContent)
    {
        this->fileContent = fileContent;
    }

    void removeFile()
    {

        string revName = "";
        for (int i = filePath.size(); filePath[i] != '\\'; i--)
        {
            if (filePath[i] != 0 && filePath[i] != '\\')
            {
                revName += filePath[i];
            }

        }
        string name = "";
        for (int i = revName.size(); i > -1; i--)
        {
            if (revName[i] != 0 && revName[i] != '\\')
            {
                name += revName[i];
            }

        }

        char* cName = new char[name.size()];

        strcpy(cName, name.c_str());
        remove(cName);
    }

    void setName(string name)
    {
        fileName = name;
    }
    bool isOfType(string fileType) {
        string temp = "";

        for (char c : filePath) {
            if (c == '.') {
                temp = ".";
            }
            else if (temp[0] == '.') {
                temp += c;
            }
        }

        if (temp == fileType) {
            return true;
        }
        return false;
    }

private:
    string filePath;
    string fileName;
    string fileContent;
};