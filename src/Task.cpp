#include "Task.h"

#include <iostream>

Task::Task(const std::string_view name, const std::string_view description,
	const DateTime& dateTime, const std::string_view category, const std::string_view status)
	: name(name), description(description), dateTime(dateTime), category(category), status(status)
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

bool Task::operator==(const Task& other) const
{
	return name == other.name &&
		description == other.description &&
		dateTime == other.dateTime &&
		description == other.description &&
		status == other.status;
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

std::ofstream& operator<<(std::ofstream& ofs, const Task& task)
{
	ofs << task.name << '\n';
	ofs << task.description << '\n';
	ofs << task.dateTime << '\n';
	ofs << task.category << '\n';
	ofs << task.status << '\n';

	return ofs;
}
