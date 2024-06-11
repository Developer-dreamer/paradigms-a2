#pragma once

#ifndef  FILEPROCESSOR
#include <iostream>
#include "ConsoleProcessor.h"

class TextProcessor {
public:
	TextProcessor(int rows, int lineChars);
	void EndInsert(char* userStr);
	void StartNewLine();
	void IndexInput();
	void SubstrSearch();
	void Concatenate();
	void PrintText();
private:
	char** text_;
	int rows_;
	int lineChars_;
	Coordinates cursorPos_;
	friend class FileProcessor;
	
	void ResizeLine();
	void ResizeRows();
	void ConcatenateTexts(char** textFromFile);
};

#endif // ! FILEPROCESSOR
