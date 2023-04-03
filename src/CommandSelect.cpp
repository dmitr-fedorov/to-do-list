#include "CommandSelect.h"
#include "InputAnalysisTools.h"

CommandSelect::CommandSelect(TaskList& taskList)
	: m_taskList(taskList)
{

}

void CommandSelect::execute(const std::string_view arguments)
{
	if (m_taskList.count() == 0)
	{
		throw "Task list is empty!";
	}

	const auto asteriskCharIndx = readFromBeginningUntilAsterisk(arguments);
	
	const auto nextNonBlankCharIndx = arguments.find_first_not_of(" ", asteriskCharIndx + 1);

	if (nextNonBlankCharIndx == std::string_view::npos)
	{
		m_taskList.displayAll();

		return;
	}
	
	if (nextNonBlankCharIndx == asteriskCharIndx + 1)
	{
		throw "Characters right after \'*\' are not allowed!";
	}

	const auto predicateStartIndx = readFromIndexUntilPredicate(arguments, nextNonBlankCharIndx);

	const auto predicate = arguments.substr(predicateStartIndx, arguments.size() - predicateStartIndx);

	const auto expressions = InputAnalysisTools::analyzePredicate(predicate);

	const auto relevantTasks = m_taskList.find(expressions);

	if (relevantTasks.empty())
	{
		throw "No relevant tasks found.";
	}

	for (auto taskPtr : relevantTasks)
	{
		std::cout << *taskPtr;

		std::cout << '\n';
	}
}

size_t CommandSelect::readFromBeginningUntilAsterisk(const std::string_view arguments)
{
	const auto asteriskCharIndx = arguments.find_first_not_of(" ", 0);

	if (asteriskCharIndx == std::string_view::npos)
	{
		throw "You should provide arguments for the command!";
	}

	if (arguments[asteriskCharIndx] != '*')
	{
		throw "After \'select\' must come the character \'*\'!";
	}

	return asteriskCharIndx;
}

size_t CommandSelect::readFromIndexUntilPredicate(const std::string_view arguments, const size_t startIndx)
{
	const auto wordEndIndx = arguments.find_first_of(" ", startIndx);

	const auto word = arguments.substr(startIndx, wordEndIndx - startIndx);

	if (word != "where")
	{
		throw "After \'*\' must come the word \'where\'!";
	}
	
	if (wordEndIndx == std::string_view::npos)
	{
		throw "Predicate is empty!";
	}

	const auto predicateStartIndx = arguments.find_first_not_of(" ", wordEndIndx + 1);

	if (predicateStartIndx == std::string_view::npos)
	{
		throw "Predicate is empty!";
	}

	return predicateStartIndx;
}
