#include "stdafx.h"
#include "RemoteControl.h"
#include "TVSet.h"

using namespace std;
using namespace std::placeholders;

CRemoteControl::CRemoteControl(CTVSet & tv, std::istream & input, std::ostream & output)
	: m_tv(tv)
	, m_input(input)
	, m_output(output)
	, m_actionMap({
		{ "TurnOn", bind(&CRemoteControl::TurnOn, this, _1) },
		{ "TurnOff", bind(&CRemoteControl::TurnOff, this, _1) },
	})
{
}

bool CRemoteControl::HandleCommand()
{
	string commandLine;
	getline(m_input, commandLine);
	istringstream strm(commandLine);

	string action;
	strm >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		it->second(strm);
	}
	
	return true;
}

bool CRemoteControl::TurnOn(std::istream & /*args*/)
{
	m_tv.TurnOn();
	m_output << "TV is turned on" << endl;
	return true;
}

bool CRemoteControl::TurnOff(std::istream & /*args*/)
{
	m_tv.TurnOff();
	m_output << "TV is turned off" << endl;
	return true;
}