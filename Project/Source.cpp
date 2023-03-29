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


using namespace std;
namespace fs = std::filesystem;


#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class File
{
public:
    bool operator==(File& file)
    {
        bool isCopy = true;
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
                    isCopy = false;
                    return isCopy;
                }
                temp1 = "";
                temp2 = "";
            }

        }
        return isCopy;
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
private:
    string filePath;
    string fileName;
    string fileContent;
};


class FileCollector {
private:
	//string is temp while there is no File class
	vector<string> files;
	bool ignoreDirectories;
public:
	FileCollector(): ignoreDirectories(false) {}
	FileCollector(bool ignore): ignoreDirectories(ignore) {}

	//finds all files in chosen directory
	bool findFiles(string rootDir) {
		for (const auto& entry : fs::directory_iterator(rootDir)) {
			//if is file
			if (!entry.is_directory()) {
				//convert path to string
				string p = entry.path().string();

				//add file path to vector
				files.push_back(p);
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

	void setIgnoreDirectories(bool ignore) {
		ignoreDirectories = ignore;
	}

	vector<string> getFiles() {
		return files;
	}
};

int main() {

	cout << "Irredeemable - the best team ever!!!" << endl;

	//testing file collector
	// FileCollector collector;
	// collector.findFiles("D:/Homework/");
	// vector<string> vec = collector.getFiles();
	// for (string file : vec) {
	// 	cout << file << endl;
	// }

    
    File f1;
    File f2;

    ifstream ifs("test.txt");
    string content((istreambuf_iterator<char>(ifs)), (istreambuf_iterator<char>()));
    ifstream ifsc("test copy.txt");
    string content_copy((istreambuf_iterator<char>(ifsc)), (istreambuf_iterator<char>()));

    f1.setContent(content);
    f2.setContent(content_copy);

    if (f1 == f2)
    {
        cout << "Copies";
    }
    else
    {
        cout << "Not copies";
    }

	return 1;



}