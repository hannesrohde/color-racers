#include <Arduino.h>
#include <FastLED.h>
#include <vector>
#include <pixeltypes.h>

#include "dot.h"

#define MAX_FPS  200
#define NUM_LEDS 144

static unsigned long FRAME_MICROS = 1000000 / MAX_FPS;

static CRGB leds[NUM_LEDS];
// static CLEDController &controller;

void setup()
{
  CLEDController &controller = FastLED.addLeds<SK9822, BGR>(leds, NUM_LEDS);
  controller.clearLeds(NUM_LEDS);
}

static std::vector<Dot> dots;

void loop()
{
  unsigned long startMicros = micros();

  /////////////////////////////////////////////////////////////////////////////

  // reset all leds
  fill_solid(leds, NUM_LEDS, CRGB::Black);

  // spawn new dots randomly:
  if (random8() < 4) {
    uint8_t hue = random8();
    float speed = (16.0 + random8(32)) / 128.0f;
    Dot dot(hue, speed);
    dots.push_back(dot);
  }

  // draw and move all dots:
  for (std::vector<Dot>::iterator it = dots.begin(); it != dots.end(); ) {

    uint8_t dotHue = it->getHue();
    float dotPos = it->getPos();

    leds[static_cast<int>(dotPos)] += CHSV(dotHue, 255, 31);

    it->move();

    if (it->getPos() > NUM_LEDS) {
      it = dots.erase(it);
    } else {
      it++;
    }
  }

  // display all dots:

  FastLED.show();

  //////////////////////////////////////////////////////////////////////////////

  unsigned long stopMicros = micros();

  // sleep for remaining time of this frame to cap FPS
  if (stopMicros >= startMicros) {
    unsigned long durationMicros = stopMicros - startMicros;
    if (durationMicros < FRAME_MICROS) {
      delayMicroseconds(FRAME_MICROS - durationMicros);
    }
  }
}
