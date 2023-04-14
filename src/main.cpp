#include "TaskList.h"
#include "TaskStorageFile.h"
#include "CommandsInvoker.h"

const std::string exitString = "q";
const std::string enterCommandInvitation = std::string("Enter command(") + exitString + " to exit): ";

void initializeTaskList(TaskList& taskList);

int main()
{
	TaskList taskList;
	initializeTaskList(taskList);

	CommandsInvoker invoker(taskList);

	std::cout << enterCommandInvitation;

	std::string commandAndArgumentsStr;

	while (std::getline(std::cin, commandAndArgumentsStr, '\n'))
	{
		if (commandAndArgumentsStr == exitString)
		{
			break;
		}
		
		try
		{
			invoker.executeCommand(commandAndArgumentsStr);

			std::cout << '\n';
			std::cout << enterCommandInvitation;
		}
		catch (const char* msg)
		{
			std::cout << msg << "\n\n";
			std::cout << enterCommandInvitation;
		}
		catch (...)
		{
			std::cout << "Unexpected error occured!";

			return -1;
		}		
	}

	return 0;
}

void initializeTaskList(TaskList& taskList)
{
	TaskStorageFile taskStorageFile;
	
	try
	{
		taskStorageFile >> taskList;
	}
	catch (const char* msg)
	{
		std::cout << "Could not fill the list from the file: " << msg << '\n';
		std::cout << "The list will be empty." << "\n\n";
	}
}
