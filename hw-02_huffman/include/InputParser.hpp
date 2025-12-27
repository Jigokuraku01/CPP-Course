#pragma once

#include <string>
#include <stdexcept>

namespace parser
{
    class ParserInfo
    {
    public:
        static ParserInfo ParseInputQuery(int argc, char **argv);
        std::string &getInputFileName();
        std::string &getOutputFileName();
        bool isEncode();

    private:
        ParserInfo(bool isEncode, const std::string &inpFileName, const std::string &outFileName);
        std::string outFileName_;
        std::string inpFileName_;
        bool isEncode_;
    };
}