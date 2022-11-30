#pragma once

#include <regex>
#include <string_view>
#include <string>
#include <vector>
#include <utility>

#include "TasksManager.h"

class InputHandler
{
public:
	InputHandler();
	~InputHandler();

	/*
	  Выводит приглашение на ввод команды в консоль, считывает введенные команды
	  и вызывает методы-обработчики для этих команд.
	*/
	int StartReading();

private:
	/*
	Регулярное выражение, необходимое для проверки
	корректности формата введенной пользователем даты.
	*/
	static const std::regex M_CONST_DATE_REGEX;
	/*
	  Строка, при вводе которой в консоль приложение завершает работу.
	*/
	static const std::string M_CONST_STRING_EXIT;
	/*
	  Приглашение на ввод пользователем команды.
	*/
	static const std::string M_CONST_STRING_ENTER_COMMAND;

	/*
	  Объект, который хранит задачи и с помощью которого происходит
	  управление этими задачами.
	*/
	TasksManager m_tasksManager;

	/*
	  Обрабатывает команду добавления новой задачи в список и
	  выводит в консоль сообщения о некорректном вводе.
	  argsView - аргументы команды.
	*/
	void HandleAdd(const std::string_view& argsView);
	/*
	  Обрабатывает команду установки находящейся в списке задачи в состояние выполненной и
	  выводит в консоль сообщения о некорректном вводе.
	  argsView - аргументы команды.
	*/
	void HandleDone(const std::string_view& argsView);
	/*
	  Обрабатывает команду установки новых значений в поля находящейся в списке задачи и
	  выводит в консоль сообщения о некорректном вводе.
	  argsView - аргументы команды.
	*/
	void HandleUpdate(const std::string_view& argsView);
	/*
	  Обрабатывает команду удаления задачи из списка и
	  выводит в консоль сообщения о некорректном вводе.
	  argsView - аргументы команды.
	*/
	void HandleDelete(const std::string_view& argsView);

	void HandleSelect(const std::string_view& argsView);

	/*
	  Возвращает пару, где первое значение - строка с командой,
	  а второе значение - строка с аргументами этой команды.
	  inpView - единая строка с командой и ее аргументами.
	*/
	std::pair<std::string_view, std::string_view> GetCommandAndArguments(const std::string_view& inpView);

	/*
	  Разделяет inpView на отдельные слова и возвращает вектор, где каждый элемент - отдельное слово в inpView.
	  Каждая подстрока в кавычках, отделенная от других слов пробелами, считается одним словом.
	  Слова заносятся в вектор вместе с кавычками.
	  inpView - строка, которую нужно разделить на слова.
	*/
	std::vector<std::string_view> SplitIntoWords(const std::string_view& inpView);

	/*
	  Возвращает true, если дата в строке inpView соответствует регулярному выражению M_CONST_DATE_REGEX.
	  В противном случае возвращает false.
	*/
	bool IsDateFormatCorrect(const std::string_view& inpView);

	/*
	  Если строка inpView заключена в кавычки, то метод возвращает эту строку без кавычек.
	  В противном случает возвращает эту строку.
	*/
	std::string_view Unquoted(const std::string_view& inpView);

	/*
	  Выводит в консоль приглашение на ввод имени задачи, считывает и анализирует ввод.
	  Выводит в консоль сообщения о некорректном вводе имени, если оно было введено неправильно.
	  Возвращает введенную строку, если она соответствует требованиям.
	  argNameView - вид на строку с именем задачи, для которой считывается новое имя.
	*/
	std::string ReadName(const std::string_view& argNameView);

	/*
	  Выводит в консоль приглашение на ввод даты создания задачи, считывает и анализирует ввод.
	  Выводит в консоль сообщения о некорректном вводе даты, если она была введена неправильно.
	  Возвращает введенную строку, если она соответствует требованиям.
	*/
	std::string ReadDate();

	/*
	  Анализирует предикат predView.
	  Возвращает пару, где first - имя поля, по которому нужно проводить поиск,
	  second.first - оператор, относящийся к полю,
	  second.second - значение, по которому производится проверка поля
	*/
	std::map<std::string, std::pair<std::string, std::string>>
		AnalyzePredicate(const std::string_view& predView);

	void ReadSelectOperator(const std::string_view& predView,
		std::pair<std::string, std::pair<std::string, std::string>>& pr, size_t& i, size_t& j);

	std::string ReadSelectValue(const std::string_view& predView, size_t& i);

	size_t SkipUntilPredicate(const std::string_view& argsView);
	size_t SkipUntilStar(const std::string_view& argsView, const size_t& startPos);
	size_t SkipUntilWhere(const std::string_view& argsView, const size_t& startPos);
};
