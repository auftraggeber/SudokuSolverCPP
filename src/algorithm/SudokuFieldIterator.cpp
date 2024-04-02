//
// Created by Jonas Langner on 01.04.24.
//

#include "../../hdr/algorithm/SudokuFieldIterator.h"
#include "../../hdr/SudokuField.h"

sudoku::algorithm::SudokuFieldIterator::SudokuFieldIterator(sudoku::SudokuField* sudoku_field_ptr): m_sudoku_field_ptr{sudoku_field_ptr} {}

sudoku::algorithm::SudokuFieldIterator::SudokuFieldIterator(sudoku::algorithm::SudokuFieldIterator &&other) noexcept:
m_sudoku_field_ptr{other.m_sudoku_field_ptr} {
    other.m_sudoku_field_ptr = nullptr;
}

sudoku::algorithm::SudokuFieldIterator &
sudoku::algorithm::SudokuFieldIterator::operator=(sudoku::algorithm::SudokuFieldIterator &&other) noexcept {
    m_sudoku_field_ptr = other.m_sudoku_field_ptr;
    other.m_sudoku_field_ptr = nullptr;

    return *this;
}

void sudoku::algorithm::SudokuFieldIterator::reset() noexcept {
    m_index = -1;
}

bool sudoku::algorithm::SudokuFieldIterator::has_next() const noexcept {
    auto begin{m_sudoku_field_ptr->m_options.begin()};
    begin += m_index + 1;
    return begin < m_sudoku_field_ptr->m_options.end();
}

unsigned short sudoku::algorithm::SudokuFieldIterator::next() {
    if (!has_next()) {
        throw std::invalid_argument("there is no next element.");
    }

    return m_sudoku_field_ptr->m_options.begin()[++m_index];
}

