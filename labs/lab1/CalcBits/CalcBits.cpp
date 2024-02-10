/*
–азработайте приложение calcbits.exe, выполн€ющее подсчет и вывод в output количества единичных битов
в байте. ƒл€ подсчета единичных битов используйте операции манипулировани€ битами.
‘ормат командной строки:

calcbits.exe <byte>
где byte Ц число в дес€тичное системе, в двоичном представлении которого должен производитьс€ подсчет
установленных в единицу бит.

Ќапример, вызов

calcbits.exe 5
должен выводить в output значение 2 (число 5 в двоичной системе равно 00000101).

¬ случае некорректных входных данных программа должна выводить пользователю сообщение об ошибке
и возвращать ненулевое значение.

*/
#include <cassert>
#include <iostream>
#include <limits>
#include <string>

int main(int argc, char* argv[])
{
	std::cout << argv[0] << std::endl;
	if (argc != 2)
	{
		std::cout << "Usage: calcbits.exe <byte>" << std::endl;

		return EXIT_SUCCESS;
	}

	assert(argc == 2);
	std::cout << argv[1] << std::endl;

	try
	{
		int byte = std::stoi(argv[1]);
		std::cout << byte << std::endl;
		if (byte < 0 || byte > std::numeric_limits<uint8_t>::max())
		{
			std::cout << "Argument is out of range" << std::endl;
			return EXIT_FAILURE;
		}

		/* ƒопишите программу самосто€тельно */
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return EXIT_FAILURE;
	}
}
