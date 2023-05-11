#pragma once

#include <iostream>
#include <string>
#include <stdio.h>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <sstream>

//colors
#define YELLOW_TEXT "\033[33m" 
#define RESET_COLOR "\033[0m" 

using namespace std;
namespace fs = std::filesystem;
using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;

//convert int of bytes to user friendly output in b, kb, mb, gb, or tb
string convertBytes(int bytes) {
    //constatnts
    const float tb = 1099511627776;
    const float gb = 1073741824;
    const float mb = 1048576;
    const float kb = 1024;

    //creating string stream and setting precision to 2
    ostringstream os;
    os << fixed <<setprecision(2);

    //formatting
    if (bytes >= tb)
        os << bytes / tb << "TB";
    else if (bytes >= gb && bytes < tb)
        os << bytes / gb << "GB";
    else if (bytes >= mb && bytes < gb)
        os << bytes / mb << "MB";
    else if (bytes >= kb && bytes < mb)
        os << bytes / kb << "KB";
    else if (bytes < kb)
        os << bytes << "B";

    else
        os << bytes<< "B";

    return os.str();
}

class File
{

public:

    File() {}
    File(string path,int s):filePath(path), size(s) {}

    friend ostream& operator<<(ostream& os, File& file)
    {
        //change colors to yellow and back
        os << file.filePath << " (" << YELLOW_TEXT << convertBytes(file.size) << RESET_COLOR <<")";
        return os;
    }
   bool operator==(File& file)
    {
        ifstream file1(this->filePath);
        ifstream file2(file.filePath);
        if(this->getSize()!=file.getSize())
        {
            return false;
        }
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

    // dividing file name from path
    string tempName;
    for (int i = filePath.size() - size; i < filePath.size(); i++) {
        if (filePath[i] != '\\')
            tempName += filePath[i];
    }
    
    // temporary folder path where we need to delete file
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
    int getSize()
    {
        return size;
    }
    void setSize(int s)
    {
        size = s;
    }
private:
    string filePath;
    bool isCopy = false;
    int size;
};
