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
	const auto newDescription = readValueForFieldDescription();
	const auto newDateTime = readValueForFieldDate();	
	const auto newCategory = readValueForFieldCategory();
	const auto newStatus = readValueForFieldStatus();
	
	const Task newTask{ newName, newDescription, newDateTime, newCategory, newStatus };

	if (unquotedOldName != newName)
	{
		m_taskList.replace(unquotedOldName, newTask);
	}
	else
	{
		m_taskList.update(newTask);
	}
}

std::string CommandUpdate::readNewNameForTask(const std::string_view oldTaskName)
{
	std::string newName;
	std::string_view unquotedNewName;
	
	std::cout << "name: ";

	while (true)
	{
		newName = readValue();

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

std::string CommandUpdate::readValue()
{	
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

std::string CommandUpdate::readValueForFieldDescription()
{
	std::cout << "description: ";

	return readValue();
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

std::string CommandUpdate::readValueForFieldCategory()
{
	std::cout << "category: ";
	
	return readValue();
}

std::string CommandUpdate::readValueForFieldStatus()
{
	std::cout << "status: ";

	return readValue();
}