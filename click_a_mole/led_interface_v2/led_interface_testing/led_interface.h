#ifndef LED_INTERFACE_H
#define LED_INTERFACE_H

#include "linked_list.h"
#include "FastLED.h"
#include <math.h>


enum class Colour {
    Green,
    Orange,
    Yellow,
    Red,
    Blue,
    Black
};

enum class AnimationCategory {
    Solid,
    Blinking,
    Wave,
    Timer
};

enum class LedType {
    Ring,
    Linear,
    Heart
};



struct AnimationObject{
    LedType led_type;
    AnimationCategory animation_type;
    int mole_id; 
    unsigned long start_time_ms;
    unsigned long end_time_ms; //calculated from the current time (determined using millis() at start of function call) + duration 
    unsigned short current_hp;
    unsigned short max_hp;
    AnimationObject* animation_to_return_to;    
    Colour colour_1; 
    Colour colour_2; 
    Colour colour_3;  
    Colour colour_4;  
    Colour colour_5;  
};


class DisplayInterface {

    public:
        DisplayInterface(
            unsigned short leds_per_ring, 
            unsigned short leds_per_linear, 
            unsigned short leds_per_heart, 
            unsigned short number_of_leds,
            unsigned short rings_data_pin,
            unsigned short hearts_data_pin
            //missing 7-seg and oled display info (data pins, # of leds)
        ); 
        ~DisplayInterface(); 
        void process_timed_animations(unsigned long current_time_ms);

        // general helper functions
        void power_on_showcase(); 
        void turn_all_light_off(); 
        void changeMoleColourMode(int mole_id, Colour colour); //for special moles 
        void turn_on_specific_light(int mole_id, Colour colour, LedType led_type); //params tbd

        // player lives helper functions
        void update_heart(int lives); 

        // 7-seg helper functions
        void show_score(int current_score); 
        void turn_off_score(); 
        void game_start(); 
        void game_over(); 

        // ring timer + mole hp bar helper functions
        void start_mole(int mole_id, int max_hp, unsigned long duration_ms, const Colour colours[], int colour_count); 
        void change_mole_hp(int mole_id, int new_hp, int max_hp); 
        void end_mole(int mole_id, bool is_timeout, bool is_hp_zero); 

        // round transition helper functions 
        void win_round(); 
        void lose_round(); 
        void changeDuration(unsigned long newDuration_ms); 
        void changeDuration(int moleID, unsigned long newDuration_ms);

        // oled display + leaderboard helper functions
        void show_idle_oled_animation();
        void update_oled_gameplay(int current_level, int current_round, int score); 
        void prompt_leaderboard_name_entry(); 
        void entering_names_to_leaderboard(char first_letter, char second_letter, char third_letter, int final_score, bool confirm); 
        void show_leaderboard(const char* leaderboard[], int size);
        
    private:
        AnimationList animation_list; //Linked List
        unsigned short leds_per_ring; 
        unsigned short leds_per_linear; 
        unsigned short leds_per_heart;
        unsigned short number_of_leds;
        unsigned short rings_data_pin;
        unsigned short hearts_data_pin;
        unsigned short total_moles = 3;
        CRGB* leds;

        //internal helper functions
        AnimationObject* queue_animation(
            LedType led_type,
            AnimationCategory animation_type,
            int mole_id,
            unsigned long start_time_ms,
            unsigned long duration_ms,
            unsigned short current_hp,
            unsigned short max_hp, 
            AnimationObject* animation_to_return_to = nullptr,
            Colour colour_1 = Colour::Black,
            Colour colour_2 = Colour::Black,
            Colour colour_3 = Colour::Black,
            Colour colour_4 = Colour::Black,
            Colour colour_5 = Colour::Black
        );
        void remove_mole_animation(int mole_id_);
        void remove_all_animation();
        CRGB convert_to_crgb(Colour colour);
        int convert_led_type_to_led_index(LedType led_type, int mole_id = -1);

        //internal helper functions for rendering animations
        void render_colour_to_led(AnimationObject* animation_, Colour colour); //CHANGE
        void render_animation(AnimationObject* animation_, unsigned long current_time_ms);




};

#endif 

