#ifndef __INC_DOT_H
#define __INC_DOT_H

#include <Arduino.h>

class Dot {

    uint8_t hue;
    float pos, speed;

  public:

    Dot (uint8_t hue, float speed):hue(hue), pos(0.0f), speed(speed) {
    }

    void move() {
      pos += speed;
    }

    // TODO: inline, const
    uint8_t getHue() { return hue; }
    float getPos() { return pos; }

};

#endif
