#pragma once

struct CAthlete
{
	CAthlete();
	CAthlete(std::string fullName, float height, float weight);

	std::string fullName;
	float height;
	float weight;
};

bool LessWeight(CAthlete const& lhs, CAthlete const& rhs);
bool LessHeight(CAthlete const& lhs, CAthlete const& rhs);
bool LessFullName(CAthlete const& lhs, CAthlete const& rhs);
bool const operator ==(CAthlete const & lhs, CAthlete const & rhs);