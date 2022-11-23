#pragma once

#include <regex>
#include <string_view>
#include <vector>

#include "TasksManager.h"

class InputHandler
{
public:
	InputHandler();
	~InputHandler();

	void StartReading();

private:
	static const std::regex M_C_DATE_REG_EXP;

	TasksManager m_tasksManager;

	bool HandleAdd(const std::string_view& inpView);

	std::vector<std::string_view> SplitIntoWords(const std::string_view& inpView);

	bool DateFormatIsCorrect(const std::string_view& inpView);

	std::string_view Unquoted(const std::string_view& inpView);
};
