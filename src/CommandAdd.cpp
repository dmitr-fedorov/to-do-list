#include "CommandAdd.h"
#include "InputAnalysisTools.h"

CommandAdd::CommandAdd(TaskList& taskList)
    : m_taskList(taskList)
{
    
}

void CommandAdd::execute(const std::string_view arguments)
{
	const auto fields = InputAnalysisTools::SplitIntoWords(arguments);

    checkFieldsValidity(fields);
    
    m_taskList.Add(fields[INDX_NAME], fields[INDX_DESCRIPTION],
    	DateTime{ fields[INDX_DATE] }, fields[INDX_CATEGORY]);
}

void CommandAdd::checkFieldsValidity(const std::vector<std::string_view>& fields)
{
    if (fields.size() != REQUIRED_NUMBER_OF_FIELDS)
    {
    	throw "Incorrect number of arguments!";
    }
    
    if (m_taskList.Contains(fields[INDX_NAME]))
    {
    	throw "This task already exists!";
    }
    
    if (fieldsContainQuotes(fields))
    {
        throw "Incorrect usage of quotes in arguments!";
    }
}

bool CommandAdd::fieldsContainQuotes(const std::vector<std::string_view>& fields)
{
    for (const auto field : fields)
    {
    	if (field.find('\"') != std::string_view::npos)
    	{
            return true;
    	}
    }

    return false;
}
