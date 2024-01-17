#pragma once
class IMesurable2D
{
public:
	virtual double perimeter() const = 0;
	virtual double surface() const = 0;

	virtual ~IMesurable2D() = default;
};

