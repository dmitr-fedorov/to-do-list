#include "DateTime.h"

DateTime::DateTime(const int year, const int month, const int day, const int hours, const int minutes)
	: m_year(year), m_month(month), m_day(day), m_hours(hours), m_minutes(minutes)
{

}

DateTime::~DateTime()
{

}

bool DateTime::operator ==(const DateTime& other) const
{
    return (m_year == other.m_year &&
            m_month == other.m_month &&
            m_day == other.m_day &&
            m_hours == other.m_hours &&
            m_minutes == other.m_minutes);
}

bool DateTime::operator !=(const DateTime& other) const
{
    return !(*this == other);
}

bool DateTime::operator <(const DateTime& other) const
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

bool DateTime::operator <=(const DateTime& other) const
{
    return (*this < other || *this == other);
}

bool DateTime::operator >(const DateTime& other) const
{
    return !(*this <= other);
}

bool DateTime::operator >=(const DateTime& other) const
{
    return (*this > other || *this == other);
}

std::ostream& operator<<(std::ostream& os, const DateTime& dt)
{
    os << dt.m_year << "-" << dt.m_month << "-" << dt.m_day << " ";

    if (dt.m_hours < 10)
        os << "0";
    os << dt.m_hours;

    os << ":";

    if (dt.m_minutes < 10)
        os << "0";
    os << dt.m_minutes;

    return os;
}
