#pragma once

#include <string>
#include <string_view>

enum TaskStatus
{
	InProgress,
	Done,  	
};

class Task
{
public:
	Task(const std::string_view& name, const std::string_view& descr,
		const std::string_view& date, const std::string_view& categ);
	~Task();

	TaskStatus GetCompletionStatus() const;
	void SetDone();
	void Update(const std::string_view& descr, const std::string_view& date,
		const std::string_view& categ);

private:	
	std::string m_name;
	std::string m_description;
	std::string m_creationDate;
	std::string m_category;
	TaskStatus m_status;
};

