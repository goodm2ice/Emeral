#pragma once

#include <stdio.h>

#define STRING_DATE_TEMPLATE "%04hu-%02hhu-%02hhuT%02hhu:%02hhu:%02hhu\0"
#define STRING_DATE_EXAMPLE "0000-00-00T00:00:00"

typedef uint8_t DateTimePartInt_t;
enum DateTimePart_t { SECOND = 1, MINUTE = 2, HOUR = 4, DAY = 8, WEEK = 16, MONTH = 32, YEAR = 64 };

bool const operator>=(DateTimePart_t const dtp1, DateTimePart_t const dtp2) {
    return static_cast<DateTimePartInt_t>(dtp1) & static_cast<DateTimePartInt_t>(dtp2) == static_cast<DateTimePartInt_t>(dtp2);
}

bool const operator<=(DateTimePart_t const dtp1, DateTimePart_t const dtp2) {
    return static_cast<DateTimePartInt_t>(dtp1) & static_cast<DateTimePartInt_t>(dtp2) == static_cast<DateTimePartInt_t>(dtp1);
}

typedef signed long long time_t;
typedef unsigned short year_t;
typedef unsigned char month_t, day_t, hour_t, minute_t, second_t;

class DateTime {
    private:
        time_t unix_time;

        year_t year:14;
        month_t month:4;
        day_t day:5;
        hour_t hour:5;
        minute_t minute:6;
        second_t second:6;

    public:
        DateTime();
        DateTime(time_t const unix_time);
        DateTime(DateTime const& dt);
        DateTime(const char* str);
    #ifdef Arduino_h
        DateTime(String const str);
    #endif
        DateTime(
            year_t const year,
            month_t const month,
            day_t const day,
            hour_t const hour,
            minute_t const minute,
            second_t const second
        );

    #pragma region Getters/Setters
        static DateTime const fromUnixTime(time_t unix_time);
        static time_t const toUnixTime(DateTime const dt);
        static time_t const toUnixTime(
            year_t const year,
            month_t const month,
            day_t const day,
            hour_t const hour,
            minute_t const minute,
            second_t const second
        );

        year_t const getYear() const;
        month_t const getMonth() const;
        day_t const getDay() const;
        hour_t const getHour() const;
        minute_t const getMinute() const;
        second_t const getSecond() const;

        void setYear(year_t const year);
        void setMonth(month_t const month);
        void setDay(day_t const day);
        void setHour(hour_t const hour);
        void setMinute(minute_t const minute);
        void setSecond(second_t const second);
    #pragma endregion

    #pragma region Math operations
        DateTime& move(long long const count, DateTimePart_t const part);
        DateTime& operator()(long long const count, DateTimePart_t const part);

        DateTime const operator+(DateTime const& dt) const;
        DateTime const operator+(time_t const time) const;
        DateTime const operator+(DateTimePart_t const part) const;

        DateTime const operator-(DateTime const& dt) const;
        DateTime const operator-(time_t const time) const;
        DateTime const operator-(DateTimePart_t const part) const;

        DateTime& operator=(DateTime const& dt);
        DateTime& operator=(time_t const time);
        DateTime& operator=(DateTimePart_t const part);

        DateTime& operator+=(DateTime const& dt);
        DateTime& operator+=(time_t const time);
        DateTime& operator+=(DateTimePart_t const part);

        DateTime& operator-=(DateTime const& dt);
        DateTime& operator-=(time_t const time);
        DateTime& operator-=(DateTimePart_t const part);
    #pragma endregion

    #pragma region Comparations
        bool const operator==(DateTime const& dt) const;
        bool const operator==(time_t const dt) const;

        bool const operator!=(DateTime const& dt) const;
        bool const operator!=(time_t const dt) const;

        bool const operator<(DateTime const& dt) const;
        bool const operator<(time_t const dt) const;

        bool const operator>(DateTime const& dt) const;
        bool const operator>(time_t const dt) const;

        bool const operator<=(DateTime const& dt) const;
        bool const operator<=(time_t const dt) const;

        bool const operator>=(DateTime const& dt) const;
        bool const operator>=(time_t const dt) const;
    #pragma endregion

    #pragma region Conversations
        static DateTime const fromString(const char* str);
        #ifdef Arduino_h
            static DateTime const fromString(String const str);
        #endif

        operator char*() const;
    #pragma endregion

    private:
        year_t const getYearDays(year_t const year);
        day_t const getMonthDays(year_t const year, month_t const month);
};
