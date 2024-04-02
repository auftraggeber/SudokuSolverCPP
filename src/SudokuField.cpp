//
// Created by Jonas Langner on 30.03.24.
//

#include <iostream>
#include "../hdr/SudokuField.h"

sudoku::SudokuField::SudokuField(unsigned int id, unsigned short max_no) noexcept: m_id{id} {
    for (int i = 1; i <= max_no; ++i) {
        m_options.push_back(i);
    }
}

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

bool sudoku::SudokuField::remove_number_option(unsigned short no) noexcept {
    if (has_value()) return false;

    auto const size_before{m_options.size()};

    m_options.erase(
            std::remove_if(
                    m_options.begin(),
                    m_options.end(),
                    [&no](unsigned short n){
                        return no == n;
                    }),
            m_options.end());

    return size_before > m_options.size();
}

bool sudoku::SudokuField::add_number_option(unsigned short no) noexcept {
    if (has_number_option(no)) return false; // already in vector

    auto const size_before{m_options.size()};

    m_options.push_back(no);
    std::sort(m_options.begin(), m_options.end(), std::greater<>());

    return size_before < m_options.size();
}

bool sudoku::SudokuField::has_number_option(unsigned short no) const noexcept {
    return std::find(m_options.begin(), m_options.end(), no) != m_options.end();
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

std::array<sudoku::SudokuFieldGroup*, 3>::const_iterator sudoku::SudokuField::begin() const noexcept {
    return m_sudoku_field_groups.begin();
}

std::array<sudoku::SudokuFieldGroup*, 3>::const_iterator sudoku::SudokuField::end() const noexcept {
    return m_sudoku_field_groups.end();
}

