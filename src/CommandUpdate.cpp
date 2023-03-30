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

	const auto unquotedName = InputAnalysisTools::Unquoted(arguments);

	if (!m_taskList.Contains(unquotedName))
	{
		throw "This task does not exist!";
	}

	std::cout << "Please, enter new fields." << '\n';

	const auto newName = ReadNewNameForTask(unquotedName);
	const auto newDescription = ReadValueForField("description");
	const auto newDateTime = ReadValueForFieldDate();
	const auto newCategory = ReadValueForField("category");

	if (unquotedName != newName)
	{
		m_taskList.Replace(unquotedName, newName, newDescription,
			newDateTime, newCategory);
	}
	else
	{
		m_taskList.Update(newName, newDescription, newDateTime, newCategory);
	}
}

std::string CommandUpdate::ReadValueForField(const std::string_view fieldName)
{
	std::cout << fieldName << ": ";
	
	std::string inputLine;
	std::string_view unquotedInputLine;

	while (std::getline(std::cin, inputLine, '\n'))
	{
		unquotedInputLine = InputAnalysisTools::Unquoted(inputLine);

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

std::string CommandUpdate::ReadNewNameForTask(const std::string_view taskName)
{
	const auto unquotedOldName = InputAnalysisTools::Unquoted(taskName);
	std::string newName;
	std::string_view unquotedNewName;

	while (true)
	{
		newName = ReadValueForField("name");

		unquotedNewName = InputAnalysisTools::Unquoted(newName);

		if (unquotedNewName == unquotedOldName)
		{
			break;
		}
		else if (m_taskList.Contains(unquotedNewName))
		{
			std::cout << "This task already exists!" << std::endl;
			std::cout << "Try again: ";
			continue;
		}

		break;
	}

	return std::string{ unquotedNewName };
}

DateTime CommandUpdate::ReadValueForFieldDate()
{
	std::cout << "date: ";
	
	std::string inputLine;

	while (std::getline(std::cin, inputLine, '\n'))
	{
		try
		{			
			return DateTime{ InputAnalysisTools::Unquoted(inputLine) };
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
