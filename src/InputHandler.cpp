#include "InputHandler.h"

#include <iostream>
#include <sstream>

const std::string InputHandler::M_CONST_STRING_EXIT = "q";
const std::string InputHandler::M_CONST_STRING_ENTER_COMMAND = std::string("Enter command(")
                                                                 + M_CONST_STRING_EXIT + " to exit): ";

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
			const auto cmdAndArgs{ SplitCommandAndArguments(inputLine) };

			const auto command  { cmdAndArgs.command };
			const auto arguments{ cmdAndArgs.arguments };

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

void InputHandler::HandleAdd(const std::string_view arguments)
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
		const auto fields{ SplitIntoWords(arguments) };

		if (fields.size() != NUM_REQUIRED_ARGS)
		{
			throw "Incorrect number of arguments!";
		}
		
		if (m_tasksManager.ContainsTask(fields[INDX_NAME]))
		{
			throw "This task already exists!";
		}

		for (int i = 0; i < NUM_REQUIRED_ARGS; i++)
		{
			if (fields[i].find('\"') != std::string_view::npos)
			{
				throw "Incorrect usage of quotes in arguments!";
			}
		}

		m_tasksManager.AddTask( fields[INDX_NAME], fields[INDX_DESCRIPTION],
			DateTime{ fields[INDX_DATE] }, fields[INDX_CATEGORY] );
	}
	catch (const char* msg)
	{
		std::cout << msg << std::endl;
		return;
	}
}

void InputHandler::HandleDone(const std::string_view taskName)
{
	const auto unquotedName{ Unquoted(taskName) };

	try
	{
		if (!m_tasksManager.ContainsTask(unquotedName))
		{
			throw "This task does not exist!";
		}

		m_tasksManager.SetTaskDone(unquotedName);
	}
	catch (const char* msg)
	{
		std::cout << msg << std::endl;
		return;
	}
}

void InputHandler::HandleUpdate(const std::string_view taskName)
{
	try
	{
		const auto unquotedName{ Unquoted(taskName) };

		if (!m_tasksManager.ContainsTask(unquotedName))
		{
			throw "This task does not exist!";
		}

		std::cout << "Please, enter new fields." << '\n';

		const auto newName{ ReadName(unquotedName) };

		const auto newDescription{ ReadField("description") };

		const auto newDateTime{ ReadDateTime() };

		const auto newCategory{ ReadField("category") };
		
		if (unquotedName != newName)
		{
			m_tasksManager.ReplaceTask(unquotedName, newName, newDescription,
				newDateTime, newCategory);
		}
		else
		{
			m_tasksManager.UpdateTask(newName, newDescription, newDateTime, newCategory);
		}		
	}
	catch (const char* msg)
	{
		std::cout << msg << std::endl;
		return;
	}
}

void InputHandler::HandleDelete(const std::string_view taskName)
{
	const auto unquotedName = Unquoted(taskName);

	try
	{
		if (!m_tasksManager.ContainsTask(unquotedName))
		{
			throw "This task does not exist!";
		}

		m_tasksManager.DeleteTask(unquotedName);
	}
	catch (const char* msg)
	{
		std::cout << msg << std::endl;
		return;
	}
}

