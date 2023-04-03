#include "CommandDone.h"
#include "InputAnalysisTools.h"

CommandDone::CommandDone(TaskList& taskList)
	: m_taskList(taskList)
{

}

void CommandDone::execute(const std::string_view arguments)
{
	if (arguments.empty())
	{
		throw "You should provide arguments for the command!";
	}

	const auto unquotedName = InputAnalysisTools::unquoted(arguments);

	if (!m_taskList.contains(unquotedName))
	{
		throw "This task does not exist!";
	}

	m_taskList.setDone(unquotedName);
}
