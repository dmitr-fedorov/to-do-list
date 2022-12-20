#pragma once

#include <map>
#include <string>
#include <vector>
#include <utility>

#include "Task.h"

/*
  Класс, который содержит контейнер с объектами Task
  и который ими управляет.
*/
class TasksManager
{
public:
	TasksManager();

	~TasksManager();

	/*
	Добавляет новую задачу в m_tasks.
	Ничего не делает, если задача с таким именем уже находится в этом контейнере.
	*/
	void AddTask(const std::string_view name, const std::string_view descr,
		         const std::string_view date, const std::string_view categ);
	/*
	Меняет значения полей задачи с именем name, если она есть в контейнере m_tasks.
	Если такой задачи нет, то метод ничего не делает.
	*/
	void UpdateTask(const std::string_view name, const std::string_view descr,
		            const std::string_view date, const std::string_view categ);

	/* 
	Заменяет задачу с именем oldName на задачу с именем newName с новыми полями
	если в m_tasks есть задача с именем oldName и нет задачи с именем newName,
	иначе ничего не делает.
	*/
	void ReplaceTask(const std::string_view oldName, const std::string_view newName,
		             const std::string_view descr,   const std::string_view date,
		             const std::string_view categ);

	/*
	  Удаляет задачу с именем name если m_tasks ее содержит,
	  иначе ничего не делает.
	*/
	void DeleteTask(const std::string_view name);

	/*
	  Проверяет, содержит ли m_tasks задачу с именем name.
	  Возвращает true если содержит, false если не содержит.
	*/
	bool ContainsTask(const std::string_view name) const;

	/*
	  Устанавливает задачу с именем name из контейнера m_tasks в статус выполненной. 
	*/
	void SetTaskDone(const std::string_view name);
	/*
	  Выводит все задачи в консоль.
	*/
	void DisplayAllTasks();

	/*
	  Производит отбор задач по требованиям, указанным в searchMap.
	  Возвращает вектор константных указателей на подходящие под требования задачи.
	*/
	std::vector<const Task*>
		TasksManager::SearchTasks(const std::map<std::string_view, std::pair<std::string_view, std::string_view>> searchMap);

private:
	/*
	  Контейнер с задачами
	*/
	std::map<std::string, Task> m_tasks;
};
