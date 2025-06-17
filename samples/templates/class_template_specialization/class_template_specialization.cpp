#include <cassert>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>

// Первичный шаблон
template <typename T>
struct IsIntegral
{
	// Тип не является целочисленным
	static inline const bool value = false;
};
// Вспомогательная константа для проверки целочисленных типов
template <typename T>
inline constexpr bool IsIntegralV = IsIntegral<T>::value;

// Базовый класс для IsIntegral-специализаций для целочисленных типов
struct IsIntegralTrue
{
	static inline const bool value = true;
};
template <>
struct IsIntegral<unsigned> : IsIntegralTrue
{
};
template <>
struct IsIntegral<int> : IsIntegralTrue
{
};

template <typename T>
void Print(T value)
{
	if constexpr (IsIntegralV<T>)
	{
		std::cout << std::hex << "0x";
	}
	std::cout << value;
	if constexpr (IsIntegralV<T>)
	{
		std::cout << std::dec;
	}
	std::cout << "\n";
}

enum class BuiltinConfigParam
{
	Login,
	Password,
	Timeout,
};

namespace detail
{

// Первичный шаблон для характеристик типов параметров конфигурации
template <BuiltinConfigParam param>
struct BuiltinConfigParamTraits
{
	// Пустая характеристика типов в первичном шаблоне нужна,
	// так как она имеет смысл только для специализаций
};

// Специализация характеристики типов для параметра Login
template <>
struct BuiltinConfigParamTraits<BuiltinConfigParam::Login>
{
	static constexpr const char* name = "Login";
	using value_type = std::string; // Логин хранится в виде строки
};

// Специализация характеристики типов для параметра Password
template <>
struct BuiltinConfigParamTraits<BuiltinConfigParam::Password>
{
	static constexpr const char* name = "Password";
	using value_type = std::string; // Пароль хранится в виде строки
};

// Специализация характеристики типов для параметра Timeout
template <>
struct BuiltinConfigParamTraits<BuiltinConfigParam::Timeout>
{
	static constexpr const char* name = "Timeout";
	using value_type = int; // Таймаут задаётся целым числом
};

template <typename T>
std::string ToString(const T& value)
{
	std::ostringstream oss;
	oss << value;
	return oss.str();
}

template <>
std::string ToString<std::string>(const std::string& value)
{
	return value; // Для std::string просто возвращаем значение
}

template <typename T>
T FromString(const std::string& str)
{
	std::istringstream iss(str);
	T value;
	if (!(iss >> value))
	{
		throw std::runtime_error("Failed to convert string to value");
	}
	return value;
}

template <>
std::string FromString<std::string>(const std::string& str)
{
	return str; // Для std::string просто возвращаем значение
}

} // namespace detail

class Config
{
public:
	template <BuiltinConfigParam param>
	void SetBuiltinParam(typename detail::BuiltinConfigParamTraits<param>::value_type value)
	{
		using detail::ToString;
		m_params[detail::BuiltinConfigParamTraits<param>::name] = ToString(value);
	}

	template <BuiltinConfigParam param>
	typename detail::BuiltinConfigParamTraits<param>::value_type GetBuiltinParam() const
	{
		using detail::FromString;
		const auto paramName = detail::BuiltinConfigParamTraits<param>::name;
		using ParamValueType = typename detail::BuiltinConfigParamTraits<param>::value_type;
		if (auto it = m_params.find(paramName); it != m_params.end())
		{
			return FromString<ParamValueType>(it->second);
		}
		throw std::runtime_error("Parameter not found: " + std::string(paramName));
	}

	void SetParam(std::string name, std::string value)
	{
		m_params[std::move(name)] = std::move(value);
	}
	const std::string& GetParam(const std::string& name) const
	{
		if (auto it = m_params.find(name); it != m_params.end())
		{
			return it->second;
		}
		throw std::runtime_error("Parameter not found: " + name);
	}

private:
	std::unordered_map<std::string, std::string> m_params;
};

int main()
{
	static_assert(IsIntegralV<float> == false);
	static_assert(IsIntegralV<int> == true);
	static_assert(IsIntegralV<unsigned> == true);
	Print(100);
	Print(10.5);

	Config cfg;
	cfg.SetParam("Timeout", "42");
	assert(cfg.GetBuiltinParam<BuiltinConfigParam::Timeout>() == 42);
	cfg.SetBuiltinParam<BuiltinConfigParam::Login>("user");
	assert(cfg.GetParam("Login") == "user");
}
