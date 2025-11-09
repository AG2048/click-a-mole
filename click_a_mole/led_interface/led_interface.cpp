#include "led_interface.h"
#include <Arduino.h>
#include <FastLED.h>
#include <crgb.h>


const int TOTAL_MOLES = 9;


// declare other helper functions
void render_animation(AnimationObject* animation_, unsigned long current_time_ms_);
void render_solid_ani(AnimationObject* animation_);
void render_blinking_ani(AnimationObject* animation_);
void render_wave_ani(AnimationObject* animation_);
void remove_mole_animation(int mole_id_);
void remove_all_animation();
void queue_Animation(
    LedType led_type,
    AnimationCategory animation_type,
    int mole_id,
    unsigned long duration_ms,
    AnimationObject* animation_to_return_to,
    Colour colour_1,  
    Colour colour_2 = Colour::Black,
    Colour colour_3 = Colour::Black
)

CRGB convert_to_crgb(Colour color)


AnimationObject* find_mole_animation(int mole_id_, LedType led_type);


// *************************************
// Actual Animations
// *************************************


// when start mole is called
void DisplayInterface::start_mole(int mole_id, int max_hp, unsigned long duration_ms, const vector<>& colors = {Color::Green}){ // vector bc for one round it may be 3 lives or 5 lives so theats like 3 vs 5 colors, its green by default but if they do pass smth then itll be what they pass
    // remove current animation if there is any
    unsigned long = millis(); // any other way to get curerent time? or just get it passed

    remove_mole_animation(mole_id);

    AnimationObject* new_mole_ring = new AnimationObject();
    new_mole_ring -> led_type = LedType::Ring;
    new_mole_ring -> animation_type = AnimationCategory::Solid;
    new_mole_ring -> mole_id = mole_id;
    new_mole_ring -> colour_1 = Colour::Green;
    new_mole_ring -> start_time_ms = millis() + duration_ms;
    new_mole_ring -> end_time_ms = current_time_ms + duration_ms;

    AnimationObject* new_mole_linear= new AnimationObject();
    new_mole_linear -> led_type = LedType::Linear;
    new_mole_linear -> animation_type = AnimationCategory::Solid;
    new_mole_linear -> mole_id = mole_id;
    new_mole_linear -> colour_1 = colors[0]; // number of led that lights up depend on vecotr and hp
    new_mole_linear -> start_time_ms = current_time_ms;
    new_mole_linear -> end_time_ms = current_time_ms + duration_ms;

    animation_list.push_back(new_mole_ring);
    animation_list.push_back(new_mole_linear);

    // queue animation for queueing animation
}

void DisplayInterface::process_timed_animations(unsigned long current_time_ms){

    // we want a millis to tell the overall current time
    // go through all animations in the animation list
    // if there is duplicat in animation for the same mole id, kick the duplicate out
    // after the duplicates are kicked out, check for the same mole id, what animations there are, if the new one that was added is start mole, then kick the other animations out
    // animations that need to be overridden: transition animation, etc.
    // insert any temporary functoins and siwtch pointers arund and keep going
        // this whole thing is similar to a linked list
    // after these are checked, call the animation functions

    for (int i = animation_list.size() - 1; i >= 0 ; i--){
        AnimationObject* animation = animation_list[i];

        if (animation -> end_time_ms <= current_time_ms){ // check if animation is done
            delete animation;
            animation_list.erase(animation_list.begin() + i);
            
        } 

        render_animation(animation, current_time_ms);
    }

    // Check duplicates and deal with it
    // check_duplicate_animations(animation_list); // this is checking duplicate mole id // new should always overwrite old? uhhhh illl see whats going onw this later

    

}

void render_animation(AnimationObject* animation_, unsigned long current_time_ms_){
    if (animation_->animation_type == AnimationCategory::Solid){
        render_solid_ani(animation_, current_time_ms_); //implement later // pass in current time? for decraseing the leds as the time goes on

    } else if (animation_->animation_type == AnimationCategory::Blinking){
        render_blinking_ani(animation_);

    } else if (animation_->animation_type == AnimationCategory::Wave){
        render_wave_ani(animation_);
    }
}


void DisplayInterface::change_mole_hp(int mole_id, int new_hp, int max_hp){
    
}

void DisplayInterface::end_mole(int mole_id, bool is_timeout, bool is_hp_zero){
    unsigned long current_time_ms = millis();
    // find the mole
    AnimationObject* ring_animation = find_mole_animation(mole_id, LedType::Ring);
    AnimationObject* linear_animation = find_mole_animation(mole_id, LedType::Linear);

    if (ring_animation == nullptr || linear_animation == nullptr){ // mole not found
        return;
    }

    remove_mole_animation(mole_id); // maybe separate

    // ring animation
    AnimationObject* timeout_ring_ani = new AnimationObject();
    timeout_ring_ani -> led_type = LedType::Ring;
    timeout_ring_ani -> mole_id = mole_id;
    timeout_ring_ani -> start_time_ms = millis() + duration_ms; // whats duration?
    timeout_ring_ani -> end_time_ms = current_time_ms + duration_ms;
    
    // linear animation
    AnimationObject* timeout_linear_ani = new AnimationObject();
    timeout_linear_ani -> led_type = LedType::Linear;
    timeout_linear_ani -> mole_id = mole_id;
    timeout_linear_ani -> start_time_ms = millis() + duration_ms; // whats duration?
    timeout_linear_ani -> end_time_ms = current_time_ms + duration_ms;

    // play animation if time out
    if (is_timeout){
        timeout_ring_ani -> animation_type = AnimationCategory::Blinking;
        timeout_ring_ani -> colour_1 = Colour::Red;

        // linear
        timeout_linear_ani -> animation_type = AnimationCategory::Blinking;
        timeout_linear_ani -> colour_1 = Colour::Red;


    } else if (is_hp_zero){  // play animation if hp becomes 0
        timeout_ring_ani -> animation_type = AnimationCategory::Blinking;
        timeout_ring_ani -> colour_1 = Colour::Green;

        // linear
        timeout_linear_ani -> animation_type = AnimationCategory::Blinking;
        timeout_linear_ani -> colour_1 = Colour::Green;
    }

    animation_list.push_back(timeout_ring_ani);
    animation_list.push_back(timeout_linear_ani);

}

void DisplayInterface::win_round(){
    // delete all animations
    remove_all_animation();

    // every ring play the same thing
    for (int i = 0; i < TOTAL_MOLES; i++){
        AnimationObject* new_mole_ring = new AnimationObject();
        new_mole_ring -> led_type = LedType::Ring;
        new_mole_ring -> animation_type = AnimationCategory::Wave;
        new_mole_ring -> mole_id = i;
        new_mole_ring -> colour_1 = Colour::Green;
        new_mole_ring -> start_time_ms = millis() + duration_ms; // duration??
        new_mole_ring -> end_time_ms = millis() + duration_ms;

        // every linear play the same
        AnimationObject* new_mole_ring = new AnimationObject();
        new_mole_ring -> led_type = LedType::Linear;
        new_mole_ring -> animation_type = AnimationCategory::Wave;
        new_mole_ring -> mole_id = i;
        new_mole_ring -> colour_1 = Colour::Green;
        new_mole_ring -> start_time_ms = millis() + duration_ms; // duration??
        new_mole_ring -> end_time_ms = millis() + duration_ms;
    }
}

