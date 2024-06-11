#pragma once

#include "TextProcessor.h"

#ifndef FILEPROCESSOR
class FileProcessor {
public:
	FileProcessor(const char* fileName);
	void SaveToFile(TextProcessor localText);
	void LoadFromFile(TextProcessor localText);
private:
	char* fileName_;
	friend TextProcessor;
};
#endif // !FILEPROCESSOR
