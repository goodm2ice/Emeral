#include "DateTime.hpp"

DateTime::DateTime() {
    #ifdef Arduino_h
        unix_time = millis() / 1000;
    #else
        unix_time = 0;
    #endif
}

DateTime::DateTime(time_t const): unix_time(unix_time) {}
DateTime::DateTime(DateTime const& dt): unix_time(dt.unix_time) {}

DateTime::DateTime(const char* str): DateTime(fromString(str)) {}
#ifdef Arduino_h
    DateTime::DateTime(String const str): DateTime(fromString(str)) {}
#endif

DateTime::DateTime(unsigned short year, unsigned char month, unsigned char day, unsigned char hour, unsigned char minute, unsigned char second) {
    //
}

// ---------------------------- Get parts -----------------------------

unsigned short const DateTime::getYear(time_t const unix_time) {
    time_t time = unix_time, tmp;
    unsigned short year = 1970;
    while (time > (tmp = getYearDays(year))) time -= tmp * DAY_DURATION, year++;
    return year;
}

unsigned char const DateTime::getMonth(time_t const unix_time) {
    time_t time = unix_time, tmp;
    unsigned short year = 1970;
    unsigned char month = 0;
    while (time > (tmp = getYearDays(year))) time -= tmp * DAY_DURATION, year++;
    while (time > (tmp = getMonthDays(year, month))) time -= tmp * DAY_DURATION, month++;
    return month;
}

bool const DateTime::isLeapYear(time_t const year) {
    return (year % 400 == 0) || ((year % 100 != 0) && (year % 4 == 0));
}

unsigned short const DateTime::getYearDays(time_t const year) {
    return isLeapYear(year) ? 366 : 365;
}

unsigned char const DateTime::getMonthDays(unsigned short const year, unsigned char const month) {
    if (month == 1)
        return isLeapYear(year) ? 29 : 28;
    if (month < 7)
        return 31 - month % 2;
    return 30 + month % 2;
}

// ------------------------------ Maths -------------------------------

DateTime& DateTime::move(long long const count, DateTimePart_t const part) {
    if (count == 0) return *this;
    if (part )
    switch (part) {
        case SECOND: unix_time += count; break;
        case MINUTE: unix_time += MINUTE_DURATION * count; break;
        case HOUR: unix_time += HOUR_DURATION * count; break;
        case DAY: unix_time += DAY_DURATION * count; break;
        case WEEK: unix_time += WEEK_DURATION * count; break;
        case MONTH: unix_time += getMonthDays(getYear(unix_time), getMonth(unix_time)) * DAY_DURATION * count;
        case YEAR: unix_time += getYearDays(getYear(unix_time)) * DAY_DURATION * count;
        default: break;
    }
    return *this;
}

DateTime& DateTime::operator()(long long const count, DateTimePart_t const part) { return move(count, part); }

DateTime const DateTime::operator+(DateTime const& dt) const { return DateTime(unix_time + dt.unix_time); }
DateTime const DateTime::operator+(time_t const time) const { return DateTime(unix_time + time); }
DateTime const DateTime::operator+(DateTimePart_t const part) const { return DateTime(*this)(1, part); }

DateTime const DateTime::operator-(DateTime const& dt) const  { return DateTime(unix_time - dt.unix_time); }
DateTime const DateTime::operator-(time_t const time) const  { return DateTime(unix_time - time); }
DateTime const DateTime::operator-(DateTimePart_t const part) const { return DateTime(*this)(-1, part); }

DateTime& DateTime::operator=(DateTime const& dt) { unix_time = dt.unix_time; return *this; }
DateTime& DateTime::operator=(time_t const time) { unix_time = time; return *this; }
DateTime& DateTime::operator=(DateTimePart_t const part) { unix_time = 0; move(1, part); return *this; }

DateTime& DateTime::operator+=(DateTime const& dt) { unix_time += dt.unix_time; return *this; }
DateTime& DateTime::operator+=(time_t const time) { unix_time += time; return *this; }
DateTime& DateTime::operator+=(DateTimePart_t const part) { return move(1, part); }

DateTime& DateTime::operator-=(DateTime const& dt)  { unix_time -= dt.unix_time; return *this; }
DateTime& DateTime::operator-=(time_t const time)  { unix_time -= time; return *this; }
DateTime& DateTime::operator-=(DateTimePart_t const part) { return move(-1, part); }

// --------------------------- Comparations ---------------------------

bool const DateTime::operator==(DateTime const& dt) const { return unix_time == dt.unix_time; }
bool const DateTime::operator==(time_t const dt) const  { return unix_time == dt; }

bool const DateTime::operator!=(DateTime const& dt) const { return unix_time != dt.unix_time; }
bool const DateTime::operator!=(time_t const dt) const { return unix_time != dt; }

bool const DateTime::operator<(DateTime const& dt) const { return unix_time < dt.unix_time; }
bool const DateTime::operator<(time_t const dt) const { return unix_time < dt; }

bool const DateTime::operator>(DateTime const& dt) const { return unix_time > dt.unix_time; }
bool const DateTime::operator>(time_t const dt) const { return unix_time > dt; }

bool const DateTime::operator<=(DateTime const& dt) const { return unix_time <= dt.unix_time; }
bool const DateTime::operator<=(time_t const dt) const { return unix_time <= dt; }

bool const DateTime::operator>=(DateTime const& dt) const { return unix_time >= dt.unix_time; }
bool const DateTime::operator>=(time_t const dt) const { return unix_time >= dt; }

// --------------------------- Convertation ---------------------------

DateTimeStruct const DateTime::toStruct(time_t const unix_time) {
    DateTimeStruct out;
    unsigned short tmp = 0;
    time_t time = unix_time;
    // Get year
    while (time > (tmp = getYearDays(out.year))) time -= tmp * DAY_DURATION, out.year++;
    // Get month
    while (time > (tmp = getMonthDays(out.year, out.month))) time -= tmp * DAY_DURATION, out.month++;
    // Get day
    out.day += time / DAY_DURATION;
    time %= DAY_DURATION;
    // Get hour
    out.hour += time / HOUR_DURATION;
    time %= HOUR_DURATION;
    // Get minute
    out.minute += time / MINUTE_DURATION;
    time %= MINUTE_DURATION;
    // Get second
    out.second += time;

    return out;
}

DateTimeStruct const DateTime::toStruct(DateTime const dt) { toStruct(dt.unix_time); }

static DateTime const fromString(const char* str) {
    unsigned short year;
    unsigned char month, day, hour, minute, second;
    if(sscanf(str, STRING_DATE_TEMPLATE, &year, &month, &day, &hour, &minute, &second) != 6)
        throw "";
    return DateTime(year, month, day, hour, minute, second);
}

#ifdef Arduino_h
    static DateTime const fromString(String const str) { return fromString(str.c_str()); }
#endif

DateTime::operator DateTimeStruct() const { return toStruct(unix_time); }

DateTime::operator char*() const {
    DateTimeStruct ts = *this;

    char* out = new char[sizeof(STRING_DATE_EXAMPLE)];
    sprintf(out, STRING_DATE_TEMPLATE, ts.year, ts.month, ts.day, ts.hour, ts.minute, ts.second);
    return out;
}
