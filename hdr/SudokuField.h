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

    /**
     * Ein Feld eines Sudokus kann immer genau ein Wert haben.
     * Ein Feld gehört immer zu einer horizontalen, zu einer vertikalen und zu einer quadratischen Feldgruppe.
     * Solange ein Feld nicht gelöst ist oder keinen festgeschriebenen Wert hat, gibt es eine beschränkte Anzahl an
     * Lösungsmöglichkeiten für das Feld.
     * Diese Klasse hölt die Daten für die Felder.
     * @author Jonas Langner
     * @version 0.1.0
     * @since 2024/04
     */
    class SudokuField {
        friend void initialize_sudoku_fields_sudoku_field_groups(unsigned short, unsigned short, unsigned short, Sudoku &, SudokuField*);
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
        /**
         * @return Der Startiterator der zu dem Feld zugehörigen Feldgruppen.
         */
        [[nodiscard]] std::array<SudokuFieldGroup*, 3>::const_iterator begin() const noexcept;
        /**
         * @return Der Enditerator der zu dem Feld zugehörigen Feldgruppen.
         */
        [[nodiscard]] std::array<SudokuFieldGroup*, 3>::const_iterator end() const noexcept;

    };

    /**
     * Setzt für ein Feld die Feldgruppen, in dem es sich befindet.
     * @param s1 Der Kennzeichner der horizontalen Feldgruppe.
     * @param s2 Der Kennzeichner der vertikalen Feldgruppe.
     * @param s3 Der Kennzeichner der quadratischen Feldgruppe.
     * @param sudoku Das Sudoku, zu dem das Feld gehört.
     * @param sudoku_field_ptr Ein Zeiger auf das Feld, dessen Feldgruppen gesetzt werden sollen.
     */
    void initialize_sudoku_fields_sudoku_field_groups(unsigned short s1, unsigned short s2, unsigned short s3, Sudoku &sudoku, SudokuField* sudoku_field_ptr);
    /**
     * Legt für ein Feld den Startwert fest.
     * @param sudoku Das Sudoku, zu dem das Feld gehört.
     * @param sudoku_field_ptr Ein Zeiger auf das Feld, dass einen Startwert bekommen soll.
     * @param s Der Startwert.
     */
    void initialize_fixed_sudoku_field_value(Sudoku &sudoku, SudokuField* sudoku_field_ptr, unsigned short s);

} // sudoku

#endif //SUDOKU_SOLVER_SUDOKUFIELD_H
