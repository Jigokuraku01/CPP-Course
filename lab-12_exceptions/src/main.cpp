#include <matrix.h>

int main()
{

    std::string curZapros;
    matrixNamespace::MatrixHolder curHandler;
    bool f = true;
    while (f)
    {
        try
        {
            std::cin >> curZapros;
            if (curZapros == "exit")
                f = false;
            if (curZapros == "load")
                curHandler.load(std::cin, std::cout);
            else if (curZapros == "add")
                curHandler.add(std::cin, std::cout);
            else if (curZapros == "mul")
                curHandler.mul(std::cin, std::cout);
            else if (curZapros == "print")
                curHandler.print(std::cin, std::cout);
            else if (curZapros == "elem")
                curHandler.elem(std::cin, std::cout);
        }
        catch (std::bad_alloc &)
        {
            std::cout << "Unable to allocate memory." << std::endl;
        }
    }
}
