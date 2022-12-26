#pragma once

#include <regex>

#include "DateTime.h"

namespace DateTimeUtility
{
	/*
	  Регулярное выражение, необходимое для проверки
	  корректности формата даты.
	*/
	const std::regex CONST_DATE_TIME_REGEX("[0-9]{4}-[0-9]{2}-[0-9]{2} [0-9]{2}:[0-9]{2}");
	/*
	  Создает объект DateTime из переданной строки dateTimeView и возвращает его.
	  Выбрасывает исключения с сообщением в следующих случаях:
	  - Формат даты некорректен,
	  - Дата не валидна,
	  - Время не валидно.
	*/
	DateTime ConstructDateTime(const std::string_view dateTimeView);

	/*
	  Возвращает true, если формат даты и времени в строке inpView соответствует
	  регулярному выражению CONST_DATE_TIME_REGEX.
	  В противном случае возвращает false.
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
