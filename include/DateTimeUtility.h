#pragma once

#include <string_view>

#include "DateTime.h"

namespace DateTimeUtility
{
	/*
	  Проверяет, соответствует ли строка dateTimeView формату "yyyy-mm-dd hh:mm"
	  Возвращает true, если строка соответствует, в противном случае возвращает false.
	*/
	bool IsDateTimeFormatCorrect(const std::string_view dateTimeView);

	/*
	  Проверяет валидность даты с учетом високосных лет.
	  Возвращает true если дата валидна, в противном случае возвращает false.
	*/
	bool IsDateValid(const int year, const int month, const int day);

	/*
	  Проверяет валидность времени.
	  Возвращает true, если время валидно, в противном случае возвращает false.
	*/
	bool IsTimeValid(const int hours, const int minutes);
};
