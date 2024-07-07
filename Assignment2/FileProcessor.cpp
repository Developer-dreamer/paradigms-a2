#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include "FileProcessor.h"

#include <cstring>

FileProcessor::FileProcessor(const char* fileName) {
	fileName_ = new char[strlen(fileName) + 1];
	strcpy(fileName_, fileName);
}

void FileProcessor::SaveToFile(TextProcessor& localText) {

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

void FileProcessor::LoadFromFile(TextProcessor& localText) {
    FILE* file = fopen(fileName_, "r");
    if (file == NULL) {
        throw std::runtime_error("Failed to open file");
    }

    try {
        localText.text_ = new char* [localText.rows_];
        for (int i = 0; i < localText.rows_; i++) {
            localText.text_[i] = new char[localText.lineChars_ + 1]; // +1 for null terminator
        }

        int i = 0;
        while (fgets(localText.text_[i], localText.lineChars_ + 1, file) != NULL) {
            size_t length = strlen(localText.text_[i]);
            if (length > 0 && localText.text_[i][length - 1] == '\n') {
                localText.text_[i][length - 1] = '\0'; // Remove newline character
            }

            i++;
            if (i >= localText.rows_) {
                localText.rows_ *= 2;
                char** temp = new char* [localText.rows_];
                for (int j = 0; j < localText.rows_ / 2; j++) {
                    temp[j] = localText.text_[j];
                }
                for (int j = localText.rows_ / 2; j < localText.rows_; j++) {
                    temp[j] = new char[localText.lineChars_ + 1]; // +1 for null terminator
                }
                delete[] localText.text_; // Clean up old memory
                localText.text_ = temp;
            }
        }

        if (i < localText.rows_) {
            for (int j = i; j < localText.rows_; j++) {
                delete[] localText.text_[j]; // Clean up unused memory
            }
            localText.rows_ = i;
        }
    }
    catch (const std::exception& e) {
        // Clean up allocated memory
        for (int i = 0; i < localText.rows_; i++) {
            delete[] localText.text_[i];
        }
        delete[] localText.text_;
        throw; // Rethrow the exception
    }

    fclose(file);
}

