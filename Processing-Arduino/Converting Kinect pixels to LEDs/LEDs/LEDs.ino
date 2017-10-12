#include "FastLED.h"
#include <math.h>

/*
 * Set number of LEDs and data pins here
 */
#define NUM_LEDS 10
//#define NUM_LEDS 200
#define DATA_PIN 6
#define LED_START 9
#define LED_END 1
// NUMBER_OF_LEDS = (NUM_LEDS - (LED_START + LED_END));
#define NUMBER_OF_LEDS 190


/*
 * skipX = kinectWidth / number of leds on the X axis
 * skipX = kinectHeight / number of leds on the Y axis
 */
float skipX = 12.8;
float skipY = 25.2632;

CRGB leds[NUMBER_OF_LEDS];

/*
 * Variables
 */
int x, y, d = -1;
int convertedX, convertedY, convertedD;
int ledX, ledY;
int ledNumber;
int ledNumbers[NUMBER_OF_LEDS];
int ledNumbersIndex = 0;
int panelNumber;

String readString;

/*
 * Setup with LED Strips and Serial
 */
void setup() { 
//  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUMBER_OF_LEDS);
  Serial.begin(9600);
}

/*
 * Main loop to recieve Kinect data and convert it into an LED address to turn on
 */
void loop() {
  // Serial connection gets through the x, y and d coordinates
  while (Serial.available()) {    
    delay(5);
    char c = Serial.read();
//
//    // When we reach the end of the string we can use it
    if (c == ',') {
////     readString += c;
     break;
    }  
    readString += c;
  }

  // When there is a string to read, figure out which coordinate it is
  if (readString.length() > 0) {
    if (readString.indexOf('x') == 0) {
      x = (readString.substring(readString.indexOf('x') + 1, readString.length())).toInt();
//      Serial.println(x);
    }
    if (readString.indexOf('y') == 0) {
      y = (readString.substring(readString.indexOf('y') + 1, readString.length())).toInt();
//      Serial.println(y);
    }
    if (readString.indexOf('d') == 0) {
      d = (readString.substring(readString.indexOf('d') + 1, readString.length())).toInt();
//      Serial.println(d);
    }
    readString = "";

    // When all coordinates have been sent through can convert them
    if (x != -1 && y != -1/* && d != -1*/) {
      // Run conversion and turn on led
      runCoordinateConversion();
//      leds[ledNumber] = CRGB::Blue;     
//      FastLED.show();
//      delay(100);

      // Record which led's have been turned on
      ledNumbers[ledNumbersIndex] = ledNumber;
      ledNumbersIndex++;

      // When the led array index reaches the max (currently set to 1 panels worth of LEDs)
      // turn the off first LED and set the index back to the first led
      if (ledNumbersIndex == NUMBER_OF_LEDS) {
        ledNumbersIndex = 0;
//        ledOff(0);
      } else {
//        ledOff(ledNumbersIndex + 1);
      }

      // Set coorindates back to -1 so we can track them again from Kinect
      x, y, d = -1;
    }    
  }
}

/*
 * Turns an LED off
 */
void ledOff(int i) {
  leds[i] = CRGB::Black;
  FastLED.show();
  delay(100);  
}

/*
 * Runs the two conversion functions
 */
void runCoordinateConversion() {   
  convertCoordinate();
  calculateLedAddress();
}

/*
 * Calculate converted coordinates and set panel number
 */
void convertCoordinate() {
  convertedX = convertX();
  setPanel();
  convertedY = convertY();
  convertedD = convertD();  
}

/*
 * Calculates LED number based on ledX and ledY position, for even y LEDs 
 * need to go back further since they zigzag and pixels do not
 */
void calculateLedAddress() {
  ledX = convertLedX();
  
  if (convertedY % 2 == 0) {
    ledNumber = ((convertedY * 10) - ledX);
  } else {
    ledNumber = ((convertedY * 10) - (10 -  ledX));
  }
}

/* 
 * Get's local panels x instead of x for all panels 
 */
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

/* 
 * Sets Panel based on X position 
 */
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

/*
 * Conversion to x is divide by number of x pixels to skip to make Kinect 
 * pixels fit to LED matrix dimensions (e.g. x=640/50  y=480/19)
 */
int convertX() {    
  int convertedX = ceil((x / skipX));
  return convertedX;
}

/*
 * Conversion to y is the same as x except you need to invert the axis since
 * Kinect's y=0 is at the top of the screen and the LED strips start with y=1 
 * at the bottom
 */
int convertY() { 
  int convertedY = ceil((y / skipY));
  convertedY = 20 - convertedY;   
  return convertedY;
}

/*
 * Could do some color conversion here relating to how close the user is
 */
int convertD() {
  // Perform x coordinate conversion in here
  convertedD = d;
  return convertedD;
}


