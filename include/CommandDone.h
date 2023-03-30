#pragma once

#include "Command.h"
#include "TaskList.h"

class CommandDone : public Command
{
public:
	CommandDone(TaskList& taskList);

	~CommandDone() = default;

	void execute(const std::string_view arguments) override;

private:
	TaskList& m_taskList;
};
