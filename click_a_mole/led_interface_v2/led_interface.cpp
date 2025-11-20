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

    queue_animation(LedType::Ring, AnimationCategory::Timer, mole_id, duration_ms, max_hp, max_hp);
    queue_animation(LedType::Linear, AnimationCategory::Solid, mole_id, duration_ms, max_hp, max_hp, nullptr, c1, c2, c3, c4, c5);

}

// Function decreases hp bar for each mole and plays a flash animation
// on the ring timer to reflect that the mole was pressed,
// immediately returns to timer animation after flash animation is done
// NOTE: The timer doesn't pause during flash animation
void DisplayInterface::change_mole_hp(int mole_id, int new_hp, int max_hp){

    // should show 200 ms intermediate flash for RING
    // HP bar should just decrease

    for (int i = animation_list.size() - 1; i >= 0 ; i--){

        AnimationObject* animation = animation_list.get(i);

        // hp bar
        if(animation->mole_id == mole_id && animation->led_type == LedType::Linear){
            animation->current_hp = new_hp;
        }

        // remove timer animation
        // guarantees that animation->animation_to_return_to == nullptr

        // REVIEW LOGIC
        if(animation->mole_id == mole_id && animation->animation_type == AnimationCategory::Timer){
            animation->current_hp = new_hp;
            
            // for safety
            // delete animation->animation_to_return_to; 
            // animation->animation_to_return_to = nullptr; 

            // copy contents of timer animation 
            // to the future timer animation, which will be 
            // eventually added back to linked list
            // Note: return_to_timer_animation preserves the start_time and end_time 
            AnimationObject* return_to_timer_animation = new AnimationObject(); 
            *return_to_timer_animation = *animation; 
            

            render_colour_to_led(animation, Colour::Black); // may be redundant, as the new queued animation will change leds to blue
            delete animation;
            animation_list.erase(i);

            // queue the new flash animation
            queue_animation(LedType::Ring, AnimationCategory::Solid, mole_id, 200, 0, 0, return_to_timer_animation, Colour::Blue);

        }

    }

} 


// Function removes all mole animations
// and plays round win animation for 2001m (divisble by 3), then sets all mole leds to black
void DisplayInterface::win_round(){
    for(int i = 1; i <= total_moles; i++){
        remove_mole_animation(i);
    }

    AnimationObject* firstRow = queue_animation(LedType::Ring, AnimationCategory::Solid, 1, 667, -1, -1, nullptr, Colour::Green);
    queue_animation(LedType::Ring, AnimationCategory::Solid, 2, 667, -1, -1, nullptr, Colour::Green);
    queue_animation(LedType::Ring, AnimationCategory::Solid, 3, 667, -1, -1, nullptr, Colour::Green);
    queue_animation(LedType::Ring, AnimationCategory::Solid, 4, 667, -1, -1, nullptr, Colour::Green);

    AnimationObject* secondRow = queue_future_animation(LedType::Ring, AnimationCategory::Solid, 5, firstRow->end_time_ms, 667, -1, -1, nullptr, Colour::Green);
    queue_future_animation(LedType::Ring, AnimationCategory::Solid, 6, firstRow->end_time_ms, 667, -1, -1, nullptr, Colour::Green);
    queue_future_animation(LedType::Ring, AnimationCategory::Solid, 7, firstRow->end_time_ms, 667, -1, -1, nullptr, Colour::Green);

    queue_future_animation(LedType::Ring, AnimationCategory::Solid, 8, secondRow->end_time_ms, 667, -1, -1, nullptr, Colour::Green);
    queue_future_animation(LedType::Ring, AnimationCategory::Solid, 9, secondRow->end_time_ms, 667, -1, -1, nullptr, Colour::Green);

}

void DisplayInterface::end_mole(int mole_id, bool is_timeout, bool is_hp_zero){
    
    remove_mole_animation(mole_id);

    if (is_timeout){
        queue_animation(LedType::Ring, AnimationCategory::Blinking, mole_id, 200, Colour::Red);
        queue_animation(LedType::Linear, AnimationCategory::Blinking, mole_id, 200);
    } else if (is_hp_zero){
        queue_animation(LedType::Ring, AnimationCategory::Blinking, mole_id, 200, Colour::Green);
        queue_animation(LedType::Linear, AnimationCategory::Blinking, mole_id, 200);
    }
}

void DisplayInterface::lose_round(){
    for(int i = 1; i <= total_moles; i++){
        remove_mole_animation(i);
    }

    AnimationObject* firstRow = queue_animation(LedType::Ring, AnimationCategory::Solid, 1, 667, -1, -1, nullptr, Colour::Green);
    queue_animation(LedType::Ring, AnimationCategory::Solid, 2, 667, -1, -1, nullptr, Colour::Red);
    queue_animation(LedType::Ring, AnimationCategory::Solid, 3, 667, -1, -1, nullptr, Colour::Red);
    queue_animation(LedType::Ring, AnimationCategory::Solid, 4, 667, -1, -1, nullptr, Colour::Red);

    AnimationObject* secondRow = queue_future_animation(LedType::Ring, AnimationCategory::Solid, 5, firstRow->end_time_ms, 667, -1, -1, nullptr, Colour::Green);
    queue_future_animation(LedType::Ring, AnimationCategory::Solid, 6, firstRow->end_time_ms, 667, -1, -1, nullptr, Colour::Red);
    queue_future_animation(LedType::Ring, AnimationCategory::Solid, 7, firstRow->end_time_ms, 667, -1, -1, nullptr, Colour::Red);

    queue_future_animation(LedType::Ring, AnimationCategory::Solid, 8, secondRow->end_time_ms, 667, -1, -1, nullptr, Colour::Red);
    queue_future_animation(LedType::Ring, AnimationCategory::Solid, 9, secondRow->end_time_ms, 667, -1, -1, nullptr, Colour::Red);

}

void DisplayInterface::update_heart(int lives){
    int heartIndex = convert_led_type_to_led_index(LedType::Heart, -1);
    int heartOnLeds = lives * leds_per_heart;

    // Turn heart leds on
    for (int i = heartIndex; i < heartIndex + heartOnLeds; i++){
        leds[i] = CRGB::Red;
    }

    // Turn off excess heart leds
    for (int i = heartIndex + heartOnLeds; i < heartIndex + (3 * leds_per_heart); i++){
        leds[i] = CRGB::Black;
    }

    FastLED.show();

}

// Function modifies the led buffer based on system time
void DisplayInterface::process_timed_animations(unsigned long current_time_ms){

    for (int i = animation_list.size() - 1; i >= 0 ; i--){

        AnimationObject* animation = animation_list.get(i);
        // int ani_mole_id = animation->mole_id;
    
        if (animation->end_time_ms <= current_time_ms){ // check if animation is done
            
            render_colour_to_led(animation, Colour::Black);

            // also check if there is animation to return to, if yes, push_back to list
            // If animation->animation_to_return_to != nullptr, we push it back into the list.
            // Important: delete animation only deletes the AnimationObject itself.
            // It does NOT delete animation->animation_to_return_to.
            // Ownership of that pointer now belongs to the animation list.

            // REVIEW LOGIC
            if(animation->animation_to_return_to != nullptr){
                AnimationObject* next = animation->animation_to_return_to;
                animation->animation_to_return_to = nullptr;

                animation_list.push_back(next); 
                
                render_animation(next, current_time_ms); //render animation only if 
            }  

            delete animation; 
            animation_list.erase(i);
        }else{
            render_animation(animation, current_time_ms);
        }
    }

    FastLED.show();

}






// *************************************
// Helper Functions
// *************************************

// Function adds an animation object to animation list
AnimationObject* DisplayInterface::queue_animation(
    LedType led_type,
    AnimationCategory animation_type,
    int mole_id,
    unsigned long duration_ms,
    unsigned short current_hp,
    unsigned short max_hp, 
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

    new_ani->current_hp = current_hp;
    new_ani->max_hp = max_hp;
    new_ani->animation_to_return_to = animation_to_return_to;
    new_ani->colour_1 = colour_1;
    new_ani->colour_2 = colour_2;
    new_ani->colour_3 = colour_3;
    new_ani->colour_4 = colour_4;
    new_ani->colour_5 = colour_5;

    // Add new animation object to animation list
    animation_list.push_back(new_ani);

    return new_ani;

}

AnimationObject* DisplayInterface::queue_future_animation(
    LedType led_type,
    AnimationCategory animation_type,
    int mole_id,
    unsigned long start_time_ms,
    unsigned long duration_ms,
    unsigned short current_hp,
    unsigned short max_hp, 
    AnimationObject* animation_to_return_to, 
    Colour colour_1,
    Colour colour_2,
    Colour colour_3,
    Colour colour_4,
    Colour colour_5
){
    // Store the time when animation functions were called
    // and create new animation object

    AnimationObject* new_ani = new AnimationObject();

    new_ani->led_type = led_type;
    new_ani->animation_type = animation_type;
    new_ani->mole_id = mole_id;
    new_ani->start_time_ms = start_time_ms;
    new_ani->end_time_ms = start_time_ms + duration_ms;    

    new_ani->current_hp = current_hp;
    new_ani->max_hp = max_hp;
    new_ani->animation_to_return_to = animation_to_return_to;
    new_ani->colour_1 = colour_1;
    new_ani->colour_2 = colour_2;
    new_ani->colour_3 = colour_3;
    new_ani->colour_4 = colour_4;
    new_ani->colour_5 = colour_5;

    // Add new animation object to animation list
    animation_list.push_back(new_ani);

    return new_ani;

}

// Function removes all ring and linear led animations for a mole
void DisplayInterface::remove_mole_animation(int mole_id_) {

    for (int i = animation_list.size() - 1; i >= 0; i--) {
        AnimationObject* animation = animation_list.get(i);
        if (animation->mole_id == mole_id_) {
            render_colour_to_led(animation, Colour::Black);
            delete animation;
            animation_list.erase(i);
        }
    }
}

// Function removes all animations from animation_list
void DisplayInterface::remove_all_animation() {

    for (int i = animation_list.size() - 1; i >= 0; i--) {
        delete animation_list.get(i);   // delete AnimationObject
    }

    animation_list.clear();
}

// Function converts user-enumerated Colour
// to FastLED enumerated CRGB
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

// Functions returns the starting led index for an led type
// at a specific mole id
int DisplayInterface::convert_led_type_to_led_index(LedType led_type, int mole_id) {

    // assumes rings, linears, then hearts are wired in series
    // eg. ring1, ..., ring9, linear1,..., linear9, heart1, heart2, heart3
    // mole ids vary from 1-9
    switch(led_type){
        case LedType::Ring:
            return (mole_id - 1) * leds_per_ring;
        case LedType::Linear:
            return (total_moles * leds_per_ring) + (mole_id - 1) * leds_per_linear;
        case LedType::Heart:
            return (total_moles * leds_per_ring) + (total_moles * leds_per_linear); 
        default:
            break;
    }

}



// *************************************
// Rendering Animations Helper Functions
// *************************************

// Function renders a colour to an animation's 
// type of led at a specific mole id
void DisplayInterface::render_colour_to_led(AnimationObject* animation, Colour colour_){

    int leds_per_led_type;

    switch(animation->led_type){
        case LedType::Ring:
            leds_per_led_type = leds_per_ring;
            break;
        case LedType::Linear:
            leds_per_led_type = leds_per_linear;
            break;
        case LedType::Heart:
            leds_per_led_type = leds_per_heart;
            break;
    }

    int start_index = convert_led_type_to_led_index(animation->led_type, animation->mole_id);
    CRGB colour = convert_to_crgb(colour_);

    for (int i = start_index; i < start_index + leds_per_led_type; i++){
        leds[i] = colour;
    }
}

// Function is reponsible for processing the logic to advance
// leds in the led buffer using animation_list
void DisplayInterface::render_animation(AnimationObject* animation, unsigned long current_time_ms){

    //for round transition animations, we may queue one row 
    //pattern to occur after the next; in doing so, some animations' start time
    //will be in the future
    if(animation->start_time_ms > current_time_ms){
        return;
    }

    AnimationCategory animation_type = animation->animation_type;

    if(animation_type == AnimationCategory::Timer){
        // POSSIBLE ISSUES
        // 1.   depending on how the leds are wired,
        //      code must be modified so that each ring timer
        //      unwinds in a CCW fashion
        //      FOR NOW, go with random unwinding direction
        //      and just set leds to Colour::Black as time goes on
        //
        // 2.   concern is that leds may turn off like 1 turns off, 
        //      then 2 turn off, as processtimedanimations may have 
        //      inconsistenecies during when it is called, as other 
        //      background proccces may happen,


        // FIRST, fill all leds to a certain colour to reflect hp stage 
        double remaining_hp_fraction = static_cast<float>(animation->current_hp) / static_cast<float>(animation->max_hp);
        int remaining_hp_percentage = round(remaining_hp_fraction * 100.0);

        if(remaining_hp_percentage <= 100 && remaining_hp_percentage >= 70){
            render_colour_to_led(animation, Colour::Green);
        }else if(remaining_hp_percentage <= 69 && remaining_hp_percentage >= 30){
            render_colour_to_led(animation, Colour::Orange);
        }else if(remaining_hp_percentage <= 29 && remaining_hp_percentage >= 0){
            render_colour_to_led(animation, Colour::Red);

        }

        // SECOND: linearly set fraction of ring LEDs to Black as time goes on
        unsigned long timer_current_time = current_time_ms - animation->start_time_ms;
        unsigned long timer_total_time = animation->end_time_ms - animation->start_time_ms;

        // Clamp timer_current_time so no divide-by-zero
        if (timer_current_time > timer_total_time) {
            timer_current_time = timer_total_time;
        }

        // Fraction of time that has passed (0.0 → 1.0)
        float fraction_elapsed = (float)timer_current_time / (float)timer_total_time;

        // Number of LEDs to turn OFF (0 → leds_per_ring)
        int leds_to_turn_off = round(fraction_elapsed * leds_per_ring);

        int start_led_index = convert_led_type_to_led_index(animation->led_type, animation->mole_id);
        int end_led_index  = start_led_index + leds_per_ring - 1;

        // Turn OFF LEDs starting from the LAST LED backward
        for (int i = 0; i < leds_to_turn_off; i++) {
            int led_index = end_led_index - i;
            leds[led_index] = CRGB::Black;
        }

    }else if(animation_type == AnimationCategory::Solid){

        if (animation->led_type == LedType::Linear) {

            int start_led_index = convert_led_type_to_led_index(animation->led_type, animation->mole_id);
            Colour arr_of_colours[] = {
                animation->colour_1,
                animation->colour_2,
                animation->colour_3,
                animation->colour_4,
                animation->colour_5
            };

            int hp = animation->current_hp;
            int maxhp = animation->max_hp;

            // 1. Draw LEDs for remaining HP
            for (int i = 0; i < hp; i++) {
                leds[start_led_index + i] = convert_to_crgb(arr_of_colours[i]);
            }

            // 2. Turn off LEDs for lost HP
            for (int i = hp; i < maxhp; i++) {
                leds[start_led_index + i] = CRGB::Black;
            }
        }else if(animation->led_type == LedType::Ring){
            render_colour_to_led(animation, animation->colour_1);
        }

    }else if(animation_type == AnimationCategory::Blinking){
    }else if(animation_type == AnimationCategory::Wave){
    }
}



