#pragma once
#include "huffmanTreeNode.hpp"
#include <vector>
#include <unordered_map>

namespace tree
{
    const int SizeOfBitset = 256;
    class HuffmanTree
    {
    public:
        HuffmanTree(HuffmanTreeNode *root);
        ~HuffmanTree();
        std::pair<std::vector<bool>, int> &findRepresentation(char ch);
        HuffmanTreeNode *root_;

    private:
        void makeObhod(std::vector<bool> &bs, int curDepth, tree::HuffmanTreeNode *curRoot);
        std::unordered_map<char, std::pair<std::vector<bool>, int>> ways_;
    };
}