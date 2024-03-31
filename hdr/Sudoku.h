//
// Created by Jonas Langner on 30.03.24.
//

#ifndef SUDOKU_SOLVER_SUDOKU_H
#define SUDOKU_SOLVER_SUDOKU_H

#include <map>
#include <memory>

namespace sudoku {

    class SudokuField;
    class SudokuFieldGroup;

    class Sudoku {
        friend void initialize_sudoku_field_group(unsigned short, unsigned short, unsigned short, Sudoku &, SudokuField*);

    private:
        unsigned short const m_size;
        std::map<unsigned int, sudoku::SudokuField*> m_fields;
        std::map<unsigned short, SudokuFieldGroup> m_row_sudoku_field_groups;
        std::map<unsigned short, SudokuFieldGroup> m_column_sudoku_field_groups;
        std::map<unsigned short, SudokuFieldGroup> m_box_sudoku_field_groups;

        void add_sudoku_field(SudokuField* sudoku_field_ptr) noexcept;

    public:
        explicit Sudoku(unsigned short size) noexcept;
        Sudoku(Sudoku const &) = delete;
        Sudoku(Sudoku &&) = delete;
        ~Sudoku();

        Sudoku& operator=(Sudoku const &) = delete;
        Sudoku& operator=(Sudoku &&) = delete;

        [[nodiscard]] unsigned short size() const noexcept;
        [[nodiscard]] std::map<unsigned int, sudoku::SudokuField*>::const_iterator begin() const noexcept;
        [[nodiscard]] std::map<unsigned int, sudoku::SudokuField*>::const_iterator end() const noexcept;
    };

    void initialize_sudoku_field_group(unsigned short, unsigned short, unsigned short, Sudoku &, SudokuField*);

} // sudoku

std::ostream& operator<<(std::ostream&, sudoku::Sudoku const &);

#endif //SUDOKU_SOLVER_SUDOKU_H
