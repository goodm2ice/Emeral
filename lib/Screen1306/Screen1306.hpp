#pragma once

#include <U8g2lib.h>

class Screen1306 {
    private:
        U8G2* u8g2 = nullptr;

    public:
        uint8_t battery = 100;
        String text = "Sample Text";

        Screen1306(const u8g2_cb_t* rotation);

        ~Screen1306();

        void setup();

        void update();
};
