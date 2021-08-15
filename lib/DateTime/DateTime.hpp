#pragma once

#include <stdio.h>

#include "DateTimeBuilder.hpp"
#include "DateTimeStruct.hpp"

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
