#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <filesystem>
#include "file.h"

using namespace std;
namespace fs = std::filesystem;
class FileCollector {
private:
    vector<File> files;
	bool ignoreDirectories;
    vector<string> avaliableFileTypes;
public:
    //default constructor
	FileCollector(): ignoreDirectories(false) {
        //add types to vector
        avaliableFileTypes = { ".txt", ".img", ".png", ".mp4"};
    }
    //constructor with ignore directories
	FileCollector(bool ignore): ignoreDirectories(ignore) {
        //add types to vector
        avaliableFileTypes = { ".txt", ".img", ".png", ".mp4" };
    }
    //constructor with ignore directories and avaliable types
	FileCollector(bool ignore, vector<string> avFileTypes): ignoreDirectories(ignore), avaliableFileTypes(avFileTypes) {}

    //constructor with root directory
    FileCollector(string rootDir) : FileCollector() {
        findFiles(rootDir);
    }
    //constructor with root directory based on const char array
    FileCollector(const char rootDir[]) : FileCollector() {
        findFiles((string)rootDir);
    }
    //constructor with root directory, ignore directories
    FileCollector(string rootDir, bool ignore) : FileCollector(ignore) {
        findFiles(rootDir);
    }
    //constructor with root directory, ignore directories and avaliable types
    FileCollector(string rootDir, bool ignore, vector<string> avFileTypes) : FileCollector(ignore, avFileTypes) {
        findFiles(rootDir);
    }

	//find all files in chosen directory
	bool findFiles(string rootDir) {
		for (const auto& entry : fs::directory_iterator(rootDir)) {
			//if is file
			if (!entry.is_directory()) {
                //convert path to string
                string p = entry.path().string();

                //create File object
                File file(p);

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

    //returns vector of files of type File
	vector<File> getFiles() {
		return files;
	}

    friend ostream& operator<<(ostream& os, FileCollector& filecol) {
        int c = 1;
        for (File f : filecol.getFiles()) {
            os <<  c << " - " << f.getPath() << endl;
            c++;
        }
        return os;
    }

    File& operator[](int i) {
        if (i >= files.size()) {
            //create error text
            ostringstream os;
            os << "Can`t get File by index - " << i << " is out of range. [Vector size: " << files.size() << "]";

            throw(invalid_argument(os.str()));
        }
        return files[i];
    }
};
