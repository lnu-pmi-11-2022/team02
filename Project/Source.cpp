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
#include "copyfinder.h"
#include "menu.h"
#include <stdio.h>
#include <cstring>
#include<iostream>
using namespace std;

using namespace std;
using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;
int main() {
	Menu menu;
	menu.opening();
	menu.getRootDir();
	menu.findCopies();
	menu.filesToDelete();
	return 1;
}