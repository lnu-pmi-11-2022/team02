#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <filesystem>
#include "file.h"
#include "filecollector.h"
#include "copyfinder.h"
#include<iostream>
#include <stdlib.h>

//colors
#define GREEN_TEXT "\033[32m" 
#define YELLOW_TEXT "\033[33m" 
#define RESET_COLOR "\033[0m" 
#define RED_TEXT "\033[31m"
#define WHITE_TEXT "\033[37m"
#define BRIGHT_WHITE_TEXT "\033[97m"
#define GREEN_BACK "\033[42m"
#define RED_BACK "\033[41m"


using namespace std;
class Menu {
	FileCollector fileCollector;
	CopyDetector copyDetector;
public:
	Menu(){}
	void opening() {
		cout << YELLOW_TEXT << "Welcome" << endl << "Team Irredeemable" << endl << "Fedyniak Volodymyr" << endl << "Kvasnytsia Uliana" << endl << "Yakymets Danylo" << endl << "Mularchyk Bohdan" <<endl<< "Fedorniak Serhii" << RESET_COLOR << endl;
	}
	bool getIgnoreDirectories() {
		cout << GREEN_BACK << BRIGHT_WHITE_TEXT << "Press button" << endl << "1- to ignore directories" << endl << "2- not to ignore directories" << RESET_COLOR << endl;
		int button;
		cin >> button;
		if (button == 1) {
			return true;
		}
		else if (button == 2) {
			return false;
		}
		else {
			cout << RED_BACK << BRIGHT_WHITE_TEXT << "Wrong button" << RESET_COLOR << endl;;
			getIgnoreDirectories();
		}
	}

	void getAvaliableTypes() {
		cout<< GREEN_BACK << BRIGHT_WHITE_TEXT << "Press button" << endl << "1- to add to already possible types" << endl << "2- to add your own types" <<endl<<"3- to use default types"<< RESET_COLOR <<endl;
		int button;
		cin >> button;
		if (button == 1) {
			vector<string> avaliableFileTypes = fileCollector.getAvaliableTypes();
			char decision;
			cout << "Avalible types: " << endl;
			for (auto t : avaliableFileTypes) {
				cout << t << " ";
			}
			cout<<endl;
			do  {
				cout << GREEN_BACK << BRIGHT_WHITE_TEXT << "Enter type to add: " << RESET_COLOR;
				string type;
				getline(cin >> ws, type);
				fileCollector.addFileType(type);
				cout << GREEN_BACK << BRIGHT_WHITE_TEXT <<"Press button" << endl << "1-to continue adding types" << endl << "Random key- to stop adding types" << RESET_COLOR << endl;
				cin>> decision;
			} while (decision == '1');
		}
		else if (button == 2) {
			vector<string> avaliableFileTypes;
			fileCollector.setAvaliableFileTypes(avaliableFileTypes);
			char decision;
			do {
				cout << GREEN_BACK << BRIGHT_WHITE_TEXT << "Enter type to add: " << RESET_COLOR;
				string type;
				getline(cin >> ws, type);
				fileCollector.addFileType(type);
				cout << GREEN_BACK << BRIGHT_WHITE_TEXT << "Press button" << endl << "1-to continue adding types" << endl << "Random key- to stop adding types" << RESET_COLOR << endl;
				cin >> decision;
			} while (decision == '1');
		}
		else if (button == 3) {
			vector<string> avaliableFileTypes = { ".txt", ".img", ".png", ".mp4" };
		}
		else {
			cout << RED_BACK << BRIGHT_WHITE_TEXT << "Wrong button" << RESET_COLOR << endl;
			getAvaliableTypes();
		}
	}

	void getRootDir() {
		cout << GREEN_BACK << BRIGHT_WHITE_TEXT << "Enter root dir (path):"<< RESET_COLOR << endl;
		string rootDir;
		getline(cin, rootDir);
		//check if directory was found
		checkDirectory(rootDir);

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
		cout << YELLOW_TEXT << "There are no copies in this directory" << RESET_COLOR << endl;
	}

	void filesToDelete() {
		cout << copyDetector << endl;
		cout << GREEN_BACK << BRIGHT_WHITE_TEXT << "Please enter indexes of original files whose copies you want to delete" << RESET_COLOR<< endl << GREEN_BACK <<"(Enter -1 to delete all)" << RESET_COLOR << endl;
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
				cout << GREEN_TEXT << "Every copy was successfully deleted" << RESET_COLOR << endl;
				break;
			}
			//index out of range exception
			if (i >= copyDetector.getCopyPairs().size()) {
				throw(out_of_range("One of indexes is out of range"));
			}
			//get father file from copyDetector
			File file = copyDetector.getCopyPairs()[i].Father;
			copyDetector.deleteFatherCopies(file);
			cout << GREEN_TEXT << "Copies of " << file << GREEN_TEXT << " were successfully deleted" << RESET_COLOR << endl;
			
		}
		//change released space color and than change color back
		cout << "You have released " << GREEN_TEXT << convertBytes(copyDetector.getReleasedSpace()) << endl << RESET_COLOR;

	}
};