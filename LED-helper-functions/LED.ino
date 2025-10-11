#include <FastLED.h>
#include "LED.h"
#define DATA_PIN 6
#define NUM_LEDS 318

CRGB leds[NUM_LEDS];
 
void setup() { 
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(50);
  Serial.begin(9600);
}
 
void loop() {
    /*

    Note
    always write FastLED.show() to flash info to actual LED strip

    Useful Functions
    fill_solid (struct CRGB *targetArray, int numToFill, const struct CRGB &color) 
    // note: we should create our own fill helper  with prototype
    // void fill(int index, int n, int colour_1, int colour_2, int colour_3)
    // allows us to fill starting from specific indicies of LED strip 

    Example usage
    Setting led to a predefined colour in library
    leds[i] = CRGB::Red; 
    leds[j] = CRGB::Black; //turns off LED 
    FastLED.show(); 
    delay(30);
    
    Setting led to a specific custom colour
    leds[i] = CRGB(colour_1, colour_2, colour_3);
    FastLED.show(); 
    delay(30);

    Fill a range of LEDs to specific colour
    fill_solid(leds, NUM_LEDS, CRGB(100,20,50));

    */
}