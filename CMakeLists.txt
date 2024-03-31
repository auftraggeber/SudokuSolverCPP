cmake_minimum_required(VERSION 3.27)
project(sudoku_solver)

set(CMAKE_CXX_STANDARD 20)

add_executable(sudoku_solver main.cpp
        src/SudokuField.cpp
        hdr/SudokuField.h
        src/Sudoku.cpp
        hdr/Sudoku.h
        src/algorithm/SolvingOperation.cpp
        hdr/algorithm/SolvingOperation.h
        src/SudokuFieldGroup.cpp
        hdr/SudokuFieldGroup.h
        src/algorithm/SudokuFieldSorter.cpp
        hdr/algorithm/SudokuFieldSorter.h)
