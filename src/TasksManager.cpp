#include "TasksManager.h"

#include <iostream>

TasksManager::TasksManager()
{

}

TasksManager::~TasksManager()
{

}

void TasksManager::AddTask(const std::string_view name, const std::string_view description,
	const DateTime& dateTime, const std::string_view category)
{
	m_tasks.emplace(name, Task{ name, description, dateTime, category });
}

void TasksManager::UpdateTask(const std::string_view name, const std::string_view description,
	const DateTime& dateTime, const std::string_view category)
{
	const auto it{ m_tasks.find(std::string(name)) };

	if (it != m_tasks.end())
	{
		it->second.Update(description, dateTime, category);
	}
}

void TasksManager::ReplaceTask(const std::string_view oldName, const std::string_view newName,
	const std::string_view description, const DateTime& dateTime, const std::string_view category)
{	
	const auto it_oldName{  m_tasks.find(std::string(oldName)) };
	const auto it_newName{ m_tasks.find(std::string(newName)) };

	if (it_oldName != m_tasks.end() && it_newName == m_tasks.end())
	{
		m_tasks.erase(std::string(oldName));

		m_tasks.emplace(newName, Task(newName, description, dateTime, category));
	}	
}

void TasksManager::DeleteTask(const std::string_view name)
{
	m_tasks.erase(std::string(name));
}

bool TasksManager::ContainsTask(const std::string_view name) const
{
	return m_tasks.find(std::string(name)) != m_tasks.end() ? true : false;
}

void TasksManager::SetTaskDone(const std::string_view name)
{	
	auto it{ m_tasks.find(std::string(name)) };

	if (it != m_tasks.end())
	{
		it->second.SetDone();
	}
}

void TasksManager::DisplayAllTasks() const
{
	for (const auto& containerElement : m_tasks)
	{
		containerElement.second.Display();

		std::cout << std::endl;
	}
}

int TasksManager::TaskCount()
{
	return m_tasks.size();
}

std::vector<const Task*>
TasksManager::SearchTasks(const std::set<Expression>& expressions) const
{
	std::vector<const Task*> relevantTasks;

	for (const auto& containerElement : m_tasks)
	{
		const Task& task{ containerElement.second };

		for (const auto& expression : expressions)
		{
			const auto field  { expression.field };
			const auto operatr{ expression.operatr };
			const auto value  { expression.value };

			if (field == "name")
			{
				if (!task.NameIs(operatr, value))
					break;
			}
			else if (field == "description")
			{
				if (!task.DescriptionIs(operatr, value))
					break;
			}
			else if (field == "date")
			{
				if (!task.DateTimeIs(operatr, DateTime(value)))
					break;
			}
			else if (field == "category")
			{
				if (!task.CategoryIs(operatr, value))
					break;
			}
			else if (field == "status")
			{
				if (!task.StatusIs(operatr, value))
					break;
			}
			else
			{
				throw "Unknown field name!";
			}

			/* 
			  Если больше нет выражений, по которым нужно проводить отбор.
			*/
			if (expressions.find(expression) == std::prev(expressions.end()))
			{
				relevantTasks.push_back(&task);
			}
		}
	}

	return relevantTasks;
}
