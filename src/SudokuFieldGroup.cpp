//
// Created by Jonas Langner on 31.03.24.
//

#include "../hdr/SudokuFieldGroup.h"
#include "../hdr/SudokuField.h"

sudoku::SudokuField* sudoku::SudokuFieldGroup::operator[](unsigned int const i) const { return m_fields[i]; }

void sudoku::SudokuFieldGroup::add_number_option(unsigned short no) const noexcept {
    std::for_each(m_fields.begin(), m_fields.end(), [&no](SudokuField* sudoku_field_ptr) {
        sudoku_field_ptr->add_number_option(no);
    });
}

void sudoku::SudokuFieldGroup::remove_number_option(unsigned short no) const noexcept {
    std::for_each(m_fields.begin(), m_fields.end(), [&no](SudokuField* sudoku_field_ptr) {
        sudoku_field_ptr->remove_number_option(no);
    });
}

std::vector<sudoku::SudokuField*>::iterator sudoku::SudokuFieldGroup::begin() noexcept {
    return m_fields.begin();
}

std::vector<sudoku::SudokuField*>::iterator sudoku::SudokuFieldGroup::end() noexcept {
    return m_fields.end();
}