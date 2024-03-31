//
// Created by Jonas Langner on 30.03.24.
//

#include <iostream>
#include "../hdr/SudokuField.h"

sudoku::SudokuField::SudokuField(unsigned int id) noexcept: m_id{id} {}

bool sudoku::SudokuField::operator==(const sudoku::SudokuField &other) const noexcept {
    return m_id == other.m_id;
}

void sudoku::SudokuField::set_value(unsigned short no) {
    if (no <= 0) {
        throw std::invalid_argument("value has to be greater than zero.");
    }
    if (has_value()) {
        throw std::invalid_argument("value already set.");
    }

    m_value = no;
}

void sudoku::SudokuField::remove_value() noexcept {
    m_value = 0;
}

void sudoku::SudokuField::remove_number_option(unsigned short no) noexcept {
    m_options.erase(
            std::remove_if(
                    m_options.begin(),
                    m_options.end(),
                    [&no](unsigned int n){
                        return no == n;
                    }),
            m_options.end());
}

void sudoku::SudokuField::add_number_option(unsigned short no) noexcept {
    if (number_is_possible(no)) return; // already in vector
    m_options.push_back(no);
}

bool sudoku::SudokuField::number_is_possible(unsigned short no) const noexcept {
    return !has_value() && std::find(m_options.begin(), m_options.end(), no) != m_options.end();
}

bool sudoku::SudokuField::has_value() const noexcept {
    return m_value > 0;
}

unsigned int sudoku::SudokuField::id() const noexcept { return m_id; }

unsigned short sudoku::SudokuField::option_count() const noexcept { return m_options.size(); }

unsigned short sudoku::SudokuField::value() const {
    if (!has_value()) {
        throw std::invalid_argument("this field has no value.");
    }

    return m_value;
}

