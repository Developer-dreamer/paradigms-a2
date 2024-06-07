#include <iostream>
#include "ConsoleProcessor.h"

class TextProcessor {
public:
	TextProcessor(int rows, int lineChars) {
		this->rows_ = rows;
		this->lineChars_ = lineChars;
	}
	void EndInsert() {

	}
	void StartNewLine() {

	}
	void IndexInput() {

	}
	void SubstrSearch() {

	}
	void Concatenate() {

	}
private:
	char* text_;
	int rows_;
	int lineChars_;
	Coordinates cursorPos_;
};
