//
// Created by Jonas Langner on 31.03.24.
//

#include "../../hdr/algorithm/SolvingOperation.h"
#include "../../hdr/SudokuField.h"
#include "../../hdr/algorithm/SudokuFieldSorter.h"
#include "../../hdr/SudokuFieldGroup.h"

sudoku::algorithm::SolvingOperation::SolvingOperation(SudokuField* sudoku_field_ptr, unsigned short no) noexcept:
m_sudoku_field_ptr{std::move(sudoku_field_ptr)}, m_number{no} {}

void sudoku::algorithm::SolvingOperation::for_each_related_sudoku_field_ptr(const std::function<void(SudokuField*)> &fnc) const {
    std::for_each(m_sudoku_field_ptr->begin(), m_sudoku_field_ptr->end(), [fnc](sudoku::SudokuFieldGroup const &sudoku_field_group) {
        std::for_each(sudoku_field_group.begin(), sudoku_field_group.end(), [fnc](SudokuField* sudoku_field_ptr) {
            fnc(sudoku_field_ptr);
        });
    });
}

void sudoku::algorithm::SolvingOperation::perform(sudoku::Sudoku &sudoku) const {
    m_sudoku_field_ptr->set_value(m_number);
    SudokuFieldSorter &sorter{sudoku.m_sorter};

    sorter.update(m_sudoku_field_ptr);
    for_each_related_sudoku_field_ptr([this, &sorter](SudokuField* sudoku_field_ptr) {
        sudoku_field_ptr->remove_number_option(m_number);
        sorter.update(sudoku_field_ptr);
    });

    sorter.flush();
}

void sudoku::algorithm::SolvingOperation::revert(sudoku::Sudoku &sudoku) const noexcept {
    auto const value{m_sudoku_field_ptr->value()};
    m_sudoku_field_ptr->remove_value();

    SudokuFieldSorter &sorter{sudoku.m_sorter};
    sorter.update(m_sudoku_field_ptr);
    for_each_related_sudoku_field_ptr([&value, &sorter](SudokuField* sudoku_field_ptr) {
       sudoku_field_ptr->add_number_option(value);
       sorter.update(sudoku_field_ptr);
    });

    sorter.flush();
}