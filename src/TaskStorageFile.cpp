#include "TaskStorageFile.h"

const std::string TaskStorageFile::FILE_NAME = "tasks.txt";

TaskStorageFile& operator>>(TaskStorageFile& storageFile, TaskList& taskList)
{
	std::ifstream ifs(TaskStorageFile::FILE_NAME);

	if (!ifs.is_open())
	{
		throw "unable to open the file that contains tasks.";
	}

	std::string name;
	std::string description;
	std::string date;
	std::string category;
	std::string status;
	std::string blankString;

	TaskList tempTaskList;

	while (std::getline(ifs, name))
	{
		storageFile.validateName(name, tempTaskList);

		std::getline(ifs, description);
		storageFile.validateField(description);

		std::getline(ifs, date);

		std::getline(ifs, category);
		storageFile.validateField(category);

		std::getline(ifs, status);
		storageFile.validateField(status);

		std::getline(ifs, blankString);
		storageFile.validateBlankString(blankString);

		Task newTask{ name, description, DateTime { date }, category, status };

		tempTaskList.add(newTask);
	}

	taskList = std::move(tempTaskList);

	ifs.close();

	return storageFile;
}

void TaskStorageFile::validateName(const std::string_view name, const TaskList& taskList) const
{
	validateField(name);

	if (taskList.contains(name))
	{
		throw "the file contains multiple tasks with the same name.";
	}
}

void TaskStorageFile::validateField(const std::string_view field) const
{
	if (field.empty())
	{
		throw "one of the fields of a task is empty.";
	}

	if (field.find('\"') != std::string_view::npos)
	{
		throw "one of the fields of a task contains quotes.";
	}
}

void TaskStorageFile::validateBlankString(const std::string_view blankString) const
{
	if (!blankString.empty())
	{
		throw "file's content has incorrect structure.";
	}
}

TaskStorageFile& operator<<(TaskStorageFile& storageFile, const TaskList& taskList)
{
	std::ofstream ofs(TaskStorageFile::FILE_NAME);

	if (!ofs.is_open())
	{
		throw "Unable to open the file that contains tasks.";
	}

	ofs << taskList;

	ofs.close();

	return storageFile;
}
