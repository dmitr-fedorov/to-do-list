#pragma once

#include <iostream>
#include <string_view>

class DateTime
{
public:
	DateTime(const std::string_view dateTimeView);

	~DateTime() = default;

	bool operator==(const DateTime& other) const;
	bool operator!=(const DateTime& other) const;
	bool operator<(const DateTime & other) const;
	bool operator<=(const DateTime& other) const;
	bool operator>(const DateTime& other) const;
	bool operator>=(const DateTime& other) const;

	friend std::ostream& operator<<(std::ostream& os, const DateTime& dt);

private:
	int m_year;
	int m_month;
	int m_day;
	int m_hours;
	int m_minutes;

	void validateStringFormat(const std::string_view dateTimeView) const;

	void assignMemberValuesFromString(const std::string_view dateTimeView);

	void validateMemberValues() const;
};
