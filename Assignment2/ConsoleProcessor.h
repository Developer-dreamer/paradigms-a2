#pragma once

#ifndef PROCESSORS
struct Coordinates {
    int row;
    int index;
};

class Console {
public:
    static void ReadConsole();
    int ReadCommand();
    Coordinates ReadCoordinates();
    void Clear();
private:
    static char* inputText_;
    static int inputTextLen_;
    int command_;
    Coordinates coords_;
    static void dynamicResize(int size);
};
#endif // !PROCESSOR
