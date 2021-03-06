#include "stdafx.h"
#include "Car.h"

static const int MAX_GEAR = 5;
static const int MIN_GEAR = -1;

static const int MIN_SPEED = 0;
static const int MAX_SPEED = 150;

static const SpeedRange speedRange = {
	{ Gear::REVERSE, Speed(0, 20) },
	{ Gear::NEUTRAL, Speed(MIN_SPEED, MAX_SPEED) },
	{ Gear::FIRST,   Speed(0, 30) },
	{ Gear::SECOND,  Speed(20, 50) },
	{ Gear::THIRD,   Speed(30, 60) },
	{ Gear::FOURTH,  Speed(40, 90) },
	{ Gear::FIFTH,   Speed(50, 150) }
};


bool CCar::IsEngineTurnOn() const
{
	return m_isTurnedOn;
}

unsigned CCar::GetSpeed() const
{
	return std::abs(m_speed);
}

Gear CCar::GetGear() const
{
	return m_gear;
}

Direction CCar::GetDirection() const
{
	if (m_speed < 0)
	{
		return Direction::BACKWARD;
	}
	else if (m_speed > 0)
	{
		return Direction::FORWARD;
	}

	return Direction::NONE;
}

bool CCar::TurnOnEngine()
{
	if (!m_isTurnedOn)
	{
		m_isTurnedOn = true;
		return true;
	}

	return false;
}

bool CCar::TurnOffEngine()
{
	bool isTurnOff = false;
	if (m_isTurnedOn && (m_speed == 0) && (m_gear == Gear::NEUTRAL))
	{
		m_isTurnedOn = false;
		isTurnOff = true;
	}
	return isTurnOff;
}


bool CCar::CheckGear(Gear gear) const
{
	return ((gear == Gear::REVERSE) && (m_speed == 0)) ||
		((m_gear == Gear::REVERSE) && (gear == Gear::FIRST) && (m_speed == 0)) ||
		((m_gear == Gear::NEUTRAL) && (gear == Gear::FIRST) && (m_speed == 0)) ||
		((m_gear != Gear::REVERSE) && (gear >= Gear::FIRST) && (m_speed >= 0)) ||
		((gear == Gear::NEUTRAL));
}

bool CCar::IsSpeedInRange(Gear const& gear, int speed) const
{
	auto it = speedRange.find(gear);
	auto speedRange = it->second;
	return  (speed <= speedRange.second) && (speed >= speedRange.first);
}

bool CCar::SetGear(Gear gear)
{
	bool isSetGear = false;
	auto intGear = static_cast<int>(gear);
	if ((MAX_GEAR >= intGear) && (MIN_GEAR <= intGear) && (m_isTurnedOn))
	{
		isSetGear = IsSpeedInRange(static_cast<Gear>(gear), GetSpeed()) && CheckGear(gear);
		if (isSetGear)
		{
			m_gear = gear;
		}
	}
	return isSetGear;
}

bool CCar::SetSpeed(unsigned speed)
{
	if (m_gear == Gear::NEUTRAL && speed <= GetSpeed())
	{
		m_speed = speed;
		return true;
	}

	if (IsSpeedInRange(m_gear, speed))
	{
		m_speed = speed;
		if (m_gear == Gear::REVERSE)
		{
			m_speed *= -1;
		}
		return true;
	}

	return false;
}