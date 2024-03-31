//
// Created by Jonas Langner on 31.03.24.
//

#ifndef SUDOKU_SOLVER_SUDOKUFIELDGROUP_H
#define SUDOKU_SOLVER_SUDOKUFIELDGROUP_H

#include <vector>

namespace sudoku {

    class Sudoku;
    class SudokuField;

    class SudokuFieldGroup {
        friend void initialize_sudoku_field_group(unsigned short, unsigned short, unsigned short, Sudoku &, SudokuField*);

    private:
        std::vector<SudokuField*> m_fields;

    public:

        SudokuField* operator[](unsigned int) const;

        void add_number_option(unsigned short) const noexcept;
        void remove_number_option(unsigned short) const noexcept;

        std::vector<SudokuField*>::iterator begin() noexcept;
        std::vector<SudokuField*>::iterator end() noexcept;
    };

} // sudoku

#endif //SUDOKU_SOLVER_SUDOKUFIELDGROUP_H
