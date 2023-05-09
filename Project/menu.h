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
	FileCollector fileCollector;
	CopyDetector copyDetector;
public:
	Menu(){}
	void opening() {
		cout << "Welcome" << endl << "Team Irredeemable" << endl << "Fedyniak Volodymyr" << endl << "Kvasnytsia Uliana" << endl << "Yakymets Danylo" << endl << "Mularchyk Bohdan" <<endl<< "Fedorniak Serhii" << endl;
	}
	bool getIgnoreDirectories() {
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
			getIgnoreDirectories();
		}
	}

	void getAvaliableTypes() {
		cout<<"Press button" << endl << "1- to add to already possible types" << endl << "2- to add your own types" <<endl<<"3- to use default types"<<endl;
		int button;
		cin >> button;
		if (button == 1) {
			vector<string> avaliableFileTypes = fileCollector.getAvaliableTypes();
			int decision;
			cout << "Avalible types" << endl;
			for (auto t : avaliableFileTypes) {
				cout << t << " ";
			}
			cout<<endl;
			do  {
				cout << "Enter type to add";
				string type;
				getline(cin >> ws, type);
				fileCollector.addFileType(type);
				cout << "Press button" << endl << "1-to continue adding types" << endl << "Random key- to stop adding types" << endl;
				cin>> decision;
			} while (decision == 1);
		}
		else if (button == 2) {
			vector<string> avaliableFileTypes;
			fileCollector.setAvaliableFileTypes(avaliableFileTypes);
			int  decision;
			do {
				cout << "Enter type to add: ";
				string type;
				getline(cin >> ws, type);
				fileCollector.addFileType(type);
				cout << "Press button" << endl << "1-to continue adding types" << endl << "Random key- to stop adding types" << endl;
				cin >> decision;
			} while (decision == 1);
		}
		else if (button == 3) {
			vector<string> avaliableFileTypes = { ".txt", ".img", ".png", ".mp4" };
		}
		else {
			cout << "Wrong button";
			getAvaliableTypes();
		}
	}

	void getRootDir() {
		cout << "Enter root dir (path):" << endl;
		string rootDir;
		getline(cin, rootDir);
		fileCollector = new FileCollector();
		fileCollector.setIgnoreDirectories(getIgnoreDirectories());
		getAvaliableTypes();
		fileCollector.findFiles(rootDir);
		cout << "Files in "<<rootDir<<endl<<fileCollector;
	}

	void findCopies() {
		copyDetector.detector(fileCollector.getFiles());
	}

	//are there files with copies
	bool isAnyCopies() {
		for (Copies c : copyDetector.getCopyPairs()) {
			if (c.CopyVector.size() > 0) {
				return true;
			}
		}
		return false;
	}

	//print that there is no copies of files found
	void printNoCopiesFound() {
		cout << "There are no copies in this directory" << endl;
	}

	void filesToDelete() {
		cout << copyDetector << endl;
		cout << "Please enter indexes of original files whose copies you want to delete\n(Enter -1 to delete all)\n";
		vector<int> inputs;
		//read input to buffer
		string buffer;
		getline(cin >> ws, buffer);
		istringstream iss(buffer);
		//go through every input divided by space and put it into int data 
		int data;
		while (iss >> data)
			inputs.push_back(data);

		//input amount exception
		if (inputs.size() > copyDetector.getCopyPairs().size()) {
			throw(length_error("Too many indexes"));
		}
		//deletion
		for (int i : inputs) {
			

			//if input is -1 delete every copy
			if (i == -1) {
				copyDetector.deleteAllCopies();
				cout << "Every copy was successfully deleted" << endl;
				break;
			}
			//index out of range exception
			if (i >= copyDetector.getCopyPairs().size()) {
				throw(out_of_range("One of indexes is out of range"));
			}
			//get father file from copyDetector
			File file = copyDetector.getCopyPairs()[i].Father;
			copyDetector.deleteFatherCopies(file);
			cout << "Copies of " << file << " were successfully deleted" << endl;
		}
		
	}
};