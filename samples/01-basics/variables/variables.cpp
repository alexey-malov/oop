#include "variables.h"

// Глобальная переменная. Из других файлов к ней можно обратиться объявив ее внешней (extern)
int globalVariableDeclaredInVariablesCpp = 12345;

// Еще одна глобальная переменная. В файле variable.h она объявлена как extern
int someOtherGlobalVariableDeclaredInVariablesCpp = 54321;

// Статическая глобальная переменная. Ее область видимости - текущий .cpp файл
// В разных .cpp файлах одной и той же программы могут быть объявлены разные статические глобальные переменные. Они будут полностью изолированы друг от друга
static int staticVariable = 66;
