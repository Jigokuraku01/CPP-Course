#include "huffmanArchiver.hpp"

tree::HuffmanTreeNode::HuffmanTreeNode(int cnt, HuffmanTreeNode *left, HuffmanTreeNode *right, const char chr, const bool isFinal)
    : chr_(chr), isFinal_(isFinal), left_(left), right_(right), cnt_(cnt)
{
}

tree::HuffmanTreeNode::~HuffmanTreeNode()
{
    delete left_;
    delete right_;
}

char tree::HuffmanTreeNode::getChr() const
{
    return chr_;
}

bool tree::HuffmanTreeNode::isFinal() const
{
    return isFinal_;
}

tree::HuffmanTreeNode *tree::HuffmanTreeNode::getLeft() const
{
    return left_;
}

tree::HuffmanTreeNode *tree::HuffmanTreeNode::getRight() const
{
    return right_;
}
int tree::HuffmanTreeNode::getCnt() const
{
    return cnt_;
}

bool tree::HuffmanTreeNode::operator<(const HuffmanTreeNode &left) const
{
    return cnt_ < left.cnt_;
}

tree::HuffmanTree::HuffmanTree(HuffmanTreeNode *root) : root_(root)
{
    ways_ = std::unordered_map<char, std::pair<std::vector<bool>, int>>();
    std::vector<bool> tmp(256);
    makeObhod(tmp, 0, root_);
}

tree::HuffmanTree::~HuffmanTree()
{
    delete root_;
}

void tree::HuffmanTree::makeObhod(std::vector<bool> &bs, int curDepth, tree::HuffmanTreeNode *curRoot)
{
    if (curRoot->getLeft())
    {
        bs[curDepth] = 0;
        curDepth++;
        makeObhod(bs, curDepth, curRoot->getLeft());
        curDepth--;
    }
    if (curRoot->getRight())
    {
        bs[curDepth] = 1;
        curDepth++;
        makeObhod(bs, curDepth, curRoot->getRight());
        curDepth--;
        bs[curDepth] = 0;
    }

    if (curRoot->isFinal())
        ways_[curRoot->getChr()] = {std::vector<bool>(bs), curDepth};
}

std::pair<std::vector<bool>, int> &tree::HuffmanTree::findRepresentation(char ch)
{
    if (!ways_.count(ch))
        throw new std::runtime_error("no char in tree");
    return ways_[ch];
}

std::pair<tree::HuffmanTreeNode *, std::vector<char>> tree::HuffmanArchiver::CreateTreeFromTxt(const std::string &FPath, std::vector<char> &FoundChar)
{
    std::ifstream file;
    file.open(FPath, std::ios::binary);
    if (!file.is_open())
    {
        throw std::runtime_error("Could not open file: " + FPath);
    }

    file.seekg(0, std::ios::end);
    std::streamsize file_size = file.tellg();
    file.seekg(0, std::ios::beg);

    if (file_size == 0)
        return {nullptr, {}};
    std::vector<char> inpStr;
    inpStr.resize(file_size);
    if (!file.read(reinterpret_cast<char *>(inpStr.data()), file_size))
        throw std::runtime_error("failed to read file " + FPath);

    std::vector<int> freq(256);
    for (std::size_t i = 0; i < inpStr.size(); ++i)
    {
        freq[(unsigned char)(inpStr[i])]++;
    }

    struct comp
    {
        bool operator()(tree::HuffmanTreeNode *a, tree::HuffmanTreeNode *b)
        {
            return a->getCnt() > b->getCnt();
        }
    };

    std::priority_queue<tree::HuffmanTreeNode *, std::vector<tree::HuffmanTreeNode *>, comp> PQueue;

    for (int i = 0; i < int(freq.size()); ++i)
        if (freq[i] != 0)
        {
            FoundChar.push_back(char(i));
            auto newNode = new tree::HuffmanTreeNode(freq[i], nullptr, nullptr, char(i), true);
            PQueue.push(newNode);
        }

    if (PQueue.size() == 1)
    {
        auto f = PQueue.top();
        auto newNode = new tree::HuffmanTreeNode(f->getCnt(), f, nullptr);
        return {newNode, inpStr};
    }
    while (PQueue.size() != 1)
    {
        auto first = PQueue.top();
        PQueue.pop();
        auto second = PQueue.top();
        PQueue.pop();
        auto newNode = new tree::HuffmanTreeNode(first->getCnt() + second->getCnt(), first, second);
        PQueue.push(newNode);
    }
    auto ret = PQueue.top();
    PQueue.pop();
    file.close();
    return {ret, inpStr};
}

