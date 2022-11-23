#pragma once

#include <string>

class Task
{
public:
	Task(std::string& name, std::string& descr, std::string& date, std::string& categ);
	~Task();
	void Edit();

private:
	std::string m_name;
	std::string m_description;
	std::string m_creationDate;
	std::string m_category;
	std::string m_completionStatus;
};

