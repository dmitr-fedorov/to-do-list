#pragma once

#include <map>
#include <string>

#include "Task.h"

class TasksManager
{
public:
	TasksManager();

	~TasksManager();

	void AddTask(const std::string_view& name, const std::string_view& descr,
		const std::string_view& date, const std::string_view& categ);

	bool ContainsTask(const std::string_view& name);

	void SetTaskDone(const std::string_view& name);

private:
	std::map<std::string, Task> m_tasks;
};
