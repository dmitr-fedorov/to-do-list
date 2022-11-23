#pragma once

#include <map>
#include <string>

#include "Task.h"

class TasksManager
{
public:
	TasksManager();
	~TasksManager();

	void AddTask(std::string& name, std::string& descr, std::string& date, std::string& categ);
	bool ContainsTask(std::string& name);

private:
	std::map<std::string, Task> m_tasks;
};
