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
    Copies() = default;

    Copies(File F) : Father(F) {}

    Copies(File F, File C) {
        Father = F;
        CopyVector.push_back(C);
    }

    void PrintCopiesFather() {
        cout << "Original file:\n" << Father << endl;
        cout << "Copies:\n";
        for (int i = 0; i < CopyVector.size(); i++) {
            cout << CopyVector[i] << endl;
        }
        cout << endl;
    }

    void AddCopyToFather(File copy) {
        CopyVector.push_back(copy);
    }

};


class CopyDetector {
private:
    vector<Copies> CopyPairs;
public:

    //Basic method for selecting copies and parent elements
    vector<Copies> CopyDetect(vector<File> files) {
        for (int i = 0; i < files.size(); i++) {

            //Ignoring file copies
            if (files[i].getIsCopy()) {
                continue;
            }
            //Creating a parent structure
            Copies temp(files[i]);
            //Selection of copies from the i+1 (i - position of the parent) position to the end of the files vector
            for (int j = i + 1; j < files.size(); j++) {
                //Ignoring file copies
                if (files[j].getIsCopy()) {
                    continue;
                }
                
                //Comparison of file[j] with parent file[i]
                if (files[j] == files[i]) {
                    temp.AddCopyToFather(files[j]);
                    files[j].setIsCopy(true);
                }
            }
            //Adding a temporary structure with parent and its copies to CopyPairs vector
            CopyPairs.push_back(temp);

        }
        return CopyPairs;
    }

};
