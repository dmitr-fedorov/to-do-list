#include "InputAnalysisTools.h"

namespace
{
	struct WordAndIndexAfterIt
	{
		std::string_view word;

		size_t indexAfterWord = std::string_view::npos;
	};

	struct ExpressionAndIndexAfterIt
	{
		TaskList::Expression expression;

		size_t indexAfterExpression = std::string_view::npos;
	};

	struct FieldNameAndIndexAfterIt
	{
		std::string_view fieldName;

		size_t indexAfterFieldName = std::string_view::npos;
	};

	struct OperatorAndIndexAfterIt
	{
		std::string_view operatr;

		size_t indexAfterOperator = std::string_view::npos;
	};

	struct ValueAndIndexAfterIt
	{
		std::string_view value;

		size_t indexAfterValue = std::string_view::npos;
	};

	WordAndIndexAfterIt readWord(const std::string_view line, const size_t startPos)
	{
		const auto lineEndIndx = line.length();

		const auto wordEndIndx = line.find_first_of(' ', startPos + 1);

		WordAndIndexAfterIt retVal;

		if (wordEndIndx != std::string_view::npos)
		{
			retVal.word = line.substr(startPos, wordEndIndx - startPos);
			retVal.indexAfterWord = wordEndIndx;
		}
		else
		{
			retVal.word = line.substr(startPos, lineEndIndx - startPos);
			retVal.indexAfterWord = lineEndIndx;
		}

		return retVal;
	}

	WordAndIndexAfterIt readWordWithQuotes(const std::string_view line, const size_t startPos)
	{
		auto quoteCharIndx = startPos;

		const auto lineEndIndx = line.length();

		WordAndIndexAfterIt retVal;

		while (quoteCharIndx < lineEndIndx)
		{
			quoteCharIndx = line.find_first_of('\"', quoteCharIndx + 1);

			if (quoteCharIndx == std::string_view::npos)
			{
				return readWord(line, startPos);
			}

			if (quoteCharIndx == lineEndIndx - 1 || line[quoteCharIndx + 1] == ' ')
			{
				retVal.word = line.substr(startPos + 1, quoteCharIndx - startPos - 1);
				retVal.indexAfterWord = quoteCharIndx + 1;

				return retVal;
			}
		}

		return retVal;
	}

	FieldNameAndIndexAfterIt readFieldName(const std::string_view predicate, const size_t startPos)
	{
		const auto nameStartIndx = predicate.find_first_not_of(' ', startPos);

		if (nameStartIndx == std::string_view::npos)
		{
			throw "Incorrect predicate!";
		}

		if (predicate[nameStartIndx] == '<' ||
			predicate[nameStartIndx] == '=' ||
			predicate[nameStartIndx] == '>')
		{
			throw "Operator cannot be the first character in field name!";
		}

		FieldNameAndIndexAfterIt retVal;

		for (auto nameEndIndx = nameStartIndx; nameEndIndx < predicate.length(); nameEndIndx++)
		{
			if (predicate[nameEndIndx] == '<' || predicate[nameEndIndx] == '=' ||
				predicate[nameEndIndx] == '>' || predicate[nameEndIndx] == ' ')
			{
				retVal.fieldName = predicate.substr(nameStartIndx, nameEndIndx - nameStartIndx);
				retVal.indexAfterFieldName = nameEndIndx;

				break;
			}
		}

		if (retVal.fieldName == "and" || retVal.fieldName == "like")
		{
			throw "Incorrect usage of key words in predicate!";
		}

		return retVal;
	}

	OperatorAndIndexAfterIt readOperator(const std::string_view predicate, const size_t startPos)
	{
		const auto opStartIndx = predicate.find_first_not_of(' ', startPos);

		if (opStartIndx == std::string_view::npos)
		{
			throw "No operator after field name!";
		}

		OperatorAndIndexAfterIt retVal;

		if (predicate[opStartIndx] == '<' ||
			predicate[opStartIndx] == '=' ||
			predicate[opStartIndx] == '>')
		{
			if (opStartIndx == predicate.length() - 1)
			{
				throw "No value after operator!";
			}

			if (predicate[opStartIndx + 1] == '<' ||
				predicate[opStartIndx + 1] == '=' ||
				predicate[opStartIndx + 1] == '>')
			{
				retVal.operatr = predicate.substr(opStartIndx, 2);
				retVal.indexAfterOperator = opStartIndx + 2;

				return retVal;
			}

			retVal.operatr = predicate.substr(opStartIndx, 1);
			retVal.indexAfterOperator = opStartIndx + 1;

			return retVal;
		}

		const auto opEndIndx = predicate.find_first_of(' ', opStartIndx + 1);

		retVal.operatr = predicate.substr(opStartIndx, opEndIndx - opStartIndx);
		retVal.indexAfterOperator = opEndIndx;

		if (retVal.operatr == "and")
		{
			throw "Incorrect usage of key words in predicate!";
		}

		return retVal;
	}

	ValueAndIndexAfterIt readValue(const std::string_view predicate, const size_t startPos)
	{
		const auto valueStartIndx = predicate.find_first_not_of(' ', startPos);

		if (valueStartIndx == std::string_view::npos)
		{
			throw "No value after operator!";
		}

		const auto valueEndIndx = predicate.find_first_of('\"', valueStartIndx + 1);

		if (predicate[valueStartIndx] != '\"' || valueEndIndx == std::string_view::npos)
		{
			throw "Value after operator must be in quotes!";
		}

		if (valueEndIndx == valueStartIndx + 1)
		{
			throw "Value in quotes is empty!";
		}

		if (valueEndIndx < predicate.length() - 1 &&
			predicate[valueEndIndx + 1] != ' ')
		{
			throw "Incorrect usage of quotes in predicate!";
		}

		ValueAndIndexAfterIt retVal;

		retVal.value = predicate.substr(valueStartIndx + 1, valueEndIndx - valueStartIndx - 1);

		retVal.indexAfterValue = valueEndIndx + 1;

		return retVal;
	}

	ExpressionAndIndexAfterIt readExpression(const std::string_view predicate, const size_t startPos)
	{
		const auto resFieldName = readFieldName(predicate, startPos);
		const auto resOperator = readOperator(predicate, resFieldName.indexAfterFieldName);
		const auto resValue = readValue(predicate, resOperator.indexAfterOperator);

		ExpressionAndIndexAfterIt retVal;

        retVal.expression.field = resFieldName.fieldName;
		retVal.expression.operatr = resOperator.operatr;
		retVal.expression.value = resValue.value;
		retVal.indexAfterExpression = resValue.indexAfterValue;

		return retVal;
	}
};

std::string_view
InputAnalysisTools::unquoted(const std::string_view line)
{
	const size_t lineLength = line.length();

	std::string_view unquotedLine;

	if (lineLength <= 2)
	{
		return line;
	}

	if (line[0] != '\"' || line[lineLength - 1] != '\"')
	{
		return line;
	}

	unquotedLine = line.substr(1, lineLength - 2);

	return unquotedLine;
}

InputAnalysisTools::CommandAndArguments
InputAnalysisTools::splitCommandAndArguments(const std::string_view line)
{
	CommandAndArguments retVal;

	const auto commandStartIndx = line.find_first_not_of(' ', 0);

	if (commandStartIndx == std::string_view::npos)
	{
		return retVal;
	}

	const auto commandEndIndx = line.find_first_of(' ', commandStartIndx);

	if (commandEndIndx == std::string_view::npos)
	{
		retVal.command = line.substr(commandStartIndx, line.length() - commandStartIndx);

		return retVal;
	}

	retVal.command = line.substr(commandStartIndx, commandEndIndx - commandStartIndx);

	const auto argumentsStartIndx = line.find_first_not_of(' ', commandEndIndx);

	if (argumentsStartIndx == std::string_view::npos)
	{
		return retVal;
	}

	retVal.arguments = line.substr(argumentsStartIndx, line.length());

	return retVal;
}

std::vector<std::string_view>
InputAnalysisTools::splitIntoWords(const std::string_view line)
{
	std::vector<std::string_view> words;

	WordAndIndexAfterIt resWord;

	size_t wordStartIndex = 0;

	while (wordStartIndex < line.length())
	{
		wordStartIndex = line.find_first_not_of(' ', wordStartIndex);

		if (wordStartIndex == std::string_view::npos)
		{
			break;
		}

		if (line[wordStartIndex] == '\"')
		{
			resWord = readWordWithQuotes(line, wordStartIndex);
		}
		else
		{
			resWord = readWord(line, wordStartIndex);
		}

		if (!resWord.word.empty())
		{
			words.push_back(resWord.word);
		}

		wordStartIndex = resWord.indexAfterWord;
	}

	return words;
}

const std::set<TaskList::Expression>
InputAnalysisTools::analyzePredicate(const std::string_view predicate)
{
	std::set<TaskList::Expression> expressions;

	for (size_t indx = 0; indx < predicate.length();)
	{
		const auto expressionAndIndex = readExpression(predicate, indx);

		expressions.insert(expressionAndIndex.expression);
		indx = expressionAndIndex.indexAfterExpression;

		indx = predicate.find_first_not_of(' ', indx);

		if (indx == std::string_view::npos)
		{
			break;
		}

		const auto wordAndIndex = readWord(predicate, indx);

		if (wordAndIndex.word != "and")
		{
			throw "To combine expressions, you need to use the word 'and'!";
		}

		if (wordAndIndex.indexAfterWord == predicate.length())
		{
			throw "No expression after the word 'and'!";
		}

		indx = wordAndIndex.indexAfterWord;
	}

	if (expressions.empty())
	{
		throw "Predicate is empty!";
	}

	return expressions;
}
