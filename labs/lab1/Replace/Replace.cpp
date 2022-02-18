#include "stdafx.h"

std::string ReplaceString(const std::string& subject,
	const std::string& searchString, const std::string& replacementString)
{
	size_t pos = 0;
	// Результат будет записан в новую строку result, оставляя строку subject неизменной
	// Какие преимущества есть у этого способа по сравнению с алгоритмом, выполняющим
	// замену прямо в строке subject?
	std::string result;
	while (pos < subject.length())
	{
		// Находим позицию искомой строки, начиная с pos
		size_t foundPos = subject.find(searchString, pos);
		// В результирующую строку записываем текст из диапазона [pos,foundPos)
		result.append(subject, pos, foundPos - pos);

		// Напишите недостающий код самостоятельно, чтобы функция работала корректно
	}
	return result;
}

void CopyFileWithReplace(std::istream& input, std::ostream& output,
	const std::string& searchString, const std::string& replacementString)
{
	std::string line;

	while (std::getline(input, line))
	{
		output << ReplaceString(line, searchString, replacementString) << "\n";
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
