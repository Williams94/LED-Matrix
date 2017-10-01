#include "FastLED.h"

#define NUM_LEDS 10
#define DATA_PIN 6

CRGB leds[NUM_LEDS];

int x, y, d;

String readString;

void setup() { 
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  Serial.begin(9600);
}

void loop() {
  while (Serial.available()) {
    delay(5);
    char c = Serial.read();
    if (c == ',') {
//     readString += c;
     break;
    }  
    readString += c;
  }

  if (readString.length() > 0) {
    if (readString.indexOf('x') == 0) {
      Serial.println(readString.substring(readString.indexOf('x') + 1, readString.length()));
      x = readString.substring(readString.indexOf('x'), readString.length()).toInt();
    }
    if (readString.indexOf('y') == 0) {
      Serial.println(readString.substring(readString.indexOf('y') + 1, readString.length()));
      x = readString.substring(readString.indexOf('y'), readString.length()).toInt();
    }
    if (readString.indexOf('d') == 0) {
      Serial.println(readString.substring(readString.indexOf('d') + 1, readString.length()));
      x = readString.substring(readString.indexOf('d'), readString.length()).toInt();
    }
    
    readString="";
  }
}

void ledOff(int i) {
  leds[i] = CRGB::Black;
  FastLED.show();
  delay(200);  
}
