#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.hpp"
#include "huffmanArchiver.hpp"
#include "InputParser.hpp"
#include <sstream>
#include <random>

bool areFilesEqual(const std::string &path1, const std::string &path2)
{
    std::ifstream file1(path1, std::ios::binary);
    std::ifstream file2(path2, std::ios::binary);

    if (!file1 || !file2)
        return false;

    file1.seekg(0, std::ios::end);
    file2.seekg(0, std::ios::end);
    if (file1.tellg() != file2.tellg())
        return false;

    file1.seekg(0);
    file2.seekg(0);

    return std::equal(
        std::istreambuf_iterator<char>(file1),
        std::istreambuf_iterator<char>(),
        std::istreambuf_iterator<char>(file2));
}

TEST_CASE("ParseInputQuery - valid arguments")
{
    SUBCASE("Encoding with short options")
    {
        char *argv[] = {
            (char *)"-c",
            (char *)"-f",
            (char *)"input.txt",
            (char *)"-o",
            (char *)"output.txt"};
        int argc = sizeof(argv) / sizeof(argv[0]);

        auto info = parser::ParserInfo::ParseInputQuery(argc, argv);
        CHECK(info.isEncode() == true);
        CHECK(info.getInputFileName() == "input.txt");
        CHECK(info.getOutputFileName() == "output.txt");
    }

    SUBCASE("Decoding with short options")
    {
        char *argv[] = {
            (char *)"-u",
            (char *)"-f",
            (char *)"input.txt",
            (char *)"-o",
            (char *)"output.txt"};
        int argc = sizeof(argv) / sizeof(argv[0]);

        auto info = parser::ParserInfo::ParseInputQuery(argc, argv);
        CHECK(info.isEncode() == false);
        CHECK(info.getInputFileName() == "input.txt");
        CHECK(info.getOutputFileName() == "output.txt");
    }

    SUBCASE("Encoding with long options")
    {
        char *argv[] = {
            (char *)"-c",
            (char *)"--file",
            (char *)"input.txt",
            (char *)"--output",
            (char *)"output.txt"};
        int argc = sizeof(argv) / sizeof(argv[0]);

        auto info = parser::ParserInfo::ParseInputQuery(argc, argv);
        CHECK(info.isEncode() == true);
        CHECK(info.getInputFileName() == "input.txt");
        CHECK(info.getOutputFileName() == "output.txt");
    }

    SUBCASE("Options in different order")
    {
        char *argv[] = {
            (char *)"-f",
            (char *)"input.txt",
            (char *)"-o",
            (char *)"output.txt",
            (char *)"-c"};
        int argc = sizeof(argv) / sizeof(argv[0]);

        auto info = parser::ParserInfo::ParseInputQuery(argc, argv);
        CHECK(info.isEncode() == true);
        CHECK(info.getInputFileName() == "input.txt");
        CHECK(info.getOutputFileName() == "output.txt");
    }
}

TEST_CASE("ParseInputQuery - invalid arguments")
{
    SUBCASE("Missing mode flag")
    {
        char *argv[] = {
            (char *)"-f",
            (char *)"input.txt",
            (char *)"-o",
            (char *)"output.txt"};
        int argc = sizeof(argv) / sizeof(argv[0]);

        CHECK_THROWS_AS(parser::ParserInfo::ParseInputQuery(argc, argv), std::runtime_error);
    }

    SUBCASE("Both -c and -u flags")
    {
        char *argv[] = {
            (char *)"-c",
            (char *)"-u",
            (char *)"-f",
            (char *)"input.txt",
            (char *)"-o",
            (char *)"output.txt"};
        int argc = sizeof(argv) / sizeof(argv[0]);

        CHECK_THROWS_AS(parser::ParserInfo::ParseInputQuery(argc, argv), std::runtime_error);
    }

    SUBCASE("Missing input file")
    {
        char *argv[] = {
            (char *)"-c",
            (char *)"-o",
            (char *)"output.txt"};
        int argc = sizeof(argv) / sizeof(argv[0]);

        CHECK_THROWS_AS(parser::ParserInfo::ParseInputQuery(argc, argv), std::runtime_error);
    }

    SUBCASE("Missing output file")
    {
        char *argv[] = {
            (char *)"-c",
            (char *)"-f",
            (char *)"input.txt"};
        int argc = sizeof(argv) / sizeof(argv[0]);

        CHECK_THROWS_AS(parser::ParserInfo::ParseInputQuery(argc, argv), std::runtime_error);
    }
}

