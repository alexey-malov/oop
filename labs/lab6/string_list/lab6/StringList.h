#pragma once

#include <string>
#include <memory>

class CStringList
{
	struct Node
	{
		Node(const std::string & data, Node * prev, std::unique_ptr<Node> && next)
			: data(data), prev(prev), next(std::move(next))
		{
		}
		std::string data;
		Node *prev;
		std::unique_ptr<Node> next;
	};
public:
	size_t GetSize()const;
	void Append(const std::string& data);

	class CIterator
	{
		friend CStringList;
		CIterator(Node *node);
	public:
		CIterator() = default;
		std::string & operator*()const;
		CIterator & operator++();
	private:
		Node *m_node = nullptr;
	};

	CIterator begin();

	std::string & GetBackElement();
	std::string const& GetBackElement()const;
private:
	size_t m_size = 0;
	std::unique_ptr<Node> m_firstNode;
	Node * m_lastNode = nullptr;
};