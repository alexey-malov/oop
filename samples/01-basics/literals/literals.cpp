#include <iostream>
#include <string>

void main()
{
	char letterA = 'A';
	char eol = '\n';

	// Символы, вроде " и \ внутри строковых литералов необходимо экранировать
	std::string filePath = "c:\\path\\to\\file.txt";

	// Либо использовать raw string literals
	std::string filePath1 = R"(c:\path\to\file.txt)";

	// Можно сцеплять несколько строковых литералов в один
	std::string multiLineString =
		"<html>\n"
		"\t<body>\n"
		"\t\t<p style=\"color:red;\"></p>"
		"\t</body>"
		"</html>";

	// При помощи raw string literal можно упростить задание строк, содержащих спецсимволы
	std::string htmlPage = R"marker(<html>
	<body>
		<p style="color:red;">Hello, world</p>
	</body>
</html>)marker";
}