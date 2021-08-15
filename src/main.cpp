#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266Ping.h>

#include <ConnectionConfig.hpp>

#include <Screen1306.hpp>
#include <WebRTC.hpp>

using namespace Emeral;

Screen1306 screen(U8G2_R0); // D1-SCL, D2-SDA
WebRTC rtc(RCT_TIME_ZONE);

void setup() {
    Serial.begin(115200);

    Serial.print("\nConnecting to: " WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print('.');
    }
    Serial.println("Done");

    Serial.println(String("Local IP:") + WiFi.localIP().toString());

    screen.setup();
    screen.update();
}

void loop() {
    if(!rtc.update()) {
        Serial.println("RTC Update error!");
        if (!Ping.ping(PING_HOST))
            Serial.println(String("Ping ") + PING_HOST.toString() + " error!");
    }
    Serial.println(*rtc.get());
}
