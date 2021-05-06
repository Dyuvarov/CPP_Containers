#include <iostream>
#include <fstream>
#include "../../includes/list.hpp"
#include "TestUtils.hpp"



void compareFiles(std::string std, std::string ft)
{
	std::ifstream stdFile(std);
	std::ifstream ftFile(ft);
	std::string stdLine;
	std::string ftLine;
	int i = 1;

	if (!stdFile.is_open() || !ftFile.is_open())
		throw std::runtime_error("cant read from file!\n");
	while (getline(stdFile, stdLine))
	{
		getline(ftFile, ftLine);
		if (stdLine != ftLine)
		{
			std::cout << "\x1b[1;31m [FAIL] difference in line: " << i << "\x1b[0m" << std::endl;
			exit(1);
		}
		i++;
	}
	std::cout << "\x1b[1;32m [OK] \x1b[0m";
	std::remove(std.c_str());
	std::remove(ft.c_str());
}