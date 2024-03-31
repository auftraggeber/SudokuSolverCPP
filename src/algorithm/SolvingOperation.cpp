//
// Created by Jonas Langner on 31.03.24.
//

#include "../../hdr/algorithm/SolvingOperation.h"
#include "../../hdr/SudokuField.h"

sudoku::algorithm::SolvingOperation::SolvingOperation(std::shared_ptr<SudokuField> sudoku_field_ptr, unsigned short no) noexcept:
m_sudoku_field_ptr{std::move(sudoku_field_ptr)}, m_number{no} {}

void sudoku::algorithm::SolvingOperation::perform(sudoku::Sudoku const &sudoku) const {
    m_sudoku_field_ptr->set_value(m_number);
}