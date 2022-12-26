#include "DateTimeUtility.h"

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

	int year = stoi(str_year);
	int month = stoi(str_month);
	int day = stoi(str_day);
	int hours = stoi(str_hours);
	int minutes = stoi(str_minutes);

	if (!IsDateValid(year, month, day))
		throw "Date is invalid!";

	if (!IsTimeValid(hours, minutes))
		throw "Time is invalid!";

	return DateTime(year, month, day, hours, minutes);
}

bool DateTimeUtility::IsDateTimeFormatCorrect(const std::string_view dateTimeView)
{
	return regex_match(dateTimeView.begin(), dateTimeView.end(), CONST_DATE_TIME_REGEX);
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
