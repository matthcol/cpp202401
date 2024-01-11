#include "Form.h"

void Form::setName(const std::string& name)
{
	m_name = name;
}

const std::string& Form::name() const
{
	return m_name;
}

Form::Form(const std::string& name): m_name(name)
{
}

std::ostream& operator<<(std::ostream& out, const Form& form)
{
	return out << form.toString();
}
