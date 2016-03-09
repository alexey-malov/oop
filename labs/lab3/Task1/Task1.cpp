// Task1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "RemoteControl.h"
#include "TVSet.h"


using namespace std;

void main()
{
	CTVSet tv;
	CRemoteControl remoteControl(tv, cin, cout);

	while (!cin.eof() && ! cin.fail())
	{
		cout << "> ";
		if (!remoteControl.HandleCommand())
		{
			cout << "Unknown command!" << endl;
		}
	}
}

