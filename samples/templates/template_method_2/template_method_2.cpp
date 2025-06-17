#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

class Config
{
public:
	void SetValue(const std::string& key, const std::string& value)
	{
		m_data[key] = value;
	}

	// Сохраняет значение произвольного типа в виде строки по ключу
	template <typename T>
	void SetValue(const std::string& key, const T& value)
	{
		std::ostringstream oss;
		oss << value;
		m_data[key] = oss.str();
	}

	// Получает значение по ключу и преобразует его в указанный тип
	template <typename T>
	T GetValue(const std::string& key) const
	{
		std::istringstream iss(m_data.at(key));
		T result;
		if (!(iss >> result))
			throw std::runtime_error("Failed to convert value for key: " + key);
		return result;
	}

private:
	std::unordered_map<std::string, std::string> m_data;
};

int main()
{
	Config config;
	config.SetValue("Threads", 4);
	config.SetValue("Threshold", 0.75);
	config.SetValue("User", std::string("Alice"));

	int threads = config.GetValue<int>("Threads");
	double threshold = config.GetValue<double>("Threshold");
	std::string user = config.GetValue<std::string>("User");

	std::cout << "Threads: " << threads
			  << ", Threshold: " << threshold
			  << ", User: " << user << '\n';
}
