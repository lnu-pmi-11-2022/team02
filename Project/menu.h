#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <filesystem>
#include "file.h"
#include "filecollector.h"
#include<iostream>

using namespace std;
class Menu {
public:
	Menu(){}
	void Opening() {
		cout << "Welcome" << endl << "Team Irredeemable" << endl << "Fedyniak Volodymyr" << endl << "Kvasnytsia Uliana" << endl << "Yakymets Danylo" << endl << "Mularchyk Bohdan" <<endl<< "Fedorniak Serhii" << endl;
	}
	bool GetIgnoreDirectories() {
		cout << "Press button" << endl << "1- to ignore directories" << endl << "2- not to ignore directories" << endl;
		int button;
		cin >> button;
		if (button == 1) {
			return true;
		}
		else if (button == 2) {
			return false;
		}
		else {
			cout << "Wrong button" << endl;;
			GetIgnoreDirectories();
		}
	}

	vector<string> getAvaliableTypes() {
		cout<<"Press button" << endl << "1- to add to already possible types" << endl << "2- to add your own types" <<endl<<"3- to use default types"<<endl;
		int button;
		cin >> button;
		if (button == 1) {
			vector<string> avaliableFileTypes = { ".txt", ".img", ".png", ".mp4" };
			int decision;
			cout << "Avalible types" << endl;
			for (auto t : avaliableFileTypes) {
				cout << t << " ";
			}
			cout<<endl;
			do  {
				cout << "Enter type to add";
				string type;
				cin >> type;
				avaliableFileTypes.push_back(type);
				cout << "Press button" << endl << "1-to continue adding types" << endl << "Random key- to stop adding types" << endl;
				cin>> decision;
			} while (decision == 1);
			
			return avaliableFileTypes;
		}
		else if (button == 2) {
			vector<string> avaliableFileTypes;
			int  decision;
			do {
				cout << "Enter type to add";
				string type;
				cin >> type;
				avaliableFileTypes.push_back(type);
				cout << "Press button" << endl << "1-to continue adding types" << endl << "Random key- to stop adding types" << endl;
				cin >> decision;
			} while (decision == 1);

			return avaliableFileTypes;
		}
		else if (button == 3) {
			vector<string> avaliableFileTypes = { ".txt", ".img", ".png", ".mp4" };
			return avaliableFileTypes;
		}
		else {
			cout << "Wrong button";
			getAvaliableTypes();
		}
	}

	vector<File> GetFilesFromRootDir() {
		cout << "Enter root dir (path):" << endl;
		string rootDir;
		cin >> rootDir;
		FileCollector fileCollector(rootDir, GetIgnoreDirectories(), getAvaliableTypes());
		cout << "Files in "<<rootDir<<endl<<fileCollector;
		vector<File> files = fileCollector.getFiles();
		return files;
	}

	vector<Copies> GetCopies() {
		CopyDetector copyDetector;
        copyDetector.detector(GetFilesFromRootDir());
		vector<Copies>copies= copyDetector.getCopyPairs();
		return copies;

	}
		
		


	
};