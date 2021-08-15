#include "WebRTC.hpp"

using namespace Emeral;

WebRTC::WebRTC(String timezone) {
    this->timezone = timezone;
    last_update = cur_time();
    last_time = 0;
    dt = new DateTime(last_update);
}

time_t const WebRTC::cur_time() { return millis() / 1000; }

void WebRTC::update_local() {
    *dt = last_time + (cur_time() - last_update);
}

bool WebRTC::update() {
    WiFiClient http;
    http.setTimeout(RTC_DEFAULT_TIMEOUT);
    if (!http.connect(RTC_HOST, RTC_PORT)) {
        update_local();
        return false;
    }

    http.println(MAKE_RTC_REQUEST(timezone));
    last_update = cur_time();
    uint64_t out = millis() + RTC_DEFAULT_TIMEOUT;
    while(!http.available())
        if (out - millis() < 0) {
            update_local();
            return false;
        }

    http.readStringUntil('{');
    String payload = String("{") + http.readStringUntil('\r');
    DynamicJsonDocument doc(DOC_MEMORY);

    DeserializationError error = deserializeJson(doc, payload);
    if (error != DeserializationError::Code::Ok) {
        update_local();
        return false;
    }

    last_time = doc[UNIX_TIME];

    return true;
}

const DateTime const* WebRTC::get() const { return dt; }
