#pragma once

struct DateTimeStruct {
    DateTimeStruct(): year{1970} {}

    unsigned short year:14;
    unsigned char month:4;
    unsigned char day:5;
    unsigned char hour:5;
    unsigned char minute:6;
    unsigned char second:6;

    DateTimeStruct const operator+(DateTimeStruct const ts) const;
    DateTimeStruct const operator-(DateTimeStruct const ts) const;

    DateTimeStruct& operator=(DateTimeStruct const ts);
    DateTimeStruct& operator+=(DateTimeStruct const ts);
    DateTimeStruct& operator-=(DateTimeStruct const ts);

    bool const operator==(DateTimeStruct const ts) const;
    bool const operator!=(DateTimeStruct const ts) const;
    bool const operator>=(DateTimeStruct const ts) const;
    bool const operator<=(DateTimeStruct const ts) const;
    bool const operator>(DateTimeStruct const ts) const;
    bool const operator<(DateTimeStruct const ts) const;
};