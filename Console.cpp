#include <iostream>
#include "Console.h"
using namespace std;

void Console::showAuthor() {
	cout << "Hello!\n";
	cout << "Author:\n";
	cout << "Nikolai Lavrinov 201302\n\n\n";
}

void Console::printMenu() {
	cout << "1) q - end program\n";
	cout << "2) g - Graphic from intc_us_data.csv to .txt\n";
	cout << "3) v - Graphic from yourReadFile to yourOutFile.txt\n";

}

