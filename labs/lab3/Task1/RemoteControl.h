#pragma once
#include <boost/noncopyable.hpp>

class CTVSet;

// Наследование от boost::noncopyable - явный способ запретить копирование и присваивание экземпляров класса
class CRemoteControl : boost::noncopyable
{
public:
	CRemoteControl(CTVSet & tv, std::istream & input, std::ostream & output);
	bool HandleCommand();

	// Избавляемся от предупреждения компилятора о том, что он не сможет сгенерировать оператор присваивания
	// CRemoteControl& operator=(const CRemoteControl &) = delete;
private:
	bool TurnOn(std::istream & args);
	bool TurnOff(std::istream & args);
private:
	typedef std::map<std::string, std::function<bool(std::istream & args)>> ActionMap;

	CTVSet & m_tv;
	std::istream & m_input;
	std::ostream & m_output;

	const ActionMap m_actionMap;
};

