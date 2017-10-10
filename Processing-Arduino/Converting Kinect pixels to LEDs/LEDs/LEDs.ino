#include "FastLED.h"
#include <math.h>

#define NUMBER_OF_LEDS_TO_KEEP_TRACK_OF 200

#define NUM_LEDS 10
#define DATA_PIN 6

CRGB leds[NUM_LEDS];

int x, y, d;
int convertedX, convertedY, convertedD;
int ledX, ledY;
int ledNumber;
int[NUMBER_OF_LEDS_TO_KEEP_TRACK_OF] ledNumbers;
int ledNumbersIndex = 0;

float skipX = 12.8;
float skipY = 25.2632;

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
      Serial.println('x' + readString.substring(readString.indexOf('x') + 1, readString.length()));
      x = readString.substring(readString.indexOf('x'), readString.length()).toInt();
    }
    if (readString.indexOf('y') == 0) {
      Serial.println('y' + readString.substring(readString.indexOf('y') + 1, readString.length()));
      y = readString.substring(readString.indexOf('y'), readString.length()).toInt();
    }
    if (readString.indexOf('d') == 0) {
      Serial.println('d' + readString.substring(readString.indexOf('d') + 1, readString.length()));
      d = readString.substring(readString.indexOf('d'), readString.length()).toInt();
    }
    readString = "";
    
    if (x !== null && y !== null && d !== null) {
      runCoordinateConversion();
      leds[ledNumber] = CRGB::Blue;
      FastLED.show();
      delay(100);
      
      ledNumbers[ledNumbersIndex] = ledNumber;
      ledNumbersIndex++;
      if (ledNumbersIndex == NUMBER_OF_LEDS_TO_KEEP_TRACK_OF) {
        ledNumbersIndex = 0;
        ledOff(0);
      } else {
        ledOff(ledNumbersIndex + 1);
      }
      
      x, y, d = null;
    } 
  }
}

void ledOff(int i) {
  leds[i] = CRGB::Black;
  FastLED.show();
  delay(100);  
}

void runCoordinateConversion() {   
  convertCoordinate();
  calculateLedAddress();
}

void convertCoordinate() {
  convertedX = convertX(x);
  setPanel();
  convertedY = convertY(y);
  convertedD = convertD(d);
}

void calculateLedAddress() {
  ledX = convertLedX();
  
  if (convertedY % 2 == 0) {
    ledY = ((convertedY * 10) - ledX);
  } else {
    ledY = ((convertedY * 10) + ledX);
  }
}

int convertLedX() {
  if (convertedX >= 1 && convertedX <= 10) {
    return convertedX;
  } else if (convertedX >= 11 && convertedX <= 20) {
    return convertedX - 10;
  } else if (convertedX >= 21 && convertedX <= 30) {
    return convertedX - 20;
  } else if (convertedX >= 31 && convertedX <= 40) {
    return convertedX - 30;
  } else if (convertedX >= 41 && convertedX <= 50) {
    return convertedX - 40;
  }
}

int convertX(float x) {    
  int convertedX = ceil((x / skipX));
  return convertedX;
}

int convertY(float y) { 
  int convertedY = ceil((y / skipY));
  convertedY = 20 - convertedY;   
  return convertedY;
}

int convertD(float d) {
  // Perform x coordinate conversion in here
  return convertedD;
}

void setPanel() {
    if (convertedX >= 1 && convertedX <= 10) {
      panelNumber = 1;
    } else if (convertedX >= 1 && convertedX <= 10) {
      panelNumber = 2;
    } else if (convertedX >= 21 && convertedX <= 30) {
      panelNumber = 3;
    } else if (convertedX >= 31 && convertedX <= 40) {
      panelNumber = 4;
    } else if (convertedX >= 41 && convertedX <= 50) {
      panelNumber = 5;
    }
  }
