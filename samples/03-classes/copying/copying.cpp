// copying.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

class PostCard
{
public:
	PostCard(const std::string& text)
		: m_text{ text }
	{
		std::cout << "Post card was created: " << m_text << std::endl;
	}
	// Копирующий конструктор
	PostCard(const PostCard& other)
		: m_text{ other.m_text }
	{
		std::cout << "Post card is copied: " << m_text << std::endl;
	}
	~PostCard() { std::cout << "Post card was destroyed: " << m_text << std::endl; }

	const std::string& GetText() const { return m_text; }

	void SetText(const std::string& text) { m_text = text; }

private:
	std::string m_text;
};

PostCard MakeModifiedPostCard(PostCard postCard) {
	std::cout << "Enter MakeModifiedPostCard" << std::endl;
	postCard.SetText(postCard.GetText() + " - modified");
	std::cout << "Exit MakeModifiedPostCard" << std::endl;
	return postCard;
}

struct Envelope
{
	PostCard postCard;
};

Envelope MakeModifiedPostcardInEnvelope(Envelope envelope)
{
	std::cout << "Enter MakeModifiedPostCard" << std::endl;
	envelope.postCard.SetText(envelope.postCard.GetText() + " - modified");
	std::cout << "Exit MakeModifiedPostCard" << std::endl;
	return envelope;
}

int main()
{
#if 0
	PostCard postCard{ "Hello" };
	auto modifiedPostCard = MakeModifiedPostCard(postCard);
	std::cout << modifiedPostCard.GetText() << std::endl;
#endif

	Envelope env{.postCard = "Hello" };
	auto modifiedEnv = MakeModifiedPostcardInEnvelope(env);
	std::cout << modifiedEnv.postCard.GetText() << std::endl;
}
