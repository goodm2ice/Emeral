#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266Ping.h>

#include <WebRTC.hpp>

#define SSID "GM"
#define PASSWORD "25650000"

#define TIME_ZONE "Asia/Yekaterinburg"

WebRTC rtc(TIME_ZONE);

void setup() {
    Serial.begin(115200);

    Serial.print("\nConnecting to " SSID);
    WiFi.begin(SSID, PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print('.');
    }
    Serial.println("Done");

    Serial.println(String("Local IP:") + WiFi.localIP().toString());
}

void loop() {
    if(!rtc.update()) {
        Serial.println("RTC Update error!");
        if (!Ping.ping(IPAddress(8, 8, 8, 8)))
            Serial.println("Ping 8.8.8.8 error!");
    }
    Serial.println(rtc.getTime());
}
