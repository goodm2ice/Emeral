#include "Screen1306.hpp"

Screen1306::Screen1306(const u8g2_cb_t* rotation) {
    u8g2 = new U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C(rotation);
}

Screen1306::~Screen1306() {
    delete u8g2;
}

void Screen1306::setup() {
    u8g2->begin();
}

void Screen1306::update() {
    u8g2->clearDisplay();
    
    u8g2->clearBuffer();
    u8g2->setFont(u8g2_font_logisoso28_tr);
    u8g2->drawStr(8, 29, text.c_str());
    u8g2->sendBuffer();

    u8g2->clearBuffer();
    u8g2->setFont(u8g2_font_logisoso16_tr);
    u8g2->drawStr(0, 0, String(battery).c_str());
    u8g2->sendBuffer();
}
