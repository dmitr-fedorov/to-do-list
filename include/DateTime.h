#pragma once

#include <iostream>
#include <string_view>

/*
   Класс, который представляет собой дату (год, месяц, день) и время (часы и минуты).
*/
class DateTime
{
public:
	/*
	  dateTimeView - строка с датой в формате "yyyy-mm-dd hh:mm".
	  Констркутор выбрасывает исключение const char* с сообщением в следующих случаях:
	  - Формат строки не соответствует формату "yyyy-mm-dd hh:mm";
	  - Дата не валидна;
	  - Время не валидно;
	*/
	DateTime(const std::string_view dateTimeView);
	/*
	  Констркутор выбрасывает исключение const char* с сообщением, если время или дата не валидны.
	*/
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
