#pragma once

#include <string>
#include <string_view>

class Task
{
public:
	enum TaskStatus
    {
    	Done,
    	InProgress
    };

	Task(const std::string_view& name, const std::string_view& descr,
		const std::string_view& date, const std::string_view& categ);
	~Task();

	TaskStatus CompletionStatus();
	void SetDone();

private:	
	std::string m_name;
	std::string m_description;
	std::string m_creationDate;
	std::string m_category;
	TaskStatus m_status;
};

