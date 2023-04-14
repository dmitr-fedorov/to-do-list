#pragma once

#include "Command.h"
#include "TaskList.h"

class CommandSave : public Command
{
public:
	CommandSave(TaskList& taskList);

	~CommandSave() = default;

	void execute(const std::string_view arguments) override;

private:
	TaskList& m_taskList;
};
