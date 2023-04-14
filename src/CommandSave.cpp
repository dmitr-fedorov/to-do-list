#include "CommandSave.h"
#include "TaskStorageFile.h"

CommandSave::CommandSave(TaskList& taskList)
	: m_taskList(taskList)
{

}

void CommandSave::execute(const std::string_view arguments)
{
	if (!arguments.empty())
	{
		throw "This command does not take arguments!";
	}

	TaskStorageFile taskStorageFile;

	taskStorageFile << m_taskList;
}
