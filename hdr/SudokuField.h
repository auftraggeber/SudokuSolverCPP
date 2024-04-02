//
// Created by Jonas Langner on 30.03.24.
//

#ifndef SUDOKU_SOLVER_SUDOKUFIELD_H
#define SUDOKU_SOLVER_SUDOKUFIELD_H

#include <vector>
#include <array>
#include "Sudoku.h"
#include "algorithm/SolvingOperation.h"
#include "SudokuFieldGroup.h"

namespace sudoku {

    class SudokuFieldGroup;

    namespace algorithm {
        class SudokuFieldIterator;
    }

    class SudokuField {
        friend void initialize_sudoku_field_group(unsigned short, unsigned short, unsigned short, Sudoku &, SudokuField*);
        friend class algorithm::SudokuFieldIterator;

    private:
        unsigned const int m_id;
        std::vector<unsigned short> m_options;
        unsigned short m_value{0};
        std::array<SudokuFieldGroup*, 3> m_sudoku_field_groups;

    public:
        explicit SudokuField(unsigned int, unsigned short) noexcept;
        SudokuField(SudokuField const &) = delete;
        SudokuField(SudokuField &&) = delete;

        SudokuField& operator=(SudokuField const &) = delete;
        SudokuField& operator=(SudokuField &&) = delete;

        [[nodiscard]] bool operator==(SudokuField const &) const noexcept;

        void set_value(unsigned short);
        void remove_value() noexcept;
        [[nodiscard]] bool remove_number_option(unsigned short) noexcept;
        [[nodiscard]] bool add_number_option(unsigned short) noexcept;
        [[nodiscard]] bool has_number_option(unsigned short) const noexcept;
        [[nodiscard]] bool has_value() const noexcept;
        [[nodiscard]] unsigned int id() const noexcept;
        [[nodiscard]] unsigned short option_count() const noexcept;
        [[nodiscard]] unsigned short value() const;
        [[nodiscard]] std::array<SudokuFieldGroup*, 3>::const_iterator begin() const noexcept;
        [[nodiscard]] std::array<SudokuFieldGroup*, 3>::const_iterator end() const noexcept;

    };

} // sudoku

#endif //SUDOKU_SOLVER_SUDOKUFIELD_H
