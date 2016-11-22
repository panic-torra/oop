#include "stdafx.h"
#include <boost/algorithm/string.hpp>
#include "Car.h"
#include "CarControl.h"

using namespace std;
using namespace std::placeholders;

CCarControl::CCarControl(CCar &car, std::istream &input, std::ostream &output)
	: m_car(car)
	, m_input(input)
	, m_output(output)
	, m_actionMap({
		{ "EngineOn", bind(&CCarControl::EngineOn, this, std::placeholders::_1) },
		{ "EngineOff", bind(&CCarControl::EngineOff, this, std::placeholders::_1) },
		{ "SetGear", bind(&CCarControl::SetGear, this, std::placeholders::_1) },
		{ "SetSpeed", bind(&CCarControl::SetSpeed, this, std::placeholders::_1) },
		{ "Info", bind(&CCarControl::Info, this, std::placeholders::_1) }
})
{
}

string GetDirectionString(Direction const& direction)
{
	std::string result;
	if (direction == Direction::FORWARD)
	{
		result = "forward";
	}
	else if (direction == Direction::BACKWARD)
	{
		result = "backward";
	}
	else
	{
		result = "none";
	}
	return result;
}

bool CCarControl::HandleCommand()
{
	string commandLine;
	getline(m_input, commandLine);
	istringstream strm(commandLine);

	string action;
	strm >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		return it->second(strm);
	}

	return false;
}

bool CCarControl::EngineOn(std::istream & /*args*/)
{
	bool callback = m_car.TurnOnEngine();

	if (callback)
	{
		m_output << "Car engine was turned on\n";
	}
	else
	{
		m_output << "Car engine is already turned on\n";
	}

	return true;
}

bool CCarControl::EngineOff(std::istream & /*args*/)
{
	bool callback = m_car.TurnOffEngine();

	if (callback)
	{
		m_output << "Car engine was turned off\n";
	}
	else
	{
		m_output << "Car engine is already turned off\n";
	}

	return true;
}

bool CCarControl::SetGear(std::istream &args)
{
	int gear;
	args >> gear;

	bool callback = m_car.SetGear(static_cast<Gear>(gear));

	if (callback)
	{
		m_output << "Gear was switched on " << m_car.GetGear() << '\n';
	}
	else
	{
		m_output << "Can't switch gear on " << gear << '\n';
	}

	return true;
}

bool CCarControl::SetSpeed(std::istream &args)
{
	int speed;
	args >> speed;

	bool callback = m_car.SetSpeed(speed);

	if (callback)
	{
		m_output << "Speed was changed on " << m_car.GetSpeed() << '\n';
	}
	else
	{
		m_output << "Speed is out of range for current gear or car engine is turned off\n";
	}

	return true;
}

bool CCarControl::Info(std::istream & /*args*/)
{
	m_output << "Engine: " << ((m_car.IsEngineTurnOn()) ? "on" : "off") << '\n'
		<< "Gear: " << static_cast<int>(m_car.GetGear()) << '\n'
		<< "Speed: " << m_car.GetSpeed() << '\n'
		<< "Direction: " << GetDirectionString(static_cast<Direction>(m_car.GetDirection())) << '\n';

	return true;
}