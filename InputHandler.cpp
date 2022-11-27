#include "InputHandler.h"

#include <iostream>

const std::regex InputHandler::M_CONST_DATE_REGEX("[0-9]{4}-[0-9]{2}-[0-9]{2} [0-9]{2}:[0-9]{2}");
const std::string InputHandler::M_CONST_STRING_EXIT = "q";
const std::string InputHandler::M_CONST_STRING_ENTER_COMMAND = std::string("Enter command(") + M_CONST_STRING_EXIT + " to exit): ";

InputHandler::InputHandler()
{

}

InputHandler::~InputHandler()
{

}

int InputHandler::StartReading()
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
			const auto commandAndArguments = GetCommandAndArguments(inputLine);

			// Ссылки сделаны для удобства
			const std::string_view& cmdPartView = commandAndArguments.first;
			const std::string_view& argsPartView = commandAndArguments.second;

			if (cmdPartView == "add")
			{
				HandleAdd(argsPartView);
			}
			else if (cmdPartView == "done")
			{
				HandleDone(argsPartView);
			}
			else if (cmdPartView == "update")
			{
				HandleUpdate(argsPartView);
			}
			else if (cmdPartView == "delete")
			{
				HandleDelete(argsPartView);
			}
			else if (cmdPartView == "select")
			{

			}
			else
			{
				std::cout << "Incorrect command or number of arguments!" << std::endl;
			}

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

void InputHandler::HandleAdd(const std::string_view& argsView)
{	
	// Колличество необходимых аргументов
	static const int NUM_REQUIRED_ARGS = 4;

	// Индексы аргументов
	static const int INDX_NAME        = 0;
	static const int INDX_DESCRIPTION = 1;
	static const int INDX_DATE        = 2;
	static const int INDX_CATEGORY    = 3;
	
	try
	{
		const auto argWords(SplitIntoWords(argsView));

		if (argWords.size() != NUM_REQUIRED_ARGS)
		{
			throw "Incorrect number of arguments!";
		}
		else if (!IsDateFormatCorrect(Unquoted(argWords[INDX_DATE])))
		{
			throw "Date format is incorrect! Suitable date format: \"yyyy-mm-dd hh:mm\".";
		}
		else if (m_tasksManager.ContainsTask(Unquoted(argWords[INDX_NAME])))
		{
			throw "This task already exists!";
		}

		m_tasksManager.AddTask( Unquoted(argWords[INDX_NAME]), Unquoted(argWords[INDX_DESCRIPTION]),
			                    Unquoted(argWords[INDX_DATE]), Unquoted(argWords[INDX_CATEGORY]) );
	}
	catch (const char* msg)
	{
		std::cout << msg << std::endl;
		return;
	}
}

void InputHandler::HandleDone(const std::string_view& argsView)
{
	const auto unquotedArgs = Unquoted(argsView);

	try
	{
		std::vector<std::string_view> argWords(SplitIntoWords(argsView));

		if (!m_tasksManager.ContainsTask(unquotedArgs))
		{
			throw "This task does not exist!";
		}

		m_tasksManager.SetTaskDone(unquotedArgs);
	}
	catch (const char* msg)
	{
		std::cout << msg << std::endl;
		return;
	}
}

void InputHandler::HandleUpdate(const std::string_view& argsView)
{
	// Индексы аргументов
	static const int INDX_NAME        = 0;
	static const int INDX_DESCRIPTION = 1;
	static const int INDX_DATE        = 2;
	static const int INDX_CATEGORY    = 3;

	try
	{
		const auto unquotedArgs = Unquoted(argsView);

		if ( !m_tasksManager.ContainsTask(unquotedArgs) )
		{
			throw "This task does not exist!";
		}

		std::cout << "Please, enter new fields." << std::endl;

		std::vector<std::string> newFields;

		std::string inputLine;

		newFields.push_back(ReadName(unquotedArgs));

		std::cout << "Description: ";
		std::getline(std::cin, inputLine, '\n');
		newFields.push_back(inputLine);

		newFields.push_back(ReadDate());

		std::cout << "Category: ";
		std::getline(std::cin, inputLine, '\n');
		newFields.push_back(inputLine);

		if (unquotedArgs != Unquoted(newFields[INDX_NAME]))
		{
			m_tasksManager.ReplaceTask( unquotedArgs, Unquoted(newFields[INDX_NAME]),
				                        Unquoted(newFields[INDX_DESCRIPTION]), Unquoted(newFields[INDX_DATE]),
				                        Unquoted(newFields[INDX_CATEGORY]) );
		}
		else
		{
			m_tasksManager.UpdateTask( Unquoted(newFields[INDX_NAME]), Unquoted(newFields[INDX_DESCRIPTION]),
				                       Unquoted(newFields[INDX_DATE]), Unquoted(newFields[INDX_CATEGORY]) );
		}
	}
	catch (const char* msg)
	{
		std::cout << msg << std::endl;
		return;
	}
}

