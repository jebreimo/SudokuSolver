//****************************************************************************
// Copyright © 2017 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2017-07-24.
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include <cassert>
#include <ostream>
#include "Sudoku.hpp"

namespace SudokuLib
{
    Sudoku::Sudoku(int boxWidth, int boxHeight)
            : m_BoxWith(boxWidth),
              m_BoxHeight(boxHeight)
    {
        m_Values.resize(size() * size());
    }

    int Sudoku::size() const
    {
        return m_BoxWith * m_BoxHeight;
    }

    int Sudoku::boxWidth() const
    {
        return m_BoxWith;
    }

    int Sudoku::boxHeight() const
    {
        return m_BoxHeight;
    }

    int Sudoku::value(int x, int y) const
    {
        return m_Values[x + y * m_BoxWith];
    }

    void Sudoku::setValue(int x, int y, int value)
    {
        assert(0 <= value && value <= size());
        m_Values[x + y * m_BoxWith] = value;
    }

    std::ostream& operator<<(std::ostream& os, const Sudoku& sudoku)
    {
        for (int i = 0; i < sudoku.size(); ++i)
        {
            if (i && i % sudoku.boxHeight() == 0)
            {
                for (int j = 0; j < sudoku.size(); ++j)
                {
                    if (j && j % sudoku.boxWidth() == 0)
                        os << "+";
                    os << "-";
                }
                os << "\n";
            }
            for (int j = 0; j < sudoku.size(); ++j)
            {
                if (j && j % sudoku.boxWidth() == 0)
                    os << "|";
                if (sudoku.value(i, j))
                    os << sudoku.value(i, j);
                else
                    os << " ";
            }
            os << "\n";
        }
        return os;
    }
}
