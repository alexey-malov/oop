#include "stdafx.h"
#include "Utils.h"

bool IsLeapYear(int year)
{
	return ((year % 4 == 0) &&
		((year % 400 == 0) || (year % 100 != 0)));
}