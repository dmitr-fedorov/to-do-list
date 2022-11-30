#pragma once

#include <string>
#include <string_view>
#include <ostream>

enum TaskStatus
{
	on,
	done,  	
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

	void Display(std::ostream& out) const;

	bool NameIs(const std::string& op, const std::string& value);
	bool DescriptionIs(const std::string& op, const std::string& value);
	bool DateIs(const std::string& op, const std::string& value);
	bool CategoryIs(const std::string& op, const std::string& value);
	bool StatusIs(const std::string& op, const std::string& value);

private:	
	std::string m_name;
	std::string m_description;
	std::string m_date;
	std::string m_category;
	TaskStatus m_status;
};
