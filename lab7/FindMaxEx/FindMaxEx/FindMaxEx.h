#pragma once

template <class T, class Less>
bool FindMaxEx(std::vector<T> const & arr, T & maxValue, Less const & less)
{
	if (arr.empty())
	{
		return false;
	}

	T tmpMaxValue = arr[0];
	for (T const & element : arr)
	{
		if (less(tmpMaxValue, element))
		{
			tmpMaxValue = element;
		}
	}

	maxValue = tmpMaxValue;
	return true;
}