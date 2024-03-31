#include <iostream>
#include "hdr/Sudoku.h"


int main() {
    using namespace sudoku;

    for (unsigned int i = 0; i < 100000000; ++i) {
        std::cout << i << std::endl;
        Sudoku s{9};
        std::cout << s << std::endl;
        std::cout << i << std::endl;
    }

    return 0;
}


