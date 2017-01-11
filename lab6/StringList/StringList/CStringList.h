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
		CIterator operator--(int);
		CIterator operator++(int);
		Node * operator->() const;

		bool operator==(CIterator const & rhs) const;
		bool operator!=(CIterator const & rhs) const;

	private:
		Node * m_node = nullptr;
		bool m_isReverse = false;
	};

	CStringList() = default;
	CStringList(CStringList & list);
	CStringList(CStringList && list);
	~CStringList();

	size_t GetSize() const;
	bool IsEmpty() const;

	void Append(std::string const & data);
	void PushFront(std::string const & data);

	void Insert(CIterator const  & it, std::string const & data);
	void Erase(CIterator const & it);

	void Clear();

	CIterator begin();
	CIterator end();
	CIterator const begin() const;
	CIterator const end() const;
	CIterator const cbegin() const;
	CIterator const cend() const;

	CIterator rbegin();
	CIterator rend();
	CIterator const rbegin() const;
	CIterator const rend() const;
	CIterator const crbegin() const;
	CIterator const crend() const;

	std::string const & GetBackElement() const;
	std::string const & GetFrontElement() const;

private:
	size_t m_size = 0;
	std::unique_ptr<Node> m_firstNode;
	Node * m_lastNode = nullptr;
};