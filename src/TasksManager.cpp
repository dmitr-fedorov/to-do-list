#include "TasksManager.h"

#include <string_view>

TasksManager::TasksManager()
{

}

TasksManager::~TasksManager()
{

}

void TasksManager::AddTask(const std::string_view name, const std::string_view descr,
	const DateTime& dateTime, const std::string_view categ)
{
	m_tasks.emplace(name, Task(name, descr, dateTime, categ));
}

void TasksManager::UpdateTask(const std::string_view name, const std::string_view descr,
	const DateTime& dateTime, const std::string_view categ)
{
	auto it = m_tasks.find(std::string(name));

	if (it != m_tasks.end())
		it->second.Update(descr, dateTime, categ);
}

void TasksManager::ReplaceTask(const std::string_view oldName, const std::string_view newName,
	const std::string_view descr, const DateTime& dateTime, const std::string_view categ)
{	
	m_tasks.erase(std::string(oldName));
	
	m_tasks.emplace(newName, Task(newName, descr, dateTime, categ));
}

void TasksManager::DeleteTask(const std::string_view name)
{
	m_tasks.erase(std::string(name));
}

bool TasksManager::ContainsTask(const std::string_view name) const
{
	return m_tasks.find(std::string(name)) == m_tasks.end() ? false : true;
}

void TasksManager::SetTaskDone(const std::string_view name)
{	
	auto it = m_tasks.find(std::string(name));

	if (it != m_tasks.end())
		it->second.SetDone();
}

void TasksManager::DisplayAllTasks() const
{
	for (const std::pair<const std::string, Task>& ref : m_tasks)
	{
		ref.second.Display();

		std::cout << std::endl;
	}
}

std::vector<const Task*>
TasksManager::SearchTasks(const SearchMap& searchMap) const
{
	std::vector<const Task*> retVec;

	for (const std::pair<const std::string, Task>& taskPair : m_tasks)
	{
		for (const SearchPair& searchPair : searchMap)
		{
			const auto field = searchPair.first;
			const auto operatr = searchPair.second.first;
			const auto value = searchPair.second.second;

			if (field == "name")
			{
				if (!taskPair.second.NameIs(operatr, value))
					break;
			}
			else if (field == "description")
			{
				if (!taskPair.second.DescriptionIs(operatr, value))
					break;
			}
			else if (field == "date")
			{
				if (!taskPair.second.DateTimeIs(operatr, DateTime(value)))
					break;
			}
			else if (field == "category")
			{
				if (!taskPair.second.CategoryIs(operatr, value))
					break;
			}
			else if (field == "status")
			{
				if (!taskPair.second.StatusIs(operatr, value))
					break;
			}
			else
			{
				throw "Unknown field name!";
			}

			/* 
			  Если больше нет полей, по которым нужно производить поиск.
			*/
			if (searchMap.find(searchPair.first) == std::prev(searchMap.end()))
				retVec.push_back(&taskPair.second);
		}
	}

	return retVec;
}
