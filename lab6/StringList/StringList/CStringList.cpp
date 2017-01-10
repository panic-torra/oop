#include "stdafx.h"
#include "CStringList.h"

CStringList::CNode::CNode(const std::string & data, CNode * prev, std::unique_ptr<CNode> && next)
	:data(data)
	, prev(prev)
	, next(std::move(next))
{
}

size_t CStringList::size() const
{
	return m_size;
}

bool CStringList::empty() const
{
	return (m_size == 0);
}

void CStringList::append(const std::string & data)
{
	auto newNode = std::make_unique<CNode>(data, m_lastNode, nullptr);
	auto * newLastNode = newNode.get();
	if (m_lastNode)
	{
		m_lastNode->next = move(newNode);
	}
	else
	{
		m_firstNode = move(newNode);
	}
	m_lastNode = newLastNode;
	++m_size;
}

void CStringList::append(std::string && data)
{
	auto newNode = std::make_unique<CNode>(std::move(data), m_lastNode, nullptr);
	auto * newLastNode = newNode.get();
	if (m_lastNode)
	{
		m_lastNode->next = move(newNode);
	}
	else
	{
		m_firstNode = move(newNode);
	}
	m_lastNode = newLastNode;
	++m_size;
}