void InputHandler::HandleSelect(const std::string_view arguments)
{
	try
	{
		const auto indx = arguments.find_first_not_of(" ", 0);

		if (indx == std::string_view::npos)
		{
			throw "You should provide arguments for the command!";
		}

		if (arguments[indx] != '*')
		{
			throw "After \'select\' must come the symbol \'*\'!";
		}

		const auto indx2 = arguments.find_first_not_of(" ", indx + 1);

		if (indx2 == std::string_view::npos)
		{
			m_tasksManager.DisplayAllTasks();

			return;
		}

		if (indx2 == indx + 1)
		{
			throw "Symbols right after \'*\' are not allowed!";
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

		const auto expressions{ AnalyzePredicate(predicate) };

		const auto suitableTasks{ m_tasksManager.SearchTasks(expressions) };

		if (suitableTasks.empty())
		{
			throw "No suitable tasks found.";
		}

		for (auto taskPtr : suitableTasks)
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

InputHandler::CommandAndArguments
InputHandler::SplitCommandAndArguments(const std::string_view line)
{
	CommandAndArguments retStruct;

	if (line.empty())
	{
		return retStruct;
	}

	size_t indx = 0;
	size_t indx2 = line.find_first_of(' ', indx);

	if (indx2 == std::string_view::npos)
	{
		retStruct.command = line.substr(indx, line.size());

		return retStruct;
	}

	retStruct.command = line.substr(indx, indx2 - indx);

	indx = indx2 + 1;
	indx2 = line.size();

	retStruct.arguments = line.substr(indx, indx2 - indx);

	return retStruct;
}

std::vector<std::string_view>
InputHandler::SplitIntoWords(const std::string_view line)
{
	std::vector<std::string_view> words;

	if (line.empty())
	{
		return words;
	}

	size_t indx = line.find_first_not_of(' ', 0);

	if (indx == std::string_view::npos)
	{
		return words;
	}

	size_t indx2 = 0;
	size_t end = line.size();

	while (indx < end)
	{
		if (line[indx] == '\"')
		{
			indx2 = indx;

			while (true)
			{
				indx2 = line.find_first_of('\"', indx2 + 1);

				if (indx2 != std::string_view::npos)
				{
					if (indx2 < end - 1)
					{
						if (line[indx2 + 1] == ' ')
						{
							if (indx2 != indx + 1)
							{
								words.push_back(line.substr(indx + 1, indx2 - indx - 1));
							}

							indx = indx2 + 2;
							break;
						}
						else
						{
							indx2 += 1;
							continue;
						}
					}
					else
					{
						if (indx2 != indx + 1)
						{
							words.push_back(line.substr(indx + 1, indx2 - indx - 1));
						}

						indx = end;
						break;
					}
				}
				else
				{
					indx2 = line.find_first_of(' ', indx);

					if (indx2 != std::string_view::npos)
					{
						words.push_back(line.substr(indx, indx2 - indx));
					}
					else
					{
						words.push_back(line.substr(indx, end - indx));
					}

					break;
				}
			}
		}
		else
		{
			indx2 = line.find_first_of(' ', indx);

			if (indx2 != std::string_view::npos)
			{
				words.push_back(line.substr(indx, indx2 - indx));				
			}
			else
			{
				words.push_back(line.substr(indx, end - indx));
			}
		}

		if (indx2 == std::string_view::npos)
		{
			break;
		}

		indx = line.find_first_not_of(' ', indx2 + 1);
	}

	return words;
}

std::string_view InputHandler::Unquoted(const std::string_view line)
{	
	const size_t lineLength = line.length();

	std::string_view unquotedLine;
	
	if (lineLength <= 2)
	{
		return line;
	}

	if (line[0] != '\"' || line[lineLength - 1] != '\"')
	{
		return line;
	}

	unquotedLine = line.substr(1, lineLength - 2);

	return unquotedLine;
}

std::string InputHandler::ReadField(const std::string_view fieldName)
{
	std::string inputLine;
	std::string_view unquotedInputLine;

	if (!fieldName.empty())
	{
		std::cout << fieldName << ": ";
	}

	while (std::getline(std::cin, inputLine, '\n'))
	{
		unquotedInputLine = Unquoted(inputLine);

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

std::string InputHandler::ReadName(const std::string_view taskName)
{
	std::string newName;

	std::cout << "name: ";

	while (true)
	{
		newName = ReadField();

		const auto unquotedNewName(Unquoted(newName));

		if (unquotedNewName == Unquoted(taskName))
		{
			break;
		}
		else if (m_tasksManager.ContainsTask(unquotedNewName))
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

DateTime InputHandler::ReadDateTime()  
{
	std::string inputLine;

	std::cout << "date: ";

	while (std::getline(std::cin, inputLine, '\n'))
	{
		try
		{
			return DateTime( Unquoted(inputLine) );
		}
		catch (const char* msg)
		{
			std::cout << msg << std::endl;
			std::cout << "Try again: ";
			continue;
		}
	}
}

const std::set<TasksManager::Expression>
InputHandler::AnalyzePredicate(const std::string_view predicate)
{
	size_t end = predicate.length();
	size_t i = 0;

	std::set<TasksManager::Expression> expressions;

	TasksManager::Expression tmpExpression;

	while (i < end)
	{
		if (predicate[i] == ' ')
		{
			i++;
		}
		else if (predicate[i] == '<' || predicate[i] == '=' ||
			 predicate[i] == '>' || predicate[i] == '"')
		{
			throw "Incorrect predicate!";
		}
		else
		{
			for (size_t j = i; j < end; j++)
			{
				if (predicate[j] == ' ')
				{
					const auto word = predicate.substr(i, j - i);

					if (word == "and")
					{
						if (expressions.empty())
						{
							throw "The word \'and\' should not be the first word in predicate!";
						}
						
						i = j + 1;

						break;						
					}
					else if (word == "like")
					{
						throw "Incorrect usage of word \'like\'!";
					}
					else
					{
						tmpExpression.field = word;

						const auto resOperator = ReadOperatorFromPredicate(predicate, j + 1);

						tmpExpression.operatr = resOperator.operatr;

						const auto resValue = ReadValueFromPredicate(predicate, resOperator.indexAfterOperator);

						tmpExpression.value = resValue.value;

						i = resValue.indexAfterValue;
					}

					if (!expressions.insert(tmpExpression).second)
					{
						throw "You cannot enter one field several times in predicate!";
					}

					tmpExpression = {};

					break;
				}
				else if (predicate[j] == '<' || predicate[j] == '=' || predicate[j] == '>')
				{
					if (j == end - 1)
					{
						throw "No value after operator!";
					}

					tmpExpression.field = predicate.substr(i, j - i);
					
					if (predicate[j + 1] == '=')
					{
						tmpExpression.operatr = predicate.substr(j, 2);
						j += 2;
					}
					else
					{
						tmpExpression.operatr = predicate.substr(j, 1);
						j++;
					}

					const auto resValue = ReadValueFromPredicate(predicate, j);

					tmpExpression.value = resValue.value;

					i = resValue.indexAfterValue;

					if (!expressions.insert(tmpExpression).second)
					{
						throw "You cannot enter one field several times in predicate!";
					}

					tmpExpression = {};

					break;
				}

				if (j == end - 1)
				{
					throw "Incorrect predicate!";
				}
			}
		}
	}

	if (expressions.empty())
	{
		throw "Predicate is empty!";
	}

	return expressions;
}

InputHandler::OperatorAndIndex
InputHandler::ReadOperatorFromPredicate(const std::string_view predicate, const size_t startPos)
{
	auto indx = predicate.find_first_not_of(' ', startPos);
	auto end = predicate.size();

	OperatorAndIndex operatorAndIndex;

	if (indx == std::string_view::npos)
	{
		throw "No operator after field name!";
	}

	auto indx2 = predicate.find_first_of(' ', indx + 1);

	if (indx2 == std::string_view::npos)
	{
		throw "No value after operator!";
	}

	operatorAndIndex.operatr = predicate.substr(indx, indx2 - indx);

	operatorAndIndex.indexAfterOperator = indx2 + 1;

	return operatorAndIndex;
}

InputHandler::ValueAndIndex
InputHandler::ReadValueFromPredicate(const std::string_view predicate, const size_t startPos)
{
	const auto indx = predicate.find_first_not_of(' ', startPos);
	auto end = predicate.size();

	ValueAndIndex valueAndIndex;

	if (indx == std::string_view::npos)
	{
		throw "No value after operator!";
	}

	if (predicate[indx] != '\"')
	{
		throw "Value after operator must be in quotes!";
	}

	auto indx2 = predicate.find_first_of('\"', indx + 1);

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
		if (predicate[indx2 + 1] != ' ')
		{
			throw "Incorrect usage of quotes in predicate!";
		}
	}

	valueAndIndex.value = predicate.substr(indx + 1, indx2 - indx - 1);

	valueAndIndex.indexAfterValue = indx2 + 1;

	return valueAndIndex;
}
