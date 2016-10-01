#include <cassert>
#include <string>

int g_globalArray[3];

// При помощи такой функции можно определить количество элементов в массиве
template<typename T, std::size_t N>
constexpr std::size_t SizeOfArray(T(&)[N])
{
	return N; 
}

// Функция, принимающая массив, на самом деле принимает указатель на первый элемент
void SomeFn(int arr[3])
{
	// модификация элементов массива, переданного в качестве параметра, внутри функции меняет переданный массив
	arr[1] = 42;
}

// Функция, принимающая ссылку массив, позволяет передать только массив (правда по ссылке)
void SomeFn1(int (&arr)[3])
{
	// модификация элементов массива, переданного в качестве параметра, внутри функции меняет переданный массив
	arr[1] = 42;
}

struct Vector3d
{
	double coords[3];
};
// структуру, содержащую массив, можно принимать еще и по значению (будет создана копия) и даже возвращать в качестве результата
Vector3d SomeFn2(Vector3d vec)
{
	vec.coords[0] += 0.5;
	return vec;
}

void main()
{

	{
		int abc[3];
		int abcd[4];
		int *x = &abc[0];
		SomeFn(x); // Так можно
		SomeFn(abc); // Так можно
		SomeFn(abcd); // Так можно

		SomeFn1(abc); // Так можно
		//SomeFn1(abcd); // Так нельзя
		// SomeFn1(x); так нельзя
	}
	// Глобальные переменные-массивы по умолчанию инициализируются нуляем
	assert(g_globalArray[0] == 0
		&& g_globalArray[1] == 0 
		&& g_globalArray[2] == 0);

	// Массив из 3-х элементов. Элементы не проинициализированы
	float floatNumbers[3];
	floatNumbers[0] = 1.0; floatNumbers[1] = 3.5; floatNumbers[2] = -4.5;

	// Массив при объявлении может быть проинициализирован
	double doubleNumbers[3] = { 3.8, 2.1, 3.53 };

	// Элементы массива, не указанные при инициализации, равны нулю
	double zeroFilledArray[3] = { 3.5, 7.2 };
	assert(zeroFilledArray[2] == 0.0);

	// Элементы проинициализированы нулями
	double zeroInitializedArray[3] = { };

	// Если не указать размер массива при инициализации, 
	// он будет определен автоматически
	double arrayOf5Items[] = { 3.5, 8.7, 2.3, -1.25, 0.0 };

	std::string name = "John", surname = "Doe";
	// При инициализации элементов массив могут также использоваться выражения
	std::string userNames[] = { "Ivan", "Sergey", name + " " + surname };
	// Так можно определить количество элементов в массиве
	assert(std::end(userNames) - std::begin(userNames) == 3);
	// Также можно воспользоваться вспомогательной объявленонй выше функцией SizeOfArray
	assert(SizeOfArray(userNames) == 3);
	assert(userNames[2] == "John Doe");
	
	// Константный массив из 5 элементов
	const char arr1[] = { 'J', 'o', 'h', 'n', '\0' };
	assert(std::end(arr1) - std::begin(arr1) == 5);

	// Неконстантный массив из 4 элементов
	char arr2[] = "Doe";
	assert(SizeOfArray(arr2) == 4);

	// Константный массив из 6 элементов
	const char arr3[6] = "Hello";
	assert(SizeOfArray(arr3) == 6);

}