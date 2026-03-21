#ifndef LED_INTERFACE_H
#define LED_INTERFACE_H

#include "linked_list.h"
#include "FastLED.h"
#include <math.h>
#include "Adafruit_LEDBackpack.h"
#include <Wire.h>

#include "Adafruit_GFX.h"  
#include "Adafruit_SSD1306.h"

//#include "qrcode.h"

// Define constants for OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define SCREEN_I2C_ADDRESS 0x3C
#define OLED_RESET_PIN -1

// Leaderboard
#define FINAL_SCORE_DISPLAY_DURATION_MS 10000
#define NAME_LENGTH 3

//#define QR_DISPLAY_DURATION_MS 10000


enum class Colour {
    Green,
    Orange,
    Yellow,
    Red,
    Blue,
    Black,
    HealerMole, 
    NormalMole,
    Dim_Yellow
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
    Indicator,
    Heart,
    Hp
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
    Colour colour; //used to indicate type of mole  
};


class DisplayInterface {

    public:
        DisplayInterface(
            unsigned short leds_per_ring, 
            unsigned short leds_per_linear, 
            unsigned short leds_per_mole_indicator,
            unsigned short leds_per_heart, 
            unsigned short number_of_leds,
            unsigned short rings_data_pin,
            unsigned short hearts_data_pin
            //missing 7-seg and oled display info (data pins, # of leds)
        ); 
        ~DisplayInterface(); 
        void process_timed_animations(unsigned long current_time_ms);
        void begin();

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
        void game_over(const String& result); 

        // ring timer + mole hp bar helper functions
        void start_mole(int mole_id, int max_hp, unsigned long duration_ms, const Colour mole_type); 
        void decrease_mole_hp(int mole_id, int new_hp, int max_hp); 
        void increase_mole_hp(int mole_id, int new_hp, int max_hp);
        void end_mole(int mole_id, bool is_timeout, bool is_hp_zero); 

        // round transition helper functions 
        void win_round(); 
        // void lose_round(); 
        void changeDuration(unsigned long newDuration_ms); 
        void changeDuration(int moleID, unsigned long newDuration_ms);

        // game end helper functions
        void win_game();
        void lose_game();
        void idle_state();

        // oled display + leaderboard helper functions
        void show_idle_oled_animation(); // Show OLED idle animation
        void update_oled_gameplay(int current_level, int current_round, int score); // Updates oled during the game play

        void display_final_score(int final_score); // shows final score

        bool is_score_in_leaderboard(int score);
        void begin_leaderboard_entry(int final_score);
        bool update_leaderboard_entry(int encoder_delta, int unused, bool button_pressed);
        void show_leaderboard(); // shows the leaderboard, unrelated to entering names

        
        // OLED CLEAR DISPLAY
        void clear_display();

        // QR Code
        //void show_leaderboard_qr();

        
    private:
        AnimationList animation_list; //Linked List
        unsigned short leds_per_ring; 
        unsigned short leds_per_linear; 
        unsigned short leds_per_mole_indicator;
        unsigned short leds_per_heart;
        unsigned short number_of_leds;
        unsigned short rings_data_pin;
        unsigned short hearts_data_pin;
        unsigned short total_moles = 8;
        unsigned short total_lives = 3;
        CRGB* leds;

        // 7-Seg
        Adafruit_7segment sevenSeg = Adafruit_7segment();
        bool sevenSegReady = false;
        uint8_t sevenSegAddr = 0x75; // default address?

        // OLED Display
        Adafruit_SSD1306 oled = Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET_PIN);
        bool oledReady = false;

        // Leaderboard/ OLED
        static const int MAX_LEADERBOARD_ENTRIES = 1;
        static const int USERNAME_MAX_LENGTH = 4;

        struct LeaderboardEntry {
            char userame[USERNAME_MAX_LENGTH]; // 3 letters + null terminator
            int score;
        };

        LeaderboardEntry leaderboard[MAX_LEADERBOARD_ENTRIES];
        int leaderboardSize = 0;

        bool final_score_active = false;
        bool final_score_drawn = false;
        int final_score_value = 0;
        unsigned long final_score_end_time_ms = 0;

        int     entry_hovered_index = 0;          // 0–25 → 'A'–'Z'
        uint8_t entry_fill_index    = 0;          // 0, 1, or 2
        char    entry_letters[NAME_LENGTH + 1];   // committed chars + '\0'
        int     entry_score         = 0;
        int     entry_prev_A_state  = LOW;
        bool          entry_awaiting_confirm = false;  // true after 3rd letter placed, waiting for confirm click
        unsigned long entry_saved_at_ms      = 0;      // timestamp when saved, for 10s display

        void redraw_entry_oled();                               // thin wrapper around entering_names_to_leaderboard
        void add_to_leaderboard(const String& name, int score); 
        // Show the entering leaderboard ui on oled, the undersocres and evertyhing
        void entering_names_to_leaderboard(char hovered_letter, char first_letter, char second_letter, char third_letter, int final_score, uint8_t fill_index, bool confirm); // Called by redraw_entry_oled 

        // // QR Code
        // bool qr_active = false;
        // unsigned long qr_end_time_ms = 0;

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
            Colour colour = Colour::Black
        );
        void remove_mole_animation(int mole_id_);
        void remove_all_animation();
        CRGB convert_to_crgb(Colour colour);
        int convert_led_type_to_led_index(LedType led_type, int mole_id = -1);

        //internal helper functions for rendering animations
        void render_colour_to_led(AnimationObject* animation_, Colour colour); //CHANGE
        void render_animation(AnimationObject* animation_, unsigned long current_time_ms);
        
        // Seven Seg Helper Functions
        void write4(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3);




};

#endif 


