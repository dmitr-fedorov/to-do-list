#include "DateTime.h"
#include "DateTimeUtility.h"

#include <string>

DateTime::DateTime(const std::string_view dateTimeView)
{
    validateStringFormat(dateTimeView);

    assignMemberValuesFromString(dateTimeView);

    validateMemberValues();
}

void DateTime::validateStringFormat(const std::string_view dateTimeView) const
{
    if (!DateTimeUtility::isDateTimeFormatCorrect(dateTimeView))
    {
        throw "Date and time format is incorrect! Relevant format: \"yyyy-mm-dd hh:mm\".";
    }
}

void DateTime::assignMemberValuesFromString(const std::string_view dateTimeView)
{
    static const int YEAR_INDEX = 0;
    static const int YEAR_LENGTH = 4;

    static const int MONTH_INDEX = 5;
    static const int MONTH_LENGTH = 2;

    static const int DAY_INDEX = 8;
    static const int DAY_LENGTH = 2;

    static const int HOURS_INDEX = 11;
    static const int HOURS_LENGTH = 2;

    static const int MINUTES_INDEX = 14;
    static const int MINUTES_LENGTH = 2;

    std::string str_year(dateTimeView.substr(YEAR_INDEX, YEAR_LENGTH));
    std::string str_month(dateTimeView.substr(MONTH_INDEX, MONTH_LENGTH));
    std::string str_day(dateTimeView.substr(DAY_INDEX, DAY_LENGTH));
    std::string str_hours(dateTimeView.substr(HOURS_INDEX, HOURS_LENGTH));
    std::string str_minutes(dateTimeView.substr(MINUTES_INDEX, MINUTES_LENGTH));

    m_year = std::stoi(str_year);
    m_month = std::stoi(str_month);
    m_day = std::stoi(str_day);
    m_hours = std::stoi(str_hours);
    m_minutes = std::stoi(str_minutes);
}

void DateTime::validateMemberValues() const
{
    if (!DateTimeUtility::isDateValid(m_year, m_month, m_day))
    {
        throw "Date is invalid!";
    }

    if (!DateTimeUtility::isTimeValid(m_hours, m_minutes))
    {
        throw "Time is invalid!";
    }
}

bool DateTime::operator==(const DateTime& other) const
{
    return (m_year == other.m_year &&
            m_month == other.m_month &&
            m_day == other.m_day &&
            m_hours == other.m_hours &&
            m_minutes == other.m_minutes);
}

bool DateTime::operator!=(const DateTime& other) const
{
    return !(*this == other);
}

bool DateTime::operator<(const DateTime& other) const
{
    if (m_year < other.m_year)
        return true;

    if (m_year > other.m_year)
        return false;

    if (m_month < other.m_month)
        return true;

    if (m_month > other.m_month)
        return false;

    if (m_day < other.m_day)
        return true;

    if (m_day > other.m_day)
        return false;

    if (m_hours < other.m_hours)
        return true;

    if (m_hours > other.m_hours)
        return false;

    if (m_minutes < other.m_minutes)
        return true;

    if (m_minutes > other.m_minutes)
        return false;

    return false;
}

bool DateTime::operator<=(const DateTime& other) const
{
    return (*this < other || *this == other);
}

bool DateTime::operator>(const DateTime& other) const
{
    return !(*this <= other);
}

bool DateTime::operator>=(const DateTime& other) const
{
    return (*this > other || *this == other);
}

std::ostream& operator<<(std::ostream& os, const DateTime& dt)
{
    os << dt.m_year << "-";

    if (dt.m_month < 10)
    {
        os << "0";
    }
    os << dt.m_month << "-";

    if (dt.m_day < 10)
    {
        os << "0";
    }
    os << dt.m_day << " ";

    if (dt.m_hours < 10)
    {
        os << "0";
    }
    os << dt.m_hours << ":";

    if (dt.m_minutes < 10)
    {
        os << "0";
    }
    os << dt.m_minutes;

    return os;
}
