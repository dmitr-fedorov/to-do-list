#include "DateTimeUtility.h"

#include <cctype>

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
