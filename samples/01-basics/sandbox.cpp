// Возвращает копию строки str, в которой буквы приведены к нижнему регистру.
// Например, ToLowercase("Hello"s) вернёт строку "hello".
std::string ToLowercase(/* std::string */ str) {
    for (char& ch : str) {
        // Функция std::tolower приводит символ к нижнему регистру.
        ch = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
    }
    return str;
}