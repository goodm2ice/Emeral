#include "DateTime.hpp"

DateTime::DateTime() {
    #ifdef Arduino_h
        unix_time = millis() / 1000;
    #else
        unix_time = 0;
    #endif
}

DateTime::DateTime(time_t const): unix_time(unix_time) {}

DateTime::DateTime(DateTime const& dt):
    unix_time(dt.unix_time),
    year(dt.year),
    month(dt.month),
    day(dt.day),
    hour(dt.hour),
    minute(dt.minute),
    second(dt.second) {}

DateTime::DateTime(const char* str): DateTime(fromString(str)) {}
#ifdef Arduino_h
    DateTime::DateTime(String const str): DateTime(fromString(str)) {}
#endif

DateTime::DateTime(unsigned short year, unsigned char month, unsigned char day, unsigned char hour, unsigned char minute, unsigned char second):
        year(year), month(month), day(day), hour(hour), minute(minute), second(second) {
    //
}

#pragma region DateTime math operations

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

#pragma endregion
#pragma region DateTime comparations

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

#pragma endregion
#pragma region DateTime conversations

static DateTime const fromString(const char* str) {
    unsigned short year;
    unsigned char month, day, hour, minute, second;
    if(sscanf(str, STRING_DATE_TEMPLATE, &year, &month, &day, &hour, &minute, &second) != 6)
        throw "Input incorrect!";
    return DateTime(year, month, day, hour, minute, second);
}

#ifdef Arduino_h
    static DateTime const fromString(String const str) { return fromString(str.c_str()); }
#endif

DateTime::operator char*() const {
    char* out = new char[sizeof(STRING_DATE_EXAMPLE)];
    sprintf(out, STRING_DATE_TEMPLATE, year, month, day, hour, minute, second);
    return out;
}

#pragma endregion
