#pragma once
#include <string>
#include <memory>

class CStringList
{
	class CNode
	{
	public:
		CNode(const std::string & data, CNode * prev, std::unique_ptr<CNode> && next);
		std::string data;
		CNode * prev;
		std::unique_ptr<CNode> next;
	};

public:
	CStringList() = default;
	CStringList(const CStringList & list);
	CStringList(CStringList && list);
	CStringList(const size_t n);

	void append(const std::string & data);
	void append(std::string && data);

	void push_back(const std::string & data);
	void push_back(std::string && data);

	void push_front(const std::string & data);
	void push_front(std::string && data);

	size_t size() const;
	bool empty() const;

private:
	size_t m_size = 0;
	std::unique_ptr<CNode> m_firstNode;
	CNode * m_lastNode = nullptr;
};