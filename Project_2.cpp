#include <iostream>
#include "Controller.h"
#include "Console.h"
using namespace std;

int main()
{
	Console console;
	Controller controller;
	console.showAuthor();
	console.printMenu();

	char turn = '0';
	while (turn != 'q') {

		cin.get(turn);
		switch (turn) {
		case 'g': controller.defaultStart(); break;
		case 'v': 
		{
			char inpF[70] = "";
			char outF[70] = "";
			int graph_height = 0, graph_size = 0, data_size = 0;
			//cout << strlen(inpF) << inpF << endl;

			while (strlen(inpF) >= 40 || strlen(inpF) == 0) {
				cout << "Please write your inputFile (length of this file <40): ";
				cin >> inpF;
			}

			while (strlen(outF) >= 40 || strlen(outF) == 0) {
				cout << "Please write your outputFile (length of this file <40):";
				cin >> outF;
			}

			cout << "Please write graph_height, graph_size, data_size (<=12)" << endl;
			cin >> graph_height, graph_size, data_size;
			controller.startWithFilesAndParams(inpF, outF, graph_height, graph_size, data_size);
		}
			break; // 
			
		default :break;
		}

	}
}
