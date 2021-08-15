#pragma once

#define MINUTE_DURATION (60)
#define HOUR_DURATION (60 * MINUTE_DURATION)
#define DAY_DURATION (24 * HOUR_DURATION)
#define WEEK_DURATION (7 * DAY_DURATION)

typedef unsigned long long time_t;

class DateTimeBuilder {
    private:
        static unsigned short const _getYear(time_t& unix_time);

        static unsigned char const _getMonth(time_t& unix_time, unsigned short year = 0);
    public:
        static unsigned short const getYear(time_t unix_time);

        static unsigned char const getMonth(time_t unix_time);

        static bool const isLeapYear(unsigned short const year);

        static unsigned short const getYearDays(unsigned short const year);

        static unsigned char const getMonthDays(unsigned short const year, unsigned char const month);
};
