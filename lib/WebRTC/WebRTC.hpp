#pragma once

#include <stdint.h>
#include <string.h>

#include <ESP8266WiFi.h>
#include <Arduino.h>

#define ARDUINOJSON_USE_LONG_LONG 1
#include <ArduinoJson.h>
#include <TimeLib.h>

#define RTC_HOST "worldtimeapi.org"
#define RTC_PORT 80
#define RTC_API_URL "/api/timezone/" // ...Asia/Yekaterinburg for ex.
#define RTC_DEFAULT_TIMEOUT 2000
#define RTC_UPDATE_INTERVAL 60000

#define UNIX_TIME "unixtime"
#define DOC_MEMORY 1024

#define MAKE_RTC_REQUEST(tz)\
    String("GET " RTC_API_URL) + tz + " HTTP/1.1\r\n"\
    "HOST: " RTC_HOST "\r\n"

namespace Emeral {
    static String RTC_timeZone = "Asia/Yekaterinburg";
    time_t RTC_updateTime();
    void RTC_Init(String timezone);
}
