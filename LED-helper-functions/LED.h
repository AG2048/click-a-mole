#ifndef LED_H
#define LED_H
#include <Arduino.h>
#include <FastLED.h>


/*
Assumptions for current prototype
leds/ring: 30
leds/linear: 10
leds/heart: 1

*/
#define RINGS_INDEX {0, 30, 60, 90, 120, 150, 180, 210, 240}
#define LINEARS_INDEX {270, 275, 280, 285, 290, 295, 300, 305, 310}
#define HEARTS_INDEX {315, 316, 317}
#define LEDS_PER_RING 30
#define LEDS_PER_LINEAR 5
#define LEDS_PER_HEART 1

const int rings_index[] = RINGS_INDEX;
const int linears_index[] = LINE_INDEX;
const int hearts_index[] = HEARTS_INDEX;

enum Color {
    RED,
    GREEN,
    BLUE
};

enum LED_Type {
    RING,
    LINEAR,
    HEART
};

void adjust_linear_lights(int moleIndex, Color colourMode, int clicksLeft);
void adjust_ring_lights(int moleIndex, Color colourMode, int currentTime, int maxTime);
void adjust_heart_lights(int currentLivesLeft);
void adjust_score_lights(int currentScore); 
CRGB toCRGB(Color c);
int mole_to_strip_index(int moleIndex, LED_Type ledType);


/*
Example call
Color myColor = Color::GREEN;
adjust_linear_lights(0, myColor, 3);
*/

#endif 

