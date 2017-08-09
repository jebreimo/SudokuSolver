cmake_minimum_required(VERSION 3.8)
project(SudokuSolver)

set(CMAKE_CXX_STANDARD 17)

if (APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
elseif (WIN32)
    add_definitions(-D_SCL_SECURE_NO_WARNINGS)
endif (APPLE)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
    "${CMAKE_SOURCE_DIR}/cmake/Modules")

find_package(YSON REQUIRED)
include_directories(${YSON_INCLUDE_DIR})

set(SUDOKULIB_FILES
    SudokuLib/FindClosestFactors.hpp
    SudokuLib/Sudoku.cpp
    SudokuLib/Sudoku.hpp
    SudokuLib/SudokuCandidates.cpp
    SudokuLib/SudokuCandidates.hpp
    SudokuLib/SudokuSolver.cpp
    SudokuLib/SudokuSolver.hpp
    )

set(SOURCE_FILES
    Source/main.cpp
    Source/ParseArguments.cpp
    Source/ParseArguments.hpp
    )

add_executable(${PROJECT_NAME}
    ${SOURCE_FILES}
    ${SUDOKULIB_FILES}
    )

target_link_libraries(${PROJECT_NAME}
    ${YSON_LIBRARY}
    )
