export module library;

import std;

export class Book
{
public:
	explicit Book(std::string title, std::string author);

	const std::string& GetTitle() const noexcept { return m_title; }

private:
	std::string m_title;
	std::string m_author;
};

