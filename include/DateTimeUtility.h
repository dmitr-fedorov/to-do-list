#pragma once

#include <string_view>

namespace DateTimeUtility
{
	bool isDateTimeFormatCorrect(const std::string_view dateTimeView);

	bool isDateValid(const int year, const int month, const int day);

	bool isYearLeap(const int year);

	bool isTimeValid(const int hours, const int minutes);
};
