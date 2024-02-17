#include <iostream>
#include "Game.h"
#include "Console.h"
using namespace std;

int main()
{
	Game game;
	Console console;
	console.showAuthor();
	console.printMenu();

	ofstream outFile;
	fstream logFile;

	int numforRead = 200; // dotad uzytkownik wpisuje ilosc dni dla wykresu
	int graph_width = 0;


	int cs = 1;

	char inputFileName[259] = "intc_us_data.csv";
	char outputFileName[259] = "chart.txt";
	char inputFileNameUser[259] = "";
	char outputFileNameUser[259] = "";

	const char X[259] = "X";
	const char X_small[11] = "X";
	const char fals_big[259] = "false";
	const char fals[11] = "false";

	int graph_size = 200;
	int graph_height = 50;
	int graph_size_user = 0;
	int graph_height_user = 0;
	int candle_scale = 1;
	int candle_scale_user = 0;
	char turn = '0';

	// napisac funkcje, ktora bedzie wpisywala informacje do pliku log
	// i dodac do tej funkcji funkcje ktora bedzie pisala czas wystapienia funkcji
	game.fileSys.readFile(inputFileName);
	char information[200];
	game.fileSys.saveInfoToLog("Program start");

	while (turn != 'q') {
		cin.get(turn);
		switch (turn) {
		
		case 'a': {
			game.fileSys.saveInfoToLog("User entered a");

			cout << "Enter the name of the source file (file name.csv in the program folder)"
				<< " or skip data entry - X\n";
			cin >> inputFileNameUser;

			strcpy_s(information, "inputFileNameUser (char[]) = ");
			char tempInf[100];
			sprintf_s(tempInf, "%s", inputFileNameUser);
			strcat_s(information, tempInf);

			game.fileSys.saveInfoToLog(information);
			memset(information, ' ', 200);

			game.fileSys.deleteFileLines();
			game.fileSys.start_data_user_x = -1;
			game.fileSys.end_data_user_x = -1;
			if (strcmp(inputFileNameUser, X) != 0)
			{
				candle_scale = 1;
				cout << "One candle will be = 1 day\n";
				game.fileSys.readFile(inputFileNameUser);
				strcpy_s(inputFileName, sizeof(inputFileName), inputFileNameUser);
				cout << "File was found" << endl;
			}
			else {
				cout << "You wrote X, the default csv was selected\n";
				strcpy_s(inputFileName, game.fileSys.defaultReadFile);
				cout << inputFileName << endl;
				game.fileSys.readFile(inputFileName);
			}
			break;
		}

		case 'b': {
			game.fileSys.saveInfoToLog("User entered b");

			cout << "Enter the name of the output file with extension or skip data entry - X\n";
			cin >> outputFileNameUser;
			if (strcmp(outputFileNameUser, X) == 0) {
				cout << "You wrote X, the default output file will be " << outputFileName << "\n";
				strcpy_s(outputFileNameUser, sizeof(outputFileNameUser), outputFileName);
			}
			strcpy_s(information, "outputFileNameUser (char[]) = ");

			char tempInf[100];
			sprintf_s(tempInf, "%s", outputFileNameUser);
			strcat_s(information, tempInf);

			game.fileSys.saveInfoToLog(information);
			memset(information, ' ', 200);
			
			game.fileSys.initializeFileSystem(inputFileName);

			game.initializeGame(graph_size, graph_height);
			game.createGameMap(candle_scale, game.fileSys.start_data_x, game.fileSys.end_data_x, graph_height, graph_size, game.fileSys.size_data_x);


			outFile.open(outputFileNameUser, ios::binary);
			if (outFile.is_open())
			{
				for (int i = game.map.total_height - 1; i >= 0; i--) {
					for (int j = 0; j < game.map.total_width; j++) {
						outFile << game.map.textMap[i][j];
					}
					if (i > 0)	outFile << "\n";
				}
				outFile << "\n\nOne candle is " << candle_scale << " day(s)\n";
				cout << "The graph was written to a file" << endl;

			}
			else {
				cout << "It is impossible to open a file named {" << outputFileName << "}\n";
			}
			outFile.close();
			game.map.deleteMap();
			game.deleteGameInfo();

			break;
		}

		case 'c': {
			game.fileSys.saveInfoToLog("User entered c");

			cout << "Select the candle scale from 1 to " << game.fileSys.end_data_x - game.fileSys.start_data_x
				<< " (for example, 1 - 1 day, 5 - 1 week, 20 - 1 month, " << ceil((game.fileSys.end_data_x - game.fileSys.start_data_x) / graph_size) + 1
				<< " to write all graph) or skip data entry - 0\n";
			cin >> candle_scale_user;
			cout << candle_scale_user << endl;

			strcpy_s(information, "candle_scale_user (int) = ");

			char tempInf[100];
			sprintf_s(tempInf, "%d", candle_scale_user);
			strcat_s(information, tempInf);

			game.fileSys.saveInfoToLog(information);
			memset(information, ' ', 200);

			if (candle_scale_user >= 1) candle_scale = candle_scale_user;
			else if (candle_scale_user == 0) {
				candle_scale = 1;
				cout << "You wrote 0, candle scale will be " << candle_scale << "\n";
			}
		/*	if (candle_scale == 1) {
				if ((graph_size - game.fileSys.size_data_x) >= 0) {
					candle_scale = 1;
				}
				else {
					game.fileSys.start_data_x = game.fileSys.end_data_x - graph_size + 1;
					candle_scale = 1;
				}
				game.fileSys.size_data_x = game.fileSys.end_data_x - game.fileSys.start_data_x + 1;
			}*/
			//else {

			//	// масштаб candle_scale  =  10
			//	// game.fileSys.start_data_x - начало расчета  =  101
			//	// game.fileSys.end_data_x - конец расчета по оси иксов = 6100
			//	// graph_height - высота графика = 100
			//	// graph_size - ширина графика  = 200
			//	// game.fileSys.size_data_x - размер в точках (кол-во дат) = game.fileSys.end_data_x - game.fileSys.start_data_x + 1;
			//}

			/*candle_scale = game.fileSys.size_data_x / graph_size;
			cout << "The number of data exceeds the size of the graph by x"
				<< "\nThe calculated coefficient is used to display the graph: one candle = " << candle_scale << " of days\n";*/

				//game.initializeGame(graph_size, graph_height);
				//game.fileSys.readFile(numforRead, game.minValue, game.maxValue, inputFileName, outFileName);
			break;
		}
		
		case 'e': {
			game.fileSys.saveInfoToLog("User entered e");

			char end_data_user[11] = "";
			while (strcmp(end_data_user, "") == 0) {
				cout << "Enter the end date of the period (from " << game.fileSys.fileLines[game.fileSys.start_data_x].data
					<< " to " << game.fileSys.fileLines[game.fileSys.end_data_x].data << ") or skip data entry - X\n";
				cin >> end_data_user;
				strcpy_s(information, "end_data_user (char[]) = ");
				char tempInf[100];
				sprintf_s(tempInf, "%s", end_data_user);
				strcat_s(information, tempInf);
				game.fileSys.saveInfoToLog(information);
				memset(information, ' ', 200);

				if (strcmp(end_data_user, X_small) != 0) {
					game.fileSys.findDate(end_data_user, game.fileSys.end_data_user_x);
					if (strcmp(end_data_user, fals) == 0) {
						cout << "No calculations were made on this day or date is incorrect, enter a different date\n";
						strcpy_s(end_data_user, sizeof(end_data_user), "");
					}
					else {
						game.fileSys.end_data_x = game.fileSys.end_data_user_x;
						cout << "End date of the period will be " << end_data_user << endl;
					}
				}
				else {
					cout << "You wrote X, end date of the period will be " << game.fileSys.fileLines[game.fileSys.end_data_x].data << "\n";
					strcpy_s(information, "end_data_user (char[]) = X, end date will be: ");
					char tempInf[100];
					sprintf_s(tempInf, "%s", game.fileSys.fileLines[game.fileSys.end_data_x].data);
					strcat_s(information, tempInf);
					game.fileSys.saveInfoToLog(information);
					memset(information, ' ', 200);
				}
			}
			break;
		}
		
		case 'g': {
			game.fileSys.saveInfoToLog("User entered g");
			game.fileSys.deleteFileLines();

			game.defaultMap(game.fileSys.defaultReadFile, cs);
			outFile.open(outputFileName, ios::binary);
			if (outFile.is_open())
			{
				for (int i = game.map.total_height - 1; i >= 0; i--) {
					for (int j = 0; j < game.map.total_width; j++) {
						outFile << game.map.textMap[i][j];
					}
					if (i > 0)	outFile << "\n";
				}
				outFile << "\n\nOne candle is " << cs << " day\n";
				cout << "The graph was written to a file" << endl;
				game.fileSys.saveInfoToLog("The graph was written to a file");

			}
			else {
				cout << "Error while writing graph in outFile\n";
				strcpy_s(information, "Error while writing graph in outFile");
				strcpy_s(information, outputFileName);
				memset(information, ' ', 200);
				game.fileSys.saveInfoToLog("Error while writing graph in outFile");

			}
			outFile.close();
			game.map.deleteMap();
			game.deleteGameInfo();
			game.fileSys.initializeFileSystem(inputFileName);

			break;
		}

		case 'h': {
			game.fileSys.saveInfoToLog("User entered h");

			cout << "Please write graphic height or skip data entry - 0" << endl;
			cin >> graph_height_user;
			if (graph_height_user != 0) graph_height = graph_height_user;
			else {
				cout << "You wrote 0, graphic height will be " << graph_height << "\n";
			}
			strcpy_s(information, "graph_height_user (int) = ");
			char tempInf[100];
			sprintf_s(tempInf, "%d", graph_height_user);
			strcat_s(information, tempInf);
			game.fileSys.saveInfoToLog(information);
			memset(information, ' ', 200);
			break;
		}
		
		case 'j': {
			game.fileSys.saveInfoToLog("User entered j (drawing a graph in the console)");
			game.fileSys.initializeFileSystem(inputFileName);

			game.initializeGame(graph_size, graph_height);
			game.createGameMap(candle_scale, game.fileSys.start_data_x, game.fileSys.end_data_x, graph_height, graph_size, game.fileSys.size_data_x);
			
			game.map.drawMap();
			cout << "\nOne candle is " << candle_scale << " day(s)\n";
			game.map.deleteMap();
			game.deleteGameInfo();

			cout << endl;
			console.printMenu();

			break;
		}
		
		case 'n': {
			game.fileSys.saveInfoToLog("User entered n");

			char start_data_user[11] = "";
			while (strcmp(start_data_user, "") == 0) {
				cout << "Enter the start date of the period (from " << game.fileSys.fileLines[game.fileSys.start_data_x].data
					<< " to " << game.fileSys.fileLines[game.fileSys.end_data_x].data << ") or skip data entry - X\n";
				cin >> start_data_user;

				strcpy_s(information, "start_data_user (char[]) = ");
				char tempInf[100];
				sprintf_s(tempInf, "%s", start_data_user);
				strcat_s(information, tempInf);
				game.fileSys.saveInfoToLog(information);
				memset(information, ' ', 200);

				if (strcmp(start_data_user, X_small) != 0) {
					game.fileSys.findDate(start_data_user, game.fileSys.start_data_user_x);
					if (strcmp(start_data_user, fals) == 0) {
						cout << "No calculations were made on this day, enter a different date\n";
						strcpy_s(start_data_user, sizeof(start_data_user), "");
					}
					else {
						game.fileSys.start_data_x = game.fileSys.start_data_user_x;
						cout << "Start date of the period will be " << start_data_user << endl;
					}
				}
				else {
					cout << "You wrote X, start date of the period will be " << game.fileSys.fileLines[game.fileSys.start_data_x].data << "\n";
					strcpy_s(information, "start_data_user (char[]) = X, start date will be: ");
					char tempInf[100];
					sprintf_s(tempInf, "%s", game.fileSys.fileLines[game.fileSys.start_data_x].data);
					strcat_s(information, tempInf);
					game.fileSys.saveInfoToLog(information);
					memset(information, ' ', 200);
				}
			}
			break;
		}

		case 'r': {
			game.fileSys.saveInfoToLog("User entered r (reset dates)");
			game.fileSys.end_data_user_x = -1;
			game.fileSys.start_data_user_x = -1;

			game.fileSys.initializeFileSystem(inputFileName);
			cout << "The dates have been successfully reset to the default values\n";
			break;
		}
		
		case 's': {
			game.fileSys.saveInfoToLog("User entered s");

			cout << "Please write graphic size or skip data entry - 0" << endl;
			cin >> graph_size_user;
			if (graph_size_user != 0) graph_size = graph_size_user;
			else {
				cout << "You wrote 0, graphic size will be " << graph_size << "\n";
			}

			strcpy_s(information, "graph_size_user (int) = ");
			char tempInf[100];
			sprintf_s(tempInf, "%d", graph_size_user);
			strcat_s(information, tempInf);
			game.fileSys.saveInfoToLog(information);
			memset(information, ' ', 200);
			break;
		}

		case '\n': {
			break;
		}
		default: {
			char tempInf[100];
			strcpy_s(tempInf, "User entered other symbol");
			game.fileSys.saveInfoToLog(tempInf);
			break;
		}
		}

	}

	game.fileSys.saveInfoToLog("User entered q (end program)");
}

