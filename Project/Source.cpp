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
#include "filecollector.h"
#include "file.h"
#include <stdio.h>
#include <cstring>


using namespace std;
namespace fs = std::filesystem;




int main() {

	cout << "Irredeemable - the best team ever!!!" << endl;
     
    File f1;
    f1.setPath("E:\\VS Projects\\Team_project\\team02\\Project\\test_1 copy.txt");
    f1.removeFile();

    // File f1;
    // File f2;
    // ifstream file1("test_1 copy.txt");
    // ifstream file2("test_1.txt");

    // string content1((istreambuf_iterator<char>(file1)), (istreambuf_iterator<char>()));
    // string content2((istreambuf_iterator<char>(file2)), (istreambuf_iterator<char>()));

    // f1.setContent(content1);
    // f2.setContent(content2);
    
    // if(f1==f2)
    // {
    //     cout<<"True";
    // }
    // else 
    // {
    //     cout<<"False";
    // }
	return 1;
    
    
    

}