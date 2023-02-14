#include "CommandHandler.h"

#include <iostream>

#include "InputAnalysisTools.h"

const std::string CommandHandler::M_CONST_STRING_EXIT = "q";
const std::string CommandHandler::M_CONST_STRING_ENTER_COMMAND = std::string("Enter command(")
                                                                 + M_CONST_STRING_EXIT + " to exit): ";

CommandHandler::CommandHandler()
{

}

CommandHandler::~CommandHandler()
{

}

int CommandHandler::StartReadingCommands()
{
	std::cout << M_CONST_STRING_ENTER_COMMAND;

	std::string inputLine;

	while (std::getline(std::cin, inputLine, '\n'))
	{
		if (inputLine == M_CONST_STRING_EXIT)
		{
			break;
		}

		try
		{
			const auto cmdAndArgs{ InputAnalysisTools::SplitCommandAndArguments(inputLine) };

			const std::string_view command  { cmdAndArgs.command };
			const std::string_view arguments{ cmdAndArgs.arguments };

			if (command == "add")
			{
				HandleAdd(arguments);
			}
			else if (command == "done")
			{
				HandleDone(arguments);
			}
			else if (command == "update")
			{
				HandleUpdate(arguments);
			}
			else if (command == "delete")
			{
				HandleDelete(arguments);
			}
			else if (command == "select")
			{
				HandleSelect(arguments);
			}
			else
			{
				std::cout << "Incorrect command!" << std::endl;
			}

			std::cout << '\n';
			std::cout << M_CONST_STRING_ENTER_COMMAND;
		}
		catch (...)
		{
			std::cout << "Unexpected error occured!";
			return -1;
		}
	}

	return 0;
}

void CommandHandler::HandleAdd(const std::string_view arguments)
{	
	// Количество необходимых аргументов
	static const int NUM_REQUIRED_ARGS = 4;

	// Индексы полей в аргументах
	static const int INDX_NAME        = 0;
	static const int INDX_DESCRIPTION = 1;
	static const int INDX_DATE        = 2;
	static const int INDX_CATEGORY    = 3;
	
	try
	{
		const auto fields{ InputAnalysisTools::SplitIntoWords(arguments) };

		if (fields.size() != NUM_REQUIRED_ARGS)
		{
			throw "Incorrect number of arguments!";
		}
		
		if (m_taskList.Contains(fields[INDX_NAME]))
		{
			throw "This task already exists!";
		}

		for (const std::string_view field : fields)
		{
			if (field.find('\"') != std::string_view::npos)
			{
				throw "Incorrect usage of quotes in arguments!";
			}
		}

		m_taskList.Add( fields[INDX_NAME], fields[INDX_DESCRIPTION],
			DateTime{ fields[INDX_DATE] }, fields[INDX_CATEGORY] );
	}
	catch (const char* msg)
	{
		std::cout << msg << std::endl;
		return;
	}
}

void CommandHandler::HandleDone(const std::string_view taskName)
{
	const auto unquotedName{ InputAnalysisTools::Unquoted(taskName) };

	try
	{
		if (!m_taskList.Contains(unquotedName))
		{
			throw "This task does not exist!";
		}

		m_taskList.SetDone(unquotedName);
	}
	catch (const char* msg)
	{
		std::cout << msg << std::endl;
		return;
	}
}

void CommandHandler::HandleUpdate(const std::string_view taskName)
{
	try
	{
		const auto unquotedName{ InputAnalysisTools::Unquoted(taskName) };

		if (!m_taskList.Contains(unquotedName))
		{
			throw "This task does not exist!";
		}

		std::cout << "Please, enter new fields." << '\n';

		const auto newName{ ReadTaskName(unquotedName) };

		const auto newDescription{ ReadFieldValue("description") };

		const auto newDateTime{ ReadDateTime() };

		const auto newCategory{ ReadFieldValue("category") };
		
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
	catch (const char* msg)
	{
		std::cout << msg << std::endl;
		return;
	}
}

void CommandHandler::HandleDelete(const std::string_view taskName)
{
	const auto unquotedName{ InputAnalysisTools::Unquoted(taskName) };

	try
	{
		if (!m_taskList.Contains(unquotedName))
		{
			throw "This task does not exist!";
		}

		m_taskList.Delete(unquotedName);
	}
	catch (const char* msg)
	{
		std::cout << msg << std::endl;
		return;
	}
}

void CommandHandler::HandleSelect(const std::string_view arguments)
{
	try
	{
		if (m_taskList.Count() == 0)
		{
			throw "Task list is empty!";
		}

		const auto indx = arguments.find_first_not_of(" ", 0);

		if (indx == std::string_view::npos)
		{
			throw "You should provide arguments for the command!";
		}

		if (arguments[indx] != '*')
		{
			throw "After \'select\' must come the character \'*\'!";
		}

		const auto indx2 = arguments.find_first_not_of(" ", indx + 1);

		if (indx2 == std::string_view::npos)
		{
			m_taskList.DisplayAll();

			return;
		}

		if (indx2 == indx + 1)
		{
			throw "Characters right after \'*\' are not allowed!";
		}

		const auto indx3 = arguments.find_first_of(" ", indx2);

		if (arguments.substr(indx2, indx3 - indx2) != "where")
		{
			throw "After \'*\' must come the word \'where\'!";
		}
		
		if (indx3 == std::string_view::npos)
		{
			throw "Predicate is empty!";
		}

		const auto predicate{ arguments.substr(indx3, arguments.size() - indx3) };

		const auto expressions{ InputAnalysisTools::AnalyzePredicate(predicate) };

		const auto relevantTasks{ m_taskList.Find(expressions) };

		if (relevantTasks.empty())
		{
			throw "No relevant tasks found.";
		}

		for (auto taskPtr : relevantTasks)
		{
			taskPtr->Display();

			std::cout << '\n';
		}
	}
	catch (const char* msg)
	{
		std::cout <<  msg << std::endl;
		return;
	}
}

std::string CommandHandler::ReadFieldValue(const std::string_view fieldName)
{
	std::string inputLine;
	std::string_view unquotedInputLine;

	if (!fieldName.empty())
	{
		std::cout << fieldName << ": ";
	}

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

std::string CommandHandler::ReadTaskName(const std::string_view taskName)
{
	std::string newName;
	const auto unquotedOldName{ InputAnalysisTools::Unquoted(taskName) };

	std::cout << "name: ";

	while (true)
	{
		newName = ReadFieldValue();

		const auto unquotedNewName{ InputAnalysisTools::Unquoted(newName) };

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
		else
		{
			break;
		}
	}

	return std::string{ newName };
}

DateTime CommandHandler::ReadDateTime()
{
	std::string inputLine;

	std::cout << "date: ";

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
}
