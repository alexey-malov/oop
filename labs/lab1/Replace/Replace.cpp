// Replace.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

void CopyFileWithReplace(std::istream& input, std::ostream& output,
	const std::string& searchString, const std::string& replacementString)
{
	std::string line;

	while (std::getline(input, line))
	{
		output << line << "\n";
	}
}

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

	CopyFileWithReplace(inputFile, outputFile, search, replace);
	outputFile.flush();

	return 0;
}
