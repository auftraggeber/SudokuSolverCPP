//
// Created by Jonas Langner on 31.03.24.
//

#include "../hdr/SudokuFieldGroup.h"

sudoku::SudokuField* sudoku::SudokuFieldGroup::operator[](unsigned int const i) const { return m_fields[i]; }

std::vector<sudoku::SudokuField*>::iterator sudoku::SudokuFieldGroup::begin() noexcept {
    return m_fields.begin();
}

std::vector<sudoku::SudokuField*>::iterator sudoku::SudokuFieldGroup::end() noexcept {
    return m_fields.end();
}