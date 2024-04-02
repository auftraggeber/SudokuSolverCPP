#include <iostream>
#include "hdr/Sudoku.h"
#include "hdr/SudokuField.h"


int main() {
    using namespace sudoku;

    Sudoku s{9};

    initialize_fixed_sudoku_field_value(s, s[3], 5);
    initialize_fixed_sudoku_field_value(s, s[8], 9);

    initialize_fixed_sudoku_field_value(s, s[15], 1);
    initialize_fixed_sudoku_field_value(s, s[16], 2);
    initialize_fixed_sudoku_field_value(s, s[17], 4);

    initialize_fixed_sudoku_field_value(s, s[21], 9);
    initialize_fixed_sudoku_field_value(s, s[22], 6);

    initialize_fixed_sudoku_field_value(s, s[26], 8);

    initialize_fixed_sudoku_field_value(s, s[28], 6);
    initialize_fixed_sudoku_field_value(s, s[30], 3);
    initialize_fixed_sudoku_field_value(s, s[32], 7);

    initialize_fixed_sudoku_field_value(s, s[36], 9);
    initialize_fixed_sudoku_field_value(s, s[43], 7);

    initialize_fixed_sudoku_field_value(s, s[46], 8);
    initialize_fixed_sudoku_field_value(s, s[51], 2);

    initialize_fixed_sudoku_field_value(s, s[54], 1);
    initialize_fixed_sudoku_field_value(s, s[56], 4);
    initialize_fixed_sudoku_field_value(s, s[59], 9);

    initialize_fixed_sudoku_field_value(s, s[65], 2);
    initialize_fixed_sudoku_field_value(s, s[67], 4);
    initialize_fixed_sudoku_field_value(s, s[70], 8);

    initialize_fixed_sudoku_field_value(s, s[76], 1);


    std::cout << s << std::endl;

    solve_sudoku(s);

    std::cout << s << std::endl;

    return 0;
}



