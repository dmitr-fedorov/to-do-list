#include "CommandSelect.h"
#include "InputAnalysisTools.h"

CommandSelect::CommandSelect(TaskList& taskList)
	: m_taskList(taskList)
{

}

void CommandSelect::execute(const std::string_view arguments)
{
	if (m_taskList.Count() == 0)
	{
		throw "Task list is empty!";
	}
	
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

	const auto predicate = arguments.substr(indx3, arguments.size() - indx3);

	const auto expressions = InputAnalysisTools::AnalyzePredicate(predicate);

	const auto relevantTasks = m_taskList.Find(expressions);

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
