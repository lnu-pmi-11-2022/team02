#pragma once

#include <iostream>
#include <string>
#include <stdio.h>
#include <cstring>
#include <filesystem>
#include <fstream>

using namespace std;
namespace fs = std::filesystem;
using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;
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
        ifstream file1(this->filePath);
        ifstream file2(file.filePath);
        
        file1 >> noskipws;
        file2 >> noskipws;

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

   void removeFile() {
    int size = 0;
    for (int i = filePath.size(); filePath[i] != '\\'; i--) {
        size++;
    }
    
    string tempName;
    for (int i = filePath.size() - size; i < filePath.size(); i++) {
        if (filePath[i] != '\\')
            tempName += filePath[i];
    }
    
    string tempPath;
    for (int i = 0; i < filePath.size() - size; i++) {
        tempPath += filePath[i];
    }
    
    char* fileName = new char[size + 1];
    strcpy(fileName, tempName.c_str());
    
    for (const auto& dirEntry : fs::recursive_directory_iterator(tempPath)) {
        if (is_regular_file(dirEntry.path()) && dirEntry.path().filename() == fileName) {
            remove(dirEntry.path());
            break;
        }
    }
   
   
}
    void setIsCopy(bool newStatus)
   {
    isCopy= newStatus;
   }
   bool getIsCopy()
   {
    return isCopy;
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
    bool isCopy = false;
};
