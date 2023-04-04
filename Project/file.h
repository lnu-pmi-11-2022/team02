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
        ifstream file1(this->filePath);
        ifstream file2(file.filePath);
        

        const int n = 1; // number of characters to read per iteration
        char buffer1[n];
        char buffer2[n];
        while (file1.read(buffer1, n)&&file2.read(buffer2,n)) {
        // do something with the buffer
            for (int i = 0; i < n; i++)
            {
                if(buffer1[i]!=buffer2[i])
                {
                    return false;
                }
            }
        
        }
        return true;
    }
    void setPath(string FP)
    {
        this->filePath = FP;
    }
    string getPath()
    {
        return filePath;
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
};