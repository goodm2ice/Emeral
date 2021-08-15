#include "WebRTC.hpp"

using namespace Emeral;

void RTC_Init(String timezone) {
    RTC_timeZone = timezone;
    setSyncProvider(Emeral::RTC_updateTime);
    setSyncInterval(RTC_UPDATE_INTERVAL);
}

time_t RTC_updateTime() {
    WiFiClient http;
    http.setTimeout(RTC_DEFAULT_TIMEOUT);
    if (!http.connect(RTC_HOST, RTC_PORT))
        return 0;

    http.println(MAKE_RTC_REQUEST(RTC_timeZone));
    uint64_t sys_time = millis() / 1000;
    uint64_t out = millis() + RTC_DEFAULT_TIMEOUT;
    while(!http.available())
        if (out - millis() < 0)
            return 0;

    http.readStringUntil('{');
    String payload = String("{") + http.readStringUntil('\r');
    DynamicJsonDocument doc(DOC_MEMORY);

    DeserializationError error = deserializeJson(doc, payload);
    if (error != DeserializationError::Code::Ok)
        return 0;

    return (time_t)doc[UNIX_TIME];
}
