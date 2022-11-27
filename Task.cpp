#include "Task.h"

Task::Task(const std::string_view& name, const std::string_view& descr,
	const std::string_view& date, const std::string_view& categ)
	: m_name(name), m_description(descr), m_creationDate(date), m_category(categ), m_status(TaskStatus::InProgress)
{

}

Task::~Task()
{

}

TaskStatus Task::GetCompletionStatus() const
{
	return m_status;
}

void Task::SetDone()
{
	m_status = TaskStatus::Done;
}

void Task::Update(const std::string_view& descr, const std::string_view& date,
	const std::string_view& categ)
{
	m_description = std::string(descr);
	m_creationDate = std::string(date);
	m_category = std::string(categ);
}
