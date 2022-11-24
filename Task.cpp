#include "Task.h"

#include <iostream>

Task::Task(const std::string_view& name, const std::string_view& descr,
	const std::string_view& date, const std::string_view& categ)
	: m_name(name), m_description(descr), m_creationDate(date), m_category(categ)	 
{
	m_status = TaskStatus::InProgress;
}

Task::~Task()
{

}

Task::TaskStatus Task::CompletionStatus()
{
	return m_status;
}

void Task::SetDone()
{
	std::cout << "yes" << std::endl;
	m_status = TaskStatus::Done;
}