void DisplayInterface::lose_round(){
        // delete all animations
    remove_all_animation();

    // every ring play the same thing
    for (int i = 0; i < TOTAL_MOLES; i++){
        AnimationObject* new_mole_ring = new AnimationObject();
        new_mole_ring -> led_type = LedType::Ring;
        new_mole_ring -> animation_type = AnimationCategory::Wave;
        new_mole_ring -> mole_id = i;
        new_mole_ring -> colour_1 = Colour::Green;
        new_mole_ring -> start_time_ms = millis() + duration_ms; // duration??
        new_mole_ring -> end_time_ms = millis() + duration_ms;

        // every linear play the same
        AnimationObject* new_mole_ring = new AnimationObject();
        new_mole_ring -> led_type = LedType::Linear;
        new_mole_ring -> animation_type = AnimationCategory::Wave;
        new_mole_ring -> mole_id = i;
        new_mole_ring -> colour_1 = Colour::Green;
        new_mole_ring -> start_time_ms = millis() + duration_ms; // duration??
        new_mole_ring -> end_time_ms = millis() + duration_ms;
    }
}

void remove_mole_animation(int mole_id_){

    for (int i = animation_list.size() - 1; i >= 0; i --){
        AnimationObject* animation = animation_list[i];

        if (animation -> mole_id == mole_id_){ // check if animation is done
            delete animation;
            animation_list -> erase(animation_list.begin() + i);
                
        } 
    }
}

void remove_all_animation(){
    for (int i = animation_list.size() - 1; i >= 0; i --){
        delete animation_list[i];
        animation_list -> erase(animation_list.begin() + i);
    }
}

void queue_Animation(
    LedType led_type,
    AnimationCategory animation_type,
    int mole_id,
    unsigned long duration_ms,
    AnimationObject* animation_to_return_to,   
    Colour colour_1,  
    Colour colour_2, 
    Colour colour_3
){
    // Store the time when animation functions were called
    // Create new animation object
    const unsigned long current_time_ms = millis();
    AnimationObject* new_ani = new AnimationObject();

    new_ani->led_type = led_type;
    new_ani->animation_type = animation_type;
    new_ani->mole_id = mole_id;
    new_ani->start_time_ms = current_time_ms;
    new_ani->end_time_ms = current_time_ms + duration_ms;    
    new_ani->colour_1 = colour_1;
    new_ani->colour_2 = colour_2;
    new_ani->colour_3 = colour_3;

    // Add new animation object to animation list
    animation_list.push_back(new_ani);


}

int calculate_mole_led_(int mole_id){ // return the starting index of the mole leds for that mole
    // should be done at first instaed of called and saved to a variobale?
}

// start mole has top priority, when should it override other functions like the transition animation (eg. )
// when pushing: git add., git commit -m "message", git push
// change mole hp: change the hp bar nnumber and get ratio of new hp and full hop and see if ring should change or not



// *************************************
// Actual Animations
// *************************************

void render_solid_ani(AnimationObject* animation_){
    // get mole id
    // get the led list
    // fill the list with the color

    // linear and ring has diff ones
    int mole_id = animation_->mole_id;
    CRGB color = convert_to_crgb(animation_->colour_1);

    get_starting_ind(mole_id); 

    //num_leds_ring & num_leds_linear is the number of leds per ring and per linear led
    // get the index of the list and fill them all

    int startingIndex = get_starting_index(mole_id);
    // for ring lights
    for (int i = startingInd; i < startingInd += num_leds_ring){
        ledArr[i] = color;
    }

}

int get_starting_index(int mole_id){

}

CRGB convert_to_crgb(Colour color){
   if (color == Colour::Red){
        return CRGB::Red;
   } else if (color == Colour::Green){
    return CRGB::Black;
   } else if (color == Colour::Green){
    return CRGB::Green;
   }
}





// void check_duplicate_animations(vector<*AnimationObject>* animation_list){ // queueu animation should already have all the animations queued together
    
//     // removing elements based on a condition
//     if (animation_list -> empty()){
//         return;
//     }
    
//     for (int i = animation_list -> size() - 1; i >= 0; i--){
//         if ((*animation_list)[i] -> mole_id == animation_mole_id){
//             delete(*animation_list)[i];
//             animation_list -> erase(animation_list -> begin() + i);
//         }
//     }

// }
