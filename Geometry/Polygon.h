#pragma once
#include <vector>

#include "Form.h"
#include "IMesurable2D.h"
#include "Point.h"

class Polygon: public Form, public IMesurable2D
{
public:
	Polygon(const std::string& name, std::initializer_list<std::shared_ptr<Point>> summits);

	template<class InputIt>
	Polygon(const std::string& name, InputIt first, InputIt last) :
		Form(name), m_summits(first, last) {

	}

	// Hérité via Form
	std::string toString() const override;
	void translate(double deltaX, double deltaY) override;

	// Hérité via IMesurable2D
	double perimeter() const override;
	double surface() const override;
private:
	std::vector<std::shared_ptr<Point>> m_summits;
};

