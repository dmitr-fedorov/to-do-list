#include "TasksManager.h"

#include <string_view>

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

void TasksManager::UpdateTask(const std::string_view& name, const std::string_view& descr,
	const std::string_view& date, const std::string_view& categ)
{
	const std::string strName(name);

	auto it = m_tasks.find(strName);

	if (it != m_tasks.end())
		it->second.Update(descr, date, categ);
}

void TasksManager::ReplaceTask(const std::string_view& oldName, const std::string_view& newName,
	const std::string_view& descr, const std::string_view& date, const std::string_view& categ)
{	
	const std::string strNewName(newName);
	const std::string strOldName(oldName);
	
	if (m_tasks.count(strOldName) && !m_tasks.count(strNewName))
	{
		m_tasks.erase(strOldName);
	
	    m_tasks.emplace(newName, Task(newName, descr, date, categ));
    }
}

void TasksManager::DeleteTask(const std::string_view& name)
{
	std::string strName(name);

	if (m_tasks.count(strName))
	{
		m_tasks.erase(strName);
	}
}

bool TasksManager::ContainsTask(const std::string_view& name) const
{
	return m_tasks.find( std::string(name) ) == m_tasks.end() ? false : true;
}

void TasksManager::SetTaskDone(const std::string_view& name)
{
	const std::string strName(name);
	
	auto it = m_tasks.find(strName);

	if (it != m_tasks.end())
		it->second.SetDone();
}
