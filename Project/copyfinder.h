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

    void addCopyToFather(File copy) {
        CopyVector.push_back(copy);
    }
    friend ostream& operator<<(ostream& os, const Copies& copies);
};
//output for structure
ostream& operator<<(ostream& os, const Copies& copies) {
    os << "Original file:\n" << copies.Father << endl;
    os << "Copies:\n";
    for (int i = 0; i < copies.CopyVector.size(); i++) {
        os << copies.CopyVector[i] << endl;
    }
    os << endl;
    return os;
}

class CopyDetector {
private:
    vector<Copies> CopyPairs;
public:
    CopyDetector(){
        CopyPairs.resize(0);
    }
    //Basic method for selecting copies and parent elements
    void detector(vector<File> files) {
        bool flag;
        for (int i = 0; i < files.size(); i++) {
            flag = false;
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
                    files[j].setIsCopy(true);
                    temp.addCopyToFather(files[j]);
                    flag = true;
                }
            }
            //Adding a temporary structure with parent and its copies to CopyPairs vector  if flag is true
            if(flag){
                CopyPairs.push_back(temp);
            }
            else{
                continue;
            }

        }
    }

    void deleteAllCopies(){
        //We go to CopyPairs
        for(int i = 0; i < CopyPairs.size(); i++){
            //We go to CopyPairs(Father and CopyVector) -> CopyVector
            for(int j = 0; j<CopyPairs[i].CopyVector.size();j++){
                //We go to CopyPairs(Father and CopyVector) -> CopyVector -> File -> remove
                CopyPairs[i].CopyVector[j].removeFile();
            }
            //Clear CopyVector after remove
            CopyPairs[i].CopyVector.clear();
        }
    }

    void deleteFatherCopies(File father){
        //flag for exception
        bool flag = false;
        //tag for clearing CopyVector
        bool tag = false;
        try {
            //We go to CopyPairs
            for (int i = 0; i < CopyPairs.size(); i++) {
                //We go to CopyPairs(Father and CopyVector) -> Father and compare with input File father
                if (CopyPairs[i].Father == father) {
                    //If equal -> remove copies
                    for (int j = 0; j < CopyPairs[i].CopyVector.size(); j++) {
                        CopyPairs[i].CopyVector[j].removeFile();
                        tag = true;
                    }
                    if(tag){
                        //Clear CopyVector after remove
                        CopyPairs[i].CopyVector.clear();
                    }
                    flag = true;
                    break;
                }
            }
            if(!flag){
                //If File father is not in CopyPair->Father
                throw invalid_argument("Invalid file uploaded");
            }
        }
        catch (string& e){
            cerr<<e<<endl;
        }
    }
    //Get CopyPairs
    vector<Copies> getCopyPairs(){
        return CopyPairs;
    };
    //output for all pairs of copies
    friend ostream& operator<<(ostream& os, const CopyDetector& copyPairs) {
        for (int i = 0; i < copyPairs.CopyPairs.size(); i++) {
            os << copyPairs.CopyPairs[i];
        }
        return os;
    }

};
