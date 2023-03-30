#pragma once

#include "Command.h"
#include "TaskList.h"

class CommandAdd : public Command
{
public:
	CommandAdd(TaskList& taskList);

	~CommandAdd() = default;

	void execute(const std::string_view arguments) override;

private:
	static const int REQUIRED_NUMBER_OF_FIELDS = 4;

	static const int INDX_NAME = 0;
	static const int INDX_DESCRIPTION = 1;
	static const int INDX_DATE = 2;
	static const int INDX_CATEGORY = 3;
	
	TaskList& m_taskList;
};
