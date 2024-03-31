//
// Created by Jonas Langner on 31.03.24.
//

#ifndef SUDOKU_SOLVER_SOLVINGOPERATION_H
#define SUDOKU_SOLVER_SOLVINGOPERATION_H

#include <memory>

namespace sudoku{
    class Sudoku;
    class SudokuField;
}

namespace sudoku::algorithm {

    class SolvingOperation {
    private:
        std::shared_ptr<SudokuField> m_sudoku_field_ptr;
        unsigned short m_number;

    public:
        explicit SolvingOperation(std::shared_ptr<SudokuField>, unsigned short) noexcept;
        SolvingOperation(SolvingOperation const &) = delete;
        SolvingOperation(SolvingOperation &&) = delete;

        SolvingOperation& operator=(SolvingOperation const &) = delete;
        SolvingOperation& operator=(SolvingOperation &&) = delete;

        void perform(Sudoku const &) const;
        void revert(Sudoku const &) const noexcept;
    };

} // sudoku::algorithm

#endif //SUDOKU_SOLVER_SOLVINGOPERATION_H
