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

    File() {}
    File(string path):filePath(path) {}

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
        int size=0;
        for (int i = filePath.size(); filePath[i] != '\\' ; i--)
        {
                size++;
        }
        int start_of_name = filePath.size()-size;
        string name="";
        for (int i = start_of_name; i < start_of_name+size; i++)
        {
            if(filePath[i]!='\\')
            {
            name+= filePath[i];
            }
        }

        char *cName = new char[name.size()];
    
        strcpy(cName,name.c_str());
        remove(cName);
    }

    void setName(string name)
    {
        fileName = name;
    }

    //checks file type
    bool isOfType(string fileType) {
        string temp = "";

        //find last dot and save everything after it
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