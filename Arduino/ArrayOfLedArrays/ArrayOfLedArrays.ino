#include "FastLED.h"

#define NUM_STRIPS 1
#define NUM_LEDS_PER_STRIP 190
CRGB leds[NUM_STRIPS][NUM_LEDS_PER_STRIP];

int stripOffSet = 9;

void setup() {

  for (int i = 0; i < NUM_STRIPS; i++) {
    int pin = i + 1;
    FastLED.addLeds<NEOPIXEL, pin>(leds[i], NUM_LEDS_PER_STRIP);
  }
  
}

void loop() {
  
  for(int x = 0; x < NUM_STRIPS; x++) {
    for(int i = stripOffSet; i < NUM_LEDS_PER_STRIP; i++) {
      leds[x][i] = CRGB::Red;
      FastLED.show();
      leds[x][i] = CRGB::Black;
      delay(100);
    }
  }
}
