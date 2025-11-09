#ifndef LED_INTERFACE_H
#define LED_INTERFACE_H

#include <vector>
#include <string>

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
};

struct AnimationObject{
    LedType led_type;
    AnimationCategory animation_type;
    int mole_id; 
    unsigned long start_time_ms;
    unsigned long end_time_ms; //calculated from the current time (determined using millis() at start of function call) + duration 
    AnimationObject* animation_to_return_to;    
    Colour colour_1; // 
    Colour colour_2; // used for patterns requiring more than 1 colour
    Colour colour_3;  // used for patterns requiring more than 2 colours
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
        void start_mole(int mole_id, int max_hp, unsigned long duration_ms, const std::vector<Colour>& colours = {Colour::Green}); 
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
        void show_leaderboard(std::vector<std::string>& leaderboard);
        
    private:
        std::vector<AnimationObject *> animation_list;
        unsigned short leds_per_ring; 
        unsigned short leds_per_linear; 
        unsigned short leds_per_heart;
        unsigned short number_of_leds;
        unsigned short rings_data_pin;
        unsigned short hearts_data_pin;
        int* led_indicies;
};

#endif 