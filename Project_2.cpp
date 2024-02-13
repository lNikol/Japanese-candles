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
	time_t currentTime = time(nullptr);

	int numforRead = 200; // dotad uzytkownik wpisuje ilosc dni dla wykresu
	int graph_width = 0;
	char inputFileName[259] = "intc_us_data.csv";
	int cs = 1;

	char turn = '0';
	while (turn != 'q') {
		cin.get(turn);
		switch (turn) {
		case 'g':
			game.fileSys.readFile(inputFileName);
			game.fileSys.size_data_x = 200;
			if (cs == 1) {
				game.fileSys.start_data_x = game.fileSys.end_data_x - 200;
				game.fileSys.size_data_x = game.fileSys.end_data_x - game.fileSys.start_data_x + 1;
			}
			game.fileSys.findMaxMin();
			game.initializeGame(200, 50);
			game.createGameMap2(cs, game.fileSys.start_data_x, game.fileSys.end_data_x, 50, 200, game.fileSys.size_data_x);

			outFile.open("chart.txt", ios::binary);
			if (outFile.is_open())
			{
				for (int i = game.map.total_height - 1; i >= 0; i--) {
					for (int j = 0; j < game.map.total_width; j++) {
						outFile << game.map.textMap[i][j];
					}
					if (i > 0)	outFile << "\n";
				}
			}
			else {
				cout << "err open\n";
			}
			outFile.close();
			break;
		case 'v':
		{
			char inputFileNameUser[259] = "";
			const char X[259] = "X";
			const char X_small[11] = "X";
			const char fals_big[259] = "false";
			const char fals[11] = "false";

			cout << "Enter the name of the source file (file name.csv in the program folder)"
				<< " or skip data entry - X\n"; //or enter the full path with the file name and the csv extension, 
			cin >> inputFileNameUser;

			logFile.open("log.log", ios::out);
			if (logFile.is_open()) {
				logFile << time(0) << " : inputFileNameUser = " << inputFileNameUser << endl;
				logFile.close();
			}
			if (strcmp(inputFileNameUser, X) != 0)
			{
				game.fileSys.readFile(inputFileNameUser);
				strcpy_s(inputFileName, sizeof(inputFileName), inputFileNameUser);
			}
			else { game.fileSys.readFile(inputFileName); }


			int graph_size = 200;
			int graph_height = 50;
			int graph_size_user = 0;
			int graph_height_user = 0;

			cout << "Please write graphic height or skip data entry - 0" << endl;
			cin >> graph_height_user;

			logFile.open("log.log", ios::app);
			if (logFile.is_open()) {
				logFile.seekg(0, std::ios::end);
				logFile << time(0) << " : graph_height_user = " << graph_height_user << endl;
				logFile.close();
			}

			if (graph_height_user != 0) graph_height = graph_height_user;

			cout << "Please write graphic size or skip data entry - 0" << endl;
			cin >> graph_size_user;

			logFile.open("log.log", ios::app);
			if (logFile.is_open()) {
				logFile << time(0) << " : graph_size_user = " << graph_size_user << endl;
				logFile.close();
			}
			if (graph_size_user != 0) graph_size = graph_size_user;


			char start_data_user[11] = "";

			while (strcmp(start_data_user, "") == 0) {
				cout << "Enter the start date of the period (from " << game.fileSys.fileLines[game.fileSys.start_data_x].data
					<< " to " << game.fileSys.fileLines[game.fileSys.end_data_x].data << ") or skip data entry - X\n";
				cin >> start_data_user;

				logFile.open("log.log", ios::app);
				if (logFile.is_open()) {
					logFile.seekg(0, std::ios::end);
					logFile << time(0) << " : start_data_user = " << start_data_user << endl;
					logFile.close();
				}

				if (strcmp(start_data_user, X_small) != 0) {
					game.fileSys.findDate(start_data_user, game.fileSys.start_data_user_x);
					if (strcmp(start_data_user, fals) == 0) {
						cout << "No calculations were made on this day, enter a different date\n";
						strcpy_s(start_data_user, sizeof(start_data_user), "");
					}
					else {
						game.fileSys.start_data_x = game.fileSys.start_data_user_x;
					}
				}
			}
			char end_data_user[11] = "";

			while (strcmp(end_data_user, "") == 0) {
				cout << "Enter the end date of the period (from " << game.fileSys.fileLines[game.fileSys.start_data_x].data
					<< " to " << game.fileSys.fileLines[game.fileSys.end_data_x].data << ") or skip data entry - X\n";
				cin >> end_data_user;

				logFile.open("log.log", ios::app);
				if (logFile.is_open()) {
					logFile.seekg(0, std::ios::end);
					logFile << time(0) << " : end_data_user = " << end_data_user << endl;
					logFile.close();
				}

				if (strcmp(end_data_user, X_small) != 0) {
					game.fileSys.findDate(end_data_user, game.fileSys.end_data_user_x);
					if (strcmp(end_data_user, fals) == 0) {
						cout << "No calculations were made on this day or date is incorrect, enter a different date\n";
						strcpy_s(end_data_user, sizeof(end_data_user), "");
					}
					else {
						game.fileSys.end_data_x = game.fileSys.end_data_user_x;
					}
				}

			}

			game.fileSys.size_data_x = game.fileSys.end_data_x - game.fileSys.start_data_x;


			int candle_scale = 1;
			int candle_scale_user = 0;
			cout << "Select the candle scale from 1 to " << game.fileSys.size_data_x
				<< " (for example, 1 - 1 day, 5 - 1 week, 20 - 1 month, " << game.fileSys.size_data_x / graph_size
				<< " to write all graph) or skip data entry - 0\n";
			cin >> candle_scale_user;


			logFile.open("log.log", ios::app);
			if (logFile.is_open()) {
				logFile.seekg(0, std::ios::end);
				logFile << time(0) << " : candle_scale_user = " << candle_scale_user << endl;
				logFile.close();
			}

			if (candle_scale_user >= 1) {
				candle_scale = candle_scale_user;
			}

			game.initializeGame(graph_size, graph_height);
			if (candle_scale == 1) {
				if ((graph_size - game.fileSys.size_data_x) >= 0) {
					candle_scale = 1;
				}
				else {
					game.fileSys.start_data_x = game.fileSys.end_data_x - graph_size + 1;
					candle_scale = 1;
				}
				game.fileSys.size_data_x = game.fileSys.end_data_x - game.fileSys.start_data_x + 1;
			}
			else {

				// масштаб candle_scale  =  10
				// game.fileSys.start_data_x - начало расчета  =  101
				// game.fileSys.end_data_x - конец расчета по оси иксов = 6100
				// graph_height - высота графика = 100
				// graph_size - ширина графика  = 200
				// game.fileSys.size_data_x - размер в точках (кол-во дат) = game.fileSys.end_data_x - game.fileSys.start_data_x + 1;

				// 
			}


			game.createGameMap2(candle_scale, game.fileSys.start_data_x, game.fileSys.end_data_x, graph_height, graph_size, game.fileSys.size_data_x);


			char outFileNameUser[259] = "";
			cout << "Write output file with extension" << endl;
			cin >> outFileNameUser;
			cout << outFileNameUser << endl;
			outFile.open(outFileNameUser, ios::binary);
			if (outFile.is_open())
			{
				for (int i = game.map.total_height - 1; i >= 0; i--) {
					for (int j = 0; j < game.map.total_width; j++) {
						outFile << game.map.textMap[i][j];
					}
					if (i > 0)	outFile << "\n";
				}
			}
			else {
				cout << "err open\n";
			}
			outFile.close();

			game.map.drawMap();
			game.map.deleteMap();

			/*candle_scale = game.fileSys.size_data_x / graph_size;
			cout << "The number of data exceeds the size of the graph by x"
				<< "\nThe calculated coefficient is used to display the graph: one candle = " << candle_scale << " of days\n";*/


				//game.initializeGame(graph_size, graph_height);
				//game.fileSys.readFile(numforRead, game.minValue, game.maxValue, inputFileName, outFileName);
			break;
		}

		default:break;
		}

	}
}

