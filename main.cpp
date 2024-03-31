#include <iostream>
#include "hdr/Sudoku.h"

int main() {
    using namespace sudoku;

    Sudoku s{9};

    std::cout << s << std::endl;

    return 0;
}
