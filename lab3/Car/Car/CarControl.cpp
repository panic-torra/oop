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
		//{ "EngineOn", bind(&CCarControl::EngineOn, this, std::placeholders::_1) },
		//{ "EngineOff", bind(&CCarControl::EngineOff, this, std::placeholders::_1) },
		//{ "SetGear", bind(&CCarControl::SetGear, this, std::placeholders::_1) },
		//{ "SetSpeed", bind(&CCarControl::SetSpeed, this, std::placeholders::_1) },
		//{ "Info", bind(&CCarControl::Info, this, std::placeholders::_1) }
})
{
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
//
//bool CCarControl::Info(std::istream & /*args*/)
//{
//	std::string info;
//
//	if (m_car.IsEngineTurnOn())
//	{
//		info = "Car engine is on\nGear: " + std::to_string(m_car.GetGear()) +
//			"\nSpeed: " + std::to_string(m_car.GetSpeed()) +
//			"\nDirection: " + std::to_string(m_car.GetDirection()) + '\n';
//	}
//	else
//	{
//		info = "Car engine is off\n";
//	}
//
//	m_output << info;
//
//	return true;
//}