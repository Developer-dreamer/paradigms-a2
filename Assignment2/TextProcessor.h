#pragma once

#ifndef  FILEPROCESSOR
#include <iostream>
#include "ConsoleProcessor.h"
#include "ProgramBackup.h"

class TextProcessor {
public:
	TextProcessor(int rows, int lineChars);
	void EndInsert(char* userStr);
	void StartNewLine();
	void IndexInput(char* userInput, Coordinates coords);
	void IndexInputReplacement(char* userInput, Coordinates coords, size_t charsToReplace);
	void IndexDelete(Coordinates coords, size_t length);
	void SubstrSearch(char* userInput);
	void PrintText();
	void Copy(size_t charsToCopy, Coordinates coords);
	void Paste(Coordinates coords);
	void Cut(size_t charsToCut, Coordinates coords);
private:
	char** text_;
	char* buffer_;
	size_t rows_;
	size_t lineChars_;
	Coordinates coords_;
	friend class FileProcessor;
	friend class Backup;
	friend class BackupHistory;
	
	void ResizeLine();
	void ResizeRows();
};

#endif // ! FILEPROCESSOR
