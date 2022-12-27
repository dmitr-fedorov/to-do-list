#pragma once

#include <string_view>

#include "DateTime.h"

namespace DateTimeUtility
{
	/*
	  Создает объект DateTime из переданной строки dateTimeView и возвращает его.
	  Выбрасывает исключения с сообщением в следующих случаях:
	  - Формат даты некорректен,
	  - Дата не валидна,
	  - Время не валидно.
	*/
	DateTime ConstructDateTime(const std::string_view dateTimeView);

	/*
	  Проверяет, соответствует ли строка dateTimeView формату "yyyy-mm-dd hh:mm"
	  Возвращает true, если строка соответствует, false, если не соответствует.
	*/
	bool IsDateTimeFormatCorrect(const std::string_view dateTimeView);
	/*
	  Проверяет валидность даты.
	*/
	bool IsDateValid(const int year, const int month, const int day);
	/*
	  Проверяет валидность времени.
	*/
	bool IsTimeValid(const int hours, const int minutes);
};
