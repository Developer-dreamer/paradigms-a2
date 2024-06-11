#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "TextProcessor.h"
#include "ProgramBackup.h"

class BackupHistory;


TextProcessor::TextProcessor(int rows, int lineChars) : rows_(rows), lineChars_(lineChars), coords_{ 0, 0 }, buffer_{} {
	text_ = new char* [rows_];
	std::fill_n(text_, rows_, nullptr);
};


void TextProcessor::EndInsert(char* userStr) {
	for (int i = 0; i < rows_; i++) {
		if (text_[i] == NULL) {
			text_[i] = new char[lineChars_];
			if (lineChars_ <= strlen(userStr)) {
				ResizeLine();
			}
			strcpy(text_[i], userStr);
			break;
		}
		else if (text_[i][0] == '\n' && i+1 < lineChars_ && text_[i + 1] == NULL) {
			strcpy(text_[i], userStr);
			break;
		}
		else if (text_[i + 1] == NULL ) {
			if (lineChars_ <= strlen(userStr) || lineChars_ <= strlen(text_[i])) {
				ResizeLine();
			}
			strcat(text_[i], userStr);
			break;
		}
		else {
			if (rows_ <= i) {
				ResizeRows();
			}
		}
		
	}
}
void TextProcessor::StartNewLine() {
	for (int i = 0; i < rows_; i++) {
		if (text_[i] == NULL) {
			text_[i] = new char[lineChars_];
			text_[i][0] = '\n';
			break;
		}
		else {
			if (rows_ <= i) {
				ResizeRows();
			}
		}

	}
}

void TextProcessor::IndexInput(char* userInput, Coordinates coords) {
	this->coords_ = coords;

	if (coords_.row < 0 || coords_.row >= rows_ || coords_.index < 0 || coords_.index >= lineChars_) {
		exit(1);
	}

	if (text_ == NULL) {
		text_ = new char* [rows_];
		std::fill_n(text_, rows_, nullptr);
	}

	if (text_[coords_.row] == NULL) {
		text_[coords_.row] = new char[lineChars_];
		std::fill_n(text_[coords_.row], lineChars_, '\0');
	}

	size_t new_length = coords_.index + strlen(userInput) + strlen(text_[coords_.row] + coords_.index);
	
	if (lineChars_ < new_length) {
		lineChars_ = new_length;
		char* temp = new char[lineChars_];
		strcpy(temp, text_[coords_.row]);
		delete[] text_[coords_.row];
		text_[coords_.row] = temp;
	}

	if (text_[coords_.row][coords_.index] == '\n') {
		text_[coords_.row][coords_.index] = '\0';
	}

	// Move existing elements to the right to make space for the new text
	memmove(text_[coords_.row] + coords_.index + strlen(userInput), text_[coords_.row] + coords_.index, strlen(text_[coords_.row] + coords_.index) + 1);

	// Insert the new text
	memcpy(text_[coords_.row] + coords_.index, userInput, strlen(userInput));

	// Free the user input
	delete[] userInput;
	userInput = nullptr;
}

void TextProcessor::IndexInputReplacement(char* userInput, Coordinates coords, size_t charsToReplace) {
	this->coords_ = coords;

	if (coords_.row < 0 || coords_.row >= rows_ || coords_.index < 0 || coords_.index >= lineChars_) {
		exit(1);
	}

	if (text_ == NULL) {
		text_ = new char* [rows_];
		std::fill_n(text_, rows_, nullptr);
	}

	if (text_[coords_.row] == NULL) {
		text_[coords_.row] = new char[lineChars_];
		std::fill_n(text_[coords_.row], lineChars_, '\0');
	}

	size_t new_length = coords_.index + strlen(userInput) + strlen(text_[coords_.row] + coords_.index) - charsToReplace;

	if (lineChars_ < new_length) {
		lineChars_ = new_length;
		char* temp = new char[lineChars_];
		strcpy(temp, text_[coords_.row]);
		delete[] text_[coords_.row];
		text_[coords_.row] = temp;
	}

	if (text_[coords_.row][coords_.index] == '\n') {
		text_[coords_.row][coords_.index] = '\0';
	}

	// Move existing elements to the right to make space for the new text
	memmove(text_[coords_.row] + coords_.index + strlen(userInput), text_[coords_.row] + coords_.index + charsToReplace, strlen(text_[coords_.row] + coords_.index + charsToReplace) + 1);

	// Insert the new text
	memcpy(text_[coords_.row] + coords_.index, userInput, strlen(userInput));

	// Free the user input
	delete[] userInput;
	userInput = nullptr;
}


void TextProcessor::SubstrSearch(char* userInput) {
	if (text_ == NULL || userInput == NULL) {
		return;
	}

	Coordinates coords[256];
	int numMatches = 0;

	for (int i = 0; i < rows_; i++) {
		if (text_[i] == NULL) {
			continue;
		}

		char* found = strstr(text_[i], userInput);
		while (found != NULL) {

			coords[numMatches].row = i;
			coords[numMatches].index = found - text_[i];
			numMatches++;

			if (found + 1 < text_[i] + strlen(text_[i]) && found != NULL) {
				found = strstr(found + 1, userInput);
			}
			else {
				break;
			}
		}
	}

    std::cout << "Coordinates of the found substrings:" << std::endl;
    for (int i = 0; i < numMatches; i++) {
        std::cout << "(" << coords[i].row << ", " << coords[i].index << ")" << std::endl;
    }

}

void TextProcessor::IndexDelete(Coordinates coords, size_t charsToDelete) {
	this->coords_ = coords;

	if (coords_.row < 0 || coords_.row >= rows_ || coords_.index < 0 || coords_.index >= lineChars_) {
		exit(1);
	}

	if (text_ == NULL || text_[coords_.row] == NULL) {
		return; // nothing to delete
	}

	size_t charsAvailable = strlen(text_[coords_.row] + coords_.index);
	size_t charsToDeleteHere = std::min(charsToDelete, charsAvailable);

	// Move existing elements to the left to fill the gap
	memmove(text_[coords_.row] + coords_.index, text_[coords_.row] + coords_.index + charsToDeleteHere, charsAvailable - charsToDeleteHere + 1);

	// Update the length of the line if necessary
	if (strlen(text_[coords_.row]) < lineChars_) {
		lineChars_ = strlen(text_[coords_.row]) + 1;
	}

	// If the entire line was deleted, free the memory
	if (strlen(text_[coords_.row]) == 0) {
		delete[] text_[coords_.row];
		text_[coords_.row] = nullptr;
	}
}

void TextProcessor::Copy(size_t charsToCopy, Coordinates coords) {
	this->coords_ = coords;

	if (coords_.row < 0 || coords_.row >= rows_ || coords_.index < 0 || coords_.index >= lineChars_) {
		exit(1);
	}

	if (text_ == NULL || text_[coords_.row] == NULL) {
		buffer_[0] = '\0';
		return;
	}
	buffer_ = new char[charsToCopy + 1];
	size_t charsAvailable = strlen(text_[coords_.row] + coords_.index);
	size_t charsToCopyHere = std::min(charsToCopy, charsAvailable);

	// Copy the specified number of characters to the buffer
	if (buffer_ != nullptr && text_[coords_.row] != nullptr && coords_.index < strlen(text_[coords_.row]) && charsToCopyHere <= sizeof(buffer_) && charsToCopyHere <= strlen(text_[coords_.row] + coords_.index)) {
    memcpy(buffer_, text_[coords_.row] + coords_.index, charsToCopyHere);
	}


	// Null-terminate the buffer
	buffer_[charsToCopyHere] = '\0';
}

void TextProcessor::Paste(Coordinates coords) {
	this->coords_ = coords;
	IndexInput(buffer_, coords);
}

void TextProcessor::Cut(size_t charsToCut, Coordinates coords) {
	Copy(charsToCut, coords);
	IndexDelete(coords, charsToCut);
}

void TextProcessor::PrintText() {
	for(int i = 0; i < rows_; i++) {
		if (text_[i] == NULL) {
			break;
		}
		if (text_[i][0] == '\n') {
			std::fill_n(text_[i], lineChars_, '\0');
		}
		std::cout << text_[i] << std::endl;
	}
}

void TextProcessor::ResizeRows() {
	char** temp = new char*[rows_ * 2];
	for (int i = 0; i < rows_; i++) {
		temp[i] = text_[i];
	}
	delete[] text_;
	text_ = temp;
	rows_ *= 2;
}

void TextProcessor::ResizeLine() {
	for (int i = 0; i < rows_; i++) {
		if (text_[i] == NULL) {
			break;
		}
		char* temp = new char[lineChars_ * 2];
		if (text_[i] != nullptr) {
			strcpy(temp, text_[i]);
		}
		delete[] text_[i];
		text_[i] = temp;
	}
	lineChars_ *= 2;
}