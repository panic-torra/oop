#pragma once
#include <string>
#include <memory>

class CStringList
{
	class Node
	{
	public:
		Node(std::string const & data, Node * prev, std::unique_ptr<Node> && next);
		std::string data;
		Node * prev;
		std::unique_ptr<Node> next;
	};

public:
	class CIterator
	{
		friend CStringList;
	public:
		CIterator() = default;
		CIterator(Node * node);
		CIterator(Node * node, bool isReverse);

		std::string & operator*() const;
		CIterator & operator--();
		CIterator & operator++();

	private:
		Node * m_node = nullptr;
		bool m_isReverse = false;
	};

	CStringList() = default;
	CStringList(CStringList & list);
	CStringList(CStringList && list);

	size_t GetSize() const;
	bool IsEmpty() const;

	void Append(std::string const & data);
	void Append(std::string && data);

	void PushFront(std::string const & data);
	void PushFront(std::string && data);

	void Insert(CIterator const  & it, std::string const & data);
	void Erase(CIterator const & it);

	CIterator begin();
	CIterator end();
	CIterator const cbegin() const;
	CIterator const cend() const;

	CIterator rbegin();
	CIterator rend();
	CIterator const crbegin() const;
	CIterator const crend() const;

	std::string & GetBackElement();
	std::string const & GetBackElement() const;
	std::string & GetFrontElement();
	std::string const & GetFrontElement() const;

private:
	size_t m_size = 0;
	std::unique_ptr<Node> m_firstNode;
	Node * m_lastNode = nullptr;


	void AppendImpl(std::unique_ptr<CStringList::Node> & newNode);
};

bool operator==(const CStringList & lhs, const CStringList & rhs);