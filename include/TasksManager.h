#pragma once

#include <map>
#include <string>
#include <vector>
#include <utility>

#include "Task.h"

/*
   ласс, который содержит контейнер с объектами Task
  и который ими управл€ет.
*/
class TasksManager
{
public:
	TasksManager();

	~TasksManager();

	/*
	ƒобавл€ет новую задачу в m_tasks.
	Ќичего не делает, если задача с таким именем уже находитс€ в этом контейнере.
	*/
	void AddTask(const std::string_view& name, const std::string_view& descr,
		         const std::string_view& date, const std::string_view& categ);
	/*
	ћен€ет значени€ полей задачи с именем name, если она есть в контейнере m_tasks.
	≈сли такой задачи нет, то метод ничего не делает.
	*/
	void UpdateTask(const std::string_view& name, const std::string_view& descr,
		            const std::string_view& date, const std::string_view& categ);

	/* 
	«амен€ет задачу с именем oldName на задачу с именем newName с новыми пол€ми
	если в m_tasks есть задача с именем oldName и нет задачи с именем newName,
	иначе ничего не делает.
	*/
	void ReplaceTask(const std::string_view& oldName, const std::string_view& newName,
		             const std::string_view& descr,   const std::string_view& date,
		             const std::string_view& categ);

	/*
	  ”дал€ет задачу с именем name если m_tasks ее содержит,
	  иначе ничего не делает.
	*/
	void DeleteTask(const std::string_view& name);

	/*
	  ѕровер€ет, содержит ли m_tasks задачу с именем name.
	  ¬озвращает true если содержит, false если не содержит.
	*/
	bool ContainsTask(const std::string_view& name) const;

	/*
	  ”станавливает задачу с именем name из контейнера m_tasks в статус выполненной. 
	*/
	void SetTaskDone(const std::string_view& name);

	/*
	  ѕроизводит отбор задач по требовани€м, указанным в searchMap.
	  ¬озвращает пару из имени подход€щей задачи и самой задачи.
	*/
	std::vector<std::pair<std::string, Task>>
		SearchTasks(std::map<std::string, std::pair<std::string, std::string>>& searchMap);

private:
	//  онтейнер с задачами
	std::map<std::string, Task> m_tasks;
};
