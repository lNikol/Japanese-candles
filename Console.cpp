#include <iostream>
#include "Console.h"
using namespace std;

void Console::showAuthor() {
	cout << "Hello!\n";
	cout << "Author:\n";
	cout << "Nikolai Lavrinov 201302\n\n\n";
}

void Console::printMenu() {

	cout << "a) Set a new input file with extension\n";
	cout << "b) Draw graph to the file\n";
	cout << "c) Set a candle scale\n";
	cout << "e) Set a new end date\n";
	cout << "g) Graph from intc_us_data.csv to chart.txt (in the last 200 days)\n";
	cout << "h) Set a new height of graph\n";
	cout << "j) Show graph in console\n";
	cout << "n) Set a new start date\n";
	cout << "r) Reset dates\n";
	cout << "s) Set a new size of graph\n";
	
	cout << "q) End program\n";

}

