#include "TaskList.h"

#include <iostream>

bool TaskList::Expression::operator<(const Expression& other) const
{
	return field < other.field;
}

bool TaskList::Expression::operator==(const Expression& other) const
{
	return field == other.field &&
		operatr == other.operatr &&
		value == other.value;
}

void TaskList::add(const Task& task)
{
	m_tasks.emplace(task.name, task);
}

void TaskList::update(const Task& task)
{
	const auto it = m_tasks.find(task.name);

	if (it == m_tasks.end())
	{
		return;
	}

	it->second.name = task.name;
	it->second.description = task.description;
	it->second.dateTime = task.dateTime;
	it->second.category = task.category;
	it->second.status = task.status;
}

void TaskList::replace(const std::string_view oldName, const Task& newTask)
{	
	const auto it_oldTask =  m_tasks.find(std::string(oldName));
	const auto it_newTask = m_tasks.find(newTask.name);

	if (it_oldTask == m_tasks.end() || it_newTask != m_tasks.end())
	{
		return;
	}

	m_tasks.erase(it_oldTask);

	m_tasks.emplace(newTask.name, newTask);
}

void TaskList::erase(const std::string_view name)
{
	m_tasks.erase(std::string(name));
}

bool TaskList::contains(const std::string_view name) const
{
	const auto it = m_tasks.find(std::string(name));
	
	bool result = it != m_tasks.end();
	
	return result;
}

void TaskList::setDone(const std::string_view name)
{	
	auto it = m_tasks.find(std::string(name));

	if (it == m_tasks.end())
	{
		return;
	}
	
	it->second.status = "done";
}

void TaskList::displayAll() const
{
	for (const auto& containerElement : m_tasks)
	{
		std::cout << containerElement.second;

		std::cout << '\n';
	}
}

size_t TaskList::count() const
{
	return m_tasks.size();
}

std::vector<const Task*>
TaskList::find(const std::set<Expression>& expressions) const
{
	std::vector<const Task*> relevantTasks;

	for (const auto& containerElement : m_tasks)
	{
		const Task& task = containerElement.second;

		for (const auto& expression : expressions)
		{
			const std::string_view field = expression.field;
			const std::string_view operatr = expression.operatr;
			const std::string_view value = expression.value;

			if (field == "name")
			{
				if (!task.nameIs(operatr, value))
					break;
			}
			else if (field == "description")
			{
				if (!task.descriptionIs(operatr, value))
					break;
			}
			else if (field == "date")
			{
				if (!task.dateTimeIs(operatr, DateTime(value)))
					break;
			}
			else if (field == "category")
			{
				if (!task.categoryIs(operatr, value))
					break;
			}
			else if (field == "status")
			{
				if (!task.statusIs(operatr, value))
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

std::ofstream& operator<<(std::ofstream& ofs, const TaskList& taskList)
{
	for (const auto& [taskName, task] : taskList.m_tasks)
	{
		ofs << task;

		if (taskList.m_tasks.find(taskName) != std::prev(taskList.m_tasks.end()))
		{
			ofs << '\n';
		}
	}

	return ofs;
}
