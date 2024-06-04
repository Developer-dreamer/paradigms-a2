#include <iostream>
# include "References.h"

int main()
{
	char* helper = "0 - close the program\n"
		"1 - append symbols to the end\n"
		"2 - start the new line\n"
		"3 / 4 - save to / load from file\n"
		"5 - print current text to console\n"
		"6 - insert text by index in file\n"
		"7 - search substring position in file\n"
		"8 - concatenate texts\n"
		"9 - clear console\n";
	printf("%s", helper);
	while (true) {

		switch (command) {

			// close the program
		case 0:
			return 0;
			// append symbols to the end of string
		case 1:
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
			break;

			// search substring position in file
		case 7:
			break;
			// additional case to work with unconcatenated texts
		case 8:
			break;
		case 9:
			break;
		default:
			printf("Such command does not exist\n");
			break;
		}
	}
}

