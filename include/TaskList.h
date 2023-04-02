#pragma once

#include <string_view>
#include <map>
#include <set>
#include <vector>

#include "Task.h"

class TaskList
{
public:
	struct Expression
	{
		std::string_view field;
		std::string_view operatr;
		std::string_view value;

		bool operator<(const Expression& other) const
		{
			return field < other.field;
		}
	};

	TaskList() = default;

	~TaskList() = default;

	void add(const Task& task);

	void update(const Task& task);

	void replace(const std::string_view oldName, const Task& newTask);

	void erase(const std::string_view name);

	bool contains(const std::string_view name) const;

	void setDone(const std::string_view name);

	void displayAll() const;

	int count() const;

	std::vector<const Task*> find(const std::set<Expression>& expressions) const;

private:
	std::map<std::string, Task> m_tasks;
};
