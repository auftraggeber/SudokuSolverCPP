//
// Created by Jonas Langner on 31.03.24.
//

#include "../../hdr/algorithm/SolvingOperation.h"
#include "../../hdr/SudokuField.h"
#include "../../hdr/algorithm/SudokuFieldSorter.h"
#include "../../hdr/SudokuFieldGroup.h"
#include <iostream>

sudoku::algorithm::SolvingOperation::SolvingOperation(SudokuField* sudoku_field_ptr, unsigned short no) noexcept:
m_sudoku_field_ptr{sudoku_field_ptr}, m_number{no} {}

sudoku::algorithm::SolvingOperation::SolvingOperation(sudoku::algorithm::SolvingOperation &&other) noexcept: m_sudoku_field_ptr{other.m_sudoku_field_ptr}, m_number{other.m_number}, m_effected_fields_by_perform{other.m_effected_fields_by_perform} {
    other.m_sudoku_field_ptr = nullptr;
    other.m_effected_fields_by_perform.clear();
}

sudoku::algorithm::SolvingOperation &sudoku::algorithm::SolvingOperation::operator=(sudoku::algorithm::SolvingOperation &&other) noexcept {
    m_sudoku_field_ptr = other.m_sudoku_field_ptr;
    m_number = other.m_number;
    m_effected_fields_by_perform = other.m_effected_fields_by_perform;

    other.m_sudoku_field_ptr = nullptr;
    other.m_effected_fields_by_perform.clear();

    return *this;
}

void sudoku::algorithm::SolvingOperation::for_each_related_sudoku_field_ptr(const std::function<void(SudokuField*)> &fnc) const {
    std::for_each(m_sudoku_field_ptr->begin(), m_sudoku_field_ptr->end(), [fnc](sudoku::SudokuFieldGroup* sudoku_field_group) {
        std::for_each(sudoku_field_group->begin(), sudoku_field_group->end(), [fnc](SudokuField* sudoku_field_ptr) {
            fnc(sudoku_field_ptr);
        });
    });
}

void sudoku::algorithm::SolvingOperation::perform(sudoku::Sudoku &sudoku) {
    m_sudoku_field_ptr->set_value(m_number);
    SudokuFieldSorter &sorter{sudoku.m_sorter};

    sorter.update(m_sudoku_field_ptr);
    for_each_related_sudoku_field_ptr([this, &sorter](SudokuField* sudoku_field_ptr) {
        if (sudoku_field_ptr->remove_number_option(m_number)) {
            m_effected_fields_by_perform.push_back(sudoku_field_ptr);
            sorter.update(sudoku_field_ptr);
        }
    });

    sorter.flush();
}

void sudoku::algorithm::SolvingOperation::rollback(Sudoku &sudoku) noexcept {
    auto const value{m_sudoku_field_ptr->value()};
    m_sudoku_field_ptr->remove_value();

    SudokuFieldSorter &sorter{sudoku.m_sorter};
    sorter.update(m_sudoku_field_ptr);

    std::for_each(m_effected_fields_by_perform.begin(), m_effected_fields_by_perform.end(), [&value, &sorter](SudokuField* sudoku_field_ptr){
        if (sudoku_field_ptr->add_number_option(value)) {
            sorter.update(sudoku_field_ptr);
        }
    });

    sorter.flush();
    m_effected_fields_by_perform.clear();
}

sudoku::SudokuField *sudoku::algorithm::SolvingOperation::sudoku_field() const noexcept {
    return m_sudoku_field_ptr;
}