//****************************************************************************
// Copyright © 2017 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2017-07-24.
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include <iosfwd>
#include <vector>

namespace SudokuLib
{
    class Sudoku
    {
    public:
        Sudoku(int boxWidth = 3, int boxHeight = 3);

        int size() const;

        int boxWidth() const;

        int boxHeight() const;

        int value(int x, int y) const;

        void setValue(int x, int y, int value);
    private:
        std::vector<int> m_Values;
        int m_BoxWith;
        int m_BoxHeight;
    };

    std::ostream& operator<<(std::ostream& os, const Sudoku& sudoku);
}
