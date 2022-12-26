#pragma once

#include <iostream>

/*
   Класс, который представляет собой дату (год, месяц, день) и время (часы и минуты).
   Класс не проводит проверку на валидность значений, передаваемых в его методы и конструктор.
*/
class DateTime
{
public:
	DateTime(const int year, const int month, const int day, const int hours, const int minutes);
	~DateTime();

	bool operator ==(const DateTime& other) const;
	bool operator !=(const DateTime& other) const;
	bool operator <(const DateTime & other) const;
	bool operator <=(const DateTime& other) const;
	bool operator >(const DateTime& other) const;
	bool operator >=(const DateTime& other) const;

	friend std::ostream& operator<<(std::ostream& os, const DateTime& dt);

private:
	int m_year;
	int m_month;
	int m_day;

	int m_hours;
	int m_minutes;
};
