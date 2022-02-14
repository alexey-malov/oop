Все идентификаторы и комментарии должны быть на английском языке.

Мы в целом соблюдаем [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines) — их список не надо читать целиком, но можно ссылаться на них при Code Review.

Не проверяйте форматирование вручную: используйте [расширение ClangFormat для Visual Studio](https://marketplace.visualstudio.com/items?itemName=HansWennborg.ClangFormat).
- Файл конфигурации для ClangFormat (`.clang-format`), соответствующий нашим соглашениям о кодировании, уже находится в репозитории проекта
- Вы можете скопировать этот файл в каталог, в котором находятся все ваши лабораторные работы

# Оформление комментариев

Хороший код бывает читаемым даже без комментариев.

* Помечайте комментариями хотфиксы и код, который со стороны кажется лишним.
* Объясняйте в комментариях неочевидные вещи, если не нашли способа объяснить именами функций.
* [NL.1 Не объясняйте в комментариях вещи, понятные из кода](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rl-comments)
* [NL.2 В комментариях описывайте цель, а не средства](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#nl2-state-intent-in-comments)
* [NL.3 Комментарии должны быть лаконичными](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#nl3-keep-comments-crisp)


# Именование

Обратите внимание:

* [NL5. Не кодируйте типы данных в именах переменных и функций](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#nl5-dont-encode-type-information-in-names)
* [NL7. Длина имени пропорциональна области видимости](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#nl7-make-the-length-of-a-name-roughly-proportional-to-the-length-of-its-scope)

Именование идентификатора зависит от категории:

| Категория                        | Пример                       | Префикс       |
|----------------------------------|------------------------------|---------------|
| класс                            | PublishDialog                |               |
| интерфейс                        | IConverterPipeline           | I             |
| тип данных (using, struct, enum) | LicenseState                 |               |
| функция или метод                | ExtractZip, ShouldQuit       |               |
| поле класса                      | m_taskQueue, m_children      | m_            |
| локальная переменная             | bookCount, env               |               |
| локальная константа              | mayExpand                    |               |
| параметр функции                 | bookCount, env               |               |
| варианты enum class              | BusinessTrial                |               |
| константы и варианты enum        | bookCount, env               |               |
| параметр template<>              | Callback, ArraySize          |               |
| макрос                           | ISPRING_BRAND_NAME           | ISPRING_, IS_ |
| глобальная переменная            | оно тебе надо? g_cachedTypes | g_            |

# Форматирование


* Отступы табами, размер таба 4 единицы
* Максимальная длина строки - 100 символов. Иначе, неудобно смотреть diff в программах, использующих для этого две вертикальные панели.
<details><summary>Настройка Visual Assist</summary>
<p>
Visual Assist Options\Display\Display indicator after column
</p>
</details>

* Ставьте скобки на новой строке везде, кроме случаев, когда продолжается выражение (начало lambda function или initializer list)
* [NL.15: используйте пробелы умеренно](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#nl15-use-spaces-sparingly)
* Символы ссылок и указателей прижимайте к типу данных: `T& operator[](size_t);`

Пример:

```cpp
void AddWords(std::string& text, const std::vector<std::string>& words) override
{
    auto addOneWord = [&text](const auto& word) {
        if (!text.empty())
        {
            text += " ";
        }
        text += word;
    };
    for (const auto& word : words)
    {
        addOneWord(word);
    }
}

void CallAddWords()
{
    std::string text = "The quick brown fox";
    const std::vector<std::string> words = {
        "jumps", "over",
        "the", "lazy", "dog"
    };
    AddWords(text, words);
}
```

При необходимости нужно настроить IDE. Например, стоит убрать опцию "Indent namespace contents":

![Dont Indent Namespace](/uploads/desktop-public/dont-indent-namespace.png "Dont Indent Namespace")

# Выражения и инструкции


* [ES.20 Всегда инициализируйте переменные и поля](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Res-always)
* [ES.21 Старайтесь не добавлять переменную раньше, чем она понадобилась](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#es21-dont-introduce-a-variable-or-constant-before-you-need-to-use-it)
* [ES.22 Старайтесь не объявлять переменную раньше, чем будет вычислено подходящее для неё значение](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#es22-dont-declare-a-variable-until-you-have-a-value-to-initialize-it-with)
* [ES.40 Избегайте сложных выражений](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#es40-avoid-complicated-expressions)
* [ES.41 Если сомневаетесь в приоритете операторов, добавьте скобки](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#es41-if-in-doubt-about-operator-precedence-parenthesize)
* [ES.45 Избегайте "магических констант", используйте именованные константы](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#es45-avoid-magic-constants-use-symbolic-constants)
* [ES.49 Если вам нужно преобразование типа, используйте именованное преобразование](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#es49-if-you-must-use-a-cast-use-a-named-cast)


# Функции и их тела

Обратите внимание:

* [F.2: Функция должна выполнять одну логическую подзадачу](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#f2-a-function-should-perform-a-single-logical-operation)
* [F.3: Сохраняйте лаконичность функций](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#f3-keep-functions-short-and-simple)
* [F.9: Неиспользуемые параметры не должны иметь имени](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#f9-unused-parameters-should-be-unnamed)
    * в объявлении метода можно закоментировать имя: `void Dump(std::ostream& /*dest*/)`
    * в определении можно удалить если у метода есть объявление
    * можно использовать `(void)ignoredVar;`


* [F.20: Для передачи результатов предпочитайте использовать возвращаемое значение, а не out-параметры](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#f20-for-out-output-values-prefer-return-values-to-output-parameters)
* [F.21: Вместо создания множества out-параметров старайтесь возвращать структуру или кортеж](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#f21-to-return-multiple-out-values-prefer-returning-a-tuple-or-struct)

Таблица типичных способов передачи параметров (из [F.15: Prefer simple and conventional ways of passing information ](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#f15-prefer-simple-and-conventional-ways-of-passing-information)):

![Иллюстрация](img/param-passing-advanced.png)

![Param Passing Advanced](/uploads/desktop-public/param-passing-advanced.png "Param Passing Advanced")

# Объектно-ориентированный код

[C.2: Пишите class, если объект имеет инвариант; пишите struct, если поля меняются независимо](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c2-use-class-if-the-class-has-an-invariant-use-struct-if-the-data-members-can-vary-independently)
[NL.16: Соблюдайте порядок в объявлении класса](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#nl16-use-a-conventional-class-member-declaration-order):

* `public:` выше чем `protected:`, `protected:` выше чем `private:`
* вверху располагаются типы: вложенные классы, enum, using
* затем конструкторы, операторы присваивания, деструкторы
* затем методы
* затем данные


# Константы


* [Enum.3: Выбирайте enum class вместо enum](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#enum3-prefer-class-enums-over-plain-enums)
* [Enum.6: Откажитесь от анонимных enum в пользу constexpr констант](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#enum6-avoid-unnamed-enumerations)
* [I.22: Избегайте сложной инициализации глобальных констант и переменных](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#i22-avoid-complex-initialization-of-global-objects)


# Практики Modern C++

Этот раздел правил можно не соблюдать, если вы прекрасно разбираетесь в C++ и точно знаете, что творите.

* Используйте умные указатели:

    *  `std::unique_ptr - `если достаточно эксклюзивного владения объектом;
    *  `std::shared_ptr - `если заведомо нужен совместный доступ;
    *  `std::weak_ptr - `если объект может быть разрушен независимо.

* [ES.47 Используйте для указателей nullptr вместо 0 и NULL](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#es47-use-nullptr-rather-than-0-or-null)
* [F6. Если функции запрещено бросать исключения, помечайте её как noexcept](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#f6-if-your-function-may-not-throw-declare-it-noexcept)
* [C.128: Виртуальные функции должны быть помечены ровно одним из трёх слов: virtual, override или final](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c128-virtual-functions-should-specify-exactly-one-of-virtual-override-or-final)
* [Если захватываете this, то захватывайте переменные явно и не используйте default capture](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#f54-if-you-capture-this-capture-all-variables-explicitly-no-default-capture)

# Изолируйте низкий уровень от высокого

Высокий уровень - это бизнес-логика, работа с жизненным циклом крупных объектов и подсистем и так далее.

Низкий уровень - это:

* Низкоуровневые циклы for/while
	* Функция не должна содержать цикл, если запуск этого цикла не является основной задачей функции
	* Используйте готовые алгоритмы либо изолируйте циклы в отдельные функции
* Низкоуровневая работа с памятью и другими ресурсами
	* Работайте с памятью и файлами на умных указателях (либо, в особых случаях, на других полуавтоматических решениях)
	* Либо изолируйте
	* См. [C++ without new and delete](http://cpp-russia.ru/?page_id=608)
* Низкоуровневая работа с объектами синхронизации
  * Разделяйте в разные классы/модули задачи многопоточности и иные задачи
  * Задачи многопоточности - это запуск задач, управление прогрессом/отменой, доступ к разделяемым данным
* Смешивание C и C++
  * Изолируйте работу с C API в отдельных классах/модулях/функциях

# Безопасное программирование

Чем более низкоуровневый класс/модуль вы пишете, тем важнее добавлять защиту от неожиданных проблем.

Приоритетные проблемы:

* Разыменование нулевых указателей, dangling pointer, double free и другие undefined behavior при работе с памятью
* Деление на ноль, деление INT_MAX на `-1`: обе ситуации приводят к фатальному SEH-исключению
* Нарушение контрактов в параметрах функции
  * Например, в какой-то функции `count` всегда должен быть больше 2 - значит, надо в функции проверять это требование
* Обработка ошибок во внешних API и сохранение информации об ошибках

Менее приоритетные проблемы

* Возможность получить NaN в вычислениях на float/double
* Переполнение в вычислениях на целочисленных типах

<!--

## Примеры:
```c_cpp
#include <iostream>
#include <fstream>
#include <optional>
#include <stdexcept>

using namespace std;

Matrix ReadMatrix(istream& input)
{
  /* Считывает матрицу с потока в случае ошибки бросает исключение */
}

optional<Matrix> TryInvertMatrix(const Matrix& mat);

// Программа инвертирует матрицу
int main(int argc, char* argv)
{
  if (argc < 2)
  {
    cout << "Usage: InvertMatrix.exe <input-file>\n";
    return 0;
  }
  
  try
  {
    ifstream inputFile(argv[1]);
    if (!inputFile)
    {
      throw std::runtime_error("Failed to open input file");
    }
    Matrix mat = ReadMatrix(inputFile);
    
    if (auto inverted = InvertMatrix(mat))
    {
      PrintMatrix(*inverted);
      return 0;
    }
    else
    {
      std::cout << "Matrix is singular\n";
      return 1;
    }
  }
  catch (const exception& e)
  {
    std::cout << e.what() << "\n";
  }
  
  return 1;
}
```
Тут плохо, что функция main содержит код из более низкого уровня (открытие файла)

Улучшить можно выделив функцию, инкапсулирующую откытие файла и обрабытающую ошибки:
```c_cpp
#include <iostream>
#include <fstream>
#include <optional>
#include <filesystem>
#include <stdexcept>

using namespace std;

Matrix ReadMatrix(istream& input)
{
  /* Считывает матрицу с потока в случае ошибки бросает исключение */
}

Matrix ReadMatrix(const path& path)
{
    ifstream inputFile(path);
    if (!inputFile)
    {
      throw std::runtime_error("Failed to open input file");
    }
    return ReadMatrix(inputFile);
}

optional<Matrix> TryInvertMatrix(const Matrix& mat);

// Программа инвертирует матрицу
int main(int argc, char* argv)
{
  if (argc < 2)
  {
    cout << "Usage: InvertMatrix.exe <input-file>\n";
    return 0;
  }
  
  try
  {
    auto mat = ReadMatrix(argv[1]);
    if (auto inverted = InvertMatrix(mat))
    {
      PrintMatrix(*inverted);
      return 0;
    }
    else
    {
      std::cout << "Matrix is singular\n";
      return 1;
    }
  }
  catch (const exception& e)
  {
    std::cout << e.what() << "\n";
  }
  
  return 1;
}
```
-->
