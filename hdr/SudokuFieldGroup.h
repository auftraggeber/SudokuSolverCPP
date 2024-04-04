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
        friend void initialize_sudoku_fields_sudoku_field_groups(unsigned short, unsigned short, unsigned short, Sudoku &, SudokuField*);

    private:
        std::vector<SudokuField*> m_fields;

    public:

        SudokuField* operator[](unsigned int) const;

        [[nodiscard]] std::vector<SudokuField*>::const_iterator begin() const noexcept;
        [[nodiscard]] std::vector<SudokuField*>::const_iterator end() const noexcept;
    };

} // sudoku

#endif //SUDOKU_SOLVER_SUDOKUFIELDGROUP_H
