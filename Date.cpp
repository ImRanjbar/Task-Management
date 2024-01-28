#include "Date.h"

Date::Date() : m_day(1), m_month(1), m_year(2000) {}

Date::Date(int day, int month, int year) : m_day(day), m_month(month), m_year(year) {
    if (!isValidDate()) {
        m_day = 1;
        m_month = 1;
        m_year = 2000;
    }
}

void Date::setDay(int day) {
    m_day = day;
    if (!isValidDate()) {
        m_day = 1;
    }
}

void Date::setMonth(int month) {
    m_month = month;
    if (!isValidDate()) {
        m_month = 1;
    }
}

void Date::setYear(int year) {
    m_year = year;
    if (!isValidDate()) {
        m_year = 2000;
    }
}

int Date::getDay() const {
    return m_day;
}

int Date::getMonth() const {
    return m_month;
}

int Date::getYear() const {
    return m_year;
}

bool Date::isValidDate() const {
    return (m_day >= 1 && m_day <= 31) &&
           (m_month >= 1 && m_month <= 12) &&
           (m_year >= 2000);
}

bool Date::operator==(const Date& other) const {
    return (m_day == other.m_day) && (m_month == other.m_month) && (m_year == other.m_year);
}

bool Date::operator<(const Date& other) const {
    if (m_year != other.m_year) {
        return m_year < other.m_year;
    }
    if (m_month != other.m_month) {
        return m_month < other.m_month;
    }
    return m_day < other.m_day;
}

bool Date::operator>(const Date& other) const {
    return !(*this == other) && !(*this < other);
}
