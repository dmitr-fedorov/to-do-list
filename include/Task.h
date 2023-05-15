#pragma once

#include <string>
#include <string_view>
#include <iostream>
#include <fstream>

#include "DateTime.h"

struct Task
{
	std::string name;
	std::string description;
	DateTime dateTime;
	std::string category;
	std::string status;

	Task(const std::string_view name, const std::string_view description,
		const DateTime& dateTime, const std::string_view category, const std::string_view status);

	~Task() = default;

	bool nameIs(const std::string_view op, const std::string_view value) const;
	bool descriptionIs(const std::string_view op, const std::string_view value) const;
	bool dateTimeIs(const std::string_view op, const DateTime& other) const;
	bool categoryIs(const std::string_view op, const std::string_view value) const;
	bool statusIs(const std::string_view op, const std::string_view value) const;

	bool operator==(const Task& other) const;
	friend std::ostream& operator<<(std::ostream& os, const Task& task);
	friend std::ofstream& operator<<(std::ofstream& ofs, const Task& task);
};
