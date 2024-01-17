#pragma once
#include "Form.h"

class Point: public Form
{
public:
	Point();
	Point(const std::string& name, double x, double y);
	virtual ~Point();
	void setX(double x);
	double x() const;
	void setY(double y);
	double y() const;
	
	// from Form
	virtual std::string toString() const override;
	void translate(double deltaX, double deltaY) override;

	double distance(const Point& other) const;

	bool operator==(const Point& other) const;
	std::partial_ordering operator<=>(const Point& other) const;
private:
	double m_x;
	double m_y;

	
};

