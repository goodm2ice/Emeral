#include "WebRTC.hpp"

using namespace Emeral;

WebRTC::WebRTC(String timezone) {
    this->timezone = timezone;
    last_update = cur_time();
    last_time = 0;
}

time_t const WebRTC::cur_time() { return millis() / 1000; }

const tm const* WebRTC::update() {
    WiFiClient http;
    http.setTimeout(RTC_DEFAULT_TIMEOUT);
    if (!http.connect(RTC_HOST, RTC_PORT))
        return get();

    http.println(MAKE_RTC_REQUEST(timezone));
    last_update = cur_time();
    uint64_t out = millis() + RTC_DEFAULT_TIMEOUT;
    while(!http.available())
        if (out - millis() < 0)
            return get();

    http.readStringUntil('{');
    String payload = String("{") + http.readStringUntil('\r');
    DynamicJsonDocument doc(DOC_MEMORY);

    DeserializationError error = deserializeJson(doc, payload);
    if (error != DeserializationError::Code::Ok)
        return get();

    last_time = doc[UNIX_TIME];

    return get();
}

const tm const* WebRTC::get() const {
    time_t now = getUnixTime();
    tm* dt = localtime(&now);
    return dt;
}

const time_t WebRTC::getUnixTime() const {
    return last_time + (cur_time() - last_update);
}
