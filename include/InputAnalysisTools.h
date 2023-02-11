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
      ����� ������ line �� ��� �����: ������� � ���������.
      ���������� ��������� � ����������� ������.
    */
    CommandAndArguments SplitCommandAndArguments(const std::string_view line);

    /*
      ��������� ������ line �� ��������� ����� � ���������� ��������� � ����� �������.
      ������ ���������, ����������� � ������� � ���������� �� ������ ���� ��������� � ����� ������,
      ��������� ����� ������. ����� ����� ��������� � ��������� ��� ������� � ������ � �����.
    */
    std::vector<std::string_view> SplitIntoWords(const std::string_view line);

    /*
      ����������� �������� predicate � ���������� ��������� �� ����� ���������.
      ���� � ������� ��� ������� ������������ ��������, �� �����������
      ���������� const char* � ��������� ����, ����� ����� ��������� �� �������� ����������.
    */
    const std::set<TasksManager::Expression> AnalyzePredicate(const std::string_view predicate);
};
