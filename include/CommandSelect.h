#pragma once

#include "Command.h"
#include "TaskList.h"

class CommandSelect : public Command
{
public:
	CommandSelect(TaskList& taskList);

	~CommandSelect() = default;

	void execute(std::string_view arguments) override;

private:
	TaskList& m_taskList;
};
