// TrimBlanksTests.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../TrimBlanks.h"

namespace
{
void VerifyTrimBlanks(const std::string &sourceStr, const std::string &expectedTrimmedString)
{
	BOOST_CHECK_EQUAL(TrimBlanks(sourceStr), expectedTrimmedString);
}
}

BOOST_AUTO_TEST_SUITE(TrimBlanks_function)
	BOOST_AUTO_TEST_CASE(must_convert_empty_string_to_empty_string)
	{
		VerifyTrimBlanks("", "");
	}

	// Последовательность действий:
	// 1.a. Раскомментировать тест "[Функция trim blanks] оставляет строку без пробелов неизменной"
	// 1.b. Убедиться, что тест не проходит
	// 1.c. Доработать функцию TrimBlanks, чтобы этот тест и предыдущий проходили успешно
	// 1.d. Навести порядок в коде, если это требуется, убедиться, что тесты проходят
	// 1.e. Закоммитить изменения в репозиторий
	//BOOST_AUTO_TEST_CASE(leaves_string_without_blanks_unchanged)
	//{
	//	VerifyTrimBlanks("text_without_blanks", "text_without_blanks");
	//}

	// 2.a. Раскомментировать тест "[Функция trim blanks] удаляет пробелы в начале"
	// 2.b. Убедиться, что тест не проходит
	// 2.c. Доработать функцию TrimBlanks, чтобы этот тест и предыдущие проходили успешно 
	//		(постараться написать минимум кода для решения задачи)
	// 2.d. Навести порядок в коде, если это требуется, убедиться, что тесты проходят
	// 2.e. Закоммитить изменения в репозиторий
	//BOOST_AUTO_TEST_CASE(removes_blanks_in_the_beginning)
	//{
	//	VerifyTrimBlanks("     blanks_in_the_beginning", "blanks_in_the_beginning");
	//}

	// 3.a. Раскомментировать тест "[Функция trim blanks] удаляет пробелы в конце"
	// 3.b. Убедиться, что тест не проходит
	// 3.c. Доработать функцию TrimBlanks, чтобы этот тест и предыдущие проходили успешно 
	//		(постараться написать минимум кода для решения задачи)
	// 3.d. Навести порядок в коде, если это требуется, убедиться, что тесты проходят
	// 3.e. Закоммитить изменения в репозиторий
	//BOOST_AUTO_TEST_CASE(removes_blanks_in_the_end)
	//{
	//	VerifyTrimBlanks("blanks_in_the_end    ", "blanks_in_the_end");
	//}

	// 4.a. Раскомментировать тест "[Функция trim blanks] оставляет пробелы в середине"
	// 4.b. Убедиться, что тест не проходит
	// 4.c. Доработать функцию TrimBlanks, чтобы этот тест и предыдущие проходили успешно 
	//		(постараться написать минимум кода для решения задачи)
	// 4.d. Навести порядок в коде, если это требуется, убедиться, что тесты проходят
	// 4.e. Закоммитить изменения в репозиторий
	//BOOST_AUTO_TEST_CASE(keeps_blank_in_the_middle)
	//{
	//	VerifyTrimBlanks("text with  blanks in    the middle", "text with  blanks in    the middle");
	//}

	// 5.a. Раскомментировать тест "[Функция trim blanks] удаляет пробелы в начале и середине"
	// 5.b. Убедиться, что тест не проходит
	// 5.c. Доработать функцию TrimBlanks, чтобы этот тест и предыдущие проходили успешно 
	//		(постараться написать минимум кода для решения задачи)
	// 5.d. Навести порядок в коде, если это требуется, убедиться, что тесты проходят
	// 5.e. Закоммитить изменения в репозиторий
	//BOOST_AUTO_TEST_CASE(trims_blanks_in_the_beginning_and_in_the_end)
	//{
	//	VerifyTrimBlanks("   text  with  blanks at both  sides   ", "text  with  blanks at both  sides");
	//}

	// 6.a. Раскомментировать тест "[Функция trim blanks] конвертирует строку пробелов в пустую"
	// 6.b. Убедиться, что тест не проходит
	// 6.c. Доработать функцию TrimBlanks, чтобы этот тест и предыдущие проходили успешно 
	//		(постараться написать минимум кода для решения задачи)
	// 6.d. Навести порядок в коде, если это требуется, убедиться, что тесты проходят
	// 6.e. Закоммитить изменения в репозиторий
	//BOOST_AUTO_TEST_CASE(converts_a_string_of_blanks_to_empty_string)
	//{
	//	VerifyTrimBlanks("       ", "");
	//}
BOOST_AUTO_TEST_SUITE_END()