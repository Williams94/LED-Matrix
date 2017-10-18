#include "FastLED.h"
#include <math.h>

/*
 * Set number of LEDs and data pins here
 */
#define NUMBER_OF_LEDS 190
#define LED_DELAY 50

// For multiple LED strips
#define NUM_STRIPS 5
#define NUM_LEDS_PER_STRIP NUMBER_OF_LEDS
//CRGB leds[NUM_STRIPS][NUM_LEDS_PER_STRIP];
//CRGB leds[NUM_LEDS_PER_STRIP];
CRGB leds[1];

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
int convertedX, convertedY, convertedD;
int ledX, ledY;
int ledNumber;
int ledNumbers[300][2];
int ledNumbersIndex = 0;

int panelNumber = -1;
int ledAddress = -1;
int blobSize = 100;

String readString;

/*
 * Setup with LED Strips and Serial
 */
void setup() { 
  // One LED Strip
  FastLED.addLeds<NEOPIXEL, 6>(leds, 1);

  // Multiple LED Strips
  /*FastLED.addLeds<NEOPIXEL, 22>(leds[0], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, 26>(leds[1], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, 30>(leds[2], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, 34>(leds[3], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, 38>(leds[4], NUM_LEDS_PER_STRIP);
    
  for (int i = 0; i < NUM_LEDS_PER_STRIP; i++) {
      leds[i] = CRGB::Black;     
  }
  FastLED.show();*/
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
//      Serial.println(ledAddress);
    }
    if (readString.indexOf('p') == 0) {
      panelNumber = (readString.substring(readString.indexOf('p') + 1, readString.length())).toInt();
//      Serial.println(panelNumber);
    }
    if (readString.indexOf('d') == 0) {
      d = (readString.substring(readString.indexOf('d') + 1, readString.length())).toInt();
//      Serial.println(d);
    }   
    readString = "";

    if (panelNumber != -1 && ledAddress != -1 && d != -1) {
//      Serial.println("l" + (String)ledAddress + "p" + (String)panelNumber + "d" + (String)d);
//      turnOffAllLeds();       
      ledBlob();     
      panelNumber, ledAddress, d = -1;
    }
  }
}

/*******************************************************************************************************
 * 
 * Functions for turning LEDs on and off with different colours and coversion of depth to color temp etc.
 * 
 ******************************************************************************************************/

 void ledBlob() {
  int r = getR(d);
  int g = getG();
  int b = getB(d);  

  int mod = ledAddress % 10;

  // If it is even or odd y axis row
  if ((ledAddress / 10) % 2 == 0) {
    // Need to go to next right panel
    if (mod > 5) {
      if (panelNumber != 4) {
        turnOnLedsInNextPanelForEvenRow(mod, r, g, b);
      }
      turnOnLedsInThisPanelForEvenRowUsingNextPanel(mod, r, g, b);
    // Need to go to next left panel
    } else if (mod < 5) {
      if (panelNumber != 0) {
        turnOnLedsInPreviousPanelForEvenRow(mod, r, g, b);
      }
      turnOnLedsInThisPanelForEvenRowUsingPreviousPanel(mod, r, g, b);
    } else if (mod == 5) {
      turnOnLedsInThisPanelForMiddleValue(mod, r, g, b);
    }
  } else if ((ledAddress / 10) % 2 != 0) {
    // Need to go to next left panel
    if (mod > 5) {
      if (panelNumber != 0) {
        
      }
    // Need to go to next right panel
    } else if (mod < 5) {      
      if (panelNumber != 4) {             
        turnOnLedsInNextPanelForOddRow(mod, r, g, b);
      }
      turnOnLedsInThisPanelForOddRow(mod, r, g, b);
    } else if (mod == 5) {
      
    }
  }
 }

/***************************************************************************
 ************************** Even Rows *************************************
 **************************************************************************/

