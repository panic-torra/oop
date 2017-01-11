#include "stdafx.h"
#include "CStringList.h"

CStringList::Node::Node(std::string const & data, Node * prev, std::unique_ptr<Node> && next)
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

CStringList::~CStringList()
{
	Clear();
}

bool CStringList::CIterator::operator==(CStringList::CIterator const & rhs) const
{
	return m_node == rhs.m_node;
}

bool CStringList::CIterator::operator!=(CStringList::CIterator const & rhs) const
{
	return m_node != rhs.m_node;
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

std::string & CStringList::CIterator::operator*() const
{
	return m_node->data;
}

CStringList::Node * CStringList::CIterator::operator->() const
{
	return m_node;
}

CStringList::CIterator CStringList::begin()
{
	return CIterator(m_firstNode.get());
}

CStringList::CIterator CStringList::end()
{
	return (m_size == 0) ? begin() : CIterator(m_lastNode->next.get());
}

CStringList::CIterator const CStringList::cbegin() const
{
	return CIterator(m_firstNode.get());
}

CStringList::CIterator const CStringList::cend() const
{
	return (m_size == 0) ? cbegin() : CIterator(m_lastNode->next.get());
}

CStringList::CIterator CStringList::rbegin()
{
	return CIterator(m_lastNode, true);
}

CStringList::CIterator CStringList::rend()
{
	return (m_size == 0) ? rbegin() : CIterator(m_firstNode->prev, true);
}

CStringList::CIterator const CStringList::crbegin() const
{
	return CIterator(m_lastNode, true);
}

CStringList::CIterator const CStringList::crend() const
{
	return (m_size == 0) ? crbegin() : CIterator(m_firstNode->prev, true);
}

size_t CStringList::GetSize() const
{
	return m_size;
}

bool CStringList::IsEmpty() const
{
	return (m_size == 0);
}

void CStringList::Append(std::string const & data)
{
	auto newNode = std::make_unique<Node>(data, m_lastNode, nullptr);
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

void CStringList::PushFront(std::string const & data)
{
	auto newNode = std::make_unique<Node>(data, nullptr, move(m_firstNode));
	if (newNode->next)
	{
		newNode->next->prev = newNode.get();
	}
	else
	{
		m_lastNode = newNode.get();
	}
	m_firstNode = std::move(newNode);
	m_firstNode->prev = nullptr;
	++m_size;
}

void CStringList::Insert(CIterator const  & it, std::string const & data)
{
	if (it == begin())
	{
		PushFront(data);
	}
	else if (it == end())
	{
		Append(data);
	}
	else
	{
		auto node = std::make_unique<CStringList::Node>(data, it->prev, move(it->prev->next));
		it->prev = std::move(node.get());
		node->prev->next = move(node);
		++m_size;
	}
}

void CStringList::Erase(CIterator const & it)
{
	if (m_size != 0)
	{
		if (m_size == 1)
		{
			Clear();
			return;
		}

		if (it == begin())
		{
			m_firstNode = std::move(m_firstNode->next);
			m_firstNode->prev = nullptr;
		}
		else if (it.m_node == m_lastNode)
		{
			m_lastNode = std::move(it->prev);
			m_lastNode->next = nullptr;
		}
		else
		{
			it->next->prev = std::move(it->prev);
			it->prev->next = std::move(it->next);
		}
		
		--m_size;

	}
	else
	{
		throw std::out_of_range("StringList is already empty");
	}
}

std::string & CStringList::GetBackElement()
{
	return m_lastNode->data;
}

std::string const & CStringList::GetBackElement() const
{
	return m_lastNode->data;
}

std::string & CStringList::GetFrontElement()
{
	return m_firstNode->data;
}

std::string const & CStringList::GetFrontElement() const
{
	return m_firstNode->data;
}

void CStringList::Clear()
{
	m_lastNode = nullptr;
	m_firstNode = nullptr;
	m_size = 0;
}

