#include <FastLED.h>
#include <math.h>

/*
 * Set number of LEDs and data pins here
 */
#define NUMBER_OF_LEDS 190
#define LED_DELAY 50
//CRGB leds[NUMBER_OF_LEDS];

// For multiple LED strips
#define NUM_STRIPS 5
#define NUM_LEDS_PER_STRIP NUMBER_OF_LEDS
CRGB leds[NUM_STRIPS][NUM_LEDS_PER_STRIP];
//CRGB leds[NUM_LEDS_PER_STRIP];

/*
 * skipX = kinectWidth / number of leds on the X axis
 * skipX = kinectHeight / number of leds on the Y axis
 */
float skipX = 12.8;
float skipY = 25.2632;

float minThresh = 400;
float maxThresh = 900;
float threshRange = maxThresh - minThresh;

/*
 * Variables
 */
int x, y, d = -1;
//int convertedX, convertedY, convertedD;
//int ledX, ledY;
//int ledNumber;
//int ledNumbers[300][2];
//int ledNumbersIndex = 0;

int panelNumber = -1;
int ledAddress = -1;
int ledDisplayCount = 0;
int ledsToTurnOn = 30;

String readString;

/*
 * Setup with LED Strips and Serial
 */
void setup() { 
  // One LED Strip
//  FastLED.addLeds<NEOPIXEL, 30>(leds, NUMBER_OF_LEDS);

  // Multiple LED Strips
  FastLED.addLeds<NEOPIXEL, 22>(leds[0], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, 26>(leds[1], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, 30>(leds[2], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, 34>(leds[3], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, 38>(leds[4], NUM_LEDS_PER_STRIP);

//  turnOffAllLeds();
//  FastLED.show();
  
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
    
    // When we reach the end of the string we can use it
    if (c == ',') {
      //     readString += c;
     break;
    }  
    readString += c;
  }

  // When there is a string to read, figure out which coordinate it is
  if (readString.length() > 0) {
    if (readString.indexOf('l') == 0) {
      ledAddress = (readString.substring(readString.indexOf('l') + 1, readString.length())).toInt();
      Serial.println("l" + (String)ledAddress);
    }
    if (readString.indexOf('p') == 0) {
      panelNumber = (readString.substring(readString.indexOf('p') + 1, readString.length())).toInt();
      Serial.println("p" + (String)panelNumber);
    }
    if (readString.indexOf('d') == 0) {
      d = (readString.substring(readString.indexOf('d') + 1, readString.length())).toInt();
      Serial.println("d" + (String)d);  
    }   
    readString = "";    

    if (panelNumber != -1 && ledAddress != -1 && d != -1) {
      Serial.println("l" + (String)ledAddress + "p" + (String)panelNumber + "d" + (String)d);
      if (ledDisplayCount == 0) {
        turnOffAllLeds();
      }
      
      convertDepthToRgbAndTurnOnLed(d);
      ledDisplayCount++;
      
      if (ledDisplayCount == ledsToTurnOn) {        
        FastLED.show();
        delay(LED_DELAY);
        ledDisplayCount = 0;
      }
      
      panelNumber, ledAddress, d = -1;
    }
  }
}

/*******************************************************************************************************
 * 
 * Functions for turning LEDs on and off with different colours and coversion of depth to color temp etc.
 * 
 ******************************************************************************************************/

 void turnOffAllLeds() {
  fill_solid(leds[0], NUMBER_OF_LEDS, CRGB::Black);
  fill_solid(leds[1], NUMBER_OF_LEDS, CRGB::Black);
  fill_solid(leds[2], NUMBER_OF_LEDS, CRGB::Black);
  fill_solid(leds[3], NUMBER_OF_LEDS, CRGB::Black);
  fill_solid(leds[4], NUMBER_OF_LEDS, CRGB::Black);
    /*for(int i = 0; i < NUM_LEDS_PER_STRIP; i++) {
      leds[0][i] = CRGB::Black;
      leds[1][i] = CRGB::Black;
      leds[2][i] = CRGB::Black;
      leds[3][i] = CRGB::Black;
      leds[4][i] = CRGB::Black;
    }*/
 }

/*
 * Turns an LED off
 */
void ledOff(int i, int panelNumber) {
//  leds[panelNumber][ledAddress] = CRGB::Black;
  FastLED.show();
  delay(LED_DELAY);  
}

/*
 * Turns an LED on with the color Red
 */
void ledOnRgb(int r, int g, int b) {  
  Serial.println("p" + (String)panelNumber + "l" + (String)ledAddress);
  leds[panelNumber][ledAddress].setRGB(r, g, b);
}

/*
 * Converts depth to rgb and turns on led with that color
 */
void convertDepthToRgbAndTurnOnLed(int depth) {
  // red is depth mapped from low to high e.g. closer = redder
  int r = map(depth, maxThresh, minThresh, 50, 255);

  // green can be used if needed
//  int g = map(depth, minThresh, maxThresh, 0, 255);
  int g = 50;

  // red is depth mapped from high to low e.g. further away = bluer
  int b = map(depth, minThresh, maxThresh, 0, 150);
  ledOnRgb(r, g, b);
}

