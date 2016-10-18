#include "stdafx.h"
#include "ProcessVector.h"
#include "stdafx.h"
#include "processVector.h"
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

int ProcessVector(std::vector<double>& nums)
{
	std::vector<double>::const_iterator max = max_element(nums.begin(), nums.end());
	std::vector<double>::const_iterator min = min_element(nums.begin(), nums.end());
	sort(nums.begin(), nums.end());

	if (*min == 0)
	{
		std::cout << "Min num is zero, division by zero is forbidden" << std::endl;
		return EXIT_FAILURE;
	}

	for (size_t i = 0; i < nums.size(); ++i)
	{
		std::cout << nums[i] * *max / *min << ' ';
	}

	return EXIT_SUCCESS;
}