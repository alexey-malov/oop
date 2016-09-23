#include <string>
#include <iostream>
#include <cassert>

enum class WeekDay
{
	Sunday, Monday, Tuesday, Wednesday,
	Thursday, Friday, Saturday
};

std::string WeekDayToString(const WeekDay & weekDay)
{
	switch (weekDay)
	{
	case WeekDay::Sunday:    return "Sunday";
	case WeekDay::Monday:    return "Monday";
	case WeekDay::Tuesday:   return "Tuesday";
	case WeekDay::Wednesday: return "Wednesday";
	case WeekDay::Thursday:  return "Thursday";
	case WeekDay::Friday:    return "Friday";
	case WeekDay::Saturday:  return "Saturday";
	default:
		assert(!"This is not possible");
		return "";
	}
}

void main()
{
	std::cout << WeekDayToString(WeekDay::Sunday) << std::endl;
}