#include "led_interface.h"

// *************************************
// Constructors and Destructors
// *************************************

// Constructor
DisplayInterface::DisplayInterface(
    unsigned short leds_per_ring_, 
    unsigned short leds_per_linear_, 
    unsigned short leds_per_heart_, 
    unsigned short number_of_leds_,
    unsigned short rings_data_pin_,
    unsigned short hearts_data_pin_
){
    
    // Initialize any other setup here if needed
    this->leds_per_ring = leds_per_ring_;
    this->leds_per_linear = leds_per_linear_;
    this->leds_per_heart = leds_per_heart_;
    this->number_of_leds = number_of_leds_;
    this->rings_data_pin = rings_data_pin_;
    this->hearts_data_pin = hearts_data_pin_;
    this->leds = new CRGB [number_of_leds_];


    // Note: for testing purposes, we will use a fixed data pin (4)
    // as the rings_data_pin_ must be known at compile time for addLeds<>
    // FastLED.addLeds<WS2812B, GRB>(leds, number_of_leds_, rings_data_pin_); //potential fix, provided by ChatGPT
    FastLED.addLeds<WS2812B, 4, GRB>(leds, number_of_leds_); //temporary fix
    FastLED.setBrightness(50);

    fill_solid(leds, number_of_leds_, CRGB::Black);
}

// Destructor
DisplayInterface::~DisplayInterface() {

    // delete LED indices array
    if (leds != nullptr) {
        delete[] leds;
        leds = nullptr;
    }

    remove_all_animation(); 
}





// *************************************
// Public Functions
// *************************************

// start_mole()
// Function starts the ring timer and hp bar for each mole
void DisplayInterface::start_mole(int mole_id, int max_hp, unsigned long duration_ms, const Colour colours[], int colour_count) { // vector bc for one round it may be 3 lives or 5 lives so theats like 3 vs 5 colors, its green by default but if they do pass smth then itll be what they pass

    // remove all previous mole animations,
    // which inludes any rings and linear LEDs
    remove_mole_animation(mole_id);

    Colour c1 = (colour_count > 0 ? colours[0] : Colour::Black);
    Colour c2 = (colour_count > 1 ? colours[1] : Colour::Black);
    Colour c3 = (colour_count > 2 ? colours[2] : Colour::Black);
    Colour c4 = (colour_count > 3 ? colours[3] : Colour::Black);
    Colour c5 = (colour_count > 4 ? colours[4] : Colour::Black);

    queue_animation(LedType::Ring, AnimationCategory::Solid, mole_id, duration_ms);
    queue_animation(LedType::Linear, AnimationCategory::Solid, mole_id, duration_ms, nullptr, c1, c2, c3, c4, c5);

}




// *************************************
// Helper Functions
// *************************************

// queue_animation
// Function adds an animation object to animation list
void DisplayInterface::queue_animation(
    LedType led_type,
    AnimationCategory animation_type,
    int mole_id,
    unsigned long duration_ms,
    AnimationObject* animation_to_return_to,   
    Colour colour_1,
    Colour colour_2,
    Colour colour_3,
    Colour colour_4,
    Colour colour_5
){
    // Store the time when animation functions were called
    // and create new animation object
    unsigned long current_time_ms = millis();
    AnimationObject* new_ani = new AnimationObject();

    new_ani->led_type = led_type;
    new_ani->animation_type = animation_type;
    new_ani->mole_id = mole_id;
    new_ani->start_time_ms = current_time_ms;
    new_ani->end_time_ms = current_time_ms + duration_ms;    

    new_ani->animation_to_return_to = animation_to_return_to;
    new_ani->colour_1 = colour_1;
    new_ani->colour_2 = colour_2;
    new_ani->colour_3 = colour_3;
    new_ani->colour_4 = colour_4;
    new_ani->colour_5 = colour_5;

    // Add new animation object to animation list
    animation_list.push_back(new_ani);

}

// remove_mole_animation
void DisplayInterface::remove_mole_animation(int mole_id_) {
    for (int i = animation_list.size() - 1; i >= 0; i--) {
        AnimationObject* animation = animation_list.get(i);
        if (animation->mole_id == mole_id_) {
            delete animation;
            animation_list.erase(i);
        }
    }
}

// remove_all_animation
void DisplayInterface::remove_all_animation() {

    for (int i = animation_list.size() - 1; i >= 0; i--) {
        delete animation_list.get(i);   // delete AnimationObject
    }

    animation_list.clear();
}

// convert_to_crgb
CRGB DisplayInterface::convert_to_crgb(Colour colour) {
    switch(colour) {
        case Colour::Green:  
            return CRGB::Green;
        case Colour::Orange: 
            return CRGB::Orange;
        case Colour::Yellow: 
            return CRGB::Yellow;
        case Colour::Red:    
            return CRGB::Red;
        case Colour::Blue:   
            return CRGB::Blue;
        case Colour::Black:  
            return CRGB::Black;
        default:             
            return CRGB::Black;
    }
}


// 
// int DisplayInterface::convert_mole_id_led_type_to_led_index(int mole_id, LedType led_type) {
//     int start_index = 0;

//     if (led_type == LedType::Ring) {
//         start_index = mole_id * leds_per_ring;
//     }
//     else if (led_type == LedType::Linear) {
//         start_index = leds_per_ring * 5 + mole_id * leds_per_linear; // assuming max 5 moles
//     }
//     else if (led_type == LedType::Heart) {
//         start_index = leds_per_ring * 5 + leds_per_linear * 5 + mole_id * leds_per_heart; // assuming max 5 moles
//     }

//     return start_index;
// }







