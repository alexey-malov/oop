#include <iostream>
#include <cstdint>

void main()
{
	// Целые числа
	char userInput = std::cin.get(); // Символ
	short printerDPI = 350; // Короткое целое
	unsigned int cityPopulation = 100500; // Целое число (со знаком)

	// Целые числа фиксированной разрядности (могут отсутствовать в реализации)
	uint8_t r = 32, g = 19, b = 33;
	int16_t imageWidth = 1280;
	uint64_t fileSize = 999999999999;
}