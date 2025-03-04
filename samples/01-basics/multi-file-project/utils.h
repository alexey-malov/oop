#pragma once

// Вместо #pragma once можно использовать #include guards,
// чтобы защитить заголовочный файл от многократного включения
#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

struct Point
{
	int x, y;
};

int Add(int x, int y, int z);

#endif