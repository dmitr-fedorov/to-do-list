#include "Task.h"

#include <iostream>

Task::Task(const std::string_view name, const std::string_view descr,
	const DateTime& dateTime, const std::string_view categ)
	: m_name(name), m_description(descr), m_dateTime(dateTime), m_category(categ), m_status("on")
{
	
}

Task::~Task()
{

}

void Task::SetDone()
{
	m_status = "done";
}

void Task::Update(const std::string_view descr, const DateTime& dateTime, const std::string_view categ)
{
	m_description = descr;
	m_dateTime = dateTime;
	m_category = categ;
}

void Task::Display() const
{
	std::cout << "name: " << m_name << std::endl;
	std::cout << "description: " << m_description << std::endl;
	std::cout << "date: " << m_dateTime << std::endl;
	std::cout << "category: " << m_category << std::endl;
	std::cout << "status: " << m_status << std::endl;

	std::cout << std::endl;
}

bool Task::NameIs(const std::string_view op, const std::string_view value) const
{
	if (op == ">")
	{
		if (m_name > value)
			return true;
	}
	else if (op == ">=")
	{
		if (m_name >= value)
			return true;
	}
	else if (op == "=")
	{
		if (m_name == value)
			return true;
	}
	else if (op == "<=")
	{
		if (m_name <= value)
			return true;
	}
	else if (op == "<")
	{
		if (m_name < value)
			return true;
	}
	else if (op == "like")
	{
		if (m_name.find(value) != std::string::npos)
			return true;
	}
	else
	{
		throw "Unknown operator related to field 'name'!";
	}

	return false;
}

bool Task::DescriptionIs(const std::string_view op, const std::string_view value) const
{
	if (op == ">")
	{
		if (m_description > value)
			return true;
	}
	else if (op == ">=")
	{
		if (m_description >= value)
			return true;
	}
	else if (op == "=")
	{
		if (m_description == value)
			return true;
	}
	else if (op == "<=")
	{
		if (m_description <= value)
			return true;
	}
	else if (op == "<")
	{
		if (m_description < value)
			return true;
	}
	else if (op == "like")
	{
		if (m_description.find(value) != std::string::npos)
			return true;
	}
	else
	{
		throw "Unknown operator related to field 'description'!";
	}

	return false;
}

bool Task::DateTimeIs(const std::string_view op, const DateTime& other) const
{
	if (op == ">")
	{
		if (m_dateTime > other)
			return true;
	}
	else if (op == ">=")
	{
		if (m_dateTime >= other)
			return true;
	}
	else if (op == "=")
	{
		if (m_dateTime == other)
			return true;
	}
	else if (op == "<=")
	{
		if (m_dateTime <= other)
			return true;
	}
	else if (op == "<")
	{
		if (m_dateTime < other)
			return true;
	}
	else
	{
		throw "Unknown operator related to field 'date'!";
	}

	return false;
}

bool Task::CategoryIs(const std::string_view op, const std::string_view value) const
{
	if (op == ">")
	{
		if (m_category > value)
			return true;
	}
	else if (op == ">=")
	{
		if (m_category >= value)
			return true;
	}
	else if (op == "=")
	{
		if (m_category == value)
			return true;
	}
	else if (op == "<=")
	{
		if (m_category <= value)
			return true;
	}
	else if (op == "<")
	{
		if (m_category < value)
			return true;
	}
	else if (op == "like")
	{
		if (m_category.find(value) != std::string::npos)
			return true;
	}
	else
	{
		throw "Unknown operator related to field 'category'!";
	}

	return false;
}

bool Task::StatusIs(const std::string_view op, const std::string_view value) const
{
	if (op == ">")
	{
		if (m_status > value)
			return true;
	}
	else if (op == ">=")
	{
		if (m_status >= value)
			return true;
	}
	else if (op == "=")
	{
		if (m_status == value)
			return true;
	}
	else if (op == "<=")
	{
		if (m_status <= value)
			return true;
	}
	else if (op == "<")
	{
		if (m_status < value)
			return true;
	}
	else if (op == "like")
	{
		if (m_status.find(value) != std::string::npos)
			return true;
	}
	else
	{
		throw "Unknown operator related to field 'status'!";
	}

	return false;
}
