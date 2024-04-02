//
// Created by Jonas Langner on 31.03.24.
//

#include "../../hdr/algorithm/SudokuFieldSorter.h"
#include "../../hdr/SudokuField.h"
#include <vector>
#include <iostream>

sudoku::SudokuField* sudoku::algorithm::SudokuFieldSorter::operator[](unsigned int const sudoku_field_id) {
    SudokuField* found_sudoku_field_ptr{nullptr};

    std::for_each(m_fields.begin(), m_fields.end(), [&found_sudoku_field_ptr, &sudoku_field_id](SudokuField* compare_sudoku_field_ptr) {
       if (compare_sudoku_field_ptr->id() == sudoku_field_id) {
           found_sudoku_field_ptr = compare_sudoku_field_ptr;
           return; // break for_each
       }
    });

    return found_sudoku_field_ptr;
}

bool sudoku::algorithm::SudokuFieldSorter::contains(sudoku::SudokuField* sudoku_field_ptr) {
    return operator[](sudoku_field_ptr->id()) != nullptr;
}

void sudoku::algorithm::SudokuFieldSorter::persist(sudoku::SudokuField* sudoku_field_ptr) {
    if (sudoku_field_ptr->has_value()) return;

    auto const option_count = sudoku_field_ptr->option_count();
    m_id_map.insert(std::make_pair(sudoku_field_ptr->id(), option_count));
    m_map.insert(std::make_pair(option_count, sudoku_field_ptr));
}

void sudoku::algorithm::SudokuFieldSorter::add_sudoku_field(sudoku::SudokuField* sudoku_field_ptr) {
    persist(sudoku_field_ptr);
    m_fields.push_back(sudoku_field_ptr);
}

void sudoku::algorithm::SudokuFieldSorter::remove_sudoku_field(sudoku::SudokuField* sudoku_field_ptr) {
    std::erase_if(m_map, [&sudoku_field_ptr](auto const &pair) {
        return sudoku_field_ptr == pair.second;
    });

    m_id_map.erase(sudoku_field_ptr->id());
    m_update_cache.erase(sudoku_field_ptr->id());
    m_fields.erase(std::remove(m_fields.begin(), m_fields.end(), sudoku_field_ptr), m_fields.end());
}

void sudoku::algorithm::SudokuFieldSorter::update(sudoku::SudokuField* sudoku_field_ptr) {
    m_update_cache.insert(std::make_pair(sudoku_field_ptr->id(), sudoku_field_ptr));
}

void sudoku::algorithm::SudokuFieldSorter::flush() {
    std::erase_if(m_map, [this](auto const &pair) {
        return m_update_cache.contains(pair.second->id());
    });

    std::for_each(m_update_cache.begin(), m_update_cache.end(), [this](auto const &pair) {
        persist(pair.second);
    });

    m_update_cache.clear();
}

bool sudoku::algorithm::SudokuFieldSorter::no_fields_without_value() const noexcept {
    return m_map.empty();
}

sudoku::SudokuField* sudoku::algorithm::SudokuFieldSorter::first() const noexcept {
    return m_map.begin()->second;
}

std::vector<sudoku::SudokuField*>::const_iterator sudoku::algorithm::SudokuFieldSorter::begin() const noexcept {
    return m_fields.begin();
}

std::vector<sudoku::SudokuField*>::const_iterator sudoku::algorithm::SudokuFieldSorter::end() const noexcept {
    return m_fields.end();
}