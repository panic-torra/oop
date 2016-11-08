#include "stdafx.h"
#include "Car.h"

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