#include "Task.h"

#include <iostream>

Task::Task(const std::string_view name, const std::string_view description,
	const DateTime& dateTime, const std::string_view category)
	: name(name), description(description), dateTime(dateTime), category(category), status("on")
{
	
}

bool Task::nameIs(const std::string_view op, const std::string_view value) const
{
	if (op == ">")
	{
		if (name > value)
			return true;
	}
	else if (op == ">=")
	{
		if (name >= value)
			return true;
	}
	else if (op == "=")
	{
		if (name == value)
			return true;
	}
	else if (op == "<=")
	{
		if (name <= value)
			return true;
	}
	else if (op == "<")
	{
		if (name < value)
			return true;
	}
	else if (op == "like")
	{
		if (name.find(value) != std::string::npos)
			return true;
	}
	else
	{
		throw "Unknown operator related to field 'name'!";
	}

	return false;
}

bool Task::descriptionIs(const std::string_view op, const std::string_view value) const
{
	if (op == ">")
	{
		if (description > value)
			return true;
	}
	else if (op == ">=")
	{
		if (description >= value)
			return true;
	}
	else if (op == "=")
	{
		if (description == value)
			return true;
	}
	else if (op == "<=")
	{
		if (description <= value)
			return true;
	}
	else if (op == "<")
	{
		if (description < value)
			return true;
	}
	else if (op == "like")
	{
		if (description.find(value) != std::string::npos)
			return true;
	}
	else
	{
		throw "Unknown operator related to field 'description'!";
	}

	return false;
}

bool Task::dateTimeIs(const std::string_view op, const DateTime& other) const
{
	if (op == ">")
	{
		if (dateTime > other)
			return true;
	}
	else if (op == ">=")
	{
		if (dateTime >= other)
			return true;
	}
	else if (op == "=")
	{
		if (dateTime == other)
			return true;
	}
	else if (op == "<=")
	{
		if (dateTime <= other)
			return true;
	}
	else if (op == "<")
	{
		if (dateTime < other)
			return true;
	}
	else
	{
		throw "Unknown operator related to field 'date'!";
	}

	return false;
}

bool Task::categoryIs(const std::string_view op, const std::string_view value) const
{
	if (op == ">")
	{
		if (category > value)
			return true;
	}
	else if (op == ">=")
	{
		if (category >= value)
			return true;
	}
	else if (op == "=")
	{
		if (category == value)
			return true;
	}
	else if (op == "<=")
	{
		if (category <= value)
			return true;
	}
	else if (op == "<")
	{
		if (category < value)
			return true;
	}
	else if (op == "like")
	{
		if (category.find(value) != std::string::npos)
			return true;
	}
	else
	{
		throw "Unknown operator related to field 'category'!";
	}

	return false;
}

bool Task::statusIs(const std::string_view op, const std::string_view value) const
{
	if (op == ">")
	{
		if (status > value)
			return true;
	}
	else if (op == ">=")
	{
		if (status >= value)
			return true;
	}
	else if (op == "=")
	{
		if (status == value)
			return true;
	}
	else if (op == "<=")
	{
		if (status <= value)
			return true;
	}
	else if (op == "<")
	{
		if (status < value)
			return true;
	}
	else if (op == "like")
	{
		if (status.find(value) != std::string::npos)
			return true;
	}
	else
	{
		throw "Unknown operator related to field 'status'!";
	}

	return false;
}

std::ostream& operator<<(std::ostream& os, const Task& task)
{
	os << "name       : " << task.name << '\n';
	os << "description: " << task.description << '\n';
	os << "date       : " << task.dateTime << '\n';
	os << "category   : " << task.category << '\n';
	os << "status     : " << task.status << '\n';

	return os;
}
