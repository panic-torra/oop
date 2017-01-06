#pragma once

#include <new>
#include <algorithm>

template <typename T>
class CMyArray
{
public:
	CMyArray() = default;

	CMyArray(const CMyArray & arr)
	{
		const auto size = arr.GetSize();
		if (size != 0)
		{
			m_begin = RawAlloc(size);
			try
			{
				CopyItems(arr.m_begin, arr.m_end, m_begin, m_end);
				m_endOfCapacity = m_end;
			}
			catch (...)
			{
				DeleteItems(m_begin, m_end);
				throw;
			}
		}
	}

	CMyArray(CMyArray && arr) 
		: m_array(arr.m_array)
		, m_begin(arr.m_begin)
		, m_end(arr.m_end)
		, m_endOfCapacity(arr.m_endOfCapacity)
	{
	}

	void Append(const T & value)
	{
		if (m_end == m_endOfCapacity)
		{
			size_t newCapacity = std::max(1u, GetCapacity() * 2);

			auto newBegin = RawAlloc(newCapacity);
			T *newEnd = newBegin;
			try
			{
				CopyItems(m_begin, m_end, newBegin, newEnd);
				// Конструируем копию value по адресу newItemLocation
				new (newEnd)T(value);
				++newEnd;
			}
			catch (...)
			{
				DeleteItems(newBegin, newEnd);
				throw;
			}
			DeleteItems(m_begin, m_end);

			// Переключаемся на использование нового хранилища элементов
			m_begin = newBegin;
			m_end = newEnd;
			m_endOfCapacity = m_begin + newCapacity;
		}
		else
		{
			new (m_end) T(value);
			++m_end;
		}
	}

	T & GetBack()
	{
		assert(GetSize() != 0u);
		return m_end[-1];
	}

	const T & GetBack()const
	{
		assert(GetSize() != 0u);
		return m_end[-1];
	}

	size_t GetSize()const
	{
		return m_end - m_begin;
	}

	size_t GetCapacity()const
	{
		return m_endOfCapacity - m_begin;
	}

	void Resize(const size_t newSize)
	{
		size_t currSize = GetSize();
		for (; currSize > newSize; --currSize)
		{
			m_end->~T();
			m_end--;
		}

		for (; currSize < newSize; ++currSize)
		{
			Append(T());
		}
	}

	void Clear()
	{
		if (GetSize() != 0)
		{
			DestroyItems(m_begin, m_end);
			m_end = m_begin;
			m_endOfCapacity = m_begin;
		}
	}

	T & operator[](const size_t index)
	{
		if (index >= GetSize())
		{
			throw std::out_of_range("Index >= size of array");
		}

		return m_begin[index];
	}

	T & operator[](const size_t index)const
	{
		if (index >= GetSize())
		{
			throw std::out_of_range("Index >= size of array");
		}

		return m_begin[index];
	}

	CMyArray & operator = (const CMyArray & scr)
	{
		if (&scr != this)
		{
			CMyArray tmp(scr);

			std::swap(m_begin, tmp.m_begin)
				std::swap(m_end, tmp.m_end);
			std::swap(m_endOfCapacity, tmp.m_endOfCapacity);
			std::swap(m_array, tmp.m_array);
		}

		return *this;
	}

	CMyArray & operator = (CMyArray && tmp)
	{
		std::move(m_begin, tmp.m_begin);
		std::move(m_end, tmp.m_end);
		std::move(m_endOfCapacity, tmp.m_endOfCapacity);
		std::move(m_array, tmp.m_array);

		return *this;
	}

	/*CMyIterator<T> begin()
	{
		return CMyIterator<T>(m_array.get());
	}

	CMyIterator<T> end()
	{
		return CMyIterator<T>(m_array.get() + GetSize());
	}

	const CMyIterator<const T> cbegin() const
	{
		return const_iterator(m_array.get());
	}
	const CMyIterator<const T> cend() const
	{
		return const_iterator(m_array.get() + GetSize());
	}

	CMyIterator<T> rbegin()
	{
		return iterator(m_array.get() + GetSize() - 1);
	}
	CMyIterator<T> rend()
	{
		return iterator(m_array.get() - 1, true);
	}

	const CMyIterator<const T> crbegin() const
	{
		return const_iterator(m_array.get() + GetSize() - 1);
	}
	const CMyIterator<const T> crend() const
	{
		return const_iterator(m_array.get() - 1);
	}*/

	~CMyArray()
	{
		DeleteItems(m_begin, m_end);
	}
private:
	static void DeleteItems(T *begin, T *end)
	{
		// Разрушаем старые элементы
		DestroyItems(begin, end);
		// Освобождаем область памяти для их хранения
		RawDealloc(begin);
	}

	// Копирует элементы из текущего вектора в to, возвращает newEnd
	static void CopyItems(const T *srcBegin, T *srcEnd, T * const dstBegin, T * & dstEnd)
	{
		for (dstEnd = dstBegin; srcBegin != srcEnd; ++srcBegin, ++dstEnd)
		{
			// Construct "T" at "dstEnd" as a copy of "*begin"
			new (dstEnd)T(*srcBegin);
		}
	}

	static void DestroyItems(T *from, T *to)
	{
		// dst - адрес объект, при конструирование которого было выброшено исключение
		// to - первый скорнструированный объект
		while (to != from)
		{
			--to;
			to->~T();
		}
	}

	static T *RawAlloc(size_t n)
	{
		size_t memSize = n * sizeof(T);
		T *p = static_cast<T*>(malloc(memSize));
		if (!p)
		{
			throw std::bad_alloc();
		}
		return p;
	}

	static void RawDealloc(T *p)
	{
		free(p);
	}

private:
	T *m_begin = nullptr;
	T *m_end = nullptr;
	T *m_endOfCapacity = nullptr;
	std::unique_ptr<T[]> m_array;
};