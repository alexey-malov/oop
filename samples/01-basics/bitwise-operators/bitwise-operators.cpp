#include <cstdint>
#include <iomanip>
#include <iostream>

struct RGBAColor
{
	uint8_t r = 0;
	uint8_t g = 0;
	uint8_t b = 0;
	uint8_t a = 255;
};

RGBAColor RGBAColorFromARGB(uint32_t argb)
{
	return {
		static_cast<uint8_t>((argb >> 16) & 0xff),
		static_cast<uint8_t>((argb >> 8) & 0xff),
		static_cast<uint8_t>(argb & 0xff),
		static_cast<uint8_t>((argb >> 24) & 0xff),
	};
}

RGBAColor RGBAColorFromABGR(uint32_t abgr)
{
	return {
		static_cast<uint8_t>(abgr & 0xff),
		static_cast<uint8_t>((abgr >> 8) & 0xff),
		static_cast<uint8_t>((abgr >> 16) & 0xff),
		static_cast<uint8_t>((abgr >> 24) & 0xff),
	};
}

void Print(RGBAColor color)
{
	std::cout << "r: " << +color.r << ", g: " << +color.g << ", b: "
			  << +color.b << ", a: " << +color.a << std::endl;
	// Унарный + здесь служит для преобразования из uint8_t в int,
	// чтобы значение выводилось в виде числа, а не в виде символа
}

int main()
{
	uint32_t value;
	std::cin >> std::hex >> value;
	Print(RGBAColorFromARGB(value));
	Print(RGBAColorFromABGR(value));
}
