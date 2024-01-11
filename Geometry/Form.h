#pragma once
#include <string>
class Form
{
protected:
	Form() = default;
	// Form(const Form& form) = delete;
	Form(const std::string& name);
private:
	std::string m_name;
};

