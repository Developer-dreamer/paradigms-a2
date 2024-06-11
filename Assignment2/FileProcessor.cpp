#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include "FileProcessor.h"

FileProcessor::FileProcessor(const char* fileName) {
	fileName_ = new char[strlen(fileName) + 1];
	strcpy(fileName_, fileName);
}

void FileProcessor::SaveToFile(TextProcessor localText) {

	std::ofstream file(fileName_);
	if (file.is_open()) {
		for (int i = 0; i < localText.rows_; i++) {
			if (localText.text_[i] == NULL) {
				break;
			}
			file << localText.text_[i] << std::endl;
		}
		file.close();
	}
	else {
		std::cout << "Unable to open file" << std::endl;
	}
}

void FileProcessor::LoadFromFile(TextProcessor localText) {
	std::ifstream file(fileName_);
	if (file.is_open()) {
		char** buffer = new char* [localText.rows_];
		int line = 0;
		while (!file.eof() && line < localText.rows_) {
			// If the line is too long for the buffer, resize the buffer
			if (file.gcount() > localText.lineChars_) {
				delete[] buffer[line];
				buffer[line] = new char[file.gcount() + 1];
			}
			else {
				buffer[line] = new char[localText.lineChars_];
			}
			file.getline(buffer[line], localText.lineChars_);
			line++;
		}
		localText.ConcatenateTexts(buffer);
		file.close();
	}
	else {
		std::cout << "Unable to open file" << std::endl;
	}
}