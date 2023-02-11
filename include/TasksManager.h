﻿#pragma once

#include <string_view>
#include <map>
#include <set>
#include <vector>

#include "Task.h"

/*
  Класс, который содержит контейнер с объектами Task
  и который ими управляет.
*/
class TasksManager
{
public:
	/*
	  Выражение, по которому проводится отбор задач.
	*/
	struct Expression
	{
		std::string_view field;
		std::string_view operatr;
		std::string_view value;

		bool operator< (const Expression& other) const
		{
			return field < other.field;
		}
	};

	TasksManager();

	~TasksManager();

	/*
	  Добавляет новую задачу с переданными в качестве аргументов полями.
	  Ничего не делает, если задача с таким именем уже существует.
	*/
	void AddTask(const std::string_view name, const std::string_view description,
		const DateTime& dateTime, const std::string_view category);
	/*
	  Меняет значения полей задачи с именем name на значения из аргументов.
	  Ничего не делает, если задача с таким именем не существует.
	*/
	void UpdateTask(const std::string_view name, const std::string_view description,
		const DateTime& dateTime, const std::string_view category);

	/*
	  Заменяет задачу с именем oldName на задачу с именем newName с новыми полями из аргументов.
	  Ничего не делает, если задача с именем oldName не существует,
	  или задача с именем newName уже существует.
	*/
	void ReplaceTask(const std::string_view oldName, const std::string_view newName,
		const std::string_view description, const DateTime& dateTime, const std::string_view category);

	/*
	  Удаляет задачу с именем name.
	  Ничего не делает, если задача с таким именем не существует.
	*/
	void DeleteTask(const std::string_view name);

	/*
	  Проверяет, существует ли задача с именем name.
	  Возвращает true, если задача существует,
	  в противном случае возвращает false.
	*/
	bool ContainsTask(const std::string_view name) const;

	/*
	  Устанавливает задачу с именем name в статус выполненной.
	  Если такой задачи нет, то метод ничего не делает.
	*/
	void SetTaskDone(const std::string_view name);

	/*
	  Выводит все задачи в консоль.
	*/
	void DisplayAllTasks() const;

	/*
	  Вовзращает количество задач в контейнере.
	*/
	int TaskCount();

	/*
	  Выполняет отбор задач, которые соответствуют выражениям из expressions.
	  Выбрасывает исключение const char* с сообщением, если expressions содержит
	  некорректные выражения.
	  Возвращает вектор константных указателей на задачи, которые соответствуют выражениям.
	  Если таких задач нет, то возвращает пустой вектор.
	*/
	std::vector<const Task*> TasksManager::SearchTasks(const std::set<Expression>& expressions) const;

private:
	/*
	  Контейнер с задачами.
	  first - название задачи,
	  second - объект, представляющий собой задачу.
	*/
	std::map<std::string, Task> m_tasks;
};
