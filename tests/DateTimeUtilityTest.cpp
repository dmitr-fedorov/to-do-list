#include <gtest/gtest.h>

#include "DateTimeUtility.h"

TEST(DateTimeUtilityTest, IsDateTimeFormatCorrect_CorrectArgumentGiven_ShouldReturnTrue)
{
	EXPECT_TRUE(DateTimeUtility::isDateTimeFormatCorrect("2020-12-12 00:00"));
}

TEST(DateTimeUtilityTest, IsDateTimeFormatCorrect_IncorrectArgumentGiven_ShouldReturnFalse)
{
	EXPECT_FALSE(DateTimeUtility::isDateTimeFormatCorrect(""));
	EXPECT_FALSE(DateTimeUtility::isDateTimeFormatCorrect(" "));
	EXPECT_FALSE(DateTimeUtility::isDateTimeFormatCorrect("2"));
	EXPECT_FALSE(DateTimeUtility::isDateTimeFormatCorrect("  2020-12-12   00:00  "));
	EXPECT_FALSE(DateTimeUtility::isDateTimeFormatCorrect("-12-12 00:00"));
	EXPECT_FALSE(DateTimeUtility::isDateTimeFormatCorrect("202012-12 00:00"));
	EXPECT_FALSE(DateTimeUtility::isDateTimeFormatCorrect("2020-1212 00:00"));
	EXPECT_FALSE(DateTimeUtility::isDateTimeFormatCorrect("2020-12-1200:00"));
	EXPECT_FALSE(DateTimeUtility::isDateTimeFormatCorrect("2020-12-12"));
	EXPECT_FALSE(DateTimeUtility::isDateTimeFormatCorrect("2020-12-12 :"));
	EXPECT_FALSE(DateTimeUtility::isDateTimeFormatCorrect("2020-12-12 0000"));
	EXPECT_FALSE(DateTimeUtility::isDateTimeFormatCorrect("2020-12-12 0:00"));
	EXPECT_FALSE(DateTimeUtility::isDateTimeFormatCorrect("2020-12-12 00:0"));
}

TEST(DateTimeUtilityTest, IsDateValid_CorrectArgumentsGiven_ShouldReturnTrue)
{
	EXPECT_TRUE(DateTimeUtility::isDateValid(2020, 12, 12));
	EXPECT_TRUE(DateTimeUtility::isDateValid(2000, 2, 29));
}

TEST(DateTimeUtilityTest, IsDateValid_IncorrectArgumentsGiven_ShouldReturnFalse)
{
	EXPECT_FALSE(DateTimeUtility::isDateValid(0, 1, 12));
	EXPECT_FALSE(DateTimeUtility::isDateValid(2020, 0, 12));
	EXPECT_FALSE(DateTimeUtility::isDateValid(2020, 1, 0));
	EXPECT_FALSE(DateTimeUtility::isDateValid(-1, 1, 12));
	EXPECT_FALSE(DateTimeUtility::isDateValid(2020, -1, 12));
	EXPECT_FALSE(DateTimeUtility::isDateValid(2020, 1, -1));
	EXPECT_FALSE(DateTimeUtility::isDateValid(2020, 13, 12));
	EXPECT_FALSE(DateTimeUtility::isDateValid(2020, 12, 32));
	EXPECT_FALSE(DateTimeUtility::isDateValid(2001, 2, 29));
}

TEST(DateTimeUtilityTest, IsTimeValid_CorrectArgumentsGiven_ShouldReturnTrue)
{
	EXPECT_TRUE(DateTimeUtility::isTimeValid(00, 00));
	EXPECT_TRUE(DateTimeUtility::isTimeValid(14, 30));
	EXPECT_TRUE(DateTimeUtility::isTimeValid(23, 59));
}

TEST(DateTimeUtilityTest, IsTimeValid_IncorrectArgumentsGiven_ShouldReturnFalse)
{
	EXPECT_FALSE(DateTimeUtility::isTimeValid(-1, 00));
	EXPECT_FALSE(DateTimeUtility::isTimeValid(00, -1));
	EXPECT_FALSE(DateTimeUtility::isTimeValid(00, 60));
	EXPECT_FALSE(DateTimeUtility::isTimeValid(24, 00));
}

TEST(DateTimeUtilityTest, IsYearLeap_CorrectArgumentGiven_ShouldReturnTrue)
{
	EXPECT_TRUE(DateTimeUtility::isYearLeap(1996));
	EXPECT_TRUE(DateTimeUtility::isYearLeap(2000));
	EXPECT_TRUE(DateTimeUtility::isYearLeap(2020));
}

TEST(DateTimeUtilityTest, IsYearLeap_IncorrectArgumentGiven_ShouldReturnFalse)
{
	EXPECT_FALSE(DateTimeUtility::isYearLeap(1900));
	EXPECT_FALSE(DateTimeUtility::isYearLeap(2019));
	EXPECT_FALSE(DateTimeUtility::isYearLeap(2100));
}