void turnOnLedsInPreviousPanelForEvenRow(int mod, int r, int g, int b) {
  int previousPanelStartLed = (ledAddress + (10 - mod));
  int count = 0;

  Serial.println("p" + (String)(panelNumber - 1));
  
  for (int i = previousPanelStartLed; count < (5 - mod); i++) {
    Serial.println(i);
//    leds[panelNumber - 1][i].setRGB(r, g, b);
    count++;
  }
  count = 0;
  for (int i = previousPanelStartLed; count < (5 - mod); i--) {   
    Serial.println(i);
//    leds[panelNumber - 1][i].setRGB(r, g, b);
    count++;
  }

  if ((previousPanelStartLed + 20) < NUMBER_OF_LEDS) {    
    previousPanelStartLed = (previousPanelStartLed + 20);
    count = 0;
    for (int i = previousPanelStartLed; count < (5 - mod); i++) {     
      Serial.println(i);
  //    leds[panelNumber - 1][i].setRGB(r, g, b);
      count++;
    }
    count = 0;
    for (int i = previousPanelStartLed; count < (5 - mod); i--) {         
      Serial.println(i);
  //    leds[panelNumber - 1][i].setRGB(r, g, b);
      count++;
    }
  }

  if ((ledAddress - 20) > 0) {
    previousPanelStartLed = ((ledAddress + (10 - mod)) - 20);
    count = 0;
    for (int i = previousPanelStartLed; count < (5 - mod); i++) {
      Serial.println(i);
  //    leds[panelNumber - 1][i].setRGB(r, g, b);     
      count++;
    }
    count = 0;
    for (int i = previousPanelStartLed; count < (5 - mod); i--) {   
      if (i > 0) {  
        Serial.println(i);
  //    leds[panelNumber - 1][i].setRGB(r, g, b);
      }
      count++;
    }
  }
}

void turnOnLedsInNextPanelForEvenRow(int mod, int r, int g, int b) {
  int nextPanelStartLed = (ledAddress - mod) + 1;
  int count = 0;

  Serial.println("p" + (String)(panelNumber + 1));
  
  for (int i = nextPanelStartLed; count <= (mod - 5); i++) {
    Serial.println(i);
//    leds[panelNumber + 1][i].setRGB(r, g, b);
    count++;
  }
  count = 0;
  for (int i = nextPanelStartLed; count < (mod - 5); i--) {   
    Serial.println(i);
//    leds[panelNumber + 1][i].setRGB(r, g, b);
    count++;
  }
    
  nextPanelStartLed = (((10 - mod) + ledAddress) + 10);
  count = 0;
  for (int i = nextPanelStartLed; count <= (mod - 5); i++) {
    Serial.println(i);
//    leds[panelNumber + 1][i].setRGB(r, g, b);
    count++;
  }
  count = 0;
  for (int i = nextPanelStartLed; count < (mod - 5); i--) {   
    Serial.println(i);
//    leds[panelNumber + 1][i].setRGB(r, g, b);
    count++;
  }

  nextPanelStartLed = (((10 - mod) + ledAddress) - 10);
  count = 0;
  for (int i = nextPanelStartLed; count <= (mod - 5); i++) {
    Serial.println(i);
//    leds[panelNumber + 1][i].setRGB(r, g, b);
    count++;
  }
  count = 0;
  for (int i = nextPanelStartLed; count < (mod - 5); i--) {   
    Serial.println(i);
//    leds[panelNumber + 1][i].setRGB(r, g, b);
    count++;
  }
}

void turnOnLedsInThisPanelForEvenRowUsingNextPanel(int mod, int r, int g, int b) {
  int thisPanelsStartLed = ledAddress;
  int count = 0;

  Serial.println("p" + (String)panelNumber);

  Serial.println("m" + (String)mod);
  Serial.println("l" + (String)thisPanelsStartLed);
  
  for (int i = thisPanelsStartLed; count < ((10 - mod) + 3); i++) {  
    Serial.println(i);  
//    leds[panelNumber][i].setRGB(r, g, b);
    count++;
  }
  count = 0;
  for (int i = thisPanelsStartLed; count < (10 - mod); i--) {
    Serial.println(i);
//    leds[panelNumber][i].setRGB(r, g, b);
    count++;
  }
  
  thisPanelsStartLed = ((ledAddress) + 20);
  count = 0;
  for (int i = thisPanelsStartLed; count < ((10 - mod) + 1); i++) {
    Serial.println(i);
//    leds[panelNumber][i].setRGB(r, g, b);
    count++;
  }
  count = 0;
  for (int i = thisPanelsStartLed; count < (10 - mod); i--) {    
    Serial.println(i);
//    leds[panelNumber][i].setRGB(r, g, b);
    count++;
  }

  thisPanelsStartLed = ((ledAddress) - 20);
  count = 0;
  for (int i = thisPanelsStartLed; count < ((10 - mod) + 3); i++) {
    Serial.println(i);
//    leds[panelNumber][i].setRGB(r, g, b);
    count++;
  }
  count = 0;
  for (int i = thisPanelsStartLed; count < (10 - mod); i--) {    
    Serial.println(i);
//    leds[panelNumber][i].setRGB(r, g, b);
    count++;
  }
}

