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

	try {
		Menu menu;
		menu.opening();
		menu.getRootDir();
		menu.findCopies();
		if (menu.isAnyCopies()) {
			menu.filesToDelete();
		}
		else {
			menu.printNoCopiesFound();
		}
	}
	catch (exception& e) {
		cerr << RED_BACK << BRIGHT_WHITE_TEXT << "Exception: " << e.what() << RESET_COLOR << endl;
	}
	return 1;
}