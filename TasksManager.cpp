#include "TasksManager.h"

#include <iostream>

TasksManager::TasksManager()
{

}

TasksManager::~TasksManager()
{

}

void TasksManager::AddTask(std::string& name, std::string& descr, std::string& date, std::string& categ)
{
	std::cout << "Adding a new task" << std::endl;
	m_tasks.emplace(name, Task(name, descr, date, categ));
}

bool TasksManager::ContainsTask(std::string& name)
{
	return m_tasks.find(name) == m_tasks.end() ? false : true;
}