// Replace.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int main(int argc, char * argv[])
{
	if (argc != 5)
	{
		std::cout << "Invalid argument count\n"
			<< "Usage: replace.exe <inputFile> <outputFile> <searchString> <replacementString>\n";
		return 1;
	}
    return 0;
}

