//
// Created by Jonas Langner on 30.03.24.
//

#include "../hdr/Sudoku.h"
#include "../hdr/SudokuField.h"
#include "../hdr/algorithm/SudokuFieldSorter.h"
#include "../hdr/algorithm/SolvingOperation.h"
#include "../hdr/algorithm/SudokuFieldIterator.h"
#include <iostream>
#include <memory>
#include <stack>

sudoku::Sudoku::Sudoku(unsigned short size) noexcept: m_size{size} {
    auto const max = m_size * m_size;

    for (unsigned int i = 0; i < m_size; ++i) {
        m_row_sudoku_field_groups[i] = std::make_unique<SudokuFieldGroup>();
        m_column_sudoku_field_groups[i] = std::make_unique<SudokuFieldGroup>();
        m_box_sudoku_field_groups[i] = std::make_unique<SudokuFieldGroup>();
    }

    for (unsigned int i = 0; i < max; ++i) {
        auto const row = static_cast<unsigned int>(std::floor(i / m_size));
        auto const column = i % m_size;
        auto const boxes_per_column_and_per_row{static_cast<unsigned short>(std::sqrt(m_size))};
        auto const box_column_index{static_cast<unsigned int>(std::floor(column / boxes_per_column_and_per_row))};
        auto const box_row_index{static_cast<unsigned int>(std::floor(row / boxes_per_column_and_per_row))};
        auto const box = box_column_index + (boxes_per_column_and_per_row * box_row_index);

        auto sudoku_field_ptr = new SudokuField{i, m_size};
        add_sudoku_field(sudoku_field_ptr);

        initialize_sudoku_fields_sudoku_field_groups(row, column, box, *this, sudoku_field_ptr);
    }
}

sudoku::Sudoku::~Sudoku() {
    while (m_sorter.begin() != m_sorter.end()) {
        SudokuField* sudoku_field_ptr = m_sorter.begin().operator[](0);
        m_sorter.remove_sudoku_field(sudoku_field_ptr);
        delete sudoku_field_ptr;
    }
}

sudoku::SudokuField* sudoku::Sudoku::operator[](unsigned int id) { return m_sorter.operator[](id); }

void sudoku::Sudoku::add_sudoku_field(sudoku::SudokuField *sudoku_field_ptr) noexcept {
    SudokuField* old_sudoku_field_ptr{m_sorter[sudoku_field_ptr->id()]};
    if (old_sudoku_field_ptr != nullptr) {
        m_sorter.remove_sudoku_field(old_sudoku_field_ptr);
        delete old_sudoku_field_ptr;
    }
    m_sorter.add_sudoku_field(sudoku_field_ptr);
}

unsigned short sudoku::Sudoku::size() const noexcept { return m_size; }



std::vector<sudoku::SudokuField*>::const_iterator sudoku::Sudoku::begin() const noexcept {
    return m_sorter.begin();
}

std::vector<sudoku::SudokuField*>::const_iterator sudoku::Sudoku::end() const noexcept {
    return m_sorter.end();
}

std::ostream& operator<<(std::ostream& ostream, sudoku::Sudoku &sudoku) {
    ostream << "Sudoku with size: " << sudoku.size() << std::endl;


    std::for_each(sudoku.begin(), sudoku.end(), [&ostream, &sudoku](sudoku::SudokuField* sudoku_field_ptr) {
        std::string begin{" "};
        auto const sudoku_field_id = sudoku_field_ptr->id();
        bool const column_line{sudoku_field_id % static_cast<unsigned short>(std::sqrt(sudoku.size())) == 0};
        bool const row_line{sudoku_field_id!= 0 && (sudoku_field_id / sudoku.size()) % static_cast<unsigned short>(std::sqrt(sudoku.size())) == 0};
        std::string out{"_"};

        /* set format and lines */
        if (sudoku_field_id % sudoku.size() == 0) {
            ostream << std::endl;

            if (row_line) {
                auto const char_length_per_row{sudoku.size() * (5 + 2) + std::sqrt(sudoku.size())};
                for (unsigned int i = 0; i < char_length_per_row; ++i) {
                    ostream << "-";
                }

                ostream << std::endl;
            }
        }
        else if (column_line) {
            begin = "| ";
        }

        /* get value */
        if (sudoku_field_ptr->has_value()) {
            out = std::to_string(sudoku_field_ptr->value());
        }

        /* format value */
        size_t remaining_char_count{5 - out.length()};
        size_t beginning_char_count{remaining_char_count / 2};
        size_t ending_char_count{remaining_char_count - beginning_char_count};
        while (beginning_char_count-- > 0) {
            out = " " + out;
        }
        while (ending_char_count-- > 0) {
            out += " ";
        }

        /* print value */
        ostream << begin << out << " ";
    });


    return ostream;
}

void sudoku::solve_sudoku(sudoku::Sudoku &sudoku) {
    using namespace algorithm;
    SudokuFieldSorter &sorter{sudoku.m_sorter};
    std::map<SudokuField*, SudokuFieldIterator> iterators;
    std::stack<SolvingOperation> operations;

    std::for_each(sorter.begin(), sorter.end(), [&sorter](SudokuField* sudoku_field_ptr) {
       sorter.update(sudoku_field_ptr);
    });
    sorter.flush();

    auto current_sudoku_field_ptr{sorter.first()};

    auto const get_iterator{
        [&iterators](SudokuField *sudoku_field_ptr) {
            if (!iterators.contains(sudoku_field_ptr)) {
                SudokuFieldIterator iterator{sudoku_field_ptr};
                iterators.insert(std::make_pair(sudoku_field_ptr, std::move(iterator)));
            }

            return &iterators.find(sudoku_field_ptr)->second;
        }
    };

    // ab hier beginnt der eingentliche algo

    auto const solve{
        [&get_iterator, &current_sudoku_field_ptr, &sorter, &sudoku, &operations]() {
            while (!sorter.no_fields_without_value()) {
                if (current_sudoku_field_ptr->option_count() <= 0) {
                    return false;
                }

                SudokuFieldIterator* iterator_ptr{get_iterator(current_sudoku_field_ptr)};

                if (iterator_ptr->has_next()) {
                    SolvingOperation solving_operation{current_sudoku_field_ptr, iterator_ptr->next()};
                    solving_operation.perform(sudoku);
                    operations.push(std::move(solving_operation));
                }
                else return false;

                current_sudoku_field_ptr = sorter.first();
            }

            return true;
        }
    };

    auto const fallback{
        [&get_iterator, &current_sudoku_field_ptr, &sudoku, &operations]() {

            SolvingOperation* last_operation_ptr{&operations.top()};
            SudokuFieldIterator* last_iterator_ptr{get_iterator(last_operation_ptr->sudoku_field())};

            while (!last_iterator_ptr->has_next()) {
                last_operation_ptr->rollback(sudoku);
                last_iterator_ptr->reset();

                operations.pop();

                if (operations.empty()) {
                    current_sudoku_field_ptr = last_operation_ptr->sudoku_field();
                    return;
                }

                last_operation_ptr = &operations.top();
                last_iterator_ptr = get_iterator(last_operation_ptr->sudoku_field());
            }

            last_operation_ptr->rollback(sudoku);
            operations.pop();

            current_sudoku_field_ptr = last_operation_ptr->sudoku_field();
        }
    };

    while (!solve()) {
        try {
            fallback();
        }
        catch (std::invalid_argument &invalid_argument){
            break;
        }
    }
}

