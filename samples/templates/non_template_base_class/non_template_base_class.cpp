#include <exception>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>

class ResultBase
{
public:
	void SetException(std::exception_ptr e) noexcept
	{
		m_exception = e;
	}
	bool HasException() const noexcept
	{
		return m_exception != nullptr;
	}
	std::exception_ptr TryGetException() const noexcept
	{
		return m_exception;
	}

protected:
	ResultBase(std::exception_ptr e) noexcept
		: m_exception(e)
	{
	}
	ResultBase() noexcept = default;

private:
	std::exception_ptr m_exception;
};

template <typename T>
class Result : public ResultBase
{
public:
	explicit Result(std::exception_ptr e) noexcept
		: ResultBase(e)
	{
	}

	explicit Result(T value) noexcept
		: m_value(std::move(value))
	{
	}

	explicit operator bool() const noexcept
	{
		return HasValue();
	}

	bool HasValue() const noexcept
	{
		return m_value.has_value();
	}

	const T& GetValue() const
	{
		if (auto e = TryGetException())
		{
			std::rethrow_exception(e);
		}
		if (!m_value)
		{
			throw std::runtime_error("Value is not set");
		}
		return *m_value;
	}

private:
	std::optional<T> m_value;
};

Result<int> ReadInt()
{
	int value;
	if (std::cin >> value)
	{
		return Result<int>(value);
	}
	else
	{
		return Result<int>(std::make_exception_ptr(
			std::runtime_error("Failed to read integer")));
	}
}

int main()
{
	if (auto result = ReadInt())
	{
		std::cout << "Read value: " << result.GetValue() << '\n';
	}
	else
	{
		// Handle error
	}
}
