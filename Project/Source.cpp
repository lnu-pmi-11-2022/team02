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
    string get_content(string file)
    {
        ifstream ifs("myFile.txt");
        string content((istreambuf_iterator<char>(ifs)), (istreambuf_iterator<char>()));
        return content;
    }
    void setContent(string fileContent)
    {
        this->fileContent = fileContent;
    }

    bool isOfType(string fileType) {
        string temp = "";

        for (char c : filePath) {
            if (c == '.') {
                temp = ".";
            }
            else if (temp[0] == 'c') {
                temp += c;
            }
        }

        if (temp == fileType) {
            return true;
        }return false;
    }

private:
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
        avaliableFileTypes.push_back(".mp4");
    }
	FileCollector(bool ignore): ignoreDirectories(ignore) {}
	FileCollector(bool ignore, vector<string> avFileTypes): ignoreDirectories(ignore), avaliableFileTypes(avFileTypes) {}

	//finds all files in chosen directory
	bool findFiles(string rootDir) {
		for (const auto& entry : fs::directory_iterator(rootDir)) {
			//if is file
			if (!entry.is_directory()) {

                //get file data
				//convert path to string
				string p = entry.path().string();

                //create File object
                File file;
                file.setPath(p);

				//add file path to vector
				files.push_back(file);
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

    void setAvaliableFileTypes(vector<string> fileTypes) {
        avaliableFileTypes = fileTypes;
    }

	vector<File> getFiles() {
		return files;
	}
};

int main() {

	//cout << "Irredeemable - the best team ever!!!" << endl;

	////testing file collector
	//FileCollector collector;
	//collector.findFiles("D:/Homework/");
	//vector<File> vec = collector.getFiles();
	//for (File file : vec) {
	//	cout << file.getPath() << endl;
	//}


    File f1;
    File f2;

    ifstream ifs("video.mp4");
    string content((istreambuf_iterator<char>(ifs)), (istreambuf_iterator<char>()));
    ifstream ifsc("video_2.mp4");
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