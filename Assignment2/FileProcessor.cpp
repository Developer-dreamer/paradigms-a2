class FileProcessor {
public:
	FileProcessor(char* fileName) {
		this->fileName_ = fileName;
	}
	void SaveToFile(char** localText) {
		// read from file
	}
	char** LoadFromFile() {
		// read from file
	}
private:
	char* fileName_;
};