void turnOnLedsInThisPanelForEvenRowUsingPreviousPanel(int mod, int r, int g, int b) {
  int thisPanelsStartLed = ledAddress;
  int count = 0;

  Serial.println("p" + (String)panelNumber);

  Serial.println("m" + (String)mod);
  Serial.println("l" + (String)thisPanelsStartLed);
  
  for (int i = thisPanelsStartLed; count < (mod - 1); i++) {  
    Serial.println(i);  
//    leds[panelNumber][i].setRGB(r, g, b);
    count++;
  }
  count = 0;
  for (int i = thisPanelsStartLed; count < (mod * 2); i--) {
    Serial.println(i);
//    leds[panelNumber][i].setRGB(r, g, b);
    count++;
  }
  
  thisPanelsStartLed = ((ledAddress) + 20);
  count = 0;
  for (int i = thisPanelsStartLed; count < (mod - 1); i++) {
    Serial.println(i);
//    leds[panelNumber][i].setRGB(r, g, b);
    count++;
  }
  count = 0;
  for (int i = thisPanelsStartLed; count < (mod * 2); i--) {    
    Serial.println(i);
//    leds[panelNumber][i].setRGB(r, g, b);
    count++;
  }

  thisPanelsStartLed = ((ledAddress) - 20);
  count = 0;
  for (int i = thisPanelsStartLed; count < (mod - 1); i++) {
    Serial.println(i);
//    leds[panelNumber][i].setRGB(r, g, b);
    count++;
  }
  count = 0;
  for (int i = thisPanelsStartLed; count < (mod * 2); i--) {    
    Serial.println(i);
//    leds[panelNumber][i].setRGB(r, g, b);
    count++;
  }
}

void turnOnLedsInThisPanelForMiddleValue(int mod, int r, int g, int b) {
  int thisPanelsStartLed = ledAddress - 25;
  int thisPanelsEndLed = ledAddress + 25;
  int count = 0;

  Serial.println("p" + (String)panelNumber);

  Serial.println("m" + (String)mod);
  Serial.println("l" + (String)thisPanelsStartLed);

  for (int i = thisPanelsStartLed; i < (thisPanelsEndLed + 1); i++) {  
    if (i < NUMBER_OF_LEDS && i > 0) {
      Serial.println(i);
//      leds[panelNumber][i].setRGB(r, g, b);
    }
  }

  /*
  for (int i = thisPanelsStartLed; count < 6; i++) {  
    Serial.println(i);  
//    leds[panelNumber][i].setRGB(r, g, b);
    count++;
  }
  count = 0;
  for (int i = thisPanelsStartLed; count < 5; i--) {
    Serial.println(i);
//    leds[panelNumber][i].setRGB(r, g, b);
    count++;
  }
  
  thisPanelsStartLed = ((ledAddress) + 10);
  count = 0;
  for (int i = thisPanelsStartLed; count < 6; i++) {
    Serial.println(i);
//    leds[panelNumber][i].setRGB(r, g, b);
    count++;
  }
  count = 0;
  for (int i = thisPanelsStartLed; count < 5; i--) {    
    Serial.println(i);
//    leds[panelNumber][i].setRGB(r, g, b);
    count++;
  }

  thisPanelsStartLed = ((ledAddress) - 10);
  count = 0;
  for (int i = thisPanelsStartLed; count < 6; i++) {
    Serial.println(i);
//    leds[panelNumber][i].setRGB(r, g, b);
    count++;
  }
  count = 0;
  for (int i = thisPanelsStartLed; count < 5; i--) {    
    Serial.println(i);
//    leds[panelNumber][i].setRGB(r, g, b);
    count++;
  }*/
}

/*******************************************************************
 ************************** Odd Rows ******************************
 *****************************************************************/

void turnOnLedsInNextPanelForOddRow(int mod, int r, int g, int b) {
  int nextPanelStartLed = ((10 - mod) + ledAddress);
  int count = 0;

  Serial.println("p" + (String)(panelNumber + 1));
  
  for (int i = nextPanelStartLed; count <= (5 - mod); i++) {
    Serial.println(i);
//    leds[panelNumber + 1][i].setRGB(r, g, b);
    count++;
  }
  count = 0;
  for (int i = nextPanelStartLed; count < (5 - mod); i--) {   
    Serial.println(i);
//    leds[panelNumber + 1][i].setRGB(r, g, b);
    count++;
  }
    
  nextPanelStartLed = (((10 - mod) + ledAddress) + 20);
  count = 0;
  for (int i = nextPanelStartLed; count <= (5 - mod); i++) {
    Serial.println(i);
//    leds[panelNumber + 1][i].setRGB(r, g, b);
    count++;
  }
  count = 0;
  for (int i = nextPanelStartLed; count < (5 - mod); i--) {   
    Serial.println(i);
//    leds[panelNumber + 1][i].setRGB(r, g, b);
    count++;
  }

  nextPanelStartLed = (((10 - mod) + ledAddress) - 20);
  count = 0;
  for (int i = nextPanelStartLed; count <= (5 - mod); i++) {
    Serial.println(i);
//    leds[panelNumber + 1][i].setRGB(r, g, b);
    count++;
  }
  count = 0;
  for (int i = nextPanelStartLed; count < (5 - mod); i--) {   
    Serial.println(i);
//    leds[panelNumber + 1][i].setRGB(r, g, b);
    count++;
  }
}

void turnOnLedsInThisPanelForOddRow(int mod, int r, int g, int b) {
  int thisPanelsStartLed = ledAddress;
  int count = 0;

  Serial.println("p" + (String)panelNumber);
  
  for (int i = thisPanelsStartLed; count < (mod - 1); i++) {  
    Serial.println(i);  
//    leds[panelNumber][i].setRGB(r, g, b);
    count++;
  }
  count = 0;
  for (int i = thisPanelsStartLed; count < (mod * 2); i--) {
    Serial.println(i);
//    leds[panelNumber][i].setRGB(r, g, b);
    count++;
  }
  
  thisPanelsStartLed = ((ledAddress) + 20);
  count = 0;
  for (int i = thisPanelsStartLed; count < (mod - 1); i++) {
    Serial.println(i);
//    leds[panelNumber][i].setRGB(r, g, b);
    count++;
  }
  count = 0;
  for (int i = thisPanelsStartLed; count < (mod * 2); i--) {    
    Serial.println(i);
//    leds[panelNumber][i].setRGB(r, g, b);
    count++;
  }

  thisPanelsStartLed = ((ledAddress) - 20);
  count = 0;
  for (int i = thisPanelsStartLed; count < (mod - 1); i++) {
    Serial.println(i);
//    leds[panelNumber][i].setRGB(r, g, b);
    count++;
  }
  count = 0;
  for (int i = thisPanelsStartLed; count < (mod * 2); i--) {    
    Serial.println(i);
//    leds[panelNumber][i].setRGB(r, g, b);
    count++;
  }
}

void turnOffLeds() {
//  fill_solid(leds[0], NUMBER_OF_LEDS, CRGB::Black);
//  fill_solid(leds[1], NUMBER_OF_LEDS, CRGB::Black);
//  fill_solid(leds[2], NUMBER_OF_LEDS, CRGB::Black);
//  fill_solid(leds[3], NUMBER_OF_LEDS, CRGB::Black);
//  fill_solid(leds[4], NUMBER_OF_LEDS, CRGB::Black);
}

 int getR(int depth) {
  return map(depth, maxThresh, minThresh, 50, 255);
 }

 int getG() {
  return 50;
 }

 int getB(int depth) {
  return map(depth, minThresh, maxThresh, 0, 150);
 }

/*
 * Turns an LED off
 */
void ledOff(int i, int panelNumber) {
//  leds[panelNumber][ledNumber] = CRGB::Black;
  FastLED.show();
  delay(LED_DELAY);  
}

/*
 * Turns an LED on with the color Red
 */
void ledOnRgb(int r, int g, int b, int panel, int led) {  
//  leds[panel][led].setRGB(r, g, b);
}

/*
 * Converts depth to rgb and turns on led with that color
 */
void convertDepthToRgbAndTurnOnLed(int depth, int panel, int led) {
  // red is depth mapped from low to high e.g. closer = redder
  int r = map(depth, maxThresh, minThresh, 50, 255);

  // green can be used if needed
//  int g = map(depth, minThresh, maxThresh, 0, 255);
  int g = 50;

  // red is depth mapped from high to low e.g. further away = bluer
  int b = map(depth, minThresh, maxThresh, 0, 150);
  ledOnRgb(r, g, b, panel, led);
}


