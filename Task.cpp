#include "Task.h"

Task::Task(std::string& name, std::string& descr, std::string& date, std::string& categ)
	: m_name(name), m_description(descr), m_creationDate(date), m_category(categ)
{

}

Task::~Task()
{

}