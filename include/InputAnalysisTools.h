#pragma once

#include <string_view>
#include <vector>
#include <set>

#include "TaskList.h"

namespace InputAnalysisTools
{
    struct CommandAndArguments
    {
        std::string_view command;
        std::string_view arguments;
    };

    std::string_view unquoted(const std::string_view line);

    CommandAndArguments splitCommandAndArguments(const std::string_view line);

    std::vector<std::string_view> splitIntoWords(const std::string_view line);

    const std::set<TaskList::Expression> analyzePredicate(const std::string_view predicate);
};
