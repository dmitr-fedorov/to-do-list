#pragma once

#include "TaskList.h"

class TaskStorageFile
{
public:
	TaskStorageFile() = default;

	~TaskStorageFile() = default;
	
	friend TaskStorageFile& operator>>(TaskStorageFile& storageFile, TaskList& taskList);

	friend TaskStorageFile& operator<<(TaskStorageFile& storageFile, const TaskList& taskList);

private:
	static const std::string FILE_NAME;

	void validateName(const std::string_view name, const TaskList& taskList) const;

	void validateField(const std::string_view field) const;

	void validateBlankString(const std::string_view blankString) const;
};
