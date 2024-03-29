#pragma once

#include "Command.h"
#include "TaskList.h"

class CommandUpdate : public Command
{
public:
	CommandUpdate(TaskList& taskList);

	~CommandUpdate() = default;

	void execute(const std::string_view arguments) override;

private:
	TaskList& m_taskList;

	std::string readNewNameForTask(const std::string_view oldTaskName);
	
	std::string readValue();

	std::string readValueForFieldDescription();

	DateTime readValueForFieldDate();

	std::string readValueForFieldCategory();

	std::string readValueForFieldStatus();
};
