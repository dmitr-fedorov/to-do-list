#include "CommandUpdate.h"
#include "InputAnalysisTools.h"

CommandUpdate::CommandUpdate(TaskList& taskList)
	: m_taskList(taskList)
{

}

void CommandUpdate::execute(const std::string_view arguments)
{
	if (arguments.empty())
	{
		throw "You should provide arguments for the command!";
	}

	const auto unquotedOldName = InputAnalysisTools::unquoted(arguments);

	if (!m_taskList.contains(unquotedOldName))
	{
		throw "This task does not exist!";
	}

	std::cout << "Please, enter new fields." << '\n';

	const auto newName = readNewNameForTask(unquotedOldName);
	const auto newDescription = readValueForField("description");
	const auto newDateTime = readValueForFieldDate();
	const auto newCategory = readValueForField("category");
	
	const Task newTask{ newName, newDescription, newDateTime, newCategory };

	if (unquotedOldName != newName)
	{
		m_taskList.replace(unquotedOldName, newTask);
	}
	else
	{
		m_taskList.update(newTask);
	}
}

std::string CommandUpdate::readValueForField(const std::string_view fieldName)
{
	std::cout << fieldName << ": ";
	
	std::string inputLine;
	std::string_view unquotedInputLine;

	while (std::getline(std::cin, inputLine, '\n'))
	{
		unquotedInputLine = InputAnalysisTools::unquoted(inputLine);

		if (unquotedInputLine.empty())
		{
			std::cout << "Try again: ";

			continue;
		}

		if (unquotedInputLine.find('\"') != std::string_view::npos)
		{
			std::cout << "Incorrect usage of quotes!" << '\n';
			std::cout << "Try again: ";

			continue;
		}

		break;
	}

	return std::string{ unquotedInputLine };
}

std::string CommandUpdate::readNewNameForTask(const std::string_view oldTaskName)
{
	std::string newName;
	std::string_view unquotedNewName;

	while (true)
	{
		newName = readValueForField("name");

		unquotedNewName = InputAnalysisTools::unquoted(newName);

		if (unquotedNewName == oldTaskName)
		{
			break;
		}
		else if (m_taskList.contains(unquotedNewName))
		{
			std::cout << "This task already exists!" << std::endl;
			std::cout << "Try again: ";

			continue;
		}

		break;
	}

	return std::string{ unquotedNewName };
}

DateTime CommandUpdate::readValueForFieldDate()
{
	std::cout << "date: ";
	
	std::string inputLine;

	while (std::getline(std::cin, inputLine, '\n'))
	{
		try
		{			
			return DateTime{ InputAnalysisTools::unquoted(inputLine) };
		}
		catch (const char* msg)
		{
			std::cout << msg << std::endl;
			std::cout << "Try again: ";

			continue;
		}
	}

	return DateTime(inputLine);
}
