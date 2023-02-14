#include "TaskList.h"

#include <iostream>

TaskList::TaskList()
{

}

TaskList::~TaskList()
{

}

void TaskList::Add(const std::string_view name, const std::string_view description,
	const DateTime& dateTime, const std::string_view category)
{
	m_tasks.emplace(name, Task{ name, description, dateTime, category });
}

void TaskList::Update(const std::string_view name, const std::string_view description,
	const DateTime& dateTime, const std::string_view category)
{
	const auto it{ m_tasks.find(std::string(name)) };

	if (it == m_tasks.end())
	{
		return;
	}

	it->second.Update(description, dateTime, category);
}

void TaskList::Replace(const std::string_view oldName, const std::string_view newName,
	const std::string_view description, const DateTime& dateTime, const std::string_view category)
{	
	const auto it_oldName{  m_tasks.find(std::string(oldName)) };
	const auto it_newName{ m_tasks.find(std::string(newName)) };

	if (it_oldName == m_tasks.end() || it_newName != m_tasks.end())
	{
		return;
	}

	m_tasks.erase(std::string(oldName));

	m_tasks.emplace(newName, Task{ newName, description, dateTime, category });
}

void TaskList::Delete(const std::string_view name)
{
	m_tasks.erase(std::string(name));
}

bool TaskList::Contains(const std::string_view name) const
{
	return m_tasks.find(std::string(name)) != m_tasks.end() ? true : false;
}

void TaskList::SetDone(const std::string_view name)
{	
	auto it{ m_tasks.find(std::string(name)) };

	if (it == m_tasks.end())
	{
		return;
	}
	
	it->second.SetDone();
}

void TaskList::DisplayAll() const
{
	for (const auto& containerElement : m_tasks)
	{
		containerElement.second.Display();

		std::cout << std::endl;
	}
}

int TaskList::Count() const
{
	return m_tasks.size();
}

std::vector<const Task*>
TaskList::Find(const std::set<Expression>& expressions) const
{
	std::vector<const Task*> relevantTasks;

	for (const auto& containerElement : m_tasks)
	{
		const Task& task{ containerElement.second };

		for (const auto& expression : expressions)
		{
			const std::string_view field  { expression.field };
			const std::string_view operatr{ expression.operatr };
			const std::string_view value  { expression.value };

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
