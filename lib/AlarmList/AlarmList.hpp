#pragma once

#include <stdint.h>

#include <WebRTC.hpp>

#define IS_ODD_YEAR ((year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0)))
#define DAY_DURATION (24 * 60 * 60)
#define WEEK_DURATION (7 * DAY_DURATION)
#define MONTH_DURATION(year, month) DAY_DUARATION *\
    ((month == 2) ? (IS_ODD_YEAR ? 29 : 28) :\
    ((month < 8) ? ((month % 2 == 0) ? 30 : 31) :\
    ((month % 2 == 0) ? 31 : 30)))
#define YEAR_DURATION (IS_ODD_YEAR ? 366 : 365)

struct Alarm {
    enum AlarmFrequency_t { NONE, TIMEOUT, WEEK_DAY, MONTH_DAY, YEAR_DAY } repeatType = NONE;
    double repeatValue = 0;
    uint64_t startTime = 0;
    uint64_t nextTime = 0;
    bool enabled = false;

    bool done(WebRTC::TimeData timeData) {
        switch (repeatType) {
            case NONE: return false;
            case TIMEOUT: nextTime += repeatValue; break;
            case WEEK_DAY: nextTime += repeatValue * WEEK_DURATION;
            case MONTH_DAY:
                for (uint64_t i = 0; i < repeatValue; i++)
                    
        }
        return true;
    }
};

class AlarmList {
    private:

};