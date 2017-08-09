#ifndef PARSEARGUMENTS_HPP
#define PARSEARGUMENTS_HPP

#include <memory>
#include <string>

/** @file
  * Defines the function parse_arguments and its result Arguments.
  */

/** @brief The result of parse_arguments
  */
struct Arguments
{
    /** @brief Assigns default values to all members.
      */
    Arguments();

    /** @brief Returns true if parse_arguments_result is RESULT_OK, otherwise false.
      */
    explicit operator bool() const;

    /** @brief Member for options: -h, --help, -H
      */
    bool help;
    /** @brief Member for arguments: sudoku_file
      */
    std::string sudoku_file;

    enum Result {
        /** @brief parse_arguments parsed the arguments successfully.
          */
        RESULT_OK,
        /** @brief parse_arguments encountered a help option.
          *
          * The help message has been displayed. The option and argument
          * members of this struct can not be relied upon.
          */
        RESULT_HELP,
        /** @brief There are invalid or missing options or arguments.
          *
          * An error message has been displayed. The option and argument
          * members of this struct can not be relied upon.
          */
        RESULT_ERROR
    };

    /** @brief The exit status of parse_arguments.
      *
      * This member should always be checked before any of the other members
      * are read.
      */
    Result parse_arguments_result;
};

/** @brief Parses the arguments in @a argv.
  *
  * @param argc the number of values in argv.
  * @param argv the arguments (an array of char-strings).
  * @returns an instance of Arguments with values in
  *     accordance with the parsed arguments. If @a argc is 0 the
  *     returned value is a nullptr.
  */
Arguments parse_arguments(int argc, char* argv[], bool autoExit = true);

#endif
