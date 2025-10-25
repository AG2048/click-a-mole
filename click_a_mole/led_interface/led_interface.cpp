#include "led_interface.h"
#include <Arduino.h>
#include <FastLED.h>


// when start mole is called
void led_interface::start_mole(int mole_id, int max_hp, unsigned long duration_ms, const vector<>& colors = {Color::Green}){ // vector bc for one round it may be 3 lives or 5 lives so theats like 3 vs 5 colors, its green by default but if they do pass smth then itll be what they pass
    const unsigned long current_time_ms = millis();
    AnimationObject* new_mole_ring;
    new_mole_ring -> led_type = LedType::Ring;
    new_mole_ring -> animation_type = AnimationCategory::Solid;
    new_mole_ring -> mole_id = mole_id;
    new_mole_ring -> colour_1 = Colour::Green;
    new_mole_ring -> start_time_ms = current_time_ms;
    new_mole_ring -> end_time_ms = current_time_ms + duration_ms;

    AnimationObject* new_mole_linear;
    new_mole_linear -> led_type = LedType::Linear;
    new_mole_linear -> animation_type = AnimationCategory::Solid;
    new_mole_linear -> mole_id = mole_id;
    new_mole_linear -> colour_1 = Colour::Red;
    new_mole_linear -> start_time_ms = current_time_ms;
    new_mole_linear -> end_time_ms = current_time_ms + duration_ms;

    animation_list.push_back(linear);
    animation_list.push_back(new_mole_ring);


}

process_animation(unsigned long overall_current_time_ms){
    // we want a millis to tell the overall current time
    // go through all animations in the animation list
    // if there is duplicat in animation for the same mole id, kick the duplicate out
    // after the duplicates are kicked out, check for the same mole id, what animations there are, if the new one that was added is start mole, then kick the other animations out
    // animations that need to be overridden: transition animation, etc.
    // insert any temporary functoins and siwtch pointers arund and keep going
        // this whole thing is similar to a linked list
    // after these are checked, call the animation functions


    // Check duplicates and deal with it
    check_duplicate_animations() // this is checking duplicate animations for the same mole id

}

void check_duplicate_animations(int animation_mole_id, vector<*AnimationObject>* animation_list){
    for (int i = 0; i < animation_list.size(); i++){
        if (animation_list[i] -> mole_id == animation_mole_id){
            // delete the animation memory properly 
        }
    }

}




int calculate_mole_led_(int mole_id){ // return the starting index of the mole leds for that mole
    // should be done at first instaed of called and saved to a variobale?
}

// start mole has top priority, when should it override other functions like the transition animation (eg. )
// when pushing: git add., git commit -m "message", git push
// change mole hp: change the hp bar nnumber and get ratio of new hp and full hop and see if ring should change or not