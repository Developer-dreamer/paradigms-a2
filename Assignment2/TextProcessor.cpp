#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "TextProcessor.h"


TextProcessor::TextProcessor(int rows, int lineChars) {
	this->rows_ = rows;
	this->lineChars_ = lineChars;
	text_ = new char*[rows_];
	std::fill_n(text_, rows_, nullptr);
}

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
		else if (text_[i][0] == '\n') {
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
void TextProcessor::IndexInput() {

}
void TextProcessor::SubstrSearch() {

}
void TextProcessor::Concatenate() {

}

void TextProcessor::ConcatenateTexts(char** textFromFile) {
	for (int i = 0; i < rows_; i++) {
		if (text_[i] == NULL || textFromFile[i] == NULL) {
			break;
		}
		strcpy(text_[i], textFromFile[i]);
	}
}

void TextProcessor::PrintText() {
	for(int i = 0; i < rows_; i++) {
		if (text_[i] == NULL) {
			break;
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
		strcpy(temp, text_[i]);
		delete[] text_[i];
		text_[i] = temp;	
   }
	lineChars_ *= 2;
}