TEST_CASE("ParserInfo getters")
{
    char *argv[] = {
        (char *)"-c",
        (char *)"-f",
        (char *)"test_input.txt",
        (char *)"-o",
        (char *)"test_output.txt"};
    int argc = sizeof(argv) / sizeof(argv[0]);

    auto info = parser::ParserInfo::ParseInputQuery(argc, argv);

    SUBCASE("Input file name")
    {
        CHECK(info.getInputFileName() == "test_input.txt");

        info.getInputFileName()[0] = 'T';
        CHECK(info.getInputFileName() == "Test_input.txt");
    }

    SUBCASE("Output file name")
    {
        CHECK(info.getOutputFileName() == "test_output.txt");

        info.getOutputFileName()[0] = 'T';
        CHECK(info.getOutputFileName() == "Test_output.txt");
    }

    SUBCASE("Encode flag")
    {
        CHECK(info.isEncode() == true);
    }
}

TEST_CASE("decode-encode test1-empty")
{
    std::string inpFileName = "../samples/test-1-empty";
    std::string encodedFileName = "../samples/tests-result/Encode/test-1-empty";
    std::string decodedFileName = "../samples/tests-result/Decode/test-1-empty";

    char *argvEncoded[] = {
        (char *)"-c",
        (char *)"-f",
        inpFileName.data(),
        (char *)"-o",
        encodedFileName.data()};

    char *argvDecoded[] = {
        (char *)"-u",
        (char *)"-f",
        encodedFileName.data(),
        (char *)"-o",
        decodedFileName.data()};
    parser::ParserInfo parserInfoEncoded = parser::ParserInfo::ParseInputQuery(sizeof(argvEncoded) / sizeof(argvEncoded[0]), argvEncoded);
    parser::ParserInfo parserInfoDecoded = parser::ParserInfo::ParseInputQuery(sizeof(argvDecoded) / sizeof(argvDecoded[0]), argvDecoded);
    tree::HuffmanArchiver::ParseInputQuery(parserInfoEncoded);
    tree::HuffmanArchiver::ParseInputQuery(parserInfoDecoded);
    CHECK(areFilesEqual(inpFileName, decodedFileName));
}

TEST_CASE("decode-encode test-2-all_chars.txt")
{
    std::string inpFileName = "../samples/test-2-all_chars.txt";
    std::string encodedFileName = "../samples/tests-result/Encode/test-2-all_chars.txt";
    std::string decodedFileName = "../samples/tests-result/Decode/test-2-all_chars.txt";

    char *argvEncoded[] = {
        (char *)"-c",
        (char *)"-f",
        inpFileName.data(),
        (char *)"-o",
        encodedFileName.data()};

    char *argvDecoded[] = {
        (char *)"-u",
        (char *)"-f",
        encodedFileName.data(),
        (char *)"-o",
        decodedFileName.data()};
    parser::ParserInfo parserInfoEncoded = parser::ParserInfo::ParseInputQuery(sizeof(argvEncoded) / sizeof(argvEncoded[0]), argvEncoded);
    parser::ParserInfo parserInfoDecoded = parser::ParserInfo::ParseInputQuery(sizeof(argvDecoded) / sizeof(argvDecoded[0]), argvDecoded);
    tree::HuffmanArchiver::ParseInputQuery(parserInfoEncoded);
    tree::HuffmanArchiver::ParseInputQuery(parserInfoDecoded);
    CHECK(areFilesEqual(inpFileName, decodedFileName));
}

