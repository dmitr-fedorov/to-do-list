#pragma once

#include <regex>

#include "DateTime.h"

namespace DateTimeUtility
{
	/*
	  ���������� ���������, ����������� ��� ��������
	  ������������ ������� ����.
	*/
	const std::regex CONST_DATE_TIME_REGEX("[0-9]{4}-[0-9]{2}-[0-9]{2} [0-9]{2}:[0-9]{2}");
	/*
	  ������� ������ DateTime �� ���������� ������ dateTimeView � ���������� ���.
	  ����������� ���������� � ���������� � ��������� �������:
	  - ������ ���� �����������,
	  - ���� �� �������,
	  - ����� �� �������.
	*/
	DateTime ConstructDateTime(const std::string_view dateTimeView);

	/*
	  ���������� true, ���� ������ ���� � ������� � ������ inpView �������������
	  ����������� ��������� CONST_DATE_TIME_REGEX.
	  � ��������� ������ ���������� false.
	*/
	bool IsDateTimeFormatCorrect(const std::string_view dateTimeView);
	/*
	  ��������� ���������� ����.
	*/
	bool IsDateValid(const int year, const int month, const int day);
	/*
	  ��������� ���������� �������.
	*/
	bool IsTimeValid(const int hours, const int minutes);
};
