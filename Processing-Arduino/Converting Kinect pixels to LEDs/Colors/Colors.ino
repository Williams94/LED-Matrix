void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}

/*
 * Turns an LED on with the color Blue
 */
void ledOnBlue(int i) {
  // This is needed to skip the first number of LEDs
  i += LED_START;
  
//  leds[i] = CRGB::Blue;
  leds[panelNumber - 1][ledNumber] = CRGB::Blue;
  FastLED.show();
  delay(LED_DELAY);
}

/*
 * Turns an LED on with the color Green
 */
void ledOnGreen(int i) {
  i = applyLedStartingOffset(i);
  
//  leds[i] = CRGB::Green;
  leds[panelNumber - 1][ledNumber] = CRGB::Green;
  FastLED.show();
  delay(LED_DELAY);
}

/*
 * Turns an LED on with the color Red
 */
void ledOnRed(int i) {  
  i = applyLedStartingOffset(i);
  
//  leds[i] = CRGB::Red;
  leds[panelNumber - 1][ledNumber] = CRGB::Red;
  FastLED.show();
  delay(LED_DELAY);
}
