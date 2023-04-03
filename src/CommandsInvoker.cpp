#include "CommandsInvoker.h"
#include "InputAnalysisTools.h"

CommandsInvoker::CommandsInvoker(TaskList& taskList)
	: m_taskList(taskList), m_commandAdd(taskList), m_commandUpdate(taskList),
	m_commandDelete(taskList), m_commandDone(taskList), m_commandSelect(taskList)
{

}

void CommandsInvoker::executeCommand(const std::string_view commandAndArgumentsStr)
{
	const auto separatedCommandAndArguments =
		InputAnalysisTools::splitCommandAndArguments(commandAndArgumentsStr);

	const std::string_view command = separatedCommandAndArguments.command;
	const std::string_view arguments = separatedCommandAndArguments.arguments;

	if (command == "add")
	{
		m_commandAdd.execute(arguments);
	}
	else if (command == "done")
	{
		m_commandDone.execute(arguments);
	}
	else if (command == "update")
	{
		m_commandUpdate.execute(arguments);
	}
	else if (command == "delete")
	{
		m_commandDelete.execute(arguments);
	}
	else if (command == "select")
	{
		m_commandSelect.execute(arguments);
	}
	else
	{
		throw "Incorrect command!";
	}
}
