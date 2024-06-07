#include <iostream>
#include "ConsoleProcessor.h"

int main()
{
	const char* helper = "0 - close the program\n"
		"1 - append symbols to the end\n"
		"2 - start the new line\n"
		"3 / 4 - save to / load from file\n"
		"5 - print current text to console\n"
		"6 - insert text by index in file\n"
		"7 - search substring position in file\n"
		"8 - concatenate texts\n"
		"9 - clear console\n";
	printf("%s", helper);

	Console consoleProcessor;

	while (true) {
		
		int command = consoleProcessor.ReadCommand();

		switch (command) {

			// close the program
		case 0:
			std::cout << "Program has been closed successfully";
			return 0;
			// append symbols to the end of string
		case 1:
			consoleProcessor.ReadConsole();
			break;
			// start new line in the string
		case 2:
			break;
		// save current string to the file 
		case 3:
			break;
			// load string from the file
		case 4:
			break;
			// print current string to console
		case 5:
			break;
			// insert text by index in file
		case 6:
			Coordinates coords = consoleProcessor.ReadCoordinates();
			break;

			// search substring position in file
		case 7:
			break;
			// additional case to work with unconcatenated texts
		case 8:
			break;
			//clear console
		case 9:
			consoleProcessor.Clear();
			break;
		default:
			printf("Such command does not exist\n");
			break;
		}
	}
}
