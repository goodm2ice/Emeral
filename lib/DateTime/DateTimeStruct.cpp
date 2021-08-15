#include "DateTimeStruct.hpp"

DateTimeStruct const DateTimeStruct::operator+(DateTimeStruct const ts) const {
    return DateTimeStruct(*this) += ts;
}

DateTimeStruct const DateTimeStruct::operator-(DateTimeStruct const ts) const {
    return DateTimeStruct(*this) -= ts;
}

DateTimeStruct& DateTimeStruct::operator=(DateTimeStruct const ts) {
    year = ts.year;
    month = ts.month;
    day = ts.day;
    hour = ts.hour;
    minute = ts.minute;
    second = ts.second;
    return *this;
}

DateTimeStruct& DateTimeStruct::operator+=(DateTimeStruct const ts) {
    DateTimeStruct out;
    out.second = (second + ts.second) % 60;
    out.minute = (second + ts.second) / 60;
    out.hour = (out.minute + minute + ts.minute) / 60;
    out.minute = (out.minute + minute + ts.minute) % 60;
    out.day = (out.hour + hour + ts.hour) / 24;
    out.hour = (out.hour + hour + ts.hour) % 24;
    ///TODO
}

DateTimeStruct& DateTimeStruct::operator-=(DateTimeStruct const ts) {} ///TODO

bool const DateTimeStruct::operator==(DateTimeStruct const ts) const {
    return (year == ts.year) && (month == ts.month) && (day == ts.day) && (hour == ts.hour) && (minute == ts.minute) && (second == ts.second);
}
bool const DateTimeStruct::operator>(DateTimeStruct const ts) const {
    return (year > ts.year) ||
            (year == ts.year && month > ts.month) ||
            (year == ts.year && month == ts.month && day > ts.day) ||
            (year == ts.year && month == ts.month && day == ts.day && hour > ts.hour) ||
            (year == ts.year && month == ts.month && day == ts.day && hour == ts.hour && minute > ts.minute) ||
            (year == ts.year && month == ts.month && day == ts.day && hour == ts.hour && minute == ts.minute && second > ts.second);
}
bool const DateTimeStruct::operator<(DateTimeStruct const ts) const {
    return (year < ts.year) ||
            (year == ts.year && month < ts.month) ||
            (year == ts.year && month == ts.month && day > ts.day) ||
            (year == ts.year && month == ts.month && day == ts.day && hour < ts.hour) ||
            (year == ts.year && month == ts.month && day == ts.day && hour == ts.hour && minute < ts.minute) ||
            (year == ts.year && month == ts.month && day == ts.day && hour == ts.hour && minute == ts.minute && second < ts.second);
}
bool const DateTimeStruct::operator!=(DateTimeStruct const ts) const { return !(*this == ts); }
bool const DateTimeStruct::operator>=(DateTimeStruct const ts) const { return (*this == ts) || (*this > ts); }
bool const DateTimeStruct::operator<=(DateTimeStruct const ts) const { return (*this == ts) || (*this < ts); }
