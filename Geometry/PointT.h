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
	PointT();
	PointT(const std::string& name, T x, T y);
	virtual ~PointT() = default;
	
	void setX(T x);
	T x() const;
	void setY(T y);
	T y() const;

	// from Form
	virtual std::string toString() const override;

	void translate(double deltaX, double deltaY) override;

	double distance(const PointT<T>& other) const;

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

#include "PointT.tpp"

