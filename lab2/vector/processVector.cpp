#include "stdafx.h"
#include <algorithm>
#include <functional>
#include <boost/phoenix/phoenix.hpp>
#include <boost/range/algorithm/transform.hpp>
#pragma warning (push, 3)
#include <boost/phoenix.hpp>
#pragma warning (pop)

std::vector<double> GetVectorFromFile(std::istream& input)
{
	std::vector<double> nums;
    copy(std::istream_iterator<double>(input), std::istream_iterator<double>(),
		back_inserter(nums));

	return nums;
}

std::vector<double> ProcessVector(std::vector<double> nums)
{
	if (nums.size() > 1)
	{
		std::vector<double> result;
		if ((*min_element(nums.begin(), nums.end()) != 0))
		{
			double ratio = *max_element(nums.begin(), nums.end()) / *min_element(nums.begin(), nums.end());
			transform(nums.begin(), nums.end(), nums.begin(), [ratio](double number) { return number * ratio; });
			return nums;
		}
	}

	return nums;
}