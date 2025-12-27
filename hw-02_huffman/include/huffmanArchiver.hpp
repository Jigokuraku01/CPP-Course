#pragma once
#include "InputParser.hpp"
#include "huffmanTree.hpp"
#include <stdexcept>
#include <bitset>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <string>
#include <iterator>
#include <filesystem>
#include <vector>
#include <queue>
#include <functional>
#include <iostream>
#include <locale>
#include <iterator>

namespace tree
{
    class HuffmanArchiver
    {
    public:
        void static ParseInputQuery(parser::ParserInfo &parserInfo);
        size_t static encodeProxy(std::string &inpFileName, std::string &OutFileName);
        size_t static decodeProxy(std::string &inpFileName, std::string &OutFileName);

    public:
        std::pair<tree::HuffmanTreeNode *, std::vector<char>> static CreateTreeFromTxt(const std::string &FPath, std::vector<char> &FoundChar);
        void static archive(std::string &OutputFile, HuffmanTree &curTree, const std::vector<char> &possibleChar, const std::vector<char> &whatEncode);
        void static writeToFileWholeBitset(std::ofstream &os, std::vector<bool> &bs);
    };
}