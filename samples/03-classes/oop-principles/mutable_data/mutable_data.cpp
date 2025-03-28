#include <chrono>
#include <functional>
#include <iostream>
#include <string>

size_t GetHash(const std::string& s)
{
	std::hash<std::string> hasher;
	return hasher(s);
}

class PasswordCracker
{
public:
	std::string CrackPassword(size_t hash, size_t maxChars) const
	{
		if (auto it = m_passwordCache.find(hash); it != m_passwordCache.end())
			return it->second;
		std::string prefix;
		return CrackPassword(prefix, hash, maxChars);
	}

private:
	std::string CrackPassword(std::string& prefix, size_t hash, size_t maxChars) const
	{
		if (GetHash(prefix) == hash)
		{
			m_passwordCache.emplace(hash, prefix);
			return prefix; // Пароль найден
		}
		if (maxChars == 0)
			return {}; // Пароль не найден, перебор закончен

		for (char ch = 'A'; ch <= 'Z'; ++ch)
		{
			prefix += ch;
			if (auto pass = CrackPassword(prefix, hash, maxChars - 1); !pass.empty())
				return pass;
			prefix.pop_back();
		}
		return {};
	}
	mutable std::unordered_map<size_t, std::string> m_passwordCache;
};

using Clock = std::chrono::high_resolution_clock;
using Seconds = std::chrono::duration<double>;

int main()
{
	PasswordCracker cracker;

	// Первый раз ищем долго

	cracker.CrackPassword(GetHash("HELLO"), 5);
	const auto start = Clock::now();
	auto password = cracker.CrackPassword(GetHash("HELLO"), 5);
	const auto end = Clock::now();

	if (!password.empty())
	{
		std::cout << "Cracked password: " << password << "\n";
		std::cout << "Time elapsed: " << Seconds(end - start).count() << "s\n";
	}
	else
	{
		std::cout << "Failed to crack password\n";
	}
}
