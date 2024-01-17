#pragma once
#include <format>

#include "Form.h"


/**
* T: type of coordinates x, y (numeric type)
*/
template<class T>
class PointT : public Form
{
public:
	PointT() = default; //: PointT("", 0.0, 0.0);
	PointT(const std::string& name, T x, T y): Form(name), m_x(x), m_y(y) {

	}
	virtual ~PointT() = default;
	void setX(T x) {
		m_x = x;
	}
	T x() const {
		return m_x;
	}
	void setY(T y) {
		m_y = y;
	}
	T y() const {
		return m_y;
	}

	// from Form
	virtual std::string toString() const override {
		return std::format("{0}({1}, {2})", name(), m_x, m_y);
	}

	void translate(double deltaX, double deltaY) override {
		m_x += static_cast<T>(deltaX);
		m_y += static_cast<T>(deltaY);
	}

	double distance(const PointT<T>& other) const {
		double deltaX = m_x - other.m_x; // need operator- on type T and conversion to type double
		double deltaY = m_y - other.m_y;
		return hypot(deltaX, deltaY);
	}

	template<class U> 
	double distance(const PointT<U>& other) const {
		double deltaX = static_cast<double>(m_x) - static_cast<double>(other.x());
		double deltaY = static_cast<double>(m_y) - static_cast<double>(other.y());
		return hypot(deltaX, deltaY);
	}

private:
	T m_x;
	T m_y;
};

//#include "PointT.tpp"

