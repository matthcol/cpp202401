#pragma once
#include <string>
#include <iostream>

class Form
{
public:
	void setName(const std::string& name);
	const std::string& name() const;

	// abstract methods: pure virtual (=0)
	virtual std::string toString() const = 0;
	virtual void translate(double deltaX, double deltaY) = 0;

protected:
	Form() = default;
	// Form(const Form& form) = delete;
	Form(const std::string& name);
	virtual ~Form() = default;
private:
	std::string m_name;
};

std::ostream& operator<<(std::ostream& out, const Form& form);