void tree::HuffmanArchiver::ParseInputQuery(parser::ParserInfo &parserInfo)
{
    size_t SizeOfExtraMetainfo;
    if (parserInfo.isEncode())
        SizeOfExtraMetainfo = tree::HuffmanArchiver::encodeProxy(parserInfo.getInputFileName(), parserInfo.getOutputFileName());
    else
        SizeOfExtraMetainfo = tree::HuffmanArchiver::decodeProxy(parserInfo.getInputFileName(), parserInfo.getOutputFileName());
    std::uintmax_t inFileSize = std::filesystem::file_size(parserInfo.getInputFileName());
    std::uintmax_t OutputFileSize = std::filesystem::file_size(parserInfo.getOutputFileName());
    if (parserInfo.isEncode())
        std::cout << inFileSize << std::endl
                  << OutputFileSize - SizeOfExtraMetainfo << std::endl
                  << SizeOfExtraMetainfo << std::endl;
    else
        std::cout << inFileSize - SizeOfExtraMetainfo << std::endl
                  << OutputFileSize << std::endl
                  << SizeOfExtraMetainfo << std::endl;
}

void tree::HuffmanArchiver::archive(std::string &OutputFile, HuffmanTree &curTree, const std::vector<char> &possibleChar, const std::vector<char> &whatEncode)
{
    std::ofstream os(OutputFile, std::ios::binary);

    if (!os.is_open())
    {
        throw std::runtime_error("Could not open file: " + OutputFile);
    }
    os.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    int x = possibleChar.size();
    os.write(reinterpret_cast<const char *>(&x), sizeof(int));

    for (size_t i = 0; i < possibleChar.size(); ++i)
    {
        auto tmp = curTree.findRepresentation(possibleChar[i]);
        os.write(&possibleChar[i], sizeof(char));
        os.write(reinterpret_cast<const char *>(&tmp.second), sizeof(int));
        writeToFileWholeBitset(os, tmp.first);
    }
    x = whatEncode.size();
    os.write(reinterpret_cast<const char *>(&x), sizeof(int));
    std::vector<char> writeVecAns = {'\0'};
    int cur_pos_in_byte = 0;
    for (auto chr : whatEncode)
    {
        auto tmpBitsetInfo = curTree.findRepresentation(chr);
        if (tmpBitsetInfo.second == 0)
            tmpBitsetInfo.second = 1;
        for (int i = 0; i < tmpBitsetInfo.second; ++i)
        {
            if (tmpBitsetInfo.first[i])
                writeVecAns[writeVecAns.size() - 1] |= (1 << cur_pos_in_byte);
            cur_pos_in_byte++;
            if (cur_pos_in_byte == 8)
            {
                writeVecAns.push_back('\0');
                cur_pos_in_byte = 0;
            }
        }
    }
    if (cur_pos_in_byte == 0)
        writeVecAns.erase(writeVecAns.end() - 1);
    os.write(writeVecAns.data(), writeVecAns.size());
    os.close();
}

void tree::HuffmanArchiver::writeToFileWholeBitset(std::ofstream &os, std::vector<bool> &bs)
{
    std::vector<char> bytes((bs.size() + 7) / 8, 0);
    for (size_t i = 0; i < bytes.size(); ++i)
        for (size_t j = 0; j < 8; ++j)
            if (i * 8 + j < bs.size() && bs[i * 8 + j])
                bytes[i] |= (1 << j);
    os.write(bytes.data(), bytes.size());
}

