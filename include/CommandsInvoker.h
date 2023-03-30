#pragma once

#include "TaskList.h"
#include "CommandAdd.h"
#include "CommandUpdate.h"
#include "CommandDelete.h"
#include "CommandDone.h"
#include "CommandSelect.h"

class CommandsInvoker
{
public:
	CommandsInvoker(TaskList& taskList);

	~CommandsInvoker() = default;

	void executeCommand(const std::string_view commandAndArgumentsStr);

private:
	TaskList& m_taskList;

	CommandAdd m_commandAdd;
	CommandUpdate m_commandUpdate;
	CommandDelete m_commandDelete;
	CommandDone m_commandDone;
	CommandSelect m_commandSelect;
};