TEST_CASE("decode-encode test-4-book.txt")
{
    std::string inpFileName = "../samples/test-4-book.txt";
    std::string encodedFileName = "../samples/tests-result/Encode/test-4-book.txt";
    std::string decodedFileName = "../samples/tests-result/Decode/test-4-book.txt";

    char *argvEncoded[] = {
        (char *)"-c",
        (char *)"-f",
        inpFileName.data(),
        (char *)"-o",
        encodedFileName.data()};

    char *argvDecoded[] = {
        (char *)"-u",
        (char *)"-f",
        encodedFileName.data(),
        (char *)"-o",
        decodedFileName.data()};
    parser::ParserInfo parserInfoEncoded = parser::ParserInfo::ParseInputQuery(sizeof(argvEncoded) / sizeof(argvEncoded[0]), argvEncoded);
    parser::ParserInfo parserInfoDecoded = parser::ParserInfo::ParseInputQuery(sizeof(argvDecoded) / sizeof(argvDecoded[0]), argvDecoded);
    tree::HuffmanArchiver::ParseInputQuery(parserInfoEncoded);
    tree::HuffmanArchiver::ParseInputQuery(parserInfoDecoded);
    CHECK(areFilesEqual(inpFileName, decodedFileName));
}

TEST_CASE("decode-encode test-3-random_chars.bin")
{
    std::string inpFileName = "../samples/test-3-random_chars.bin";
    std::string encodedFileName = "../samples/tests-result/Encode/test-3-random_chars.bin";
    std::string decodedFileName = "../samples/tests-result/Decode/test-3-random_chars.bin";

    char *argvEncoded[] = {
        (char *)"-c",
        (char *)"-f",
        inpFileName.data(),
        (char *)"-o",
        encodedFileName.data()};

    char *argvDecoded[] = {
        (char *)"-u",
        (char *)"-f",
        encodedFileName.data(),
        (char *)"-o",
        decodedFileName.data()};
    parser::ParserInfo parserInfoEncoded = parser::ParserInfo::ParseInputQuery(sizeof(argvEncoded) / sizeof(argvEncoded[0]), argvEncoded);
    parser::ParserInfo parserInfoDecoded = parser::ParserInfo::ParseInputQuery(sizeof(argvDecoded) / sizeof(argvDecoded[0]), argvDecoded);
    tree::HuffmanArchiver::ParseInputQuery(parserInfoEncoded);
    tree::HuffmanArchiver::ParseInputQuery(parserInfoDecoded);
    CHECK(areFilesEqual(inpFileName, decodedFileName));
}

TEST_CASE("incorrect Encoded File test-1-empty")
{
    std::string inpFileName = "../samples/test-1-empty-wrongEncoded";
    std::string outFileName = "../samples/tests-result/WrongEncodeDecoded/test-1-empty-wrongEncoded";
    CHECK_THROWS(tree::HuffmanArchiver::decodeProxy(inpFileName, outFileName));
}

TEST_CASE("incorrect Encoded File test-2-all_chars")
{
    std::string inpFileName = "../samples/test-2-all_chars-WrongEncoded.txt";
    std::string outFileName = "../samples/tests-result/WrongEncodeDecoded/test-2-all_chars-WrongEncoded.txt";
    CHECK_THROWS(tree::HuffmanArchiver::decodeProxy(inpFileName, outFileName));
}

TEST_CASE("incorrect Encoded File test-3-random")
{
    std::string inpFileName = "../samples/test-3-random_chars-wrongEncoded.bin";
    std::string outFileName = "../samples/tests-result/WrongEncodeDecoded/test-3-random_chars-wrongEncoded.bin";
    CHECK_THROWS(tree::HuffmanArchiver::decodeProxy(inpFileName, outFileName));
}

TEST_CASE("incorrect Encoded File test-4-book")
{
    std::string inpFileName = "../samples/test-4-book-WrongEncoded.txt";
    std::string outFileName = "../samples/tests-result/WrongEncodeDecoded/test-4-book-WrongEncoded.txt";
    CHECK_THROWS(tree::HuffmanArchiver::decodeProxy(inpFileName, outFileName));
}

