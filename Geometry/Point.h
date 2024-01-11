#pragma once
#include "Form.h"

class Point: public Form
{
public:
	Point();
	Point(const std::string& name, double x, double y);
	virtual ~Point() = default;
	void setX(double x);
	double x() const;
	void setY(double y);
	double y() const;
	
	// from Form
	virtual std::string toString() const override;
	void translate(double deltaX, double deltaY) override;

	double distance(const Point& other) const;
private:
	double m_x;
	double m_y;

	
};

