﻿#include <cassert>

typedef double Matrix2x2[2][2];

// В функцию массивы передаются без копирования
// (фактически, передается адрес первого элемента массива)
void Fn(Matrix2x2 mat)
{
	// Модификация массива внутри функции изменяет переданный массив
	mat[0][0] = 3.0;
}

struct WrappedMatrix2x2
{
	Matrix2x2 items;
};

// Структура (даже содержащая массив) при передаче в функцию по значению
// будет скопирована (включая содержимое массива)
void Fn2(WrappedMatrix2x2 mat)
{
	// Модификация массива mat внутри не окажет влиянияния на переданный массив
	mat.items[0][0] = 3.0;
}

void main()
{
	Matrix2x2 mat = {
		{1.0, 2.5},
		{4.5, 3.2}
	};
	assert(mat[0][0] == 1.0);
	assert(mat[0][1] == 2.5);
	assert(mat[1][0] == 4.5);
	assert(mat[1][1] == 3.2);

	// При передаче массива в функцию Fn будет передан, фактически, оригинал
	Fn(mat);
	// Модификация элементов массива внутри Fn модифицирует переданный массив
	assert(mat[0][0] == 3.0);

	WrappedMatrix2x2 wrappedMat = {
		{
			{ 1.0, 2.5 },
			{ 4.5, 3.2 }
		} 
	};
	// При передаче структуры в функцию Fn2 будет передана копия структуры
	Fn2(wrappedMat);
	// Модификация элементов массива внутри Fn2 на оригинальный массив влияния не окажет
	assert(wrappedMat.items[0][0] == 1.0);
}