#include <fstream>
#include <iostream>
#include <vector>

//using namespace std;

#if 0
int main(int argc, char* argv[]) {
	if (argc != 3) { // Указаны ли верно параметры командной строки?
		std::cout << "Invalid arguments count\n"
			 << "Usage: copyfile.exe <input file> <output file>\n";
		return 1;
	}
	std::ifstream input(argv[1]);
	if (!input.is_open()) { // Удалось ли открыть входной файл?
		std::cout << "Failed to open " << argv[1] << " for reading\n";
		return 1;
	}
	std::ofstream output(argv[2]);
	if (!output.is_open()) { // Удалось ли открыть выходной файл
		std::cout << "Failed to open " << argv[2] << " for writing\n";
		return 1;
	}
	for (char ch; input.get(ch);) { // Читаем посимвольно данные
		if (!output.put(ch)) {      // и записываем в выходной файл
			std::cout << "Failed to save data on disk\n";
			return 1;
		}
	}
	if (!input.eof()) { // Все ли данные были считаны?
		std::cout << "Failed to read input file\n";
		return 1;
	}
	if (!output.flush()) { // Успешно ли данные были записаны?
		std::cout << "Failed to save data on disk\n";
		return 1;
	}
	return 0; // Всё ок, завершаем программу и сообщаем об успехе
}
#endif

#if 0
bool CopyFile(std::string inputName, std::string outputName, std::string& error) {
	std::ifstream input(inputName);
	if (!input.is_open()) { // Удалось ли открыть входной файл?
		error = "Failed to open " + inputName + " for reading";
		return false;
	}
	std::ofstream output(outputName);
	if (!output.is_open()) { // Удалось ли открыть выходной файл
		error = "Failed to open " + outputName + " for writing";
		return false;
	}
	for (char ch; input.get(ch);) { // Читаем посимвольно данные
		if (!output.put(ch)) {      // и записываем в выходной файл
			error = "Failed to save data on disk";
			return false;
		}
	}
	if (!input.eof()) { // Все ли данные были считаны?
		error = "Failed to read input file";
		return false;
	}
	if (!output.flush()) { // Успешно ли данные были записаны?
		error = "Failed to save data on disk";
		return false;
	}
	return true;
}

int main(int argc, char* argv[]) {
	if (argc != 3) { // Указаны ли верно параметры командной строки?
		std::cout << "Invalid arguments count\n"
			 << "Usage: copyfile.exe <input file> <output file>\n";
		return 1;
	}
	if (std::string error; !CopyFile(argv[1], argv[2], error))
	{
		std::cout << error << std::endl;
	}
	return 0;
}
#endif

#if 1
bool CopyStream(std::ifstream& input, std::ofstream& output, std::string& error) {
	for (char ch; input.get(ch);) { // Читаем посимвольно данные
		if (!output.put(ch)) {      // и записываем в выходной файл
			error = "Failed to save data on disk";
			return false;
		}
	}
	if (!input.eof()) { // Все ли данные были считаны?
		error = "Failed to read input file";
		return false;
	}
	if (!output.flush()) { // Успешно ли данные были записаны?
		error = "Failed to save data on disk";
		return false;
	}
	return true;
}

bool CopyFile(std::string inputName, std::string outputName, std::string& error) {
	std::ifstream input(inputName);
	if (!input.is_open()) { // Удалось ли открыть входной файл?
		error = "Failed to open " + inputName + " for reading";
		return false;
	}
	std::ofstream output(outputName);
	if (!output.is_open()) { // Удалось ли открыть выходной файл
		error = "Failed to open " + outputName + " for writing";
		return false;
	}
	return CopyStream(input, output, error);
}

// Переводит время в строку
std::string TimeToString(Time t) { ... }

// Переводит время в строку в формате "hh:mm:ss"
std::string TimeToString(Time t) { ... }


int GenerateRandomNumber() {
	// TODO: Генератор случайных числе будет доработан в задаче TASK-888
	return 42;
}

void OnClick()
{
}

enum class Gear { 
    NEUTRAL = 0, FIRST, SECOND, THIRD, FOURTH, FIFTH, REVERSE = -1 
};

struct GearSpeedRange {
    Gear gear;     // Передача.
    int minSpeed; // Минимальная скорость на этой передаче.
    int maxSpeed; // Максимальная скорость на этой передаче.
};

// car.h

class Car {
    
private:
    // Так статическое поле объявляется и определяется внутри класса.
    inline static const std::vector<GearSpeedRange> speed_ranges_ = {
        { Gear::NEUTRAL, 0, 150 },
        { Gear::FIRST, 0, 30 },
        { Gear::SECOND, 20, 50 },
        { Gear::THIRD, 30, 70 },
        { Gear::FOURTH, 40, 100 },
        { Gear::FIFTH, 60, 150 },
        { Gear::REVERSE, 0, 30 },
    };
};


int main(int argc, char* argv[]) {
	if (argc != 3) { // Указаны ли верно параметры командной строки?
		std::cout << "Invalid arguments count\n"
			 << "Usage: copyfile.exe <input file> <output file>\n";
		return 1;
	}
	if (std::string error; !CopyFile(argv[1], argv[2], error))
	{
		std::cout << error << std::endl;
	}
	return 0;
}
#endif