void InputHandler::HandleDelete(const std::string_view& argsView)
{
	const auto unquotedArgs = Unquoted(argsView);
	try
	{
		if (!m_tasksManager.ContainsTask(unquotedArgs))
		{
			throw "This task does not exist!";
		}

		m_tasksManager.DeleteTask(unquotedArgs);
	}
	catch (const char* msg)
	{
		std::cout << msg << std::endl;
		return;
	}
}

std::pair<std::string_view, std::string_view>
InputHandler::GetCommandAndArguments(const std::string_view& inpView)
{
	std::pair<std::string_view, std::string_view> retPair;

	size_t first = 0;
	size_t second = inpView.find_first_of(" ", first);
	if (second != std::string_view::npos)
	{
		retPair.first = inpView.substr(first, second - first);
	}

	first = second + 1;
	second = inpView.size();

	retPair.second = inpView.substr(first, second - first);

	return retPair;
}

std::vector<std::string_view>
InputHandler::SplitIntoWords(const std::string_view& inpView)
{
	std::vector<std::string_view> wordViews;

	size_t first = 0;

	while (first < inpView.size())
	{
		size_t second = 0;

		if (inpView[first] == '"')
		{
			second = inpView.find_first_of('"', first + 1);

			wordViews.emplace_back(inpView.substr(first, second - first + 1));
		}
		else
		{
			second = inpView.find_first_of(" ", first);

			if (first != second)
				wordViews.emplace_back(inpView.substr(first, second - first));
		}

		if (second == std::string_view::npos)
		{
			break;
		}

		first = second + 1;
	}

	return wordViews;
}

bool InputHandler::IsDateFormatCorrect(const std::string_view& inpView)
{
	const std::string_view unquotedDateView(Unquoted(inpView));

	return regex_match(unquotedDateView.begin(), unquotedDateView.end(), M_CONST_DATE_REGEX);
}

std::string_view InputHandler::Unquoted(const std::string_view& inpView)
{	
	const size_t inpLength = inpView.length();

	std::string_view retView;

	if (inpLength == 0)
	{
		return retView;
	}
	else if (inpLength <= 2)
	{
		retView = inpView;
	}
	else if (inpView[0] != '\"')
	{
		retView = inpView;
	}
	else if (inpView[0] == '\"' && inpView[inpLength - 1] != '\"')
	{
		retView = inpView;
	}
	else
	{
		retView = inpView.substr(1, inpLength - 2);
	}

	return retView;
}

std::string InputHandler::ReadName(const std::string_view& argNameView)
{
	std::string inputLine;

	std::cout << "Name: ";

	while (std::getline(std::cin, inputLine, '\n'))
	{
		const auto unqInpLineView = Unquoted(inputLine);

		if (SplitIntoWords(inputLine).size() < 1)
		{
			std::cout << "Try again: ";
			continue;
		}
		else if (unqInpLineView == argNameView)
		{
			break;
		}
		else if (m_tasksManager.ContainsTask(unqInpLineView))
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

	return inputLine;
}

std::string InputHandler::ReadDate()
{
	std::string inputLine;

	std::cout << "Creation date: ";

	while (std::getline(std::cin, inputLine, '\n'))
	{
		if (!IsDateFormatCorrect(inputLine))
		{
			std::cout << "Date format is incorrect! Suitable date format: \"yyyy-mm-dd hh:mm\"." << std::endl;
			std::cout << "Try again: ";

			continue;
		}
		else
			break;
	}

	return inputLine;
}