#pragma once

#include <map>
#include <string>
#include <vector>
#include <utility>

#include "Task.h"
#include "DateTimeUtility.h"

/*
  Класс, который содержит контейнер с объектами Task
  и который ими управляет.
*/
class TasksManager
{
public:
	/*
	  Контейнер, который содержит критерии для отбора задач.
	  first - имя поля, по которому нужно проводить поиск,
      second.first - оператор, относящийся к полю,
      second.second - значение, по которому производится проверка поля.
	*/
	typedef std::map<std::string_view, std::pair<std::string_view, std::string_view>> SearchMap;
	typedef std::pair<std::string_view, std::pair<std::string_view, std::string_view>> SearchPair;

	TasksManager();

	~TasksManager();

	/*
	  Добавляет новую задачу в m_tasks.
	  Ничего не делает, если задача с таким именем уже находится в этом контейнере.
	*/
	void AddTask(const std::string_view name, const std::string_view descr,
		         const DateTime& dateTime, const std::string_view categ);
	/*
	  Меняет значения полей задачи с именем name, если она есть в контейнере m_tasks.
	  Если такой задачи нет, то метод ничего не делает.
	*/
	void UpdateTask(const std::string_view name, const std::string_view descr,
		            const DateTime& dateTime, const std::string_view categ);

	/*
	  Заменяет задачу с именем oldName на задачу с именем newName с новыми полями.
	  Если нет задачи с именем oldName, то добавляет задачу с именем newName.
	*/
	void ReplaceTask(const std::string_view oldName, const std::string_view newName,
		             const std::string_view descr, const DateTime& dateTime, const std::string_view categ);

	/*
	  Удаляет задачу с именем name в m_tasks.
	  Если такой задачи нет, то метод ничего не делает.
	*/
	void DeleteTask(const std::string_view name);

	/*
	  Проверяет, содержит ли m_tasks задачу с именем name.
	  Возвращает true если содержит, false если не содержит.
	*/
	bool ContainsTask(const std::string_view name) const;

	/*
	  Устанавливает задачу с именем name из контейнера m_tasks в статус выполненной.
	  Если такой задачи нет, то метод ничего не делает.
	*/
	void SetTaskDone(const std::string_view name);

	/*
	  Выводит все задачи в консоль.
	*/
	void DisplayAllTasks() const;

	/*
	  Производит отбор задач по требованиям, указанным в searchMap.
	  Выбрасывает исключение const char* с сообщением, если searchMap содержит поле с некорректным названием.
	  Возвращает вектор константных указателей на подходящие под требования задачи.
	  Возвращает пустой вектор, если нет подходящих под требования задач.
	*/
	std::vector<const Task*> TasksManager::SearchTasks(const SearchMap& searchMap) const;

private:
	/*
	  Контейнер с задачами
	*/
	std::map<std::string, Task> m_tasks;
};
