#include "stdafx.h"
#include <algorithm>
#include <functional>
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

std::vector<double> ProcessVector(std::vector<double>& nums)
{
	std::vector<double>::const_iterator max = max_element(nums.begin(), nums.end());
	std::vector<double>::const_iterator min = min_element(nums.begin(), nums.end());
	std::vector<double> result(nums.size());

	if ((*min == 0) || (nums.size() <= 1))
	{
		return nums;
	}

	for (size_t i = 0; i < nums.size(); ++i)
	{
		result[i] = nums[i] * *max / *min;
	}

	sort(result.begin(), result.end());

	return result;
}