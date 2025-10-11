#ifndef LED_H
#define LED_H


/*
Assumptions for current prototype
leds/ring: 30
leds/linear: 10
leds/heart: 1

*/
#define RINGS_INDEX {0, 30, 60, 90, 120, 150, 180, 210, 240}
#define LINEARS_INDEX {270, 275, 280, 285, 290, 295, 300, 305, 310}
#define HEARTS_INDEX {301, 302, 303}
#define LEDS_PER_RING 30
#define LEDS_PER_LINEAR 5
#define LEDS_PER_HEART 1

const int rings_index[] = RINGS_INDEX
const int linears_index[] = LINE_INDEX;
const int hearts_index[] = HEARTS_INDEX;

enum Color {
    RED,
    GREEN,
    BLUE
};

CRGB toCRGB(Color c) {
    
    switch (c) {
        case Color::RED: 
            return CRGB::Red;
        case Color::Greeen: 
            return CRGB(100, 200, 40);
        default: 
            return CRGB::Black; // fallback
    }
}

/*
Example call
Color myColor = Color::GREEN;
adjust_linear_lights(0, myColor, 3);
*/

void adjust_linear_lights(int moleIndex, Color colourMode, int clicksLeft);
void adjust_ring_lights(int moleIndex, Color colourMode, int currentTime, int maxTime);
void adjust_heart_lights(int currentLivesLeft);
void adjust_score_lights(int currentScore); 

#endif 

