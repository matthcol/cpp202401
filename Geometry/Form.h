#pragma once
#include <string>
class Form
{
public:
	void setName(const std::string& name);
	const std::string& name() const;
protected:
	Form() = default;
	// Form(const Form& form) = delete;
	Form(const std::string& name);
	virtual ~Form() = default;
private:
	std::string m_name;
};

