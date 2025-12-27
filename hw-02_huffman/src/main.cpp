#include "huffmanArchiver.hpp"
#include <iostream>
#include "InputParser.hpp"

int main(int argc, char **argv)
{
    try
    {
        parser::ParserInfo parseInfo = parser::ParserInfo::ParseInputQuery(argc, argv);
        tree::HuffmanArchiver::ParseInputQuery(parseInfo);
    }
    catch (const std::ifstream::failure &e)
    {
        std::cerr << "File reading error: " << e.what() << std::endl;
    }
    catch (const std::runtime_error &e)
    {
        std::cout << "Runtime error: " << e.what() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
}
