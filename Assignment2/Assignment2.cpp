#include <iostream>
#include "ConsoleProcessor.h"
#include "TextProcessor.h"
#include "FileProcessor.h"
#include "ProgramBackup.h"

int main()
{
	const char fileName[] = "Text.txt";
	const char* helper = "0 - close the program\n"
		"1 - append symbols to the end\n"
		"2 - start the new line\n"
		"3 / 4 - save to / load from file\n"
		"5 - print current text to console\n"
		"6 - insert text by index in file\n"
		"7 - search substring position in file\n"
		"8 - delete by index\n"
		"9 - copy\n"
		"10 - paste\n"
		"11 - cut\n"
		"12 - insert with replacement\n"
		"13 - udno\n"
		"14 - redo\n"
		"15 - clear console\n";
	printf("%s", helper);

	Console consoleProcessor;
	TextProcessor localText(64, 64);
	FileProcessor file(fileName);
	BackupHistory backupHistory;

	while (true) {
		
		int command = consoleProcessor.ReadCommand();
		char* userInput = nullptr;
		char* strToSearch;

		Backup backup;
		
		switch (command) {

			// close the program
		case 0:
			std::cout << "Program has been closed successfully";
			return 0;
			// append symbols to the end of string
		case 1:
			backup = Backup(localText);
			backupHistory.AddToHistory(backup);
			userInput = consoleProcessor.ReadConsole();
			localText.EndInsert(userInput);
			
			
			break;
			// start new line in the string
		case 2:
			backup = Backup(localText);
			backupHistory.AddToHistory(backup);
			localText.StartNewLine();
			
			std::cout << "New line has been started" << std::endl;
			break;
		// save current string to the file 
		case 3:
			file.SaveToFile(localText);

			std::cout << "Text has been saved to the file" << std::endl;
			break;
			// load string from the file
		case 4:
			file.LoadFromFile(localText);
			break;
			// print current string to console
		case 5:
			localText.PrintText();
			break;
			// insert text by index in file
		case 6:
			backup = Backup(localText);
			backupHistory.AddToHistory(backup);
			Coordinates coords = consoleProcessor.ReadCoordinates();
			userInput = consoleProcessor.ReadConsole();
			localText.IndexInput(userInput, coords);
			
			break;

			// search substring position in file
		case 7:
			strToSearch = consoleProcessor.ReadConsole();
			localText.SubstrSearch(strToSearch);
			break;
			// Delete by index
		case 8:
			backup = Backup(localText);
			backupHistory.AddToHistory(backup);
			Coordinates coordsToDelete = consoleProcessor.ReadCoordinates();
            int deleteLength;
			std::cout << "Enter the length of the string to delete: ";
            std::cin >> deleteLength;
            localText.IndexDelete(coordsToDelete, deleteLength);
			
			break;
			// Copy
		case 9:
			Coordinates coordsToCopy = consoleProcessor.ReadCoordinates();
			int copyLength;
			std::cout << "Enter the length of the string to copy: ";
			std::cin >> copyLength;
			localText.Copy(copyLength, coordsToCopy);
			break;
			// Paste
		case 10:
			Coordinates coordsToPaste = consoleProcessor.ReadCoordinates();
			localText.Paste(coordsToPaste);
			break;
			// Cut
		case 11:
			Coordinates coordsToCut = consoleProcessor.ReadCoordinates();
			int cutLength;
			std::cout << "Enter the length of the string to cut: ";
			std::cin >> cutLength;
			localText.Cut(cutLength, coordsToCut);
			break;
			// insert with replacement
		case 12:
			backup = Backup(localText);
			backupHistory.AddToHistory(backup);
			Coordinates coordsToReplace = consoleProcessor.ReadCoordinates();
			userInput = consoleProcessor.ReadConsole();
			size_t charsToReplace;
			std::cout << "Enter the length of the string to replace: ";
			std::cin >> charsToReplace;
			localText.IndexInputReplacement(userInput, coordsToReplace, charsToReplace);
			break;
			// Undo
		case 13: 
			backup = Backup(localText);
			backupHistory.AddToHistory_redo(backup);
			backupHistory.Undo(localText);
			break;
		// Redo
		case 14:
			backup = Backup(localText);
			backupHistory.AddToHistory(backup);
			backupHistory.Redo(localText);
			break;
		// clear console
		case 15:
			consoleProcessor.Clear();
			break;
		default:
			printf("Such command does not exist\n");
			break;
		}
	}
}
