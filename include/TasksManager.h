#pragma once

#include <map>
#include <string>
#include <vector>
#include <utility>

#include "Task.h"

/*
  �����, ������� �������� ��������� � ��������� Task
  � ������� ��� ���������.
*/
class TasksManager
{
public:
	TasksManager();

	~TasksManager();

	/*
	��������� ����� ������ � m_tasks.
	������ �� ������, ���� ������ � ����� ������ ��� ��������� � ���� ����������.
	*/
	void AddTask(const std::string_view& name, const std::string_view& descr,
		         const std::string_view& date, const std::string_view& categ);
	/*
	������ �������� ����� ������ � ������ name, ���� ��� ���� � ���������� m_tasks.
	���� ����� ������ ���, �� ����� ������ �� ������.
	*/
	void UpdateTask(const std::string_view& name, const std::string_view& descr,
		            const std::string_view& date, const std::string_view& categ);

	/* 
	�������� ������ � ������ oldName �� ������ � ������ newName � ������ ������
	���� � m_tasks ���� ������ � ������ oldName � ��� ������ � ������ newName,
	����� ������ �� ������.
	*/
	void ReplaceTask(const std::string_view& oldName, const std::string_view& newName,
		             const std::string_view& descr,   const std::string_view& date,
		             const std::string_view& categ);

	/*
	  ������� ������ � ������ name ���� m_tasks �� ��������,
	  ����� ������ �� ������.
	*/
	void DeleteTask(const std::string_view& name);

	/*
	  ���������, �������� �� m_tasks ������ � ������ name.
	  ���������� true ���� ��������, false ���� �� ��������.
	*/
	bool ContainsTask(const std::string_view& name) const;

	/*
	  ������������� ������ � ������ name �� ���������� m_tasks � ������ �����������. 
	*/
	void SetTaskDone(const std::string_view& name);

	/*
	  ���������� ����� ����� �� �����������, ��������� � searchMap.
	  ���������� ���� �� ����� ���������� ������ � ����� ������.
	*/
	std::vector<std::pair<std::string, Task>>
		SearchTasks(std::map<std::string, std::pair<std::string, std::string>>& searchMap);

private:
	// ��������� � ��������
	std::map<std::string, Task> m_tasks;
};
