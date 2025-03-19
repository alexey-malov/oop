#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

int main()
{
	auto currentPath = fs::current_path();
	std::cout << currentPath << "\n";
	std::cout << currentPath.string() << "\n";
	std::cout << currentPath.generic_string() << "\n";
	auto parent = currentPath.parent_path();
	std::cout << parent << "\n";
	std::cout << currentPath.filename() << "\n";
	auto textFile = parent / "file.txt";
	std::cout << textFile << "\n";
	std::cout << textFile.stem() << "\n";
	std::cout << textFile.extension() << "\n";
	textFile.replace_extension("dat");
	std::cout << textFile << "\n";
	std::cout << "---\n";
	for (auto entry : fs::recursive_directory_iterator(currentPath))
	{
		std::cout << entry.path() << "\n";
	}
}
