//****************************************************************************
// Copyright © 2017 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2017-07-25.
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#pragma once

#include <vector>

namespace SudokuLib
{
    class SudokuCandidates
    {
    public:
        SudokuCandidates(int boxWidth = 3, int boxHeight = 3);

        void removeValues(int x, int y, unsigned values);

        void setValues(int x, int y, unsigned values);

        unsigned values(int x, int y) const;

        bool hasSingleValue(int x, int y) const;
    private:
        std::vector<unsigned> m_Candidates;
        int m_BoxWith;
        int m_BoxHeight;
    };
}
