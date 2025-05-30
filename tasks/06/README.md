# Лабораторная работа №6. Обработка ошибок, исключительные ситуации.

- [Лабораторная работа №6. Обработка ошибок, исключительные ситуации.](#лабораторная-работа-6-обработка-ошибок-исключительные-ситуации)
  - [Практические задания](#практические-задания)
  - [Обязательные задания](#обязательные-задания)
    - [Задание 1](#задание-1)
      - [Вариант 1 – Triangle – 30 баллов](#вариант-1--triangle--30-баллов)
      - [Вариант 2 – Решение квадратных уравнений – 30 баллов](#вариант-2--решение-квадратных-уравнений--30-баллов)
      - [Вариант 3 – Решение кубических уравнений – 60 баллов](#вариант-3--решение-кубических-уравнений--60-баллов)
      - [Вариант 4 – Решение уравнений 4 степени – 100 баллов](#вариант-4--решение-уравнений-4-степени--100-баллов)
      - [Вариант 5 – Сортировка строк - 20 баллов](#вариант-5--сортировка-строк---20-баллов)
      - [Вариант 6 – Студент – 50 баллов](#вариант-6--студент--50-баллов)
      - [Вариант 7 – HTTP URL – 100 баллов](#вариант-7--http-url--100-баллов)
  - [Дополнительные задания](#дополнительные-задания)
    - [Задание 2](#задание-2)
      - [Вариант 1 – StringStack - 150 баллов](#вариант-1--stringstack---150-баллов)
      - [Вариант 2 – StringList - 300 баллов](#вариант-2--stringlist---300-баллов)

## Практические задания

На оценку «**удовлетворительно**» необходимо набрать **не менее 150 баллов**.

На оценку «**хорошо**» необходимо набрать **не менее 220 баллов**.

На оценку «**отлично**» необходимо набрать **не менее 350 баллов**.

## Обязательные задания

### Задание 1

#### Вариант 1 – Triangle – 30 баллов

Разработайте класс `CTriangle`, представляющий треугольник, заданный длинами трех своих сторон и предоставляющий информацию о своих сторонах, площади и периметре.

Площадь треугольника, длины сторон которого известны, можно вычислить по формуле Герона:

$S=\sqrt{p(p-a)(p-b)(p-c)}$,

где a, b и c – длины сторон треугольника, а p – полупериметр:

$p=\frac{(a+b+c)}{2}$

Каркас класса представлен ниже:

```c++
class CTriangle
{
public:
    CTriangle(double side1, double side2, double side3);
    double GetSide1()const;
    double GetSide2()const;
    double GetSide3()const;
    double GetArea()const;
    double GetPerimeter()const;
};
```

При работе данного класса возможны следующие внештатные ситуации:

- Некорректное значение аргументов конструктора – длины сторон треугольника не могут быть отрицательными
- Не любые 3 отрезка могут сформировать треугольник.
  - В невырожденном треугольнике длина каждой стороны должна быть меньше суммы двух других сторон.
  - В случае вырожденного треугольника допускается равенство длины некоторой стороны треугольника сумме длин двух других сторон.
  - Если длина одного из отрезков превышает сумму двух других, то треугольник с их помощью создать не удастся.

В конструкторе класса `CTriangle` необходимо обрабатывать данные внештатные ситуации, выбрасывая соответствующие исключения. При некорректном значении аргументов необходимо выбрасывать исключение `std::invalid_argument`, а при недопустимой комбинации длин сторон – исключение `std::domain_error`. При создании исключения необходимо инициализировать его текстом сообщения об ошибке.

Разработайте на базе данного класса приложение, выполняющее считывание со стандартного потока ввода длины сторон трех отрезков, формирование из них треугольника и выводящее в стандартный поток вывода его площадь и периметр. Приложение должно перехватывать выбрасываемые исключения и выводить в поток вывода диагностическую информацию об исключительной ситуации (текст сообщения об ошибке из перехваченного сообщения).

Ввод данных прекращается, как только во входном потоке будет встречен символ конца файла.

<span style="color:red">Для класса CTriangle должен быть разработан набор автоматических тестов, проверяющих работу его методов и конструктора как на корректных, так и некорректных наборах данных. Рекомендуется использование библиотек и фреймворков для написания тестов, например, [boost::test](https://www.boost.org/doc/libs/1_55_0/libs/test/doc/html/index.html), [Google Test](https://github.com/google/googletest), CxxTest и других. Без тестов работа будет принята с коэффициентом не выше 0.3.</span>

#### Вариант 2 – Решение квадратных уравнений – 30 баллов

Разработайте функцию `Solve`, выполняющую вычисление корней квадратного уравнения $ax^{2}+bx+c=0$ и возвращающую результат в виде структуры `EquationRoots`:

```cpp
struct EquationRoots
{
    int numRoots;
    double roots[2];
};

// Вычисляем корни квадратного уравнения ax^2 + bx + c = 0
EquationRoots Solve(double a, double b, double c)
{
    ...
}
```

Функция `Solve` должна обрабатывать следующие внештатные ситуации:

- Не допускается нулевое значение коэффициента при $x^{2}$. В случае возникновения данной ситуации должно выбрасываться исключение `std::invalid_argument`.
- Квадратное уравнение может не иметь действительных корней. В случае возникновения данной ситуации должно выбрасываться исключение `std::domain_error`.

При выбрасывании исключения необходимо инициализировать его текстом с описанием проблемы.

Разработать на основе данной функции программу, запрашивающую со стандартного потока ввода коэффициенты квадратного уравнения и вычисление при помощи функции `Solve` корней квадратного уравнения с последующим выводом результата в стандартный поток вывода. Исключения, выбрасываемые функцией `Solve`, должны перехватываться программой, а текст диагностического сообщения с информацией об ошибке выводиться в стандартный поток вывода.

Ввод данных программой со стандартного ввода прекращается, как только будет встречен символ конца файла.

<span style="color:red">Для функции Solve должен быть разработан набор автоматических тестов, ее работу как на корректных, так и некорректных наборах данных. Рекомендуется использование библиотек и фреймворков для написания тестов, например, [boost::test](https://www.boost.org/doc/libs/1_55_0/libs/test/doc/html/index.html), [Google Test](https://github.com/google/googletest), CxxTest и других. Без тестов работа будет принята с коэффициентом не выше 0.3.</span>

#### Вариант 3 – Решение кубических уравнений – 60 баллов

Разработайте функцию `Solve3`, выполняющую вычисление корней кубического уравнения $ax^{3}+bx^{2}+cx+d=0$ и возвращающую результат в виде структуры `EquationRoots3`:

```c++
struct EquationRoots3
{
    int numRoots;
    double roots[3];
};

// Вычисляем корни кубического уравнения ax^3 + bx^2 + cx + d = 0
EquationRoots3 Solve3(double a, double b, double c, double d)
{
    ...
}
```

Функция `Solve3` должна обрабатывать следующие внештатные ситуации:

- Не допускается нулевое значение коэффициента при $x^{3}$. В случае возникновения данной ситуации должно выбрасываться исключение `std::invalid_argument`.

При выбрасывании исключения необходимо инициализировать его текстом с описанием проблемы.

Разработать на основе данной функции программу, запрашивающую со стандартного потока ввода коэффициенты кубического уравнения и вычисление при помощи функции `Solve3` корней кубического уравнения с последующим выводом результата в стандартный поток вывода. Исключения, выбрасываемые функцией `Solve3`, должны перехватываться программой, а текст диагностического сообщения с информацией об ошибке выводиться в стандартный поток вывода.

Ввод данных программой со стандартного ввода прекращается, как только будет встречен символ конца файла.

<span style="color:red">Для функции Solve3 должен быть разработан набор автоматических тестов, ее работу как на корректных, так и некорректных наборах данных. Рекомендуется использование библиотек и фреймворков для написания тестов, например, [boost::test](https://www.boost.org/doc/libs/1_55_0/libs/test/doc/html/index.html), [Google Test](https://github.com/google/googletest), CxxTest и других. Без тестов работа будет принята с коэффициентом не выше 0.3.</span>

#### Вариант 4 – Решение уравнений 4 степени – 100 баллов

Разработайте функцию `Solve4`, выполняющую вычисление корней уравнения 4 степени $ax^{4}+bx^{3}+cx^{2}+dx+e=0$ и возвращающую результат в виде структуры `EquationRoot4`:

```cpp
struct EquationRoot4
{
    double numRoots
    double roots[4];
};

// Вычисляем корни кубического уравнения ax^4 + bx^3 + cx^2 + dx + e = 0
EquationRoot4 Solve4(double a, double b, double c, double d, double e)
{
    ...
}
```

Функция `Solve4` должна обрабатывать следующие внештатные ситуации:

- Не допускается нулевое значение коэффициента при $x^{4}$. В случае возникновения данной ситуации должно выбрасываться исключение `std::invalid_argument`.
- Уравнение 4 степени может не иметь действительных корней. В случае возникновения данной ситуации должно выбрасываться исключение `std::domain_error`.

При выбрасывании исключения необходимо инициализировать его текстом с описанием проблемы.

Разработать на основе данной функции программу, запрашивающую со стандартного потока ввода коэффициенты уравнения 4 степени и вычисление при помощи функции `Solve4` корней данного уравнения с последующим выводом результата в стандартный поток вывода. Исключения, выбрасываемые функцией `Solve4`, должны перехватываться программой, а текст диагностического сообщения с информацией об ошибке выводиться в стандартный поток вывода.

Ввод данных программой со стандартного ввода прекращается, как только будет встречен символ конца файла.

<span style="color:red">Для функции Solve4 должен быть разработан набор автоматических тестов, ее работу как на корректных, так и некорректных наборах данных. Рекомендуется использование библиотек и фреймворков для написания тестов, например, [boost::test](https://www.boost.org/doc/libs/1_55_0/libs/test/doc/html/index.html), [Google Test](https://github.com/google/googletest), CxxTest и других. Без тестов работа будет принята с коэффициентом не выше 0.3.</span>

#### Вариант 5 – Сортировка строк - 20 баллов

Разработайте функцию `SortStrings3`, выполняющую упорядочивание трех строк в лексикографическом порядке и предоставляющую **гарантию отсутствия исключений**.

```cpp
void SortStrings(std::string & s1, std::string & s2, std::string & s3);
```

На основе данной функции разработайте программу, считывающую строки со стандартного потока ввода и выводящую в стандартный поток вывода каждую тройку строк, отсортированных в лексикографическом порядке.

#### Вариант 6 – Студент – 50 баллов

Реализуйте класс `CStudent`, описание методов которого представлено ниже. Все методы класса должны предоставлять строгую гарантию безопасности исключений, т.е. поддерживать семантику выполнения commit-or-rollback.

Студент характеризуется фамилией, именем, отчеством, а также возрастом. Имя и фамилия студента должны быть непустыми строками, содержащими символы, отличные от пробела. Отчество студента может быть пустой строкой (если отчество не пустое, то оно также должно содержать символы, отличные от пробела). Возраст студента может быть в диапазоне от 14 до 60 лет (включительно)  

<table>
    <thead>
        <tr>
            <th>Метод</th>
            <th>Описание</th>
        </tr>
    </thead>
    <tbody>
        <tr>
            <th>Конструктор</th>
            <th>Создает и инициализирует объект «Студент»,= с использованием указанного имени (name), фамилии (surname) и отчества (patronymic), а также возраста.
                <br>В качестве отчества допускается пустая строка.
                <br>При недопустимом ФИО должно выбрасываться исключение std::invalid_argument. При недопустимом возрасте должно выбрасываться исключение std::out_of_range</th>
        </tr>
        <tr>
            <th>GetName</th>
            <th>Возвращает имя студента</th>
        </tr>
        <tr>
            <th>GetSurname</th>
            <th>Возвращает фамилию студента</th>
        </tr>
        <tr>
            <th>GetPatronymic</th>
            <th>Возвращает отчество студента</th>
        </tr>
        <tr>
            <th>GetAge</th>
            <th>Возвращает возраст студента</th>
        </tr>
        <tr>
            <th>Rename(name, surname, patronymic)</th>
            <th>Переименовывает студента. На ФИО налагаются ограничения, описанные выше. Не забудьте обеспечить семантику выполнения commit-or-rollback при выбрасывании исключения (в том числе и std::bad_alloc при нехватке памяти)</th>
        </tr>
        <tr>
            <th>SetAge(age)</th>
            <th>Изменяет возраст студента. Возраст не может быть изменен в
                сторону уменьшения (при нарушении бросать std::domain_error).
                <br>При выходе за пределы диапазона от 14 до 60, выбрасывать
                исключение std::out_of_range</th>
        </tr>
    </tbody>
</table>

<span style="color:red">Для класса CStudent должен быть разработан набор автоматических тестов, проверяющих работу его методов и конструктора как на корректных, так и некорректных наборах данных. Рекомендуется использование библиотек и фреймворков для написания тестов, например, [boost::test](https://www.boost.org/doc/libs/1_55_0/libs/test/doc/html/index.html), [Google Test](https://github.com/google/googletest), CxxTest и других. Без тестов работа будет принята с коэффициентом не выше 0.3.</span>

#### Вариант 7 – HTTP URL – 100 баллов

Разработайте класс `CHttpUrl`, выполняющий хранение http и https – URL-ов. В конструкторе класса должны осуществляться проверка валидности входных параметров.

Каркас класса:

```cpp
enum class Protocol
{
    HTTP,
    HTTPS
};

class CUrlParsingError : public std::invalid_argument
{
public:
    …
};

class CHttpUrl
{
public:
    // выполняет парсинг строкового представления URL-а, в случае ошибки парсинга
    // выбрасывает исключение CUrlParsingError, содержащее текстовое описание ошибки
    CHttpUrl(std::string const& url);

    /* инициализирует URL на основе переданных параметров.
        При недопустимости входных параметров выбрасывает исключение
        std::invalid_argument
        Если имя документа не начинается с символа /, то добавляет / к имени документа
    */
    CHttpUrl(
        std::string const& domain, 
        std::string const& document, 
        Protocol protocol = HTTP);

    /* инициализирует URL на основе переданных параметров.
        При недопустимости входных параметров выбрасывает исключение
        std::invalid_argument
        Если имя документа не начинается с символа /, то добавляет / к имени документа
    */
    CHttpUrl(
        std::string const& domain, 
        std::string const& document, 
        Protocol protocol,
        Unsigned short port);

    // возвращает строковое представление URL-а. Порт, являющийся стандартным для
    // выбранного протокола (80 для http и 443 для https) в эту строку
    // не должен включаться
    std::string GetURL()const;

    // возвращает доменное имя
    std::string GetDomain()const;

    /* 
        Возвращает имя документа. Примеры: 
            /
            /index.html
            /images/photo.jpg
    */
    std::string GetDocument()const;

    // возвращает тип протокола
    Protocol GetProtocol()const;

    // возвращает номер порта
    unsigned short GetPort()const;
};
```

**Классы CUrlParsingError и CHttpUrl должны располагаться в разных парах .h/.cpp файлов.**

Конструктор класса должен анализировать входные параметры и выбрасывать нужный тип исключений в случае ошибок.

На основе данного класса напишите приложение, считывающее со стандартного потока ввода URL-ы и выводящее информацию об URL-е в стандартный поток вывода, пока не встретит символ конца файла. Исключения, выбрасываемые классом должны перехватываться программой, и в стандартный поток вывода должна выводиться информация об ошибке обработки URL-а.

<span style="color:red">Для класса CHttpUrl должен быть разработан набор автоматических тестов, проверяющих работу его методов и конструктора как на корректных, так и некорректных наборах данных. Рекомендуется использование библиотек и фреймворков для написания тестов, например, [boost::test](https://www.boost.org/doc/libs/1_55_0/libs/test/doc/html/index.html), [Google Test](https://github.com/google/googletest), CxxTest и других. Без тестов работа будет принята с коэффициентом не выше 0.3.</span>

Требования

- Регистр записи символов протокола URL значения не имеет. HtTps и https — это валидные URL-ы.
- Допустимые значения портов: от 1 до 65535 включительно.

## Дополнительные задания

### Задание 2

#### Вариант 1 – StringStack - 150 баллов

Реализуйте класс `CStringStack`, реализующий стек строк. Для хранения данных стек должен использовать **динамический массив** (реализовать своими силами), либо односвязный список. Определите набор непредвиденных ситуаций и соответствующие им исключения, которые должны выбрасываться классом в случае ошибок. Методы класса должны предоставлять **уровень безопасности исключений не ниже строгого**, а деструктор – гарантировать отсутствие исключений. На защите лабораторной работы необходимо обосновать предоставление классом данных гарантий безопасности исключений. У класса должны быть конструкторы копирования и перемещения, а также операторы присваивания (копирующий и перемещающий). Операции перемещения должны гарантировать отсутствие исключений, а конструктор копирования и копирующий оператор присваивания – обеспечивать строгую гарантию безопасности исключений.

<span style="color:red">Для класса CStringStack должен быть разработан набор автоматических тестов, проверяющих работу его методов и конструктора как на корректных, так и некорректных наборах данных. Рекомендуется использование библиотек и фреймворков для написания тестов, например, [boost::test](https://www.boost.org/doc/libs/1_55_0/libs/test/doc/html/index.html), [Google Test](https://github.com/google/googletest), CxxTest и других. Без тестов работа будет принята с коэффициентом не выше 0.3.</span>

#### Вариант 2 – StringList - 300 баллов

Реализуйте класс `CStringList`, реализующий двусвязный список строк. Список должен предоставлять следующие операции:

- Конструкторы: по умолчанию, копирования и перемещения
- Операторы присваивания (копирующий и перемещающий)
- Деструктор
- Добавление строки в начало и в конец списка (за время O(1))
- Узнать количество элементов (за время O(1)), а также узнать пуст список или нет
- Удалить все элементы из списка (за время О(N) с использованием памяти O(1) в области стека)
- Вставка элемента в позицию, задаваемую итератором (за время О(1))
- Удаление элемента в позиции, задаваемой итератором (за время О(1))
- Получение итераторов, указывающих на начало списка и его конец (константные и некостантные), совместимых со алгоритмами STL и range-based for
- Реверсированные итераторы (константные и неконстантные)

Все операции над списком должны предоставлять уровень безопасности исключений не ниже строгого, а деструктор гарантировать отсутствие исключений.

Разрешается использовать умные указатели для хранения структуры данных списка. **Убедиться, что деструктор класса и метод Clear не используют неявным образом рекурсию** (в противном случае удаление списка с большим количеством элементов приведет к переполнению стека).

<span style="color:red">Для класса CStringList должен быть разработан набор автоматических тестов, проверяющих работу его методов и конструктора как на корректных, так и некорректных наборах данных. Рекомендуется использование библиотек и фреймворков для написания тестов, например, [boost::test](https://www.boost.org/doc/libs/1_55_0/libs/test/doc/html/index.html), [Google Test](https://github.com/google/googletest), CxxTest и других. Без тестов работа будет принята с коэффициентом не выше 0.3.</span>
