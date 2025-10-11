#include "LED.h"
#include <Arduino.h>
#include <FastLED.h>

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