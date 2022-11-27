#pragma once

#include <string>
#include <string_view>

enum TaskStatus
{
	InProgress,
	Done,  	
};

/*
  Класс, представляющий собой задачу.
*/
class Task
{
public:
	// Логика класса не подразумевает наличие конструктора по-умолчанию.

	Task(const std::string_view& name, const std::string_view& descr,
		const std::string_view& date, const std::string_view& categ);
	~Task();

	/*
	  Возвращает значение TaskStatus, которое отображает
	  статус выполнения этой задачи.
	*/
	TaskStatus GetCompletionStatus() const;

	/*
	  Устанавливает эту задачу в статус выполненной. 
	*/
	void SetDone();

	/*
	  Присваивает полям этой задачи значения из аргументов.
	*/
	void Update(const std::string_view& descr, const std::string_view& date,
		const std::string_view& categ);

private:	
	std::string m_name;
	std::string m_description;
	std::string m_creationDate;
	std::string m_category;
	TaskStatus m_status;
};