size_t tree::HuffmanArchiver::encodeProxy(std::string &inpFileName, std::string &OutFileName)
{
    std::vector<char> foundChar;
    std::pair<tree::HuffmanTreeNode *, std::vector<char>> resultOfCreating = CreateTreeFromTxt(inpFileName, foundChar);
    if (resultOfCreating.first == nullptr)
    {
        std::ofstream outFile(OutFileName);
        if (!outFile)
        {
            throw std::runtime_error("Couldn't create file " + OutFileName);
        }
        int x = 0;
        outFile.write(reinterpret_cast<char *>(&x), sizeof(int));
        return sizeof(int);
    }
    tree::HuffmanTree curTree(resultOfCreating.first);

    archive(OutFileName, curTree, foundChar, resultOfCreating.second);
    return (tree::SizeOfBitset / 8 + sizeof(char) + sizeof(int)) * foundChar.size() + 2 * sizeof(int);
}

size_t tree::HuffmanArchiver::decodeProxy(std::string &inpFileName, std::string &OutFileName)
{
    std::ifstream is;
    is.open(inpFileName, std::ios::binary);
    if (!is.is_open())
    {
        throw std::runtime_error("Could not open file: " + inpFileName);
    }

    is.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    size_t szInpFile = std::filesystem::file_size(inpFileName);

    std::unordered_map<std::string, char> possibleCharMap;
    int possibleCharSize;

    is.read(reinterpret_cast<char *>(&possibleCharSize), sizeof(int));
    if (possibleCharSize < 0)
        throw std::runtime_error("Invalid file format: " + OutFileName);
    if (possibleCharSize == 0 || szInpFile == 4)
    {
        std::ofstream outFile(OutFileName);
        if (!outFile)
        {
            throw std::runtime_error("Couldn't create file " + OutFileName);
        }
        return sizeof(int);
    }
    for (int i = 0; i < possibleCharSize; ++i)
    {
        char curChar;
        int curTmpSz;

        is.read(reinterpret_cast<char *>(&curChar), sizeof(char));

        is.read(reinterpret_cast<char *>(&curTmpSz), sizeof(int));
        std::vector<char> tmpVecForRead(tree::SizeOfBitset / 8);

        is.read(&tmpVecForRead[0], tmpVecForRead.size());
        std::string boolVector;
        boolVector.resize(tree::SizeOfBitset, 2);
        for (size_t i = 0; i < tmpVecForRead.size(); ++i)
            for (size_t j = 0; j < 8; ++j)
            {
                if (j + i * 8 >= (size_t)curTmpSz)
                    continue;
                else if (tmpVecForRead[i] & (1 << j))
                    boolVector[i * 8 + j] = 1;
                else
                    boolVector[i * 8 + j] = 0;
            }
        possibleCharMap[boolVector] = curChar;
    }
    int cntOfChr;
    is.read(reinterpret_cast<char *>(&cntOfChr), sizeof(int));
    int curPosInFile = is.tellg();
    is.seekg(0, std::ios::end);
    int sz = int(is.tellg()) - curPosInFile;
    is.seekg(curPosInFile);
    std::vector<char> whatDecode(sz);

    is.read(&whatDecode[0], sz);

    std::vector<char> ans;

    int curCntOfChr = 0;
    std::string tmpBoolVec;
    tmpBoolVec.resize(tree::SizeOfBitset, 2);
    int curPosInStr = 0;
    for (size_t i = 0; i < whatDecode.size() && curCntOfChr < cntOfChr; ++i)
        for (int j = 0; j < 8 && curCntOfChr < cntOfChr; ++j)
        {
            if (whatDecode[i] & (1 << j))
                tmpBoolVec[curPosInStr] = 1;
            else
                tmpBoolVec[curPosInStr] = 0;
            curPosInStr++;
            if (possibleCharMap.count(tmpBoolVec))
            {
                ans.push_back(possibleCharMap[tmpBoolVec]);
                tmpBoolVec.clear();
                tmpBoolVec.resize(tree::SizeOfBitset, 2);
                curCntOfChr++;
                curPosInStr = 0;
            }
        }
    if (curCntOfChr != cntOfChr)
        throw std::runtime_error("incorrect file format: " + inpFileName);
    std::ofstream os;
    os.open(OutFileName, std::ios::binary);
    if (!os.is_open())
    {
        throw std::runtime_error("Could not open file: " + OutFileName);
    }
    os.write(ans.data(), ans.size());
    is.close();
    os.close();
    return (tree::SizeOfBitset / 8 + sizeof(char) + sizeof(int)) * possibleCharSize + 2 * sizeof(int);
}