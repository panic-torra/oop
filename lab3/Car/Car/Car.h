#pragma once
#include "stdafx.h"

enum class Gear
{
	REVERSE = -1,
	NEUTRAL = 0,
	FIRST = 1,
	SECOND = 2,
	THIRD = 3,
	FOURTH = 4,
	FIFTH = 5
};

enum class Direction
{
	BACKWARD = -1,
	NONE = 0,
	FORWARD = 1
};

typedef std::pair<int, int> Speed;
typedef std::map<Gear, Speed> SpeedRange;

class CCar
{
public:

	Gear GetGear() const;
	unsigned GetSpeed() const;
	Direction GetDirection() const;

	bool TurnOnEngine();
	bool TurnOffEngine();

	bool SetGear(Gear gear);
	bool SetSpeed(unsigned speed);

	bool IsEngineTurnOn() const;
private:
	bool CheckGear(Gear gear) const;
	bool IsSpeedInRange(Gear const& gear, int speed) const;

	bool m_isTurnedOn = false;
	Gear m_gear = Gear::NEUTRAL;
	int m_speed = 0;
};