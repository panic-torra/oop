#include "stdafx.h"
#include "Car.h"

static const int MAX_GEAR = 5;
static const int MIN_GERA = -1;

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
	return m_isTurnOn;
}

int CCar::GetSpeed() const
{
	return std::abs(m_speed);
}

int CCar::GetGear() const
{
	return static_cast<int>(m_gear);
}

int CCar::GetDirection() const
{
	return static_cast<int>(m_direction);
}

bool CCar::TurnOnEngine()
{
	return !m_isTurnOn ? m_isTurnOn = true : false;
}

bool CCar::TurnOffEngine()
{
	bool isTurnOff = false;
	if (m_isTurnOn && (m_speed == 0) && IsNeutralGear())
	{
		m_isTurnOn = false;
		isTurnOff = true;
	}
	return isTurnOff;
}

bool CCar::IsNeutralGear() const
{
	return m_gear == Gear::NEUTRAL;
}

bool CCar::CheckGear(Gear gear) const
{
	return ((static_cast<Gear>(gear) == Gear::REVERSE) && (m_speed == 0)) ||
		((m_gear == Gear::REVERSE) && (gear == Gear::FIRST) && (m_speed == 0)) ||
		((m_gear == Gear::NEUTRAL) && (gear == Gear::FIRST) && (m_speed == 0)) ||
		((m_gear != Gear::REVERSE) && (gear >= Gear::FIRST) && (m_speed >= 0)) ||
		((gear == Gear::NEUTRAL));
}

bool CCar::IsSpeedInRange(Gear const& gear, int speed) const
{
	auto it = speedRange.find(gear);
	auto speedRange = it->second;
	return  (speedRange.second >= speed) && (speedRange.first <= speed);
}

bool CCar::SetGear(Gear gear)
{
	bool isSetGear = false;
	auto intGear = static_cast<int>(gear);
	bool isAvailableGear = (MAX_GEAR >= intGear) && (MIN_GERA <= intGear) && (m_isTurnOn);
	if (isAvailableGear)
	{
		isSetGear = isAvailableGear && IsSpeedInRange(static_cast<Gear>(gear), GetSpeed()) && CheckGear(gear);
		if (isSetGear)
		{
			m_gear = gear;
		}
	}
	return isSetGear;
}

bool CCar::SetSpeed(int speed)
{
	if (IsSpeedInRange(m_gear, speed))
	{
		if (IsNeutralGear() && (speed <= GetSpeed()) || !IsNeutralGear())
		{
			m_speed = (Gear::REVERSE == m_gear) || (m_speed < 0) ? -speed : speed;
			return true;
		}
	}

	return false;
}