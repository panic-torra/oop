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
extern const SpeedRange speedRange;

class CCar
{
public:

	int GetGear() const;
	int GetSpeed() const;
	int GetDirection();

	bool TurnOnEngine();
	bool TurnOffEngine();

	bool SetGear(Gear gear);
	bool SetSpeed(int speed);

	bool IsSpeedInRange(Gear const& gear, int speed) const;
	bool IsEngineTurnOn() const;
	bool CheckGear(Gear gear) const;
private:
	bool m_isTurnOn = false;
	Gear m_gear = Gear::NEUTRAL;
	int m_speed = 0;
	Direction m_direction = Direction::NONE;
};