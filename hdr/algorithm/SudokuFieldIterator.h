//
// Created by Jonas Langner on 01.04.24.
//

#ifndef SUDOKU_SOLVER_SUDOKUFIELDITERATOR_H
#define SUDOKU_SOLVER_SUDOKUFIELDITERATOR_H

namespace sudoku {

    class SudokuField;

    namespace algorithm {

        class SudokuFieldIterator {
        private:
            SudokuField* m_sudoku_field_ptr;
            int m_index{-1};

        public:
            explicit SudokuFieldIterator(SudokuField* sudoku_field_ptr);

            SudokuFieldIterator(SudokuFieldIterator const &) = delete;
            SudokuFieldIterator(SudokuFieldIterator &&) noexcept;

            SudokuFieldIterator& operator=(SudokuFieldIterator const &) = delete;
            SudokuFieldIterator& operator=(SudokuFieldIterator &&) noexcept;

            void reset() noexcept;
            [[nodiscard]] bool has_next() const noexcept;
            [[nodiscard]] unsigned short next();
        };

    } // algorithm
} // sudoku

#endif //SUDOKU_SOLVER_SUDOKUFIELDITERATOR_H
