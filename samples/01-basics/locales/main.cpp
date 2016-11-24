#include <iostream>
#include <string>
#include <windows.h>
#include <corecrt_io.h>
#include <fcntl.h>


using namespace std;

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	{
		string name;
		cout << "Введите свое имя> ";
		getline(cin, name);
		cout << "Привет, " << name << endl;
	}

	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);
	{
		wstring name;
		wcout << L"Введите свое имя> ";
		getline(wcin, name);
		wcout << L"Привет, " << name << endl;

	}
	return 0;
}