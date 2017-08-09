#include "ParseArguments.hpp"

#include <algorithm>
#include <cstring>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

namespace
{
    std::string programName;
    std::string helpText =
        "USAGE\n"
        "    %prog% <sudoku file>\n"
        "\n"
        "OPTIONS\n"
        "  -h --helpDisplay help text.\n"
        "\n";

    void writeHelp()
    {
        std::string s = "$prog$";
        auto first = begin(helpText);
        while (first != end(helpText))
        {
            auto last = std::search(first, end(helpText), begin(s), end(s));
            if (last == end(helpText))
                break;
            std::cout.write(&*first, distance(first, last));
            std::cout << programName;
            first = last + 6;
        }
        std::cout.write(&*first, distance(first, end(helpText)));
        std::cout.flush();
    }

    bool resemblesShortOption(const char* s)
    {
        if ((s[0] == '-') && (s[1] != '\0') &&
            (s[1] != '-' || s[2] == '\0' || s[2] == '='))
            return true;
        else
            return false;
    }

    bool resemblesOption(const char* s)
    {
        return s[0] == '-' && s[1] != '\0';
    }

    class ArgumentIterator
    {
    public:
        ArgumentIterator(int argc, char* argv[])
            : m_ArgIt(*argv),
              m_ArgsIt(&argv[0]),
              m_ArgsEnd(&argv[argc])
        {}

        bool nextArgument(std::string& arg)
        {
            arg.clear();
            if (m_ArgsIt == m_ArgsEnd)
            {
                return false;
            }
            else if (m_ArgIt != *m_ArgsIt)
            {
                arg = "-";
                arg.push_back(*m_ArgIt);
                if (!*++m_ArgIt)
                    m_ArgIt = *++m_ArgsIt;
                return true;
            }

            if (resemblesShortOption(m_ArgIt))
            {
                arg.assign(m_ArgIt, m_ArgIt + 2);
                if (*(m_ArgIt + 2))
                    m_ArgIt += 2;
                else
                    m_ArgIt = *++m_ArgsIt;
                return true;
            }

            char* end = m_ArgIt;
            if (resemblesOption(m_ArgIt))
            {
                end += 3;
                while (*end && *end != '=')
                    ++end;
            }
            else
            {
                while (*end)
                    ++end;
            }

            arg.assign(m_ArgIt, end);
            if (*end)
                m_ArgIt = end + 1;
            else
                m_ArgIt = *++m_ArgsIt;
            return true;
        }

        bool hasValue() const
        {
            return m_ArgIt != *m_ArgsIt;
        }
    private:
        char* m_ArgIt;
        char** m_ArgsIt;
        char** m_ArgsEnd;
    };

    template <typename T>
    bool fromString(const std::string& s, T& value)
    {
        std::istringstream stream(s);
        stream >> std::boolalpha >> value;
        return !stream.fail();
    }

    bool error(const std::string& flag,
               Arguments& result,
               const std::string& errorMsg)
    {
        std::cerr << "Error: " << flag << ": " << errorMsg << "\n"
                  << "Run \"" << programName
                  << " -h\" for help.\n";
        result.parse_arguments_result = Arguments::RESULT_ERROR;
        return false;
    }

    bool process_help_option(const std::string& flag,
                             ArgumentIterator& argIt,
                             Arguments& result)
    {
        writeHelp();
        result.help = true;
        result.parse_arguments_result = Arguments::RESULT_HELP;
        return false;
    }

    typedef bool (*ProcessOptionFunc)(const std::string&,
                                      ArgumentIterator&,
                                      Arguments&);
    typedef std::pair<std::string, ProcessOptionFunc> OptionProcessor;

    OptionProcessor optionProcessors[] = {
        OptionProcessor("-h", process_help_option),
        OptionProcessor("--help", process_help_option),
        OptionProcessor("-H", process_help_option)
    };

    ProcessOptionFunc findOptionProcessor(const std::string& flag)
    {
        const OptionProcessor* op = std::find_if(
                std::begin(optionProcessors),
                std::end(optionProcessors),
                [&](const OptionProcessor& o) {return o.first == flag;});
        if (op == std::end(optionProcessors))
            return nullptr;
        return op->second;
    }

}

Arguments::Arguments()
    : help(false),
      parse_arguments_result(RESULT_OK)
{
}

Arguments::operator bool() const
{
    return parse_arguments_result == RESULT_OK;
}

Arguments parse_arguments(int argc, char* argv[], bool autoExit)
{
    if (argc == 0)
        return Arguments();

    size_t pos = std::string(argv[0]).find_last_of("/\\");
    if (pos == std::string::npos)
        programName = argv[0];
    else
        programName = &argv[0][pos + 1];

    Arguments result;
    std::vector<std::string> args;

    ArgumentIterator argIt(argc - 1, argv + 1);
    std::string arg;
    while (argIt.nextArgument(arg))
    {
        ProcessOptionFunc func = findOptionProcessor(arg);
        if (func)
        {
            if (!func(arg, argIt, result))
            {
                if (autoExit)
                    exit(result.parse_arguments_result);
                return result;
            }
        }
        else if (resemblesOption(arg.c_str()))
        {
            error(arg, result, "unknown option.");
            if (autoExit)
                exit(result.parse_arguments_result);
            return result;
        }
        else
        {
            args.push_back(arg);
        }
    }

    if (args.size() != 1)
    {
        std::cerr << "Error: incorrect number of arguments";
        if (args.size() != 0)
            std::cerr << "(expected 1, but received "
                      << args.size() << ")";
        std::cerr << ".\nRun \"" << programName << " -h\" for help.\n";
        result.parse_arguments_result = Arguments::RESULT_ERROR;
        if (autoExit)
            exit(result.parse_arguments_result);
        return result;
    }

    std::vector<std::string>::const_iterator it = args.begin();

    result.sudoku_file = *it++;
    return result;
}
