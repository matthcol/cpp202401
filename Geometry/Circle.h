#pragma once
#include "Form.h"
#include "IMesurable2D.h"
#include "Point.h"

class Circle: public Form, public IMesurable2D
{
public:
	Circle(const std::string& name, std::shared_ptr<Point> center, double radius);
	virtual ~Circle() = default;

	// Hérité via Form
	std::string toString() const override;
	void translate(double deltaX, double deltaY) override;

	// Hérité via IMesurable2D
	double perimeter() const override;
	double surface() const override;

	// getter/setter
	std::shared_ptr<Point> center() const;
	void setCenter(std::shared_ptr<Point> center);
	double radius() const;
	void setRadius(double radius);
private:
	std::shared_ptr<Point> m_center;
	double m_radius;
};

