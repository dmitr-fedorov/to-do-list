#pragma once

#include <string>
#include <string_view>

#include "DateTime.h"

/*
  Класс, который представляет собой задачу.
*/
class Task
{
public:
	Task(const std::string_view name, const std::string_view descr,
		const DateTime& dateTime, const std::string_view categ);
	~Task();

	/*
	  Устанавливает эту задачу в статус выполненной. 
	*/
	void SetDone();

	/*
	  Присваивает полям этой задачи значения из аргументов.
	*/
	void Update(const std::string_view descr, const DateTime& dateTime, const std::string_view categ);

	/*
	  Выводит эту задачу в консоль.
	*/
	void Display() const;

	bool NameIs(const std::string_view op, const std::string_view value) const;
	bool DescriptionIs(const std::string_view op, const std::string_view value) const;
	bool DateTimeIs(const std::string_view op, const DateTime& other) const;
	bool CategoryIs(const std::string_view op, const std::string_view value) const;
	bool StatusIs(const std::string_view op, const std::string_view value) const;

private:	
	std::string m_name;
	std::string m_description;
	std::string m_category;
	std::string m_status;
	DateTime m_dateTime;	
};
