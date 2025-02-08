#include <iostream>
#include <string>

enum class TrafficLightColor // или enum struct TrafficLightColor
{
	Yellow,
	Red,
	Green
};

enum class CarColor
{
	Red,
	Black,
	White
};

std::string TrafficLightToString(TrafficLightColor color)
{
	if (color == TrafficLightColor::Red)
		return "Red";
	if (color == TrafficLightColor::Yellow)
		return "Yellow";
	if (color == TrafficLightColor::Green)
		return "Green";
	return "Unknown Color";
}

int main()
{
	TrafficLightColor color1 = TrafficLightColor::Red;
	CarColor color2 = CarColor::Red;

	std::cout << TrafficLightToString(TrafficLightColor::Yellow) << std::endl;
}
