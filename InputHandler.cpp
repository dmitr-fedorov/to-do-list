#include "InputHandler.h"

#include <iostream>
#include <exception>

const std::regex InputHandler::M_C_DATE_REG_EXP("[0-9]{4}-[0-9]{2}-[0-9]{2} [0-9]{2}:[0-9]{2}");

InputHandler::InputHandler()
{

}

InputHandler::~InputHandler()
{

}

int InputHandler::StartReading()
{
	std::cout << "Enter command: ";
	
	std::string inputLine;

	while (std::getline(std::cin, inputLine, '\n'))
	{
		std::string_view inpLineView(inputLine);

		if (inpLineView == "q")
		{
			break;
		}

		try
		{
			size_t first = 0;
		    size_t second = inpLineView.find_first_of(" ", first);
		    if (second == std::string_view::npos)
		    {
				throw "Invalid input!";
		    }
		    
			std::string_view cmdPartView( inpLineView.substr(first, second - first) );
		    
		    first = second + 1;
		    second = inpLineView.size();
		    
			std::string_view argsPartView( inpLineView.substr(first, second - first) );
			
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

			}
			else if (cmdPartView == "delete")
			{

			}
			else if (cmdPartView == "select")
			{

			}
			else
			{
				throw "Incorrect command!";
			}

			std::cout << "Enter command: ";
		}
		catch (const char* msg)
		{
			std::cout << msg << std::endl;
			std::cout << "Enter command: ";
			continue;
		}
		catch (...)
		{
			std::cout << "Unexpected error occured!";
			return -1;
		}
	}

	return 0;
}

bool InputHandler::HandleAdd(const std::string_view& inpView)
{
	const int NAME_INDX = 0;
	const int DATE_INDX = 2;
	const int REQUIRED_FIELDS_NUM = 4;

	std::vector<std::string_view> argWords( SplitIntoWords(inpView) );

	if (argWords.size() != REQUIRED_FIELDS_NUM)
	{
		throw "Incorrect number of arguments!";
		return false;
	}
	else if ( !DateFormatIsCorrect( Unquoted(argWords[DATE_INDX])) )
	{
		throw "Date format is incorrect! Suitable date format: \"yyyy-mm-dd hh:mm\".";
		return false;
	}
	else if ( m_tasksManager.ContainsTask(Unquoted(argWords[NAME_INDX])) )
	{
		throw "This task already exists!";
		return false;
	}
	
	m_tasksManager.AddTask(argWords[0], argWords[1], argWords[2], argWords[3]);

	return true;
}

bool InputHandler::HandleDone(const std::string_view& inpView)
{
	const int REQUIRED_FIELDS_NUM = 1;

	std::vector<std::string_view> argWords( SplitIntoWords(inpView) );
	
	if (argWords.size() != REQUIRED_FIELDS_NUM)
	{
		throw "Incorrect number of arguments!";
		return false;
	}
	else if ( !m_tasksManager.ContainsTask(Unquoted(argWords[0])) )
	{
		throw "No such task!";
		return false;
	}
	
	m_tasksManager.SetTaskDone( Unquoted(argWords[0]) );

	return true;
}

bool InputHandler::HandleUpdate(const std::string_view& inpView)
{
	const int REQUIRED_FIELDS_NUM = 1;

	std::vector<std::string_view> argWords(SplitIntoWords(inpView));

	if (argWords.size() != REQUIRED_FIELDS_NUM)
	{
		throw "Incorrect number of arguments!";
		return false;
	}
	else if ( !m_tasksManager.ContainsTask(Unquoted(argWords[0])))
	{
		throw "No such task!";
		return false;
	}

	return true;
}

std::vector<std::string_view> InputHandler::SplitIntoWords(const std::string_view& inpView)
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

bool InputHandler::DateFormatIsCorrect(const std::string_view& inpView)
{
	std::string_view unquotedDateView( Unquoted(inpView) );

	bool result = regex_match(unquotedDateView.begin(), unquotedDateView.end(), M_C_DATE_REG_EXP);

	return result;
}

std::string_view InputHandler::Unquoted(const std::string_view& inpView)
{
	std::string_view retView;
	size_t inpLength = inpView.length();

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
