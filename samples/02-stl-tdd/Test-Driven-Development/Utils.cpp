#include "stdafx.h"
#include "Utils.h"

bool IsLeapYear(int year)
{
	return 
		(year % 400 == 0) ? true :
		(year % 100 == 0) ? false :
		(year % 4 == 0);
}