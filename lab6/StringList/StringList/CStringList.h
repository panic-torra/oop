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

private:
	size_t m_size = 0;
	std::unique_ptr<CNode> m_firstNode;
	CNode * m_lastNode = nullptr;
};