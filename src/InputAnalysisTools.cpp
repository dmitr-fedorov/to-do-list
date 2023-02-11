#include "InputAnalysisTools.h"

namespace
{
	struct WordAndIndex
	{
		std::string_view word;

		size_t indexAfterWord = std::string_view::npos;
	};

	struct ExpressionAndIndex
	{
		TasksManager::Expression expression;

		size_t indexAfterExpression = std::string_view::npos;
	};

	struct FieldNameAndIndex
	{
		// Имя поля, по которому будет производиться поиск.
		std::string_view fieldName;

		// Индекс следующего после имени поля символа в предикате.
		size_t indexAfterFieldName = std::string_view::npos;
	};

	struct OperatorAndIndex
	{
		// Оператор, с помощью которого будет производиться поиск.
		std::string_view operatr;

		// Индекс следующего после оператора символа в предикате.
		size_t indexAfterOperator = std::string_view::npos;
	};

	struct ValueAndIndex
	{
		// Значение, по которому будет производиться поиск.
		std::string_view value;

		// Индекс следующего после значения символа в предикате.
		size_t indexAfterValue = std::string_view::npos;
	};

	/*
	  Считывает все символы до пробела или до конца строки, начиная с позиции startPos.
	  Подразумевается, что функция получает корректные данные в качестве аргументов.
	*/
	WordAndIndex ReadWord(const std::string_view line, const size_t startPos)
	{
		const auto end = line.size();

		auto indx = line.find_first_of(' ', startPos + 1);
		
		WordAndIndex wordAndIndex;

		if (indx != std::string_view::npos)
		{
			wordAndIndex.word = line.substr(startPos, indx - startPos);

			wordAndIndex.indexAfterWord = indx + 1;
		}
		else
		{
			wordAndIndex.word = line.substr(startPos, end - startPos);

			wordAndIndex.indexAfterWord = end;
		}

		return wordAndIndex;
	}

	/*
	  Начиная с позиции startPos, считывает все символы до пробела,
	  либо до следующей кавычки, после которой следует пробел.
	  Подразумевается, что функция получает корректные данные в качестве аргументов.
	*/
	WordAndIndex ReadWordWithQuotes(const std::string_view line, const size_t startPos)
	{
		auto indx = startPos;
		
		const auto end = line.size();
		
		WordAndIndex wordAndIndex;

		while (indx < end)
		{
			indx = line.find_first_of('\"', indx + 1);

			if (indx == std::string_view::npos)
			{
				return ReadWord(line, startPos);
			}

			if (indx == end - 1 || line[indx + 1] == ' ')
			{
				wordAndIndex.word = line.substr(startPos + 1, indx - startPos - 1);
				wordAndIndex.indexAfterWord = indx + 1;

				return wordAndIndex;
			}
		}

		return wordAndIndex;
	}

	/*
	  Считывает название поля из predicate до пробела или до символа-оператора, начиная с позиции startPos.
	  Выбрасывает исключение const char* с сообщением в случае, если название поля в predicate некорректно.
	*/
	FieldNameAndIndex ReadFieldName(const std::string_view predicate, const size_t startPos)
	{		
		auto indx = predicate.find_first_not_of(' ', startPos);

		if (indx == std::string_view::npos)
		{
			throw "Incorrect predicate!";
		}

		if (predicate[indx] == '<' ||
			predicate[indx] == '=' ||
			predicate[indx] == '>')
		{
			throw "Operator cannot be the first character in field name!";
		}
		
		const auto end = predicate.size();

		FieldNameAndIndex fieldNameAndIndex;

		for (auto indx2 = indx; indx2 < end; indx2++)
		{
			if (predicate[indx2] == '<' || predicate[indx2] == '=' ||
				predicate[indx2] == '>' || predicate[indx2] == ' ')
			{
				fieldNameAndIndex.fieldName = predicate.substr(indx, indx2 - indx);

				fieldNameAndIndex.indexAfterFieldName = indx2;

				break;
			}
		}

		return fieldNameAndIndex;
	}

	/*
	  Считывает оператор из predicate, начиная с позиции startPos.
	  Выбрасывает исключение const char* с сообщением, если оператор отсутствует,
	  или если после оператора нет значения.
	  Возвращает структуру, со считанным оператором и индексом места в predicate,
	  где заканчивается этот оператор.
	*/
	OperatorAndIndex ReadOperator(const std::string_view predicate, const size_t startPos)
	{
		auto indx = predicate.find_first_not_of(' ', startPos);

		if (indx == std::string_view::npos)
		{
			throw "No operator after field name!";
		}

		const auto end = predicate.size();

		OperatorAndIndex operatorAndIndex;

		if (predicate[indx] == '<' ||
			predicate[indx] == '=' ||
			predicate[indx] == '>')
		{
			if (indx == end - 1)
			{
				throw "No value after operator!";
			}

			if (predicate[indx + 1] == '<' ||
				predicate[indx + 1] == '=' ||
				predicate[indx + 1] == '>')
			{
				operatorAndIndex.operatr = predicate.substr(indx, 2);
				operatorAndIndex.indexAfterOperator = indx + 2;

				return operatorAndIndex;
			}

			operatorAndIndex.operatr = predicate.substr(indx, 1);
			operatorAndIndex.indexAfterOperator = indx + 1;

			return operatorAndIndex;
		}

		auto indx2 = predicate.find_first_of(' ', indx + 1);

		operatorAndIndex.operatr = predicate.substr(indx, indx2 - indx);
		operatorAndIndex.indexAfterOperator = indx2;

		return operatorAndIndex;
	}

	/*
	  Считывает значение выражения из predicate, начиная с позиции startPos.
	  Выбрасывает исключение const char* с сообщением в случае, если значение в predicate некорректно.
	  Возвращает структуру со считанным значением без кавычек с обеих сторон,
	  и c индексом места в predicate, где заканчивается это значение.
	*/
	ValueAndIndex ReadValue(const std::string_view predicate, const size_t startPos)
	{
		const auto end = predicate.size();

		auto indx = predicate.find_first_not_of(' ', startPos);

		if (indx == std::string_view::npos)
		{
			throw "No value after operator!";
		}

		auto indx2 = predicate.find_first_of('\"', indx + 1);

		if (predicate[indx] != '\"' || indx2 == std::string_view::npos)
		{
			throw "Value after operator must be in quotes!";
		}

		if (indx2 == indx + 1)
		{
			throw "Value in quotes is empty!";
		}

		if (indx2 < end - 1 && predicate[indx2 + 1] != ' ')
		{
			throw "Incorrect usage of quotes in predicate!";
		}
		
		ValueAndIndex valueAndIndex;

		valueAndIndex.value = predicate.substr(indx + 1, indx2 - indx - 1);

		valueAndIndex.indexAfterValue = indx2 + 1;

		return valueAndIndex;
	}

	/*
	  Считывает выражение из predicate, начиная с позиции startPos.
	  Выбрасывает исключение const char* с сообщением в случае,
	  если после startPos не следует выражение, или выражение содержит некорректные части.
	  Возвращает считанное выражение.
	*/
    ExpressionAndIndex ReadExpression(const std::string_view predicate, const size_t startPos)
	{
		ExpressionAndIndex expressionAndIndex;

		auto indx = startPos;

		const auto resFieldName{ ReadFieldName(predicate, indx) };

		if (resFieldName.fieldName == "and" || resFieldName.fieldName == "like")
		{
			throw "Incorrect usage of key words in predicate!";
		}

		expressionAndIndex.expression.field = resFieldName.fieldName;
		indx = resFieldName.indexAfterFieldName;

		const auto resOperator{ ReadOperator(predicate, indx) };

		if (resOperator.operatr == "and")
		{
			throw "Incorrect usage of key words in predicate!";
		}

		expressionAndIndex.expression.operatr = resOperator.operatr;
		indx = resOperator.indexAfterOperator;

		const auto resValue{ ReadValue(predicate, indx) };

		expressionAndIndex.expression.value = resValue.value;
		expressionAndIndex.indexAfterExpression = resValue.indexAfterValue;

		return expressionAndIndex;
	}
};

InputAnalysisTools::CommandAndArguments
InputAnalysisTools::SplitCommandAndArguments(const std::string_view line)
{
	CommandAndArguments retStruct;

	if (line.empty())
	{
		return retStruct;
	}

	size_t indx = 0;
	size_t indx2 = line.find_first_of(' ', indx);

	if (indx2 == std::string_view::npos)
	{
		retStruct.command = line.substr(indx, line.size());

		return retStruct;
	}

	retStruct.command = line.substr(indx, indx2 - indx);

	indx = indx2 + 1;
	indx2 = line.size();

	retStruct.arguments = line.substr(indx, indx2 - indx);

	return retStruct;
}

std::vector<std::string_view>
InputAnalysisTools::SplitIntoWords(const std::string_view line)
{
	std::vector<std::string_view> words;

	WordAndIndex resWord;
	
	const auto end = line.size();

	size_t indx = 0;

	while (indx < end)
	{
		indx = line.find_first_not_of(' ', indx);

		if (indx == std::string_view::npos)
		{
			break;
		}

		if (line[indx] == '\"')
		{
			resWord = ReadWordWithQuotes(line, indx);
		}
		else
		{
			resWord = ReadWord(line, indx);
		}

		if (!resWord.word.empty())
		{
			words.push_back(resWord.word);
		}

		indx = resWord.indexAfterWord;
	}

	return words;
}

const std::set<TasksManager::Expression>
InputAnalysisTools::AnalyzePredicate(const std::string_view predicate)
{
	const auto end = predicate.size();

	std::set<TasksManager::Expression> expressions;

	for (size_t indx = 0; indx < end;)
	{
		const auto expressionAndIndex{ ReadExpression(predicate, indx) };

		expressions.insert(expressionAndIndex.expression);
		indx = expressionAndIndex.indexAfterExpression;

		indx = predicate.find_first_not_of(' ', indx);

		if (indx == std::string_view::npos)
		{
			break;
		}

		const auto wordAndIndex{ ReadWord(predicate, indx) };

		if (wordAndIndex.word != "and")
		{
			throw "To combine expressions, you need to use the word 'and'!";
		}

		if (wordAndIndex.indexAfterWord == end)
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
