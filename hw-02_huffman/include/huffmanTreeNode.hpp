#pragma once

namespace tree
{
    class HuffmanTreeNode
    {
    public:
        HuffmanTreeNode(int cnt, HuffmanTreeNode * = nullptr, HuffmanTreeNode * = nullptr, const char = 0, const bool = false);
        ~HuffmanTreeNode();
        bool isFinal() const;
        HuffmanTreeNode *getRight() const;
        HuffmanTreeNode *getLeft() const;
        char getChr() const;
        bool operator<(const HuffmanTreeNode &left) const;
        int getCnt() const;

    private:
        char chr_;
        bool isFinal_;
        HuffmanTreeNode *left_;
        HuffmanTreeNode *right_;
        int cnt_;
    };
}