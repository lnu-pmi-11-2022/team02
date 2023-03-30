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
	FileCollector(bool ignore): ignoreDirectories(ignore) {
        //add types to vector
        avaliableFileTypes.push_back(".txt");
        avaliableFileTypes.push_back(".img");
        avaliableFileTypes.push_back(".png");
        avaliableFileTypes.push_back(".mp4");
    }
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

    friend ostream& operator<<(ostream& os, FileCollector& filecol) {
        int c = 1;
        for (File f : filecol.getFiles()) {
            os <<  c << " - " << f.getPath() << endl;
            c++;
        }
        return os;
    }
};
