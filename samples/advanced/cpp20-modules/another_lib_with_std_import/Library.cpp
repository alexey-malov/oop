module library;

Book::Book(std::string title, std::string author)
	: m_title{ std::move(title) }
	, m_author{ std::move(author) }
{
}
