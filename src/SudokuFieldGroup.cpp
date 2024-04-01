//
// Created by Jonas Langner on 31.03.24.
//

#include "../hdr/SudokuFieldGroup.h"
#include "../hdr/SudokuField.h"

sudoku::SudokuField* sudoku::SudokuFieldGroup::operator[](unsigned int const i) const { return m_fields[i]; }

std::vector<sudoku::SudokuField*>::const_iterator sudoku::SudokuFieldGroup::begin() const noexcept {
    return m_fields.begin();
}

std::vector<sudoku::SudokuField*>::const_iterator sudoku::SudokuFieldGroup::end() const noexcept {
    return m_fields.end();
}