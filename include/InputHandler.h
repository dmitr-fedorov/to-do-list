#pragma once

#include <regex>
#include <string_view>
#include <string>
#include <vector>
#include <utility>

#include "TasksManager.h"

class InputHandler
{
public:
	InputHandler();
	~InputHandler();

	/*
	  ������� ����������� �� ���� ������� � �������, ��������� ��������� �������
	  � �������� ������-����������� ��� ���� ������.
	*/
	int StartReading();

private:
	/*
	���������� ���������, ����������� ��� ��������
	������������ ������� ��������� ������������� ����.
	*/
	static const std::regex M_CONST_DATE_REGEX;
	/*
	  ������, ��� ����� ������� � ������� ���������� ��������� ������.
	*/
	static const std::string M_CONST_STRING_EXIT;
	/*
	  ����������� �� ���� ������������� �������.
	*/
	static const std::string M_CONST_STRING_ENTER_COMMAND;

	/*
	  ������, ������� ������ ������ � � ������� �������� ����������
	  ���������� ����� ��������.
	*/
	TasksManager m_tasksManager;

	/*
	  ������������ ������� ���������� ����� ������ � ������ �
	  ������� � ������� ��������� � ������������ �����.
	  argsView - ��������� �������.
	*/
	void HandleAdd(const std::string_view& argsView);
	/*
	  ������������ ������� ��������� ����������� � ������ ������ � ��������� ����������� �
	  ������� � ������� ��������� � ������������ �����.
	  argsView - ��������� �������.
	*/
	void HandleDone(const std::string_view& argsView);
	/*
	  ������������ ������� ��������� ����� �������� � ���� ����������� � ������ ������ �
	  ������� � ������� ��������� � ������������ �����.
	  argsView - ��������� �������.
	*/
	void HandleUpdate(const std::string_view& argsView);
	/*
	  ������������ ������� �������� ������ �� ������ �
	  ������� � ������� ��������� � ������������ �����.
	  argsView - ��������� �������.
	*/
	void HandleDelete(const std::string_view& argsView);

	void HandleSelect(const std::string_view& argsView);

	/*
	  ���������� ����, ��� ������ �������� - ������ � ��������,
	  � ������ �������� - ������ � ����������� ���� �������.
	  inpView - ������ ������ � �������� � �� �����������.
	*/
	std::pair<std::string_view, std::string_view> GetCommandAndArguments(const std::string_view& inpView);

	/*
	  ��������� inpView �� ��������� ����� � ���������� ������, ��� ������ ������� - ��������� ����� � inpView.
	  ������ ��������� � ��������, ���������� �� ������ ���� ���������, ��������� ����� ������.
	  ����� ��������� � ������ ������ � ���������.
	  inpView - ������, ������� ����� ��������� �� �����.
	*/
	std::vector<std::string_view> SplitIntoWords(const std::string_view& inpView);

	/*
	  ���������� true, ���� ���� � ������ inpView ������������� ����������� ��������� M_CONST_DATE_REGEX.
	  � ��������� ������ ���������� false.
	*/
	bool IsDateFormatCorrect(const std::string_view& inpView);

	/*
	  ���� ������ inpView ��������� � �������, �� ����� ���������� ��� ������ ��� �������.
	  � ��������� ������� ���������� ��� ������.
	*/
	std::string_view Unquoted(const std::string_view& inpView);

	/*
	  ������� � ������� ����������� �� ���� ����� ������, ��������� � ����������� ����.
	  ������� � ������� ��������� � ������������ ����� �����, ���� ��� ���� ������� �����������.
	  ���������� ��������� ������, ���� ��� ������������� �����������.
	  argNameView - ��� �� ������ � ������ ������, ��� ������� ����������� ����� ���.
	*/
	std::string ReadName(const std::string_view& argNameView);

	/*
	  ������� � ������� ����������� �� ���� ���� �������� ������, ��������� � ����������� ����.
	  ������� � ������� ��������� � ������������ ����� ����, ���� ��� ���� ������� �����������.
	  ���������� ��������� ������, ���� ��� ������������� �����������.
	*/
	std::string ReadDate();

	/*
	  ����������� �������� predView.
	  ���������� ����, ��� first - ��� ����, �� �������� ����� ��������� �����,
	  second.first - ��������, ����������� � ����,
	  second.second - ��������, �� �������� ������������ �������� ����
	*/
	std::map<std::string, std::pair<std::string, std::string>>
		AnalyzePredicate(const std::string_view& predView);

	void ReadSelectOperator(const std::string_view& predView,
		std::pair<std::string, std::pair<std::string, std::string>>& pr, size_t& i, size_t& j);

	std::string ReadSelectValue(const std::string_view& predView, size_t& i);

	size_t SkipUntilPredicate(const std::string_view& argsView);
	size_t SkipUntilStar(const std::string_view& argsView, const size_t& startPos);
	size_t SkipUntilWhere(const std::string_view& argsView, const size_t& startPos);
};
