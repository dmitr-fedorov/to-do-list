#include "TasksManager.h"

#include <string_view>
#include <array>

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

std::vector<std::pair<std::string, Task>>
TasksManager::SearchTasks(std::map<std::string, std::pair<std::string, std::string>>& searchMap)
{
	std::vector<std::pair<std::string, Task>> retVec;

	for (std::pair<const std::string, Task>& taskPair : m_tasks)
	{
		for (const std::pair<std::string, std::pair<std::string, std::string>>& searchPair : searchMap)
		{
			const std::string& field = searchPair.first;
			const std::string& op = searchPair.second.first;
			const std::string& value = searchPair.second.second;

			if (field == "name")
			{
				if (!taskPair.second.NameIs(op, value))
					break;
			}
			else if (field == "description")
			{
				if (!taskPair.second.DescriptionIs(op, value))
					break;
			}
			else if (field == "date")
			{
				if (!taskPair.second.DateIs(op, value))
					break;
			}
			else if (field == "category")
			{
				if (!taskPair.second.CategoryIs(op, value))
					break;
			}
			else if (field == "status")
			{
				if (!taskPair.second.StatusIs(op, value))
					break;
			}

			if(searchMap.find(searchPair.first) == std::prev(searchMap.end()))
				retVec.push_back(taskPair);
		}
	}

	return retVec;
}
