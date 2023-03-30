#pragma once

#include <string_view>

class Command
{
public:
	Command() = default;

	virtual ~Command() = default;

	virtual void execute(const std::string_view arguments) = 0;
};
