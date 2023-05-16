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
    File(fs::path path,int s):filePath(path), size(s) {}

    friend ostream& operator<<(ostream& os, File& file)
    {
        //change colors to yellow and back
        os << file.filePath << RESET_COLOR << " (" << YELLOW_TEXT << convertBytes(file.size) << RESET_COLOR <<")";
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
    fs::path getPath()
    {
        return filePath;
    }

   void removeFile() {
       fs::remove(filePath);
   
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
        string temp = filePath.extension().generic_string();
        
        //compare
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
    fs::path filePath;
    bool isCopy = false;
    int size;
};
