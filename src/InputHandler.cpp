#include "InputHandler.h"

#include <iostream>
#include <sstream>

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
			const auto divLine = GetCommandAndArguments(inputLine);

			if (divLine.command == "add")
			{
				HandleAdd(divLine.arguments);
			}
			else if (divLine.command == "done")
			{
				HandleDone(divLine.arguments);
			}
			else if (divLine.command == "update")
			{
				HandleUpdate(divLine.arguments);
			}
			else if (divLine.command == "delete")
			{
				HandleDelete(divLine.arguments);
			}
			else if (divLine.command == "select")
			{
				HandleSelect(divLine.arguments);
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

void InputHandler::HandleAdd(const std::string_view argsView)
{	
	// Количество необходимых аргументов
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
		
		if (m_tasksManager.ContainsTask(Unquoted(argWords[INDX_NAME])))
		{
			throw "This task already exists!";
		}

		const DateTime dateTime((Unquoted(argWords[INDX_DATE])));

		m_tasksManager.AddTask( Unquoted(argWords[INDX_NAME]), Unquoted(argWords[INDX_DESCRIPTION]),
			                    dateTime, Unquoted(argWords[INDX_CATEGORY]) );
	}
	catch (const char* msg)
	{
		std::cout << msg << std::endl;
		return;
	}
}

void InputHandler::HandleDone(const std::string_view argsView)
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

void InputHandler::HandleUpdate(const std::string_view argsView)
{
	try
	{
		const auto unquotedArgs = Unquoted(argsView);

		if ( !m_tasksManager.ContainsTask(unquotedArgs) )
		{
			throw "This task does not exist!";
		}

		std::cout << "Please, enter new fields." << std::endl;

		std::string inputLine;

		const auto newName(ReadName(unquotedArgs));

		std::cout << "description: ";
		std::getline(std::cin, inputLine, '\n');
		const auto newDescription(inputLine);

		const auto newDateTime(ReadDateTime());

		std::cout << "category: ";
		std::getline(std::cin, inputLine, '\n');
		const auto newCategory(inputLine);
		
		if (unquotedArgs != Unquoted(newName))
		{
			m_tasksManager.ReplaceTask(unquotedArgs, Unquoted(newName), Unquoted(newDescription), newDateTime, Unquoted(newCategory));
		}
		else
		{
			m_tasksManager.UpdateTask(Unquoted(newName), Unquoted(newDescription), newDateTime, Unquoted(newCategory));
		}		
	}
	catch (const char* msg)
	{
		std::cout << msg << std::endl;
		return;
	}
}

void InputHandler::HandleDelete(const std::string_view argsView)
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

void InputHandler::HandleSelect(const std::string_view argsView)
{
	try
	{
		const auto indx = argsView.find_first_not_of(" ", 0);

		if (indx == std::string_view::npos)
		{
			throw "You should provide arguments for the command!";
		}

		if (argsView[indx] != '*')
		{
			throw "After \'select\' must come the symbol \'*\'!";
		}

		const auto indx2 = argsView.find_first_not_of(" ", indx + 1);

		if (indx2 == std::string_view::npos)
		{
			m_tasksManager.DisplayAllTasks();

			return;
		}

		if (indx2 == indx + 1)
		{
			throw "Symbols right after \'*\' are not allowed!";
		}

		const auto indx3 = argsView.find_first_of(" ", indx2);  //

		if (argsView.substr(indx2, indx3 - indx2) != "where")
		{
			throw "After \'*\' must come the word \'where\'!";
		}
		
		if (indx3 == std::string_view::npos)
		{
			throw "Predicate is empty!";
		}

		const auto searchMap = AnalyzePredicate(argsView.substr(indx3, argsView.size() - indx3));

		auto vec(m_tasksManager.SearchTasks(searchMap));

		if (vec.empty())
			throw "No suitable tasks found.";

		for (auto taskRef : vec)
		{
			taskRef->Display();
		}
	}
	catch (const char* msg)
	{
		std::cout <<  msg << std::endl;
		return;
	}
}

DividedInput InputHandler::GetCommandAndArguments(const std::string_view inpView)
{
	DividedInput retVal;

	size_t first = 0;
	size_t second = inpView.find_first_of(" ", first);
	if (second != std::string_view::npos)
	{
		retVal.command = inpView.substr(first, second - first);
	}

	first = second + 1;
	second = inpView.size();

	retVal.arguments = inpView.substr(first, second - first);

	return retVal;
}

const std::vector<std::string_view>
InputHandler::SplitIntoWords(const std::string_view inpView)
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

std::string_view InputHandler::Unquoted(const std::string_view inpView)
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

std::string InputHandler::ReadName(const std::string_view argNameView)
{
	std::string inputLine;
	std::string_view unqInpLineView;

	std::cout << "name: ";

	while (std::getline(std::cin, inputLine, '\n'))
	{
		unqInpLineView = Unquoted(inputLine);

		if (SplitIntoWords(inputLine).size() < 1)
		{
			std::cout << "Try again: ";
			continue;
		}
		else if (unqInpLineView == Unquoted(argNameView))
		{
			break;
		}
		else if (m_tasksManager.ContainsTask(unqInpLineView))
		{
			std::cout << "This task already exists!" << std::endl;
			std::cout << "Try again: ";
			continue;
		}
		else if (unqInpLineView.find('\"') != unqInpLineView.npos)
		{
			std::cout << "Redundant quotes are not allowed in name!" << std::endl;
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

DateTime InputHandler::ReadDateTime()  
{
	std::string inputLine;

	std::cout << "date: ";

	while (std::getline(std::cin, inputLine, '\n'))
	{
		try
		{
			const DateTime retDateTime((Unquoted(inputLine)));

			return retDateTime;
		}
		catch (const char* msg)
		{
			std::cout << msg << std::endl;
			std::cout << "Try again: ";
			continue;
		}
	}
}

const std::map<std::string_view, std::pair<std::string_view, std::string_view>>
InputHandler::AnalyzePredicate(const std::string_view predView)
{
	std::map<std::string_view, std::pair<std::string_view, std::string_view>> retMap;
	std::pair <std::string_view, std::pair<std::string_view, std::string_view>> tmpPair;

	size_t end = predView.length();
	size_t i = 0;

	while (i < end)
	{
		if (predView[i] == ' ')
		{
			i++;
		}
		else if (predView[i] == '<' || predView[i] == '=' || predView[i] == '>' || predView[i] == '"')
		{
			throw "Incorrect predicate!";
		}
		else
		{
			for (size_t j = i; j < end; j++)
			{
				if (predView[j] == ' ')
				{
					const auto word = predView.substr(i, j - i);

					if (word == "and")
					{
						if (retMap.empty())
							throw "The word \'and\' should not be the first word in predicate!";
						
						i = j + 1;

						break;						
					}
					else if (word == "like")
					{
						throw "Incorrect usage of word \'like\'!";
					}
					else
					{
						tmpPair.first = word;

						const auto result = ReadSelectOperator(predView, j + 1);

						tmpPair.second.first = result.operatr;

						const auto result2 = ReadSelectValue(predView, result.indexAfterOperator);

						tmpPair.second.second = Unquoted(result2.value);

						i = result2.indexAfterValue;
					}

					if (!retMap.emplace(tmpPair).second)
						throw "You cannot enter one field several times in predicate!";

					tmpPair = {};

					break;
				}
				else if (predView[j] == '<' || predView[j] == '=' || predView[j] == '>')
				{
					if (j == end - 1)
					{
						throw "No value after operator!";
					}

					tmpPair.first = predView.substr(i, j - i);
					
					if (predView[j + 1] == '=')
					{
						tmpPair.second.first = predView.substr(j, 2);
						j += 2;
					}
					else
					{
						tmpPair.second.first = predView.substr(j, 1);
						j++;
					}

					const auto result = ReadSelectValue(predView, j);

					tmpPair.second.second = Unquoted(result.value);

					i = result.indexAfterValue;

					if (!retMap.emplace(tmpPair).second)
						throw "You cannot enter one field several times in predicate!";

					tmpPair = {};

					break;
				}

				if (j == end - 1)
				{
					throw "Incorrect predicate!";
				}
			}
		}
	}

	if (retMap.empty())
		throw "Predicate is empty!";

	return retMap;
}

RetSelectOperator InputHandler::ReadSelectOperator(const std::string_view predView, const size_t startPos)
{
	auto indx = predView.find_first_not_of(' ', startPos);
	auto end = predView.size();

	RetSelectOperator retStruct;

	if (indx == std::string_view::npos)
	{
		throw "No operator after field name!";
	}

	auto indx2 = predView.find_first_of(' ', indx + 1);

	if (indx2 == std::string_view::npos)
	{
		throw "No value after operator!";
	}

	retStruct.operatr = predView.substr(indx, indx2 - indx);

	retStruct.indexAfterOperator = indx2 + 1;

	return retStruct;
}

RetSelectValue InputHandler::ReadSelectValue(const std::string_view predView, const size_t startPos)
{
	const auto indx = predView.find_first_not_of(' ', startPos);
	auto end = predView.size();

	RetSelectValue retStruct;

	if (indx == std::string_view::npos)
	{
		throw "No value after operator!";
	}

	if (predView[indx] != '\"')
	{
		throw "Value after operator must be in quotes!";
	}

	auto indx2 = predView.find_first_of('\"', indx + 1);

	if (indx2 == std::string_view::npos)
	{
		throw "Value after operator must be in quotes!";
	}

	if (indx2 == indx + 1)
	{
		throw "Value in quotes is empty!";
	}

	if (indx2 < end - 1)
	{
		if (predView[indx2 + 1] != ' ')
		{
			throw "Incorrect usage of quotes in predicate!";
		}
	}

	retStruct.value = predView.substr(indx, indx2 - indx + 1);

	retStruct.indexAfterValue = indx2 + 1;

	return retStruct;
}
