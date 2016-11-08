#pragma once

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


class CCar
{
public:

	int GetGear() const;
	int GetSpeed() const;
	int GetDirection() const;

	bool IsEngineTurnOn() const;

	bool TurnOnEngine();
	bool TurnOffEngine();

	bool SetGear(int gear);
	bool SetSpeed(int speed);

	bool IsNeutralGear() const;
	bool IsSpeedInRange(Gear const& gear, int speed) const;

	bool CheckGear(int gear) const;
private:
	bool m_isTurnOn = false;
	Gear m_gear = Gear::NEUTRAL;
	int m_speed = 0;
	Direction m_direction = Direction::NONE;
};