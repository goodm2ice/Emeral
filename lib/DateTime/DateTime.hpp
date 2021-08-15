#pragma once

#include <stdio.h>

#include "DateTimeStruct.hpp"

#define MINUTE_DURATION (60)
#define HOUR_DURATION (60 * MINUTE_DURATION)
#define DAY_DURATION (24 * HOUR_DURATION)
#define WEEK_DURATION (7 * DAY_DURATION)

#define STRING_DATE_TEMPLATE "%04hu-%02hhu-%02hhuT%02hhu:%02hhu:%02hhu\0"
#define STRING_DATE_EXAMPLE "0000-00-00T00:00:00"

typedef unsigned long long time_t;

typedef uint8_t DateTimePartInt_t;
enum DateTimePart_t { SECOND = 1, MINUTE = 2, HOUR = 4, DAY = 8, WEEK = 16, MONTH = 32, YEAR = 64 };

bool const operator>=(DateTimePart_t const dtp1, DateTimePart_t const dtp2) {
    return static_cast<DateTimePartInt_t>(dtp1) & static_cast<DateTimePartInt_t>(dtp2) == static_cast<DateTimePartInt_t>(dtp2);
}

bool const operator<=(DateTimePart_t const dtp1, DateTimePart_t const dtp2) {
    return static_cast<DateTimePartInt_t>(dtp1) & static_cast<DateTimePartInt_t>(dtp2) == static_cast<DateTimePartInt_t>(dtp1);
}

class DateTime {
    private:
        time_t unix_time;
    public:
        DateTime();
        DateTime(time_t const unix_time);
        DateTime(DateTime const& dt);
        DateTime(const char* str);
        #ifdef Arduino_h
            DateTime(String const str);
        #endif
        DateTime(unsigned short year, unsigned char month, unsigned char day, unsigned char hour, unsigned char minute, unsigned char second);

        // ---------------------------- Get parts -----------------------------

        static unsigned short const getYear(time_t const unix_time);

        static unsigned char const getMonth(time_t const unix_time);

        static bool const isLeapYear(time_t const year);

        static unsigned short const getYearDays(time_t const year);

        static unsigned char const getMonthDays(unsigned short const year, unsigned char const month);

        // ------------------------------ Maths -------------------------------

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

        // --------------------------- Comparations ---------------------------

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

        // --------------------------- Convertation ---------------------------

        static DateTimeStruct const toStruct(time_t const unix_time);
        static DateTimeStruct const toStruct(DateTime const dt);

        static DateTime const fromString(const char* str);
        #ifdef Arduino_h
            static DateTime const fromString(String const str);
        #endif

        operator DateTimeStruct() const;

        operator char*() const;
};
