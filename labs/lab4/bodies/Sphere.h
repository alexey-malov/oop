#pragma once
#include "Body.h"

class CSphere final : public CBody
{
public:
	CSphere(double density, double radius);

	double GetRadius() const;
	double GetVolume() const override;

private:
	// Переопределяем AppendProperties, чтобы добавить информацию о сфере.
	void AppendProperties(std::ostream& strm) const override;
	double m_radius;
};
