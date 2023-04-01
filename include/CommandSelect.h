#pragma once

#include "Command.h"
#include "TaskList.h"

class CommandSelect : public Command
{
public:
	CommandSelect(TaskList& taskList);

	~CommandSelect() = default;

	void execute(const std::string_view arguments) override;

private:
	TaskList& m_taskList;
	
	size_t readFromBeginningUntilAsterisk(const std::string_view arguments);

	size_t readFromIndexUntilPredicate(const std::string_view arguments, const size_t startIndx);
};
