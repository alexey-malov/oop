#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <random>

using namespace std;

void main()
{
	// Простейший цикл for
	{
		// Выводит 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
		// Область видимости переменной i ограничена телом цикла
		for (int i = 0; i < 10; ++i)
		{
			cout << i << ", ";
		}
		cout << endl;

		for (int i = 100; i >= 0; i -= 2)
		{
			cout << i << ", ";
		}
		cout << endl;
	}

	// Используем вложенный цикл for для поиска простых чисел
	{
		cout << "Primes: ";
		for (int i = 2; i < 100; ++i)
		{
			bool isPrime = true;

			// Наивный метод определения простоты числа i
			//	проверяем i на делимость на любое из чисел диапазона [2; sqrt(i)]
			for (int j = 2; j * j <= i; ++j)
			{
				// Если найден множитель числа i, выходим из цикла при помощи break
				if (i % j == 0)
				{
					isPrime = false;
					break;
				}
			}
			if (isPrime)
			{
				cout << i << ", ";
			}
		}
		cout << endl;
	}

	// Range-based цикл for
	{
		// Обход элементов массива
		{
			int numbers[] = { 10, 15, 17, 33, 18 };
			int sum = 0;
			int product = 1;
			cout << "Array items: ";
			for (int number : numbers)
			{
				cout << number << ", ";
				sum += number;
				product *= number;
			}
			cout << endl << "\tSum: " << sum << endl << "\tProduct: " << product << endl;
		}

		// Обход символов строки и контейнера map
		{
			string pangram = "the quick brown fox jumps over the lazy dog";

			// Отображение (map) - контейнер, хранящий пары ключ-значение
			// в роли ключа выступает код символа, в роли значения - число (его частота встречаемости)
			map<char, int> characterOccurrences;
			// Пробегаем по символам строки и для каждого буквенного символа увеличиваем его частоту встречаемости
			for (char ch : pangram)
			{
				cout << ch;
				if (isalpha(ch))
				{
					// Оператор [] контейнера map возвращает ссылку на значение для указанного ключа
					// При отсутствии ключа предварительно добавит ключ со значением по умолчанию (в нашем случае 0)
					++characterOccurrences[ch]; // Возращенное значение частоты встречаемости символа увеличиваем на 1
				}
			}

			cout << "Character occurrence in \"" << pangram << "\":" << endl;
			// Выводим информацию о частоте встречаемости каждого символа

			for (const auto & charOcc : characterOccurrences)
			{
				// charOcc имеет тип pair<char, int> и содержит поля first (ключ) и second (значение)
				cout << "\t" << charOcc.first << ": " << charOcc.second << endl;
			}

			/*for (map<char, int>::const_iterator it = characterOccurrences.begin(); it != characterOccurrences.end(); ++it)
			{
				const auto & charOcc = *it;
				cout << "\t" << charOcc.first << ": " << charOcc.second << endl;
			}*/
		}
	}


	// Цикл while
	{
		unsigned a = 714;
		unsigned b = 312;
		cout << "Greatest Common Denominator of " << a << " and " << b << " is ";
		while (b != 0)
		{
			swap(a, b);
			b = b % a;
		}
		cout << max(a, 1u) << endl;
	}

	// Цикл do-while
	{
		string userInput;
		do 
		{
			cout << R"(Enter text or "bye" to finish: )";
			getline(cin, userInput);
			cout << "You entered: " << userInput << endl;
		} while (userInput != "bye");
	}

	// Бесконечный цикл for
	{
		// Генератор псевдослучайных чисел с использованием Вихря Мерсенна (Mersenne Twister)
		mt19937 generator;
		// Адаптер для получения равномерно распределенных чисел в диапазоне [1; 10]
		uniform_int_distribution<int> dist(1, 10);
		for (;;)
		{
			cout << "Next random number: " << dist(generator) << endl;
			cout << "Type q or Q to quit the game: ";
			string userInput;
			getline(cin, userInput);
			if (userInput == "q" || userInput == "Q")
			{
				break;
			}
		}

		// Также можно использовать цикл while:
		//	while (true)
		//	{
		//		тело цикла 
		//	}
		// либо цикл do-while: 
		//	do 
		//	{
		//		тело цикла
		//	} while(true);
	}
}
