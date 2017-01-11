#include "stdafx.h"
#include "CStringList.h"

CStringList::Node::Node(const std::string & data, Node * prev, std::unique_ptr<Node> && next)
	:data(data)
	, prev(prev)
	, next(std::move(next))
{
}

CStringList::CIterator::CIterator(Node * node)
	:m_node(node)
{
}

CStringList::CIterator::CIterator(Node * node, bool isReverse)
	:m_node(node)
	, m_isReverse(isReverse)
{
}


CStringList::CStringList(CStringList & list)
{
	m_size = list.m_size;
	m_firstNode = std::move(list.m_firstNode);
	m_lastNode = list.m_lastNode;
}

CStringList::CStringList(CStringList && list)
{
	m_size = list.m_size;
	m_firstNode = std::move(list.m_firstNode);
	m_lastNode = std::move(list.m_lastNode);

	list.m_size = 0;
}

CStringList::CIterator & CStringList::CIterator::operator--()
{
	m_node = (!m_isReverse) ? (m_node->prev) : (m_node->next.get());
	return *this;
}

CStringList::CIterator & CStringList::CIterator::operator++()
{
	m_node = (!m_isReverse) ? (m_node->next.get()) : (m_node->prev);
	return *this;
}

CStringList::CIterator CStringList::begin()
{
	return CIterator(m_firstNode.get());
}

size_t CStringList::GetSize() const
{
	return m_size;
}

bool CStringList::IsEmpty() const
{
	return (m_size == 0);
}

void CStringList::Append(const std::string & data)
{
	auto newNode = std::make_unique<Node>(data, m_lastNode, nullptr);
	AppendImpl(newNode);
}

void CStringList::Append(std::string && data)
{
	auto newNode = std::make_unique<Node>(std::move(data), m_lastNode, nullptr);
	AppendImpl(newNode);
}

void  CStringList::AppendImpl(std::unique_ptr<CStringList::Node> & newNode)
{
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

//bool operator==(const CStringList & lhs, const CStringList & rhs)
//{
//	if (lhs.GetSize() == rhs.GetSize())
//	{
//		auto itr = rhs.begin();
//		for (auto itl = lhs.begin(); itl != lhs.end(); ++itl, ++itr)
//		{
//			if (*itl != *itr)
//			{
//				return false;
//			}
//		}
//		return true;
//	}
//	return false;
//}
