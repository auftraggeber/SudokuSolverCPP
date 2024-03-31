//
// Created by Jonas Langner on 31.03.24.
//

#ifndef SUDOKU_SOLVER_SUDOKUFIELDSORTER_H
#define SUDOKU_SOLVER_SUDOKUFIELDSORTER_H

#include <map>

namespace sudoku {
    class SudokuField;
}

namespace sudoku::algorithm {

        class SudokuFieldSorter {
        private:
            std::multimap<unsigned short, SudokuField*> m_map;
            std::map<unsigned int, unsigned short> m_id_map;
            std::map<unsigned int, SudokuField*> m_update_cache;
            std::vector<SudokuField*> m_fields;

            void persist(SudokuField*);

        public:
            SudokuFieldSorter() = default;
            SudokuFieldSorter(SudokuFieldSorter const &) = delete;
            SudokuFieldSorter(SudokuFieldSorter &&) = delete;

            SudokuFieldSorter& operator=(SudokuFieldSorter const &) = delete;
            SudokuFieldSorter& operator=(SudokuFieldSorter &&) = delete;

            SudokuField* operator[](unsigned int);

            bool contains(SudokuField*);

            void add_sudoku_field(SudokuField*);
            void remove_sudoku_field(SudokuField*);
            void update(SudokuField*);
            void flush();
            [[nodiscard]] std::vector<SudokuField*>::const_iterator begin() const noexcept;
            [[nodiscard]] std::vector<SudokuField*>::const_iterator end() const noexcept;
        };
} // sudoku:algorithm

#endif //SUDOKU_SOLVER_SUDOKUFIELDSORTER_H