TEST_CASE("incorrect Encoded File test-5-oneChar")
{
    std::string inpFileName = "../samples/test-5-oneChar";
    std::string outFileName = "../samples/tests-result/WrongEncodeDecoded/test-5-oneChar";
    CHECK_THROWS(tree::HuffmanArchiver::decodeProxy(inpFileName, outFileName));
}

TEST_CASE("HuffmanTreeNode constructor and getters")
{
    tree::HuffmanTreeNode node(10, nullptr, nullptr, 'a', true);
    CHECK(node.getCnt() == 10);
    CHECK(node.getChr() == 'a');
    CHECK(node.isFinal() == true);
    CHECK(node.getLeft() == nullptr);
    CHECK(node.getRight() == nullptr);
}

TEST_CASE("HuffmanTreeNode operator<")
{
    tree::HuffmanTreeNode node1(5, nullptr, nullptr, 'a', true);
    tree::HuffmanTreeNode node2(10, nullptr, nullptr, 'b', true);
    CHECK(node1 < node2);
    CHECK(!(node2 < node1));
}

TEST_CASE("HuffmanTree construction and traversal")
{
    auto *left = new tree::HuffmanTreeNode(5, nullptr, nullptr, 'a', true);
    auto *right = new tree::HuffmanTreeNode(10, nullptr, nullptr, 'b', true);
    auto *root = new tree::HuffmanTreeNode(15, left, right);
    tree::HuffmanTree tree(root);

    SUBCASE("Check root node")
    {
        CHECK(tree.findRepresentation('a').second == 1);
        CHECK(tree.findRepresentation('b').second == 1);
    }

    SUBCASE("Check non-existent character")
    {
        CHECK_THROWS_AS(tree.findRepresentation('c'), std::runtime_error *);
    }
}

TEST_CASE("HuffmanArchiver::CreateTreeFromTxt with empty file")
{
    std::string filename = "../samples/test-empty.txt";
    {
        std::ofstream out(filename);
    }
    std::vector<char> foundChars;
    auto result = tree::HuffmanArchiver::CreateTreeFromTxt(filename, foundChars);
    CHECK(result.first == nullptr);
    CHECK(foundChars.empty());
    std::filesystem::remove(filename);
}

TEST_CASE("HuffmanArchiver::CreateTreeFromTxt with single character")
{
    std::string filename = "../samples/test-single-char.txt";
    {
        std::ofstream out(filename);
        out << 'a';
    }
    std::vector<char> foundChars;
    auto result = tree::HuffmanArchiver::CreateTreeFromTxt(filename, foundChars);
    CHECK(result.first != nullptr);
    CHECK(foundChars.size() == 1);
    CHECK(foundChars[0] == 'a');
    CHECK(result.first->getCnt() == 1);
    std::filesystem::remove(filename);
}

TEST_CASE("HuffmanArchiver::archive and decode with random data")
{
    std::string original = "../samples/test-random-data.bin";
    std::string encoded = "../samples/tests-result/Encode/test-random-encoded.bin";
    std::string decoded = "../samples/tests-result/Decode/test-random-decoded.bin";

    {
        std::ofstream out(original, std::ios::binary);
        std::mt19937 gen(42);
        std::uniform_int_distribution<> dis(0, 255);
        for (int i = 0; i < 1000; ++i)
        {
            char c = static_cast<char>(dis(gen));
            out.write(&c, 1);
        }
    }

    tree::HuffmanArchiver::encodeProxy(original, encoded);
    tree::HuffmanArchiver::decodeProxy(encoded, decoded);

    std::ifstream origFile(original, std::ios::binary);
    std::ifstream decFile(decoded, std::ios::binary);
    CHECK(std::equal(
        std::istreambuf_iterator<char>(origFile),
        std::istreambuf_iterator<char>(),
        std::istreambuf_iterator<char>(decFile)));

    std::filesystem::remove(original);
    std::filesystem::remove(encoded);
    std::filesystem::remove(decoded);
}

