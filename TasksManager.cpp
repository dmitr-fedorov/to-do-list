#include "TasksManager.h"

#include <string_view>

#include <iostream>


TasksManager::TasksManager()
{

}

TasksManager::~TasksManager()
{

}

void TasksManager::AddTask(const std::string_view& name, const std::string_view& descr,
	const std::string_view& date, const std::string_view& categ)
{
	m_tasks.emplace(name, Task(name, descr, date, categ));
}

bool TasksManager::ContainsTask(const std::string_view& name)
{
	return m_tasks.find( std::string(name) ) == m_tasks.end() ? false : true;
}

void TasksManager::SetTaskDone(const std::string_view& name)
{
	m_tasks.at(std::string(name)).SetDone();
}