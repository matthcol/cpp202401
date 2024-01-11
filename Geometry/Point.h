#pragma once
#include "Form.h"

class Point: public Form
{
public:
	Point() = default;
	Point(const std::string& name, double x, double y);
	virtual ~Point() = default;
	void setX(double x);
	double getX() const;
	void setY(double y);
	double getY() const;
private:
	double m_x;
	double m_y;
};

