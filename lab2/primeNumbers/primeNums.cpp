#include "stdafx.h"
#include <vector>
#include <set>

std::vector<bool> InitVectorOfPrimes(unsigned int upperBound)
{
	std::vector<bool> vector(upperBound + 1, true);
	if (upperBound >= 2 && upperBound < 100000001)
	{
		vector[0] = vector[1] = false;
		for (size_t i = 2; i * i <= upperBound; ++i)
		{
			if (vector[i])
			{
				for (size_t j = i * i; j <= upperBound; j += i)
				{
					vector[j] = false;
				}
			}
		}
	}
	else
	{
		vector = {};
	}
	return vector;
}

std::set<int> GeneratePrimeNumbersSet(unsigned int upperBound)
{
	std::vector<bool> tmpSet = InitVectorOfPrimes(upperBound);

	std::set<int> result;
	if (upperBound >= 2 && upperBound < 100000001)
	{
		result.insert(2);
		for (size_t i = 3; i <= upperBound; i += 2)
		{
			if (tmpSet[i])
			{
				result.insert(i);
			}
		}
	}

	return result;
}