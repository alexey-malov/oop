#include <iostream>
#include <vector>

class Car
{
public:
	void TurnEngineOn()
	{
		m_isTurnedOn = true;
	}

	bool IsEngineTurnedOn() const
	{
		return m_isTurnedOn;
	}

	bool TurnEngineOff()
	{
		if (m_speed == 0)
		{
			m_isTurnedOn = false;
			return true;
		}
		return false;
	}

	bool Drive(double speed)
	{
		if (m_isTurnedOn && speed >= 0 && speed <= 150)
		{
			m_speed = speed;
			return true;
		}
		return false;
	}

	void Stop()
	{
		m_speed = 0;
	}

	double GetSpeed() const
	{
		return m_speed;
	}

private:
	bool m_isTurnedOn = false;
	double m_speed = 0;
};

int main()
{
	Car car;
	car.TurnEngineOn();
	car.Drive(10);
	std::cout << car.GetSpeed() << "\n";
	car.TurnEngineOff();
	std::cout << "Is engine on: " << std::boolalpha << car.IsEngineTurnedOn() << "\n";
	car.Stop();
	car.TurnEngineOff();
	std::cout << "Is engine on: " << std::boolalpha << car.IsEngineTurnedOn() << "\n";
}
