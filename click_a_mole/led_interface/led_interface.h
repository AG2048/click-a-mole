#ifndef LED_INTERFACE_H
#define LED_INTEFACE_H
#include <Arduino.h>
#include <FastLED.h>


enum class Colour {
    Red,
    Blue,
    Green,
    Black
};

enum class AnimationCategory {
    Solid,
    Blinking,
    Wave
};

enum class LedType {
    Ring,
    Linear,
    Heart
}

struct AnimationObject{
    LedType led_type;
    AnimationCategory animation_type;
    int mole_id; 
    Colour colour_1; // 
    Colour colour_2; // used for patterns requiring more than 1 colour
    Colour colour_3;  // used for patterns requiring more than 2 colours
    unsigned long start_time_ms;
    unsigned long end_time_ms; //calculated from the current time (determined using millis() at start of function call) + duration 
    AnimationObject* animation_to_return_to;

}


class DisplayInterface {

    public:
        DisplayInterface(
            unsigned short leds_per_ring, 
            unsigned short leds_per_linear, 
            unsigned short leds_per_heart, 
            unsigned short number_of_leds,
            unsigned short rings_data_pin,
            unsigned short hearts_data_pin,
            //missing 7-seg and oled display info (data pins, # of leds)
        ); 
        ~DisplayInterface(); 
        void process_timed_animations(unsigned long current_time_ms);

        // general helper functions
        power_on_showcase(); 
        turn_all_light_off(); 
        changeMoleColourMode(int mole_id, Colour colour); //for special moles 
        turn_on_specific_light(int mole_id, Colour colour, LedType led_type); //params tbd

        // player lives helper functions
        update_heart(int lives); 

        // 7-seg helper functions
        show_score(int current_score); 
        turn_off_score(); 
        game_start(); 
        game_over(); 

        // ring timer + mole hp bar helper functions
        void start_mole(int mole_id, int max_hp, unsigned long duration_ms, const vector<>& colors = {Color::Green}); 
        void change_mole_hp(int mole_id, int new_hp, int max_hp); 
        void end_mole(int mole_id, bool is_timeout, bool is_hp_zero); 

        // round transition helper functions 
        void win_round(); 
        void lose_round(); 
        changeDuration(newDuration); 
        changeDuration(moleID, newDuration) 

        // oled display + leaderboard helper functions
        show_idle_oled_animation();
        update_oled_gameplay(int current_level, int current_round, int score); 
        prompt_leaderboard_name_entry() 
        entering_names_to_leaderboard(char first_letter, char second_letter, char third_letter, int final_score, bool confirm) 
        show_leaderboard(vector<LeaderboardEntry> leaderboard) 

        
    private:
        vector<*AnimationObject> animation_list;
        int leds_per_ring;
        int leds_per_linear;
        int leds_per_heart;
        int led_indicies*;
}

#endif 