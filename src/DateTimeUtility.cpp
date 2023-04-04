#include "DateTimeUtility.h"

#include <cctype>

bool DateTimeUtility::isDateTimeFormatCorrect(const std::string_view dateTimeView)
{
	static const int NUM_REQUIRED_CHARACTERS = 16;

	static const int FIRST_DASH_INDX = 4;
	static const int SECOND_DASH_INDX = 7;
	static const int WHITESPACE_INDX = 10;
	static const int COLON_INDX = 13;

	if (dateTimeView.length() != NUM_REQUIRED_CHARACTERS)
	{
		return false;
	}

	for (size_t i = 0; i < dateTimeView.length(); i++)
	{
		if (i == FIRST_DASH_INDX || i == SECOND_DASH_INDX)
		{
			if (dateTimeView[i] != '-')
			{
				return false;
			}
		}
		else if (i == WHITESPACE_INDX)
		{
			if (dateTimeView[i] != ' ')
			{
			    return false;
			}
		}
		else if (i == COLON_INDX)
		{
			if (dateTimeView[i] != ':')
			{
				return false;
			}
		}
		else if (!std::isdigit(dateTimeView[i]))
		{
			return false;
		}
	}

	return true;
}

bool DateTimeUtility::isDateValid(const int year, const int month, const int day)
{
	if (year < 1900 || year > 2200)
	{
		return false;
	}		
	
	if (month < 1 || month > 12)
	{
		return false;
	}
	
	if (day < 1 || day > 31)
	{
		return false;
	}

	if (month == 4 || month == 6 || month == 9 || month == 11)
	{
		if (day > 30)
		{
			return false;
		}
	}
	
	if (month == 2)
	{
		if (isYearLeap(year))
		{
			if (day > 29)
			{
				return false;
			}
		}
		else 
		{
			if (day > 28)
			{
				return false;
			}
		}
	}

	return true;
}

bool DateTimeUtility::isYearLeap(const int year)
{
	return (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0));
}

bool DateTimeUtility::isTimeValid(const int hours, const int minutes)
{
	if (hours < 0 || hours > 23)
	{
		return false;
	}

	if (minutes < 0 || minutes > 59)
	{
		return false;
	}

	return true;
}
