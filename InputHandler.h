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

	int StartReading();

private:
	static const std::regex M_CONST_DATE_REGEX;
	static const std::string M_CONST_STRING_EXIT;
	static const std::string M_CONST_STRING_ENTER_COMMAND;

	TasksManager m_tasksManager;

	void HandleAdd(const std::string_view& argsView);
	void HandleDone(const std::string_view& argsView);
	void HandleUpdate(const std::string_view& argsView);
	void HandleDelete(const std::string_view& argsView);

	std::pair<std::string_view, std::string_view> GetCommandAndArguments(const std::string_view& inpView);

	std::vector<std::string_view> SplitIntoWords(const std::string_view& inpView);

	bool IsDateFormatCorrect(const std::string_view& inpView);

	std::string_view Unquoted(const std::string_view& inpView);

	std::string ReadName(const std::string_view& argNameView);
	std::string ReadDate();
};
