#pragma once

#include <string_view>
#include <vector>
#include <set>

#include "TasksManager.h"

namespace InputAnalysisTools
{
    struct CommandAndArguments
    {
        std::string_view command;
        std::string_view arguments;
    };

    /*
      Делит строку line на две части: команду и аргументы.
      Возвращает структуру с разделенным вводом.
    */
    CommandAndArguments SplitCommandAndArguments(const std::string_view line);

    /*
      Разделяет строку line на отдельные слова и возвращает контейнер с этими словами.
      Каждая подстрока, заключенная в кавычки и отделенная от других слов пробелами с обеих сторон,
      считается одним словом. Такие слова заносятся в контейнер без кавычек в начале и конце.
    */
    std::vector<std::string_view> SplitIntoWords(const std::string_view line);

    /*
      Анализирует предикат predicate и возвращает выражения из этого предиката.
      Если в функцию был передан некорректный предикат, то выбрасывает
      исключение const char* с описанием того, какая часть предиката не является корректной.
    */
    const std::set<TasksManager::Expression> AnalyzePredicate(const std::string_view predicate);
};
