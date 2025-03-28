﻿#include "PngFileHeader.h"
#include <cassert>
#include <cstdint>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <numbers>
#include <sstream>
#include <string>
#include <winsock.h>

using namespace std;

// Пример функции, использующей работу с двоичными файлами для чтения информации о PNG-изображении (PngFileHeader.h)
bool GetPngFileInfo(const wstring& fileName, PNGInfo& pngInfo);

void StandardIO()
{
	int number;

	// Читаем число из потока в number
	std::cin >> number;
	// Выводим число из number в поток вывода
	std::cout << number << std::endl;
	// Выводим число из number в поток ошибок
	std::cerr << number << std::endl;

	if (!(std::cin >> number))
	{
		// При чтении числа произошла ошибка
	}
}

void ReadStrings()
{
	std::string phrase;
	std::getline(std::cin, phrase); // Прочитать строку до символа конца строки
	std::cout << phrase << std::endl;

	std::string name, surname;
	std::cin >> name >> surname; // Прочитать name и surname, разделённые пробелами
	std::cout << name << ' ' << surname;
}

#include <iomanip>

void IOManip()
{
	int number;
	std::cin >> std::hex >> number; // Считываем число в hex-формате
	std::cout << number
			  << std::hex << " " << number << " "
			  << std::oct << number << " "
			  << std::dec << number << std::endl;

	auto defaultPrecision = std::cout.precision();
	std::cout << std::numbers::pi << " "
			  << std::setprecision(15) << std::numbers::pi << " "
			  << std::setprecision(3) << std::numbers::pi << " "
			  << std::setprecision(defaultPrecision) << std::numbers::pi << std::endl;
}

int main()
{
	IOManip();
	return 0;

	// Запись текстового файла
	{
		// Открываем файл text.txt для записи
		ofstream outputFile("text.txt");
		if (outputFile.is_open())
		{
			outputFile << "Hello, world: " << 10 << " " << 42 << endl; // Форматированный вывод
			outputFile.put('!'); // вывод одиночного символа
			// Вызов flush() выполняет запись буферизированных данных из памяти в файл
			outputFile.flush();

			// Лаконичный способ проверить поток на состояние ошибки
			if (!outputFile)
			{
				cout << "An error occurred when writing outputFile" << endl;
			}
		}
		else
		{
			cout << "Failed to open text.txt for writing" << endl;
		}
	}

	// Чтение текстового файла
	{
		// Создаем поток для чтения, связанный с только что записанным файлом text.txt
		ifstream inputFile("text.txt");
		if (inputFile.is_open())
		{
			string line1;
			if (!getline(inputFile, line1))
			{
				cout << "Failed to read a line from file" << endl;
				return 1;
			}

			assert(line1 == "Hello, world: 10 42");
		}
		else
		{
			cout << "Failed to open text.txt for reading" << endl;
		}
	}

	// Извлечение информации из двоичного файла формата PNG
	{
		PNGInfo pngInfo;
		if (GetPngFileInfo(L"test.png", pngInfo))
		{
			auto& hdr = pngInfo.imageHeader;
			cout << "test.png file size is " << hdr.width << "x" << hdr.height << "pixels" << endl;
		}
		else
		{
			cout << "test.png is not a valid PNG image" << endl;
		}
	}

	// Работа с со строковыми потоками
	{
		// Запись
		{
			ostringstream strm;
			strm << "Hello, " << 42;

			assert(strm.str() == "Hello, 42");
		}

		// Чтение
		{
			istringstream strm("Hello world 42");
			string hello;
			string world;
			int answerToTheUltimateQuestionOfLifeTheUniverseAndEverything;
			strm >> hello >> world >> answerToTheUltimateQuestionOfLifeTheUniverseAndEverything;
			assert(hello == "Hello");
			assert(world == "world");
			assert(answerToTheUltimateQuestionOfLifeTheUniverseAndEverything == 42);
		}

		// Чтение и запись
		{
			stringstream strm;
			strm << "Hello! How are you?";
			string hello, how, are, you;
			strm >> hello >> how >> are >> you;
			assert(hello == "Hello!");
			assert(how == "How");
			assert(are == "are");
			assert(you == "you?");
		}
	}
}

bool GetPngFileInfo(const wstring& fileName, PNGInfo& pngInfo)
{
	ifstream pngFile(fileName, ios_base::binary | ios_base::in);
	if (!pngFile.is_open())
	{
		return false;
	}

	if (!pngFile.read(reinterpret_cast<char*>(&pngInfo), sizeof(pngInfo)))
	{
		// Возникла ошибка при чтении начала PNG-файла
		return false;
	}

	if (memcmp(pngInfo.pngSignature, PNG_SIGNATURE, sizeof(PNG_SIGNATURE)) != 0)
	{
		// Сигнатура в начале файла не соответствует спецификации PNG
		return false;
	}

	auto& hdr = pngInfo.imageHeader;

	// В PNG используется сетевой порядок байт (big-endian) для представления чисел размером больше 1 байта,
	// нужно преобразовать его в формат, используемых на данном компьютере
	// Для этого воспользуемся функцией ntohl (network to host (long))
	hdr.chunkSize = ntohl(hdr.chunkSize);
	if (hdr.chunkSize != (sizeof(IHDRChunk) - sizeof(ChunkHeader)))
	{
		// Длина блока данных не соответствует спецификации блока IHDR
		return false;
	}

	// Первым блоком в PNG файле должен идти блок IHDR
	if (memcmp(hdr.signature, IHDR_SIGNATURE, sizeof(IHDR_SIGNATURE)) != 0)
	{
		return false;
	}

	// Преобразуем формат байт ширины и высоты из сетевого представления в используемый на компьютере
	hdr.width = ntohl(hdr.width);
	hdr.height = ntohl(hdr.height);

	if (hdr.width == 0 || hdr.height == 0)
	{
		// Ни ширина, ни высота PNG-изображения не могут быть равны нулю
		return false;
	}

	return true;
}
