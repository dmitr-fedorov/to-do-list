#include "TaskList.h"
#include "CommandsInvoker.h"

int main()
{
	TaskList taskList;
	CommandsInvoker invoker(taskList);

	const std::string exitString = "q";
	const std::string enterCommandInvitation = std::string("Enter command(") 
		                                           + exitString + " to exit): ";
	std::cout << enterCommandInvitation;
	
	std::string commandAndArgumentsString;

	while (std::getline(std::cin, commandAndArgumentsString, '\n'))
	{
		if (commandAndArgumentsString == exitString)
		{
			break;
		}
		
		try
		{
			invoker.executeCommand(commandAndArgumentsString);

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
