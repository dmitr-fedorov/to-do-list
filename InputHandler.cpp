#include "InputHandler.h"

#include <iostream>

const std::regex InputHandler::M_C_DATE_REG_EXP("[0-9]{4}-[0-9]{2}-[0-9]{2} [0-9]{2}:[0-9]{2}");

InputHandler::InputHandler()
{

}

InputHandler::~InputHandler()
{

}

void InputHandler::StartReading()
{
	const int NAME_INDX = 0;
	const int DATE_INDX = 2;
	const int ADD_FIELDS_CNT = 4;

	std::cout << "Enter command: ";
	
	std::string inputLine;

	while (std::getline(std::cin, inputLine, '\n'))
	{
		std::string_view inpLineView(inputLine);

		if (inpLineView == "q")
		{
			break;
		}

		size_t first = 0;
		size_t second = inpLineView.find_first_of(" ", first);
		if (second == std::string_view::npos)
		{
			std::cout << "Invalid input!\n"
				      << "Enter command: ";
			continue;
		}

		std::string_view cmdPartView( inpLineView.substr(first, second - first) );

		first = second + 1;
		second = inpLineView.size();

		std::string_view argsPartView( inpLineView.substr(first, second - first) );

		if (cmdPartView == "add")
		{
			std::vector<std::string_view> argWords(SplitIntoWords(argsPartView));

			if (argWords.size() != ADD_FIELDS_CNT)
			{
				std::cout << "Too few arguments!\n"
					<< "Enter command: " << std::endl;
				continue;
			}

			if (!DateFormatIsCorrect(Unquoted(argWords[DATE_INDX])))
			{
				std::cout << "Date format is incorrect! Suitable date format: \"yyyy-mm-dd hh:mm\"\n"
					<< "Enter command: " << std::endl;
				continue;
			}

			std::cout << "Everything is correct" << std::endl;
		}
		else if (cmdPartView == "done")
		{

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
			std::cout << "Incorrect command!" << std::endl;

		std::cout << "Enter command: ";
	}
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