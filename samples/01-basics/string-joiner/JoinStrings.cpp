// JoinStrings.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

int main(int argc, char* argv[])
{
	if (argc >= 2)
	{
		for (int i = 1; i < argc; ++i)
		{
			std::cout << argv[i];
		}

		std::cout << std::endl;
	}
	return 0;
}
