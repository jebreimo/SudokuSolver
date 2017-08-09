//****************************************************************************
// Copyright © 2017 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2017-07-24.
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include <vector>
#include "Sudoku.hpp"

namespace SudokuLib
{
    struct Position
    {
        int x;
        int y;
    };

    struct Conflict
    {
        Position first;
        Position second;
    };

    struct Solution
    {
        Position cell;
        int value;
    };

    /*
     * Elimination methods:
     *      1 Direct candidate elimination (box, row, column)
     *      4 Indirect candidate elimination (row, column, box)
     *      7 Candidate group elimination (size: 2, 3, ..., SIZE / 2)
     *
     * Solution detection:
     *      0 Single candidate-cell in box
     *      1 Single candidate-cell on row/column
     *      2 Single candidate-value in cell
     */
    class SudokuSolver
    {
    public:
        std::vector<Conflict> validate(const Sudoku& sudoku);

        std::vector<Solution> solveNext();
    };
}
