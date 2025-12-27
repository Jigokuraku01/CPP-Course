#include "InputParser.hpp"

std::string &parser::ParserInfo::getOutputFileName()
{
    return outFileName_;
}
std::string &parser::ParserInfo::getInputFileName()
{
    return inpFileName_;
}

bool parser::ParserInfo::isEncode()
{
    return isEncode_;
}

parser::ParserInfo::ParserInfo(bool isEncode, const std::string &inpFileName, const std::string &outFileName)
{
    isEncode_ = isEncode;
    inpFileName_ = inpFileName;
    outFileName_ = outFileName;
}

parser::ParserInfo parser::ParserInfo::ParseInputQuery(int argc, char **argv)
{
    bool tmpFlagForInput = false;
    bool IsEncode;
    for (int i = 0; i < argc; ++i)
        if (std::string(argv[i]) == "-u")
        {
            IsEncode = false;
            tmpFlagForInput = true;
        }
    for (int i = 0; i < argc; ++i)
        if (std::string(argv[i]) == "-c")
        {
            IsEncode = true;
            if (tmpFlagForInput)
                throw std::runtime_error("incorrect input format");
            tmpFlagForInput = true;
        }
    if (!tmpFlagForInput)
        throw std::runtime_error("incorrect input format");
    tmpFlagForInput = false;
    std::string inpFileName;
    for (int i = 0; i < argc; ++i)
        if (std::string(argv[i]) == "-f" || std::string(argv[i]) == "--file")
        {
            if (i + 1 >= argc)
                throw std::runtime_error("incorrect input format");
            inpFileName = std::string(argv[i + 1]);
            tmpFlagForInput = true;
        }
    if (!tmpFlagForInput)
        throw std::runtime_error("incorrect input format");

    tmpFlagForInput = false;
    std::string outFileName;
    for (int i = 0; i < argc; ++i)
        if (std::string(argv[i]) == "-o" || std::string(argv[i]) == "--output")
        {
            if (i + 1 >= argc)
                throw std::runtime_error("incorrect input format");
            outFileName = std::string(argv[i + 1]);
            tmpFlagForInput = true;
        }
    if (!tmpFlagForInput)
        throw std::runtime_error("incorrect input format");
    return ParserInfo(IsEncode, inpFileName, outFileName);
}