#include "Task.h"

#include <iostream>

Task::Task(const std::string_view name, const std::string_view descr,
	const std::string_view date, const std::string_view categ)
	: m_name(name), m_description(descr), m_date(date), m_category(categ), m_status(TaskStatus::on)
{
	
}

Task::~Task()
{

}

TaskStatus Task::GetCompletionStatus() const
{
	return m_status;
}

void Task::SetDone()
{
	m_status = TaskStatus::done;
}

void Task::Update(const std::string_view descr, const std::string_view date, const std::string_view categ)
{
	m_description = std::string(descr);
	m_date = std::string(date);
	m_category = std::string(categ);
}

void Task::Display() const
{
	std::cout << "name: " << m_name << std::endl;
	std::cout << "description: " << m_description << std::endl;
	std::cout << "date: " << m_date << std::endl;
	std::cout << "category: " << m_category << std::endl;

	std::cout << "status: ";
	if (m_status == TaskStatus::on)
		std::cout << "on" << std::endl;
	else
		std::cout << "done" << std::endl;

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
		throw "Unknown operator!";
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
		throw "Unknown operator!";
	}

	return false;
}

bool Task::DateIs(const std::string_view op, const std::string_view value) const
{
	if (op == ">")
	{
		if (m_date > value)
			return true;
	}
	else if (op == ">=")
	{
		if (m_date >= value)
			return true;
	}
	else if (op == "=")
	{
		if (m_date == value)
			return true;
	}
	else if (op == "<=")
	{
		if (m_date <= value)
			return true;
	}
	else if (op == "<")
	{
		if (m_date < value)
			return true;
	}
	else if (op == "like")
	{
		if (m_date.find(value) != std::string::npos)
			return true;
	}
	else
	{
		throw "Unknown operator!";
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
		throw "Unknown operator!";
	}

	return false;
}

bool Task::StatusIs(const std::string_view op, const std::string_view value) const
{
	if (op == "=")
	{
		if (value == "on")
		{
			if (m_status == TaskStatus::on)
				return true;
		}
		if (value == "done")
		{
			if (m_status == TaskStatus::done)
				return true;
		}
	}
	else
	{
		throw "Unknown operator!";
	}

	return false;
}
