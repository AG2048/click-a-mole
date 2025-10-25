#include "led_interface.h"

void led_interface::start_mole(int mole_id, int max_hp, unsigned long duration_ms, const vector<>& colors = {Color::Green}){
    const unsigned long current_time_ms = millis();
    AnimatoinObject* new_mole_ring;
    new_mole_ring -> led_type = LedType::Ring;
    new_mole_ring -> animation_type = AnimationCategory::fade; // fading countdown starts
    new_mole_ring -> mole_id = mole_id;
    new_mole_ring -> colour_1 = Colour::Green;
    new_mole_ring -> colour_2 = Colour::Red;
    new_mole_ring -> colour_3 = Colour::Black;
    new_mole_ring -> start_time_ms = current_time_ms;
    new_mole_ring -> end_time_ms = current_time_ms + duration_ms;


    animation_list.push_back(new_mole_ring);

    AnimationObject* new_mole_linear;
    new_mole_linear -> led_type = LedType::Linear;
    new_mole_linear -> animation_type = AnimationCategory::Solid; // fading countdown starts
    new_mole_linear -> mole_id = mole_id;
    new_mole_linear -> colour_1 = Colour::Red;
    new_mole_linear -> start_time_ms = current_time_ms;
    new_mole_linear -> end_time_ms = current_time_ms + duration_ms;

    animation_list.push_back(linear);



}


int calculate_mole_led_(int mole_id){ // return the starting index of the mole leds for that mole
    // should be done at first instaed of called and saved to a variobale?
}
