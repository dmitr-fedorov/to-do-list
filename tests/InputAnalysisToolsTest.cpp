#include <gtest/gtest.h>

#include "InputAnalysisTools.h"

TEST(InputAnalysisToolsTest, Unquoted_CorrectArgumentGiven_ShouldReturnCorrectString)
{	
	EXPECT_EQ(InputAnalysisTools::unquoted(" "), " ");
	EXPECT_EQ(InputAnalysisTools::unquoted("   "), "   ");
	EXPECT_EQ(InputAnalysisTools::unquoted("\"input\""), "input");
	EXPECT_EQ(InputAnalysisTools::unquoted("input\""), "input\"");
	EXPECT_EQ(InputAnalysisTools::unquoted("\"input"), "\"input");
	EXPECT_EQ(InputAnalysisTools::unquoted("\"input string\""), "input string");
	EXPECT_EQ(InputAnalysisTools::unquoted("\"input string"), "\"input string");
	EXPECT_EQ(InputAnalysisTools::unquoted("in\"put string"), "in\"put string");
	EXPECT_EQ(InputAnalysisTools::unquoted("input str\"ing"), "input str\"ing");
	EXPECT_EQ(InputAnalysisTools::unquoted("input\" string"), "input\" string");
	EXPECT_EQ(InputAnalysisTools::unquoted("input \"string"), "input \"string");
	EXPECT_EQ(InputAnalysisTools::unquoted("input string\""), "input string\"");
}

TEST(InputAnalysisToolsTest, Unquoted_EmptyStringGiven_ShouldReturnEmptyString)
{
	EXPECT_EQ(InputAnalysisTools::unquoted(""), "");	
}

TEST(InputAnalysisToolsTest, SplitCommandAndArguments_CorrectArgumentGiven_ShouldReturnCorrectValue)
{
	const std::string line = "add \"name\" \"description\" \"2020-12-12 00:00\" \"category\"";
	const std::string expectedCmd = "add";
	const std::string expectedArgs = "\"name\" \"description\" \"2020-12-12 00:00\" \"category\"";
	
	const auto [resCmd, resArgs] = InputAnalysisTools::splitCommandAndArguments(line);
		
	EXPECT_EQ(resCmd, expectedCmd);
	EXPECT_EQ(resArgs, expectedArgs);
}

TEST(InputAnalysisToolsTest, SplitCommandAndArguments_EmptyStringGiven_ShouldReturnEmptyValue)
{
	const std::string emptyStr = "";
	const std::string emptyExpectedCmd = "";
	const std::string emptyExpectedArgs = "";
	const auto [emptyResCmd, emptyResArgs] = InputAnalysisTools::splitCommandAndArguments(emptyStr);

	EXPECT_EQ(emptyResCmd, emptyExpectedCmd);
	EXPECT_EQ(emptyResArgs, emptyExpectedArgs);
}

TEST(InputAnalysisToolsTest, SplitIntoWords_CorrectArgumentGiven_ShouldReturnCorrectValue)
{
	const std::string wordsLine = "\"name\" description \"2020-12-12 00:00\" category\"";
	const std::string word1 = "name";
	const std::string word2 = "description";
	const std::string word3 = "2020-12-12 00:00";
	const std::string word4 = "category\"";
	const std::vector<std::string_view> expectedWords{ word1, word2, word3, word4 };
	
	const auto resWords = InputAnalysisTools::splitIntoWords(wordsLine);

	EXPECT_EQ(resWords, expectedWords);
}

TEST(InputAnalysisToolsTest, SplitIntoWords_EmptyStringGiven_ShouldReturnEmptyValue)
{
	const std::string emptyWordsLine = "";
	const std::string emptyWordsLine2 = " ";
	const std::string emptyWordsLine3 = "       ";
	const std::vector<std::string_view> emptyExpectedWords{};

	const auto emptyResWords = InputAnalysisTools::splitIntoWords(emptyWordsLine);
	const auto emptyResWords2 = InputAnalysisTools::splitIntoWords(emptyWordsLine2);
	const auto emptyResWords3 = InputAnalysisTools::splitIntoWords(emptyWordsLine3);

	EXPECT_EQ(emptyResWords, emptyExpectedWords);
	EXPECT_EQ(emptyResWords2, emptyExpectedWords);
	EXPECT_EQ(emptyResWords3, emptyExpectedWords);
}

TEST(InputAnalysisToolsTest, AnalyzePredicate_CorrectArgumentGiven_ShouldReturnCorrectValue)
{
	const std::set<TaskList::Expression> expectedExpressions{
		{"name", "=", "Go to work"},
		{"description", "like", "amazing"},
		{"date", ">=", "2020-01-05 12:15"}
	};
	const std::string predicate =
		"   name   =   \"Go to work\" and description    like    \"amazing\" and   date>=\"2020-01-05 12:15\"    ";

	const auto resExpressions = InputAnalysisTools::analyzePredicate(predicate);

	EXPECT_EQ(resExpressions, expectedExpressions);
}

TEST(InputAnalysisToolsTest, AnalyzePredicate_IncorrectArgumentGiven_ShouldThrowErrorMessage)
{
	const std::string predicate1 = "name and \"Go to work\" and description like \"amazing\"";
	const std::string predicate2 = "name like \"Go to work\" and description like";
	const std::string predicate3 = "name like \"Go to work\" and description =";
	const std::string predicate4 = "name like \"Go to work\" and description >=";
	const std::string predicate5 = "name = \"Go to work\" like description like \"amazing\"";
	const std::string predicate6 = "name = Go to work and description like \"amazing\"";
	const std::string predicate7 = "name = \"Go to work and description like \"amazing\"";
	const std::string predicate8 = "name = Go to work\" and description like \"amazing\"";
	const std::string predicate9 = "name = \"Go to work\" and description like \"amazing";
	const std::string predicate10 = "name = \"Go to work\" and description like amazing\"";
	const std::string predicate11 = "and            and                and        and";
	const std::string predicate12 = "like like            likelike      like";
	const std::string predicate13 = "";
	const std::string predicate14 = " ";
	const std::string predicate15 = "        1   ";

	EXPECT_THROW(InputAnalysisTools::analyzePredicate(predicate1), const char*);
	EXPECT_THROW(InputAnalysisTools::analyzePredicate(predicate2), const char*);
	EXPECT_THROW(InputAnalysisTools::analyzePredicate(predicate3), const char*);
	EXPECT_THROW(InputAnalysisTools::analyzePredicate(predicate4), const char*);
	EXPECT_THROW(InputAnalysisTools::analyzePredicate(predicate5), const char*);
	EXPECT_THROW(InputAnalysisTools::analyzePredicate(predicate6), const char*);
	EXPECT_THROW(InputAnalysisTools::analyzePredicate(predicate7), const char*);
	EXPECT_THROW(InputAnalysisTools::analyzePredicate(predicate8), const char*);
	EXPECT_THROW(InputAnalysisTools::analyzePredicate(predicate9), const char*);
	EXPECT_THROW(InputAnalysisTools::analyzePredicate(predicate10), const char*);
	EXPECT_THROW(InputAnalysisTools::analyzePredicate(predicate11), const char*);
	EXPECT_THROW(InputAnalysisTools::analyzePredicate(predicate12), const char*);
	EXPECT_THROW(InputAnalysisTools::analyzePredicate(predicate13), const char*);
	EXPECT_THROW(InputAnalysisTools::analyzePredicate(predicate14), const char*);
	EXPECT_THROW(InputAnalysisTools::analyzePredicate(predicate15), const char*);
}
