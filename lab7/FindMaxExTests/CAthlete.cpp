#include "stdafx.h"
#include "CAthlete.h"

CAthlete::CAthlete()
{
}

CAthlete::CAthlete(std::string fullName, float height, float weight)
	: fullName(fullName)
	, height(height)
	, weight(weight)
{
}

bool LessFullName(CAthlete const& lhs, CAthlete const& rhs)
{
	return lhs.fullName < rhs.fullName;
}

bool LessHeight(CAthlete const& lhs, CAthlete const& rhs)
{
	return lhs.height < rhs.height;
}

bool LessWeight(CAthlete const& lhs, CAthlete const& rhs)
{
	return lhs.weight < rhs.weight;
}

bool const operator ==(CAthlete const & lhs, CAthlete const & rhs)
{
	return (lhs.fullName == rhs.fullName && lhs.height == rhs.height && lhs.weight == rhs.weight);
}