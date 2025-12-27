#include "employees.h"
#include <iostream>
#include <string>
#include <fstream>

int main()
{
	std::cin.exceptions(std::ios_base::eofbit | std::ios_base::failbit | std::ios_base::badbit | std::ios_base::goodbit);
	employees::EmployeesArray arr;
	std::string command;
	while (true)
	{
		try
		{
			std::cin >> command;
			if (command == "exit")
				return 0;

			else if (command == "add")
			{
				int32_t type = 0;
				std::cin >> type;
				if (type == 1)
				{
					employees::Developer *e = new employees::Developer();
					std::cin >> Manip::nobin >> *e;
					arr.add(e);
				}
				else if (type == 2)
				{
					employees::SalesManager *e = new employees::SalesManager();
					std::cin >> Manip::nobin >> *e;
					arr.add(e);
				}
			}

			else if (command == "list")
				std::cout << Manip::nobin << arr;

			else if (command == "save")
			{
				std::string path;
				std::cin >> path;
				std::ofstream os;
				os.exceptions(std::ios_base::eofbit | std::ios_base::failbit | std::ios_base::badbit | std::ios_base::goodbit);
				try
				{
					os.open(path);
					os << Manip::bin << arr;
				}
				catch (std::exception *e)
				{
					std::cerr << "exception with output stream working";
					return 0;
				}
			}
			else if (command == "load")
			{
				std::string path;
				std::cin >> path;
				std::ifstream is;
				is.exceptions(std::ios_base::eofbit | std::ios_base::failbit | std::ios_base::badbit | std::ios_base::goodbit);
				try
				{
					is.open(path);
					is >> Manip::bin >> arr;
				}
				catch (std::exception *e)
				{
					std::cerr << "exception with input stream working";
					return 0;
				}
			}
		}
		catch (std::exception *e)
		{
			std::cerr << "exception with stream working";
			return 0;
		}
	}
	return 0;
}
