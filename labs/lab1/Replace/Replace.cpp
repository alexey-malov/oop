// Replace.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int main(int argc, char* argv[])
{
	if (argc != 5)
	{
		std::cout << "Invalid argument count\n"
				  << "Usage: replace.exe <inputFile> <outputFile> <searchString> <replacementString>\n";
		return 1;
	}

	std::ifstream inputFile;
	inputFile.open(argv[1]);

	std::ofstream outputFile;
	outputFile.open(argv[2]);

	std::string search = argv[3];
	std::string replace = argv[4];

	std::string line;

	while (std::getline(inputFile, line))
	{
		outputFile << line << "\n";
	}
	outputFile.flush();

	return 0;
}
