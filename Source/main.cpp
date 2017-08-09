//****************************************************************************
// Copyright © 2017 Jan Erik Breimo. All rights reserved.
// Created by Jan Erik Breimo on 2017-07-24.
//
// This file is distributed under the BSD License.
// License text is included with the source distribution.
//****************************************************************************
#include <iostream>
#include <Yson/JsonReader.hpp>
#include <cmath>
#include "../SudokuLib/Sudoku.hpp"
#include "../SudokuLib/FindClosestFactors.hpp"
#include "ParseArguments.hpp"

#define THROW_ERROR(msg) \
    throw std::runtime_error(msg)

struct SudokuFile
{
    int boxWidth = 0;
    int boxHeight = 0;
    std::vector<int> puzzle;
};

SudokuFile readSudokuFile(const std::string& fileName)
{
    SudokuFile sudokuFile;

    Yson::JsonReader reader(fileName);
    reader.nextValue();
    reader.enter();
    while (reader.nextKey())
    {
        auto key = Yson::read<std::string>(reader);
        reader.nextValue();
        if (key == "box width")
            sudokuFile.boxWidth = Yson::read<int>(reader);
        else if (key == "box height")
            sudokuFile.boxHeight = Yson::read<int>(reader);
        else if (key == "puzzle")
        {
            reader.enter();
            while (reader.nextValue())
                sudokuFile.puzzle.push_back(Yson::read<int>(reader));
            reader.leave();
        }
    }
    reader.leave();

    return sudokuFile;
}

SudokuLib::Sudoku readSudoku(const std::string& fileName)
{
    auto sudokuFile = readSudokuFile(fileName);

    auto sizeF = sqrt(double(sudokuFile.puzzle.size()));
    if (std::floor(sizeF) != sizeF)
        THROW_ERROR("The number of values in the sudoku ("
                    + std::to_string(sudokuFile.puzzle.size())
                    + ") isn't a quadratic number.");
    auto size = int(sizeF);
    if (!sudokuFile.boxWidth && !sudokuFile.boxHeight)
        std::tie(sudokuFile.boxWidth, sudokuFile.boxHeight) = SudokuLib::findClosestFactors(size);
    else if (!sudokuFile.boxWidth)
        sudokuFile.boxWidth = size / sudokuFile.boxHeight;
    else if (!sudokuFile.boxHeight)
        sudokuFile.boxHeight = size / sudokuFile.boxWidth;
    if (sudokuFile.boxHeight * sudokuFile.boxWidth != size)
        THROW_ERROR("The box height and/or width are incorrect.");

    SudokuLib::Sudoku sudoku(sudokuFile.boxWidth, sudokuFile.boxHeight);
    for (int i = 0; i < sudokuFile.puzzle.size(); ++i)
        sudoku.setValue(i % sudokuFile.boxWidth,
                        i / sudokuFile.boxWidth,
                        sudokuFile.puzzle[i]);
    return sudoku;
}

int main(int argc, char* argv[])
{
    auto args = parse_arguments(argc, argv);
    auto sudoku = readSudoku(args.sudoku_file);
    std::cout << sudoku;
    return 0;
}
