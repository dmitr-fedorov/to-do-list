#include "Command.h"
#include "TaskList.h"

class CommandDelete : public Command
{
public:
	CommandDelete(TaskList& taskList);

	~CommandDelete() = default;

	void execute(const std::string_view arguments) override;

private:
	TaskList& m_taskList;
};
