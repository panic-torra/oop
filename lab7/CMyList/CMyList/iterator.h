#pragma once

#include <iterator>

template<typename T>
class CMyIterator : public std::iterator<std::random_access_iterator_tag, T>
{
	template <typename> friend class CMyArray;

public:
	CMyIterator() = default;
	CMyIterator(T *p)
		: m_ptr(p)
	{}

	T & CMyIterator<T>::operator*() const
	{
		return *m_ptr;
	}

	CMyIterator<T> &CMyIterator<T>::operator++()
	{
		(m_reverse) ? --m_ptr : ++m_ptr;

		return *this;
	}

	CMyIterator<T> &CMyIterator<T>::operator--()
	{

		return *this;
	}

	bool CMyIterator<T>::operator==(CMyIterator const & rhs) const
	{
		return m_ptr == rhs.m_ptr;
	}
private:
	T *m_ptr;
	bool m_reverse;
};