TEST_CASE("HuffmanArchiver::writeToFileWholeBitset")
{
    std::string filename = "../samples/test-bitset.bin";
    std::vector<bool> bits = {1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1};
    {
        std::ofstream out(filename, std::ios::binary);
        tree::HuffmanArchiver::writeToFileWholeBitset(out, bits);
    }

    std::ifstream in(filename, std::ios::binary);
    char byte1, byte2;
    in.read(&byte1, 1);
    in.read(&byte2, 1);
    CHECK(byte1 == static_cast<char>(0b00101101));
    CHECK(byte2 == static_cast<char>(0b00000111));
    std::filesystem::remove(filename);
}

TEST_CASE("HuffmanArchiver error handling")
{
    SUBCASE("Non-existent input file for encoding")
    {
        std::string nonExistent = "../samples/non-existent.txt";
        std::string outFile = "../samples/tests-result/Encode/out.bin";
        CHECK_THROWS_AS(tree::HuffmanArchiver::encodeProxy(nonExistent, outFile), std::runtime_error);
    }

    SUBCASE("Non-existent input file for decoding")
    {
        std::string nonExistent = "../samples/non-existent.bin";
        std::string outFile = "../samples/out.txt";
        CHECK_THROWS_AS(tree::HuffmanArchiver::decodeProxy(nonExistent, outFile), std::runtime_error);
    }

    SUBCASE("Invalid encoded file format")
    {
        std::string bad_file = "../samples/test-bad-format.bin";
        {
            std::ofstream out(bad_file, std::ios::binary);
            int x = -1;
            out.write(reinterpret_cast<const char *>(&x), sizeof(int));
        }
        std::string outFile = "../samples/out.txt";
        CHECK_THROWS_AS(tree::HuffmanArchiver::decodeProxy(bad_file, outFile), std::runtime_error);
        std::filesystem::remove(bad_file);
    }
}

TEST_CASE("HuffmanArchiver edge cases")
{
    SUBCASE("Single repeated character")
    {
        std::string filename = "../samples/test-single-repeated.txt";
        std::string encoded = "../samples/tests-result/Encode/test-single-encoded.bin";
        std::string decoded = "../samples/tests-result/Decode/test-single-decoded.txt";

        {
            std::ofstream out(filename);
            for (int i = 0; i < 100; ++i)
                out << 'x';
        }

        tree::HuffmanArchiver::encodeProxy(filename, encoded);
        tree::HuffmanArchiver::decodeProxy(encoded, decoded);

        std::ifstream orig(filename);
        std::ifstream dec(decoded);
        CHECK(std::equal(
            std::istreambuf_iterator<char>(orig),
            std::istreambuf_iterator<char>(),
            std::istreambuf_iterator<char>(dec)));

        std::filesystem::remove(filename);
        std::filesystem::remove(encoded);
        std::filesystem::remove(decoded);
    }

    SUBCASE("All possible characters")
    {
        std::string filename = "../samples/test-all-chars.bin";
        std::string encoded = "../samples/tests-result/Encode/test-all-encoded.bin";
        std::string decoded = "../samples/tests-result/Decode/test-all-decoded.bin";

        {
            std::ofstream out(filename, std::ios::binary);
            for (int i = 0; i < 256; ++i)
            {
                char c = static_cast<char>(i);
                out.write(&c, 1);
            }
        }

        tree::HuffmanArchiver::encodeProxy(filename, encoded);
        tree::HuffmanArchiver::decodeProxy(encoded, decoded);

        std::ifstream orig(filename, std::ios::binary);
        std::ifstream dec(decoded, std::ios::binary);
        CHECK(std::equal(
            std::istreambuf_iterator<char>(orig),
            std::istreambuf_iterator<char>(),
            std::istreambuf_iterator<char>(dec)));

        std::filesystem::remove(filename);
        std::filesystem::remove(encoded);
        std::filesystem::remove(decoded);
    }
}

int main(int argc, char **argv)
{
    doctest::Context context;
    context.applyCommandLine(argc, argv);
    return context.run();
}