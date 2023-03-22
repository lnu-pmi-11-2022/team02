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
	FileCollector collector;
	collector.findFiles("D:/Homework/");
	vector<string> vec = collector.getFiles();
	for (string file : vec) {
		cout << file << endl;
	}
	return 1;
}