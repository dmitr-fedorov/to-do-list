#pragma once

#include <string>
#include <string_view>

/*
  Статус выполнения задачи.
*/
enum TaskStatus
{
	on,
	done,  	
};

/*
  Класс, который представляет собой задачу.
*/
class Task
{
public:
	/* 
	  Логика класса не подразумевает наличие конструктора по - умолчанию.
	*/

	Task(const std::string_view name, const std::string_view descr,
		const std::string_view date, const std::string_view categ);
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
	void Update(const std::string_view descr, const std::string_view date,
		const std::string_view categ);

	void Display() const;

	bool NameIs(const std::string_view op, const std::string_view value) const;
	bool DescriptionIs(const std::string_view op, const std::string_view value) const;
	bool DateIs(const std::string_view op, const std::string_view value) const;
	bool CategoryIs(const std::string_view op, const std::string_view value) const;
	bool StatusIs(const std::string_view op, const std::string_view value) const;

private:	
	std::string m_name;
	std::string m_description;
	std::string m_date;
	std::string m_category;
	TaskStatus m_status;
};
