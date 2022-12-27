#include "DateTimeUtility.h"

#include <string>
#include <cctype>

DateTime DateTimeUtility::ConstructDateTime(const std::string_view dateTimeView)
{
	static const int YEAR_INDEX = 0;
	static const int YEAR_LENGTH = 4;

	static const int MONTH_INDEX = 5;
	static const int MONTH_LENGTH = 2;

	static const int DAY_INDEX = 8;
	static const int DAY_LENGTH = 2;

	static const int HOURS_INDEX = 11;
	static const int HOURS_LENGTH = 2;

	static const int MINUTES_INDEX = 14;
	static const int MINUTES_LENGTH = 2;

	if (!IsDateTimeFormatCorrect(dateTimeView))
		throw "Date and time format is incorrect! Suitable format: \"yyyy-mm-dd hh:mm\".";

	std::string str_year(dateTimeView.substr(YEAR_INDEX, YEAR_LENGTH));
	std::string str_month(dateTimeView.substr(MONTH_INDEX, MONTH_LENGTH));
	std::string str_day(dateTimeView.substr(DAY_INDEX, DAY_LENGTH));
	std::string str_hours(dateTimeView.substr(HOURS_INDEX, HOURS_LENGTH));
	std::string str_minutes(dateTimeView.substr(MINUTES_INDEX, MINUTES_LENGTH));

	int year = std::stoi(str_year);
	int month = std::stoi(str_month);
	int day = std::stoi(str_day);
	int hours = std::stoi(str_hours);
	int minutes = std::stoi(str_minutes);

	if (!IsDateValid(year, month, day))
		throw "Date is invalid!";

	if (!IsTimeValid(hours, minutes))
		throw "Time is invalid!";

	return DateTime(year, month, day, hours, minutes);
}

bool DateTimeUtility::IsDateTimeFormatCorrect(const std::string_view dateTimeView)
{
	static const int NUM_REQUIRED_SYMBOLS = 16;

	static const int INDX_FIRST_DASH = 4;
	static const int INDX_SECOND_DASH = 7;
	static const int INDX_WHITESPACE = 10;
	static const int INDX_COLON = 13;

	const int end = dateTimeView.size();

	if (end != NUM_REQUIRED_SYMBOLS)
		return false;

	for (int i = 0; i < end; i++)
	{
		if (i == INDX_FIRST_DASH || i == INDX_SECOND_DASH)
		{
			if (dateTimeView[i] != '-')
				return false;
		}
		else if (i == INDX_WHITESPACE)
		{
			if (dateTimeView[i] != ' ')
				return false;
		}
		else if (i == INDX_COLON)
		{
			if (dateTimeView[i] != ':')
				return false;
		}
		else if (!std::isdigit(dateTimeView[i]))
			return false;
	}

	return true;
}

bool DateTimeUtility::IsDateValid(const int year, const int month, const int day)
{
	bool validation = true;

	if (year >= 1900 && year <= 2200)
	{
		if (month >= 1 && month <= 12 && day > 0 && day <= 31)
		{
			if (month == 4 || month == 6 || month == 9 || month == 11)
			{
				if (day > 30)
					validation = false;
			}
			else if (month == 2)
			{
				if ((year % 400 == 0 || (year % 100 != 0 && year % 4 == 0)))
				{
					if (day > 29)
						validation = false;
				}
				else if (day > 28)
					validation = false;
			}
		}
		else
			validation = false;
	}
	else
		validation = false;

	return validation;
}

bool DateTimeUtility::IsTimeValid(const int hours, const int minutes)
{
	if (hours < 0 || hours > 23)
		return false;

	if (minutes < 0 || minutes > 59)
		return false;

	return true;
}
