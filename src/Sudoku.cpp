//
// Created by Jonas Langner on 30.03.24.
//

#include "../hdr/Sudoku.h"
#include "../hdr/SudokuField.h"
#include "../hdr/algorithm/SudokuFieldSorter.h"
#include <iostream>

sudoku::Sudoku::Sudoku(unsigned short size) noexcept: m_size{size} {
    auto const max = m_size * m_size;

    for (unsigned int i = 0; i < max; ++i) {
        auto const row = static_cast<unsigned int>(std::floor(i / m_size));
        auto const column = i % m_size;
        auto const box = column + (static_cast<unsigned short>(std::sqrt(m_size)) * row);

        auto sudoku_field_ptr = new SudokuField{i, m_size};
        add_sudoku_field(sudoku_field_ptr);

        initialize_sudoku_field_group(row, column, box, *this, sudoku_field_ptr);
    }
}

sudoku::Sudoku::~Sudoku() {
    while (m_sorter.begin() != m_sorter.end()) {
        SudokuField* sudoku_field_ptr = m_sorter.begin().operator[](0);
        m_sorter.remove_sudoku_field(sudoku_field_ptr);
        delete sudoku_field_ptr;
    }
}

void sudoku::Sudoku::add_sudoku_field(sudoku::SudokuField *sudoku_field_ptr) noexcept {
    SudokuField* old_sudoku_field_ptr{m_sorter[sudoku_field_ptr->id()]};
    if (old_sudoku_field_ptr != nullptr) {
        m_sorter.remove_sudoku_field(old_sudoku_field_ptr);
        delete old_sudoku_field_ptr;
    }
    m_sorter.add_sudoku_field(sudoku_field_ptr);
}

unsigned short sudoku::Sudoku::size() const noexcept { return m_size; }

void sudoku::initialize_sudoku_field_group(unsigned short row, unsigned short column, unsigned short box,
                                           Sudoku &sudoku, SudokuField* sudoku_field_ptr) {
    short calls = 0;

    auto init = [&calls, &sudoku_field_ptr](SudokuFieldGroup &sudoku_field_group) {
        sudoku_field_group.m_fields.push_back(sudoku_field_ptr);
        sudoku_field_ptr->m_sudoku_field_groups[calls++] = sudoku_field_group;
    };

    init(sudoku.m_row_sudoku_field_groups[row]);
    init(sudoku.m_column_sudoku_field_groups[column]);
    init(sudoku.m_box_sudoku_field_groups[box]);
}

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