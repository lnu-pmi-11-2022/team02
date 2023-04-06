#pragma once

#include <iostream>
#include <vector>
#include <filesystem>
#include <fstream>
#include "file.h"

using namespace std;
//Copies: Father + vector of his copies
struct Copies {
	File Father;
	vector<File> CopyVector;

	// constructors
	Copies(File F): Father(F) {}
	Copies(File F, File C) {
		Father = F;
		CopyVector.push_back(C);
	}

	void PrintCopieswFather() {
		cout << "original file:\n" << Father << endl;
		cout << "copies:\n";
		for (int i = 0; i < CopyVector.size(); i++) {
			cout << CopyVector[i]<<endl;
		}
	}
	void AddCopyToFather(File copy) {
		CopyVector.push_back(copy);
	}
};

//func is copy that checks and sets a bool field of file to true
//maybe it should be in "for" 


class CopyDetector {
private:
	vector<Copies> CopyPairs;
	
public:
	CopyDetector(){}

	//add copy to te vector of copies 
	void AddToCVector(File father, File copy) {
		if (CopyPairs.empty() || CopyPairs.back().Father != father) 
			CopyPairs.push_back(Copies(father, copy));
		else {
			CopyPairs.back().AddCopyToFather(copy);
		}
	}
};