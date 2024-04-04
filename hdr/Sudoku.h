//
// Created by Jonas Langner on 30.03.24.
//

#ifndef SUDOKU_SOLVER_SUDOKU_H
#define SUDOKU_SOLVER_SUDOKU_H

#include <map>
#include <memory>
#include "algorithm/SudokuFieldSorter.h"


namespace sudoku {

    class SudokuField;
    class SudokuFieldGroup;

    namespace algorithm {
        class SudokuFieldSorter;
        class SolvingOperation;
    }

    /**
     * Die Sudoku-Klasse ist für die Instaziierung und Verwaltung der Datenelemente eines Sodukus verantwortlich.
     * @author Jonas Langner
     * @version 0.1.0
     * @since 2024/04
     */
    class Sudoku {
        friend void initialize_sudoku_fields_sudoku_field_groups(unsigned short s1, unsigned short s2, unsigned short s3, Sudoku &sudoku, SudokuField *sudoku_field_ptr);
        friend void solve_sudoku(Sudoku &sudoku);
        friend class algorithm::SolvingOperation;

    private:
        unsigned short const m_size;
        algorithm::SudokuFieldSorter m_sorter;
        std::map<unsigned short, std::unique_ptr<SudokuFieldGroup>> m_row_sudoku_field_groups;
        std::map<unsigned short, std::unique_ptr<SudokuFieldGroup>> m_column_sudoku_field_groups;
        std::map<unsigned short, std::unique_ptr<SudokuFieldGroup>> m_box_sudoku_field_groups;

        void add_sudoku_field(SudokuField* sudoku_field_ptr) noexcept;

    public:
        /**
         * Erstellt ein neues Sudoku.
         * Dabei werden auch die zugehörigen Felder und Feldgruppen instanziiert.
         * @param size Die Größe des Sudokus und gleichzeigt der maximale Wert, der in einem Feld vorkommen darf.
         */
        explicit Sudoku(unsigned short size) noexcept;
        Sudoku(Sudoku const &) = delete;
        Sudoku(Sudoku &&) = delete;
        ~Sudoku();

        Sudoku& operator=(Sudoku const &) = delete;
        Sudoku& operator=(Sudoku &&) = delete;

        /**
         * Ermittelt das Feld an der entsprechenden Stelle.
         * @param i1 Die Stelle des Feldes.
         * @return Ein Zeiger auf das Feld.
         */
        SudokuField* operator[](unsigned int i1);

        [[nodiscard]] unsigned short size() const noexcept;
        /**
         * @return Der Startiterator der zu dem Sudoku zugehörigen Felder (Zeiger auf die Felder).
         */
        [[nodiscard]] std::vector<SudokuField*>::const_iterator begin() const noexcept;
        /**
         * @return Der Enditerator der zu dem Sudoku zugehörigen Felder (Zeiger auf die Felder).
         */
        [[nodiscard]] std::vector<SudokuField*>::const_iterator end() const noexcept;
    };


    /**
     * Löst das Sudoku.
     * @param sudoku Das Sudoku, das gelöst werden soll.
     */
    void solve_sudoku(Sudoku &sudoku);

} // sudoku

std::ostream& operator<<(std::ostream&, sudoku::Sudoku &); // überladung des print operators.

#endif //SUDOKU_SOLVER_SUDOKU_H
