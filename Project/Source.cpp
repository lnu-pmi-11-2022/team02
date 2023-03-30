//FILE COPIES FINDER
//Team 02 - Irredeemable
//Members:
//Fedyniak Volodymyr
//Kvasnytsia Uliana
//Yakymets Danylo
//Mularchyk Bohdan
//Fedorniak Serhii

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <sstream>
#include <filesystem>
#include <stdio.h>
#include <cstring>

using namespace std;
namespace fs = std::filesystem;


#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class File
{
public:

    friend ostream& operator<<(ostream& os, File& file )
    {
        os<< file.filePath;
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

        string revName="";
        for (int i = filePath.size(); filePath[i] != '\\' ; i--)
        {
            if(filePath[i]!=0&&filePath[i]!='\\')
            {
                revName+=filePath[i];
            }
            
        }
        string name="";
        for (int i = revName.size(); i >-1; i--)
        {
            if(revName[i]!=0&&revName[i]!='\\')
            {
                name+=revName[i];   
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


class FileCollector {
private:
	//string is temp while there is no File class
	vector<File> files;
	bool ignoreDirectories;
    vector<string> avaliableFileTypes;
public:
	FileCollector(): ignoreDirectories(false) {
        //add types to vector
        avaliableFileTypes.push_back(".txt");
        avaliableFileTypes.push_back(".img");
        avaliableFileTypes.push_back(".png");
        avaliableFileTypes.push_back(".mp4");
    }
	FileCollector(bool ignore): ignoreDirectories(ignore) {}
	FileCollector(bool ignore, vector<string> avFileTypes): ignoreDirectories(ignore), avaliableFileTypes(avFileTypes) {}

	//finds all files in chosen directory
	bool findFiles(string rootDir) {
		for (const auto& entry : fs::directory_iterator(rootDir)) {
			//if is file
			if (!entry.is_directory()) {
                //convert path to string
                string p = entry.path().string();

                //create File object
                File file;
                file.setPath(p);

                //if is one of avaliable file types
                if (checkAllFileTypes(file)) {
                    
                    //add file path to vector
                    files.push_back(file);
                }
			}
			//if file is directory and directories are not ignored
			else if (!ignoreDirectories) {
				//convert path to string
				string p = entry.path().string();

				//go into this directory
				findFiles(p);
			}
		}
			
		return true;
	}

    //check if files are one of avaliable types
    bool checkAllFileTypes(File file) {
        for (string type : avaliableFileTypes) {
            if (file.isOfType(type)) {
                return true;
            }
        }
        return false;
    }

    //add new avaliable file type
    bool addFileType(string fileType) {
        //if type enetered with .
        if (fileType[0] == '.') {
            avaliableFileTypes.push_back(fileType);
            return true;
        }
        //if type enetered without .
        else if (fileType.find('.') == string::npos) {
            avaliableFileTypes.push_back("." + fileType);
            return true;
        }
        //wrong input
        return false;

    }

	void setIgnoreDirectories(bool ignore) {
		ignoreDirectories = ignore;
	}

    void setAvaliableFileTypes(vector<string> fileTypes) {
        avaliableFileTypes = fileTypes;
    }

	vector<File> getFiles() {
		return files;
	}
};


int main() {

	cout << "Irredeemable - the best team ever!!!" << endl;
     
    File f1;
    f1.setPath("E:\\VS Projects\\Team_project\\team02\\Project\\test_1 copy.txt");
    f1.removeFile();

    // File f1;
    // File f2;
    // ifstream file1("test_1 copy.txt");
    // ifstream file2("test_1.txt");

    // string content1((istreambuf_iterator<char>(file1)), (istreambuf_iterator<char>()));
    // string content2((istreambuf_iterator<char>(file2)), (istreambuf_iterator<char>()));

    // f1.setContent(content1);
    // f2.setContent(content2);
    
    // if(f1==f2)
    // {
    //     cout<<"True";
    // }
    // else 
    // {
    //     cout<<"False";
    // }
	return 1;
    
    
    

}