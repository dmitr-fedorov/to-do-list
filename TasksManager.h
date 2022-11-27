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

	void UpdateTask(const std::string_view& name, const std::string_view& descr,
		            const std::string_view& date, const std::string_view& categ);

	void ReplaceTask(const std::string_view& oldName, const std::string_view& newName,
		             const std::string_view& descr,   const std::string_view& date,
		             const std::string_view& categ);

	void DeleteTask(const std::string_view& name);

	bool ContainsTask(const std::string_view& name) const;

	void SetTaskDone(const std::string_view& name);

private:
	std::map<std::string, Task> m_tasks;
};
