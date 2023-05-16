#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <filesystem>
#include "file.h"

using namespace std;
namespace fs = std::filesystem;

//check if directory is found
void checkDirectory(fs::path rootDir) {
    try {

        //check if works without errors
        fs::directory_iterator it = fs::directory_iterator(rootDir);
    }
    catch (exception& e) {
        ostringstream os;
        os << "Wrong path " << rootDir << " directory could not be found" << endl;
        throw(invalid_argument(os.str()));
    }
}

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
    FileCollector(fs::path rootDir) : FileCollector() {
        findFiles(rootDir);
    }
    //constructor with root directory based on const char array
    FileCollector(const char rootDir[]) : FileCollector() {
        findFiles((fs::path)rootDir);
    }
    //constructor with root directory, ignore directories
    FileCollector(fs::path rootDir, bool ignore) : FileCollector(ignore) {
        findFiles(rootDir);
    }
    //constructor with root directory, ignore directories and avaliable types
    FileCollector(fs::path rootDir, bool ignore, vector<string> avFileTypes) : FileCollector(ignore, avFileTypes) {
        findFiles(rootDir);
    }

	//find all files in chosen directory
    //Parameter inner: if true says that findFiles was called recursively
	bool findFiles(fs::path rootDir, bool inner = false) {

		for (const auto& entry : fs::directory_iterator(rootDir)) {
			//if is file
			if (!entry.is_directory()) {
                //convert path to string
                fs::path p = entry.path().string();

                //get file size from entry
                uintmax_t size = entry.file_size();

                //create File object
                File file(p, size);


                //if is one of avaliable file types
                if (checkAllFileTypes(file)) {
                    
                    //add file path to vector
                    files.push_back(file);
                }
			}
			//if file is directory and directories are not ignored
			else if (!ignoreDirectories) {
				//convert path to string
                fs::path p = entry.path().string();

				//go into this directory with inner flag set to true
				findFiles(p, true);
			}
		}
        //if no files found and is not inner directory
        if (files.size() == 0 && !inner) {
            throw(length_error("No files were found"));
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

    //returns avaliable file types
    vector<string> getAvaliableTypes() {
        return avaliableFileTypes;
    }

    friend ostream& operator<<(ostream& os, FileCollector& filecol) {
        int c = 1;
        for (File f : filecol.getFiles()) {
            os <<  c << " - " << f << endl;
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
