//
// Created by Jonas Langner on 31.03.24.
//

#ifndef SUDOKU_SOLVER_SOLVINGOPERATION_H
#define SUDOKU_SOLVER_SOLVINGOPERATION_H

#include <memory>
#include <functional>

namespace sudoku{
    class Sudoku;
    class SudokuField;
}

namespace sudoku::algorithm {

    class SolvingOperation {
    private:
        SudokuField* m_sudoku_field_ptr;
        unsigned short m_number;

        void for_each_related_sudoku_field_ptr(std::function<void(SudokuField*)> const &) const;

    public:
        explicit SolvingOperation(SudokuField*, unsigned short) noexcept;
        SolvingOperation(SolvingOperation const &) = delete;
        SolvingOperation(SolvingOperation &&) = delete;

        SolvingOperation& operator=(SolvingOperation const &) = delete;
        SolvingOperation& operator=(SolvingOperation &&) = delete;

        void perform(Sudoku &) const;
        void revert(Sudoku &) const noexcept;
    };

} // sudoku::algorithm

#endif //SUDOKU_SOLVER_SOLVINGOPERATION_H
