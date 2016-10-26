#include "stdafx.h"
#include <vector>
#include <set>

std::vector<bool> InitVectorOfPrimes(unsigned int upperBound)
{
	std::vector<bool> vector(upperBound + 1, true);
	if (upperBound >= 2 && upperBound < 100000001)
	{
		vector[0] = vector[1] = false;
		for (unsigned int i = 2; i * i <= upperBound; ++i)
		{
			if (vector[i])
			{
				for (unsigned int j = i * i; j <= upperBound; j += i)
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
	std::vector<bool> sieve = InitVectorOfPrimes(upperBound);

	std::set<int> result;
	if (upperBound >= 2 && upperBound < 100000001)
	{
		result.emplace_hint(result.end(), 2);
		for (unsigned int i = 3; i <= upperBound; i += 2)
		{
			if (sieve[i])
			{
				result.emplace_hint(result.end(), i);
			}
		}
	}

	return result;
}