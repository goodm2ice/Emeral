#include "DateTimeBuilder.hpp"

unsigned short const DateTimeBuilder::_getYear(time_t& unix_time) {
    time_t tmp;
    unsigned short year = 1970;
    while (unix_time > (tmp = getYearDays(year))) unix_time -= tmp * DAY_DURATION, year++;
    return year;
}

unsigned char const DateTimeBuilder::_getMonth(time_t& unix_time, unsigned short year) {
    time_t tmp;
    unsigned char month = 0;
    if (unix_time >= 365 || year == 0)
        year = _getYear(unix_time);
    while (unix_time > (tmp = getMonthDays(year, month))) unix_time -= tmp * DAY_DURATION, month++;
    return month;
}

unsigned short const DateTimeBuilder::getYear(time_t unix_time) { return _getYear(unix_time); }

unsigned char const DateTimeBuilder::getMonth(time_t unix_time) { return _getMonth(unix_time); }

bool const DateTimeBuilder::isLeapYear(unsigned short const year) {
    return (year % 400 == 0) || ((year % 100 != 0) && (year % 4 == 0));
}

unsigned short const DateTimeBuilder::getYearDays(unsigned short const year) {
    return isLeapYear(year) ? 366 : 365;
}

unsigned char const DateTimeBuilder::getMonthDays(unsigned short const year, unsigned char const month) {
    if (month == 1)
        return isLeapYear(year) ? 29 : 28;
    if (month < 7)
        return 31 - month % 2;
    return 30 + month % 2;
}
