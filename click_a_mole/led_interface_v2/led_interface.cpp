#include "led_interface.h"


// *************************************
// Const for Seven Segment Display
// *************************************

// Segment bits: A=0x01 B=0x02 C=0x04 D=0x08 E=0x10 F=0x20 G=0x40
static const uint8_t SEG_BLANK = 0x00;

// Letters/numbers for LOSE / LU1N on a 4-digit 7-seg
static const uint8_t SEG_L_CHAR = 0x38;
static const uint8_t SEG_O_CHAR = 0x3F;
static const uint8_t SEG_S_CHAR = 0x6D;
static const uint8_t SEG_E_CHAR = 0x79;

static const uint8_t SEG_U_CHAR = 0x3E;
static const uint8_t SEG_1_CHAR = 0x06;
static const uint8_t SEG_N_CHAR = 0x54;


// *************************************
// Const for OLED Display
// *************************************


const unsigned char diglett[] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xf0, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x3e, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x03, 0x80, 0x00, 0x00,
  0x00, 0x00, 0x01, 0x80, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x30, 0x00, 0x00,
  0x00, 0x00, 0x04, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x10, 0x04, 0x08, 0x00, 0x00,
  0x00, 0x00, 0x18, 0x08, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x10, 0x38, 0x0e, 0x06, 0x00, 0x00,
  0x00, 0x00, 0x30, 0x38, 0x06, 0x02, 0x00, 0x00, 0x00, 0x00, 0x20, 0x10, 0x04, 0x03, 0x00, 0x00,
  0x00, 0x00, 0x60, 0x10, 0x04, 0x01, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x01, 0x80, 0x00,
  0x00, 0x00, 0x40, 0x06, 0x30, 0x01, 0x80, 0x00, 0x00, 0x00, 0x40, 0x10, 0x04, 0x00, 0x80, 0x00,
  0x00, 0x00, 0x40, 0x10, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x40, 0x10, 0x04, 0x00, 0x80, 0x00,
  0x00, 0x00, 0x40, 0x08, 0x08, 0x00, 0x80, 0x00, 0x00, 0x00, 0x40, 0x01, 0xc0, 0x00, 0x80, 0x00,
  0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x80, 0x00,
  0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x80, 0x00,
  0x00, 0x04, 0xc0, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x80, 0x00,
  0x00, 0x20, 0x80, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x01, 0x00, 0x80, 0x00, 0x00, 0x00, 0x84, 0x00,
  0x02, 0x0e, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00,
  0x08, 0x00, 0x80, 0x00, 0x00, 0x00, 0xa0, 0x00, 0x00, 0x01, 0xd0, 0x00, 0x00, 0x00, 0x84, 0x00,
  0x40, 0x00, 0x00, 0x40, 0x08, 0x06, 0x06, 0x10, 0x40, 0x04, 0x00, 0x22, 0x10, 0x30, 0x03, 0x08,
  0x40, 0x18, 0x00, 0x00, 0x80, 0x10, 0x00, 0x84, 0x40, 0x00, 0x00, 0x00, 0x40, 0x04, 0x00, 0x02,
  0x20, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x02, 0x30, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x02,
  0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1d, 0x80,
  0x01, 0x80, 0xd0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x63, 0x04, 0x00, 0x00, 0x00, 0x40, 0x00,
  0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x02, 0x00, 0x20, 0x43, 0x00, 0x00,
  0x00, 0x00, 0x02, 0x00, 0x40, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x01, 0xfd, 0x80, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// *************************************
// Constructors and Destructors
// *************************************

void DisplayInterface::begin() {
  Wire.begin();
  Serial.println("Wire OK");
  
  sevenSeg.begin(0x75);
  Serial.println("7seg OK");
  
  sevenSeg.clear();
  sevenSeg.writeDisplay();
  sevenSegReady = true;
  Serial.println("7seg ready");
  
  oledReady = oled.begin(SSD1306_SWITCHCAPVCC, SCREEN_I2C_ADDRESS);
  Serial.println("OLED done");
  Serial.println(oledReady);
}

// Constructor
DisplayInterface::DisplayInterface(
  unsigned short leds_per_ring_,
  unsigned short leds_per_linear_,
  unsigned short leds_per_mole_indicator_,
  unsigned short leds_per_heart_,
  unsigned short number_of_leds_,
  unsigned short rings_data_pin_,
  unsigned short hearts_data_pin_) {

  // Initialize any other setup here if needed
  this->leds_per_ring = leds_per_ring_;
  this->leds_per_linear = leds_per_linear_;
  this->leds_per_mole_indicator = leds_per_mole_indicator_;
  this->leds_per_heart = leds_per_heart_;
  this->number_of_leds = number_of_leds_;
  this->rings_data_pin = rings_data_pin_;
  this->hearts_data_pin = hearts_data_pin_;
  this->leds = new CRGB[number_of_leds_];


  // Note: for testing purposes, we will use a fixed data pin (4)
  // as the rings_data_pin_ must be known at compile time for addLeds<>
  // FastLED.addLeds<WS2812B, GRB>(leds, number_of_leds_, rings_data_pin_); //potential fix, provided by ChatGPT
  FastLED.addLeds<WS2812B, 4, GRB>(leds, number_of_leds_);  //temporary fix
  FastLED.setBrightness(5);

  fill_solid(leds, number_of_leds_, CRGB::Black);

  //Wire.begin();
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

// Function starts the ring timer and hp bar for each mole
void DisplayInterface::start_mole(int mole_id, int max_hp, unsigned long duration_ms, const Colour colour) {  // vector bc for one round it may be 3 lives or 5 lives so theats like 3 vs 5 colors, its green by default but if they do pass smth then itll be what they pass

  unsigned long start_time_ms = millis();

  // remove all previous mole animations,
  // which inludes any rings and linear LEDs
  remove_mole_animation(mole_id);

  queue_animation(LedType::Ring, AnimationCategory::Timer, mole_id, start_time_ms, duration_ms, max_hp, max_hp);
  queue_animation(LedType::Linear, AnimationCategory::Solid, mole_id, start_time_ms, duration_ms, max_hp, max_hp, nullptr, Colour::Green);
  queue_animation(LedType::Indicator, AnimationCategory::Solid, mole_id, start_time_ms, duration_ms, max_hp, max_hp, nullptr, colour);
}

// Function decreases hp bar for a mole and plays a flash animation
// on the ring timer to reflect that the mole was pressed,
// immediately returns to timer animation after flash animation is done
// NOTE: The timer doesn't pause during flash animation
void DisplayInterface::decrease_mole_hp(int mole_id, int new_hp, int max_hp) {
  unsigned long current_time_ms = millis();

  // should show 200 ms intermediate flash for RING
  // HP bar should just decrease

  for (int i = animation_list.size() - 1; i >= 0; i--) {

    AnimationObject* animation = animation_list.get(i);

    // hp bar
    if (animation->mole_id == mole_id && animation->led_type == LedType::Linear) {
      animation->current_hp = new_hp;
    }

    // remove timer animation
    // guarantees that animation->animation_to_return_to == nullptr

    // REVIEW LOGIC
    if (animation->mole_id == mole_id && animation->animation_type == AnimationCategory::Timer) {
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

      render_colour_to_led(animation, Colour::Black);  // may be redundant, as the new queued animation will change leds to blue
      delete animation;
      animation_list.erase(i);

      // queue the new flash animation
      unsigned long current_time_ms = millis();
      unsigned long time_till_timer_end_ms = return_to_timer_animation->end_time_ms - current_time_ms;

      if (time_till_timer_end_ms < 200) {
        queue_animation(LedType::Ring, AnimationCategory::Solid, mole_id, current_time_ms, time_till_timer_end_ms, -1, -1);
        delete return_to_timer_animation;  // no time left after flash, so delete queued timer animation
      } else {
        queue_animation(LedType::Ring, AnimationCategory::Solid, mole_id, current_time_ms, 200, -1, -1, return_to_timer_animation, Colour::Blue);
      }
    }

    // when the mole is hit during the flash
    if (animation->mole_id == mole_id && animation->animation_type == AnimationCategory::Solid && animation->led_type == LedType::Ring && animation->animation_to_return_to != nullptr) {

      // Update HP in the original timer animation
      animation->animation_to_return_to->current_hp = new_hp;  //what if hit during the else block

      // Restart flash
      if (animation->end_time_ms + 200 < animation->animation_to_return_to->end_time_ms) {
        animation->end_time_ms += 200;
      } else {  // cap flash at end time and remove animation to return to
        animation->end_time_ms = animation->animation_to_return_to->end_time_ms;

        delete animation->animation_to_return_to;
        animation->animation_to_return_to = nullptr;
      }
    }
  }
}

// Function increases hp bar for a mole
// Only hp bar changes and goes to the new hp
void DisplayInterface::increase_mole_hp(int mole_id, int new_hp, int max_hp) {
  unsigned long current_time_ms = millis();

  for (int i = animation_list.size() - 1; i >= 0; i--) {

    AnimationObject* animation = animation_list.get(i);

    // hp bar
    if (animation->mole_id == mole_id && animation->led_type == LedType::Linear) {
      animation->current_hp = new_hp;
    }
  }
}

// Function plays a blinking animation on the ring and linear leds
// (of a specific mole)  if the timer ran out or the mole's hp is 0
void DisplayInterface::end_mole(int mole_id, bool is_timeout, bool is_hp_zero) {

  unsigned long start_time_ms = millis();

  remove_mole_animation(mole_id);

  if (is_timeout) {
    queue_animation(LedType::Ring, AnimationCategory::Blinking, mole_id, start_time_ms, 200, -1, -1, nullptr, Colour::Red);
    queue_animation(LedType::Linear, AnimationCategory::Blinking, mole_id, start_time_ms, 200, -1, -1, nullptr, Colour::Red);

  } else if (is_hp_zero) {
    //POTENTIAL ISSUES
    //each queued animation in end_mole should share the same start_time_ms
    //but, this is not the case
    //previous public animations share this same issue
    //potentially, this is not a big deal as queue_animation barely takes processing time
    //but keep in mind
    queue_animation(LedType::Ring, AnimationCategory::Blinking, mole_id, start_time_ms, 200, -1, -1, nullptr, Colour::Green);
    queue_animation(LedType::Linear, AnimationCategory::Blinking, mole_id, start_time_ms, 200, -1, -1, nullptr, Colour::Green);
  }
}

// Function removes all mole animations
// and plays round win animation for 2001m (divisble by 3), then sets all mole leds to black
void DisplayInterface::win_round() {

  unsigned long start_time_ms = millis();

  for (int i = 1; i <= total_moles; i++) {
    remove_mole_animation(i);
  }

  // light first row
  AnimationObject* firstRow = queue_animation(LedType::Ring, AnimationCategory::Solid, 1, start_time_ms, 667, -1, -1, nullptr, Colour::Green);
  queue_animation(LedType::Ring, AnimationCategory::Solid, 2, start_time_ms, 667, -1, -1, nullptr, Colour::Green);
  queue_animation(LedType::Ring, AnimationCategory::Solid, 3, start_time_ms, 667, -1, -1, nullptr, Colour::Green);

  // light second row
  AnimationObject* secondRow = queue_animation(LedType::Ring, AnimationCategory::Solid, 4, firstRow->end_time_ms, 667, -1, -1, nullptr, Colour::Green);
  queue_animation(LedType::Ring, AnimationCategory::Solid, 5, firstRow->end_time_ms, 667, -1, -1, nullptr, Colour::Green);

  
  // light thrid row
  queue_animation(LedType::Ring, AnimationCategory::Solid, 7, secondRow->end_time_ms, 667, -1, -1, nullptr, Colour::Green);
  queue_animation(LedType::Ring, AnimationCategory::Solid, 8, secondRow->end_time_ms, 667, -1, -1, nullptr, Colour::Green);
  queue_animation(LedType::Ring, AnimationCategory::Solid, 9, secondRow->end_time_ms, 667, -1, -1, nullptr, Colour::Green);
}

// Function removes all mole animations
// and plays lose win animation for 2001m (divisble by 3), then sets all mole leds to black
// void DisplayInterface::lose_round() {

//   unsigned long start_time_ms = millis();

//   for (int i = 1; i <= total_moles; i++) {
//     remove_mole_animation(i);
//   }

//   AnimationObject* firstRow = queue_animation(LedType::Ring, AnimationCategory::Solid, 1, start_time_ms, 667, -1, -1, nullptr, Colour::Red);
//   queue_animation(LedType::Ring, AnimationCategory::Solid, 2, start_time_ms, 667, -1, -1, nullptr, Colour::Red);
//   queue_animation(LedType::Ring, AnimationCategory::Solid, 3, start_time_ms, 667, -1, -1, nullptr, Colour::Red);
//   queue_animation(LedType::Ring, AnimationCategory::Solid, 4, start_time_ms, 667, -1, -1, nullptr, Colour::Red);

//   AnimationObject* secondRow = queue_animation(LedType::Ring, AnimationCategory::Solid, 5, firstRow->end_time_ms, 667, -1, -1, nullptr, Colour::Red);
//   queue_animation(LedType::Ring, AnimationCategory::Solid, 6, firstRow->end_time_ms, 667, -1, -1, nullptr, Colour::Red);
//   queue_animation(LedType::Ring, AnimationCategory::Solid, 7, firstRow->end_time_ms, 667, -1, -1, nullptr, Colour::Red);

//   queue_animation(LedType::Ring, AnimationCategory::Solid, 8, secondRow->end_time_ms, 667, -1, -1, nullptr, Colour::Red);
//   queue_animation(LedType::Ring, AnimationCategory::Solid, 9, secondRow->end_time_ms, 667, -1, -1, nullptr, Colour::Red);
// }

// Function shows the number of lives the
// player has on the heart led display
void DisplayInterface::update_heart(int lives) {
  int heartIndex = convert_led_type_to_led_index(LedType::Heart, -1);
  int num_heart_leds_on = lives * leds_per_heart;  //number of leds to turn on

  // Turn heart leds on
  for (int i = heartIndex; i < heartIndex + num_heart_leds_on; i++) {
    leds[i] = CRGB::Red;
  }

  // Turn off excess heart leds
  for (int i = heartIndex + num_heart_leds_on; i < heartIndex + (total_lives * leds_per_heart); i++) {
    leds[i] = CRGB::Black;
  }

  FastLED.show();  // note that update heart animations are not
                   // added to animation_list
}

// Function modifies the led buffer based on system time
void DisplayInterface::process_timed_animations(unsigned long current_time_ms) {

  for (int i = animation_list.size() - 1; i >= 0; i--) {

    AnimationObject* animation = animation_list.get(i);
    // int ani_mole_id = animation->mole_id;

    if (animation->end_time_ms <= current_time_ms) {  // check if animation is done

      render_colour_to_led(animation, Colour::Black);

      // also check if there is animation to return to, if yes, push_back to list
      // If animation->animation_to_return_to != nullptr, we push it back into the list.
      // Important: delete animation only deletes the AnimationObject itself.
      // It does NOT delete animation->animation_to_return_to.
      // Ownership of that pointer now belongs to the animation list.

      // REVIEW LOGIC
      if (animation->animation_to_return_to != nullptr) {
        AnimationObject* next = animation->animation_to_return_to;
        animation->animation_to_return_to = nullptr;

        animation_list.push_back(next);

        render_animation(next, current_time_ms);  //render animation only if
      }

      delete animation;
      animation_list.erase(i);
    } else {
      render_animation(animation, current_time_ms);
    }
  }

  FastLED.show();


  /* OLED FINAL SCORE */

  if (final_score_active) {
    if (!final_score_drawn) {
      oled.clearDisplay();
      oled.setTextSize(2);

      oled.setTextColor(WHITE);
      oled.setCursor(15, 20);
      oled.print("Score:");
      oled.setCursor(50, 40);
      oled.print(final_score_value);
      oled.display();
      final_score_drawn = true;
    }
  }


  // Change the condition to also require final_score_active:
if (final_score_active && current_time_ms >= final_score_end_time_ms) {
    final_score_active = false;
    final_score_drawn = false;
    if (oledReady) show_idle_oled_animation();
}
  
  // // QR CODE DISPLAY TIMEOUT
  // if (qr_active && current_time_ms >= qr_end_time_ms) {
  //   qr_active = false;
  //   if (oledReady) show_idle_oled_animation();
  // }
}

void DisplayInterface::win_game() {
  unsigned long start_time_ms = millis();

  for (int i = 1; i <= total_moles; i++) {
    remove_mole_animation(i);
  }

  // Animation goes in a circle 3 times 1->2->3->4->8->7->6->5
  // could loop through an array with the proper mole ids
  int path[] = { 1, 2, 3, 4, 8, 7, 6, 5 };

  int start_delay = 0;

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < total_moles; j++) {
      int id = path[j];
      queue_animation(LedType::Ring, AnimationCategory::Solid, id, start_time_ms + start_delay, 100, -1, -1, nullptr, Colour::Green);
      start_delay += 100;
    }
  }

  // Hold green animation for a duration of time
  for (int id = 1; id <= total_moles; id++) {
    queue_animation(LedType::Ring, AnimationCategory::Solid, id, start_time_ms + start_delay, 2000, -1, -1, nullptr, Colour::Green);
  }
}

void DisplayInterface::lose_game() {
  // Light whole thing, then only bottom two row, then last row only
  unsigned long start_time_ms = millis();

  for (int i = 1; i <= total_moles; i++) {
    remove_mole_animation(i);
  }

  unsigned long flash_duration = 600;
  unsigned long gap_duration = 300;
  unsigned long total_offset = flash_duration + gap_duration;

  // All
  for (int id = 1; id <= total_moles; id++) {
    queue_animation(LedType::Ring, AnimationCategory::Solid, id, start_time_ms, flash_duration, -1, -1, nullptr, Colour::Red);
  }

  // Second and last row, may need to extend start time so itll be a flash and turn black for a few seconds
  for (int id = 4; id <= total_moles; id++) {
    queue_animation(LedType::Ring, AnimationCategory::Solid, id, start_time_ms + total_offset, flash_duration, -1, -1, nullptr, Colour::Red);
  }

  total_offset += flash_duration + gap_duration;

  // Last row
  for (int id = 6; id <= total_moles; id++) {
    queue_animation(LedType::Ring, AnimationCategory::Solid, id, start_time_ms + total_offset, flash_duration, -1, -1, nullptr, Colour::Red);
  }
}

void DisplayInterface::idle_state() {
  remove_all_animation();

  CRGB idle_yellow = convert_to_crgb(Colour::Dim_Yellow);

  for (int i = 0; i < number_of_leds; i++) {
    leds[i] = idle_yellow;
  }

  FastLED.show();
}

// *************************************
// 7-Seg
// *************************************

void DisplayInterface::show_score(int current_score) {
  if (!sevenSegReady) return;

  if (current_score < 0) current_score = 0;
  if (current_score > 9999) current_score = 9999;

  sevenSeg.clear();
  sevenSeg.print(current_score);
  sevenSeg.writeDisplay();
}

void DisplayInterface::turn_off_score() {
  if (!sevenSegReady) return;

  sevenSeg.clear();
  sevenSeg.writeDisplay();
}

void DisplayInterface::game_start() {
  show_score(0);
}

void DisplayInterface::game_over(const String& result) {
  if (!sevenSegReady) return;

  if (result == "WIN") {
    write4(SEG_L_CHAR, SEG_U_CHAR, SEG_1_CHAR, SEG_N_CHAR);  // LU1N
  } else if (result == "LOSE") {
    write4(SEG_L_CHAR, SEG_O_CHAR, SEG_S_CHAR, SEG_E_CHAR);  // LOSE
  } else {
    return;
  }

  //delay(2000);
  //turn_off_score();
  //idle_state();
}


// // *************************************
// // OLED
// // *************************************

void DisplayInterface::clear_display(){
  oled.clearDisplay();
}


void DisplayInterface::update_oled_gameplay(int current_level, int current_round, int score) {
  // Implementation for updating OLED display during gameplay
  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setTextColor(WHITE);
  oled.setCursor(0, 0);
  oled.print("Level: ");
  oled.println(current_level);

  oled.setCursor(0, 10);
  oled.print("Round: ");
  oled.println(current_round);

  oled.setCursor(0, 20);
  oled.print("Score: ");
  oled.println(score);
  oled.display();

  //maybe animate a mole during gameplay on the side
}

void DisplayInterface::show_idle_oled_animation() {
  // Implementation for idle animation on OLED display
  oled.clearDisplay();
  oled.setTextSize(1);

  oled.setTextColor(WHITE);
  oled.setCursor(20, 0);
  oled.println("Click-A-Mole!");

  // Draw Diglett bitmap at center
  int x = (SCREEN_WIDTH - 64) / 2;
  int y = (SCREEN_HEIGHT - 64) / 2 + 10;
  oled.drawBitmap(x, y, diglett, 64, 64, SSD1306_WHITE);
  oled.display();
}

void DisplayInterface::display_final_score(int final_score) {
  final_score_active = true;
  final_score_drawn = false;
  final_score_value = final_score;

  final_score_end_time_ms = millis() + FINAL_SCORE_DISPLAY_DURATION_MS;
}

bool DisplayInterface::is_score_in_leaderboard(int score) {
  // Board not full yet — always allow entry
  if (leaderboardSize < MAX_LEADERBOARD_ENTRIES) {
    return true;
  }

  // Board full — only allow if score beats the lowest entry
  int lowest_score = leaderboard[0].score;
  for (int i = 1; i < leaderboardSize; i++) {
    if (leaderboard[i].score < lowest_score) {
      lowest_score = leaderboard[i].score;
    }
  }

  return score > lowest_score;
}

void DisplayInterface::entering_names_to_leaderboard(char hovered_letter, char first_letter, char second_letter, char third_letter,
                                                     int final_score, uint8_t fill_index, bool confirm) {

  if (fill_index > NAME_LENGTH - 1) {
    fill_index = NAME_LENGTH - 1;  // cap fill index to 2, as there are only 3 letters MAKE THIS A CONSTANT: MAX_NAME_LENGTH = 3
  }

  if (confirm) {
    // add name and score to leaderboard
    String name = "";
    name += first_letter;
    name += second_letter;
    name += third_letter;

  if (is_score_in_leaderboard(entry_score)) {  // guard here
    add_to_leaderboard(name, entry_score);
  }
    return;
  }

  /*DRAW ENTRY SCREEN*/

  oled.clearDisplay();
  oled.setTextColor(SSD1306_WHITE);
  oled.setTextSize(1);

  // Top: hovered letter
  oled.setCursor(0, 0);
  oled.print("Select: ");
  oled.print(hovered_letter);

  // Score line
  oled.setCursor(0, 10);
  oled.print("Score: ");
  oled.print(final_score);

  // Instruction
  oled.setCursor(0, 20);
  oled.print("Press to confirm");

  // Big letters (committed)
  oled.setTextSize(3);

  const int letters_y = 34;
  const int letters_x_start = 18;
  const int letters_spacing = 30;

  oled.setCursor(letters_x_start, letters_y);
  oled.write(first_letter);

  oled.setCursor(letters_x_start + letters_spacing, letters_y);
  oled.write(second_letter);

  oled.setCursor(letters_x_start + 2 * letters_spacing, letters_y);
  oled.write(third_letter);

  // Underline cursor at current fill_index
  const int underline_y = letters_y + 28;
  int underline_at_letter = letters_x_start + (int)fill_index * letters_spacing;
  oled.drawLine(underline_at_letter, underline_y, underline_at_letter + 18, underline_y, SSD1306_WHITE);

  oled.display();
}

// ── Public: call once when transitioning into name-entry mode ───
void DisplayInterface::begin_leaderboard_entry(int final_score) {
  entry_hovered_index = 0;
  entry_fill_index = 0;
  entry_score = final_score;
  entry_awaiting_confirm = false;  // ADD THIS
  entry_saved_at_ms = 0;           // ADD THIS

  // Pre-fill slots with '_' so the OLED always shows 3 characters.
  for (int i = 0; i < NAME_LENGTH; i++) {
    entry_letters[i] = '_';
  }
  entry_letters[NAME_LENGTH] = '\0';

  entry_prev_A_state = LOW;  // will sync on the first update call

  redraw_entry_oled();
}


// PUBLIC: Returns true once the 3rd letter is confirmed and saved.
bool DisplayInterface::update_leaderboard_entry(int encoder_delta, int unused, bool button_pressed) {

  // ROTARY ENCODER — ignore rotation while waiting for confirm click
  if (encoder_delta != 0 && !entry_awaiting_confirm) {
    if (encoder_delta > 0) {
      if (entry_hovered_index == 25) entry_hovered_index = 0;
      else entry_hovered_index++;
    } else {
      if (entry_hovered_index == 0) entry_hovered_index = 25;
      else entry_hovered_index--;
    }
    redraw_entry_oled();
  }

  // BUTTON
  if (button_pressed) {

    // ── Confirm click after all 3 letters placed ──
    if (entry_awaiting_confirm) {
      String name = "";
      name += String(entry_letters[0]);
      name += String(entry_letters[1]);
      name += String(entry_letters[2]);

      if (is_score_in_leaderboard(entry_score)) {  // guard here
        add_to_leaderboard(name, entry_score);
      }
      entry_awaiting_confirm = false;
      entry_saved_at_ms = millis();

      // Show saved screen
      oled.clearDisplay();
      oled.setTextColor(SSD1306_WHITE);

      oled.setTextSize(2);
      oled.setCursor(20, 8);
      oled.print("SAVED!");

      oled.setTextSize(1);
      oled.setCursor(20, 36);
      oled.print("Name:  ");
      oled.write(entry_letters[0]);
      oled.write(entry_letters[1]);
      oled.write(entry_letters[2]);

      oled.setCursor(20, 48);
      oled.print("Score: ");
      oled.print(entry_score);

      oled.display();
      return true;  // signal to sketch: entry is done
    }

    // ── Normal letter selection click ──
    char chosen = (char)('A' + entry_hovered_index);
    entry_letters[entry_fill_index] = chosen;

    if (entry_fill_index < 2) {
      entry_fill_index++;
      redraw_entry_oled();
    } else {
      // 3rd letter placed — next click will confirm/save
      entry_awaiting_confirm = true;
      redraw_entry_oled();  // show all 3 letters, cursor stays on slot 3
    }
  }

  return false;
}

// PRIVATE: redraws the OLED entry screen
void DisplayInterface::redraw_entry_oled() {
  char hovered_letter = (char)('A' + entry_hovered_index);

  entering_names_to_leaderboard(
    hovered_letter,
    entry_letters[0],
    entry_letters[1],
    entry_letters[2],
    entry_score,
    entry_fill_index,
    false);
}

// PRIVATE: insertion-sort add into leaderboard array, just add to the leaderboard, doesn't display anything
void DisplayInterface::add_to_leaderboard(const String& name, int score) {

  LeaderboardEntry new_entry;
  strncpy(new_entry.userame, name.c_str(), USERNAME_MAX_LENGTH - 1);
  new_entry.userame[USERNAME_MAX_LENGTH - 1] = '\0';
  new_entry.score = score;

  if (leaderboardSize < MAX_LEADERBOARD_ENTRIES) {
    leaderboard[leaderboardSize] = new_entry;
    leaderboardSize++;
  } else {
    // Board full — only replace the lowest score if the new one is better.
    int lowest_idx = 0;
    for (int i = 1; i < leaderboardSize; i++) {
      if (leaderboard[i].score < leaderboard[lowest_idx].score) {
        lowest_idx = i;
      }
    }
    if (score <= leaderboard[lowest_idx].score) return;
    leaderboard[lowest_idx] = new_entry;
  }

  // Keep the array sorted descending by score.
  for (int i = leaderboardSize - 1; i > 0; i--) {
    if (leaderboard[i].score > leaderboard[i - 1].score) {
      LeaderboardEntry tmp = leaderboard[i];
      leaderboard[i] = leaderboard[i - 1];
      leaderboard[i - 1] = tmp;
    } else {
      break;
    }
  }
}

//*************************************
//QR Code
//*************************************

// void DisplayInterface::show_leaderboard_qr() {
//   // Build URL: https://anthonyx4.github.io/qrCodeTesting/?Name1=Score1&Name2=Score2
//   String url = "https://anthonyx4.github.io/qrCodeTesting/?";

//   for (int i = 0; i < leaderboardSize; i++) {
//     if (i > 0) url += "&";
//     url += String(leaderboard[i].userame);
//     url += "=";
//     url += String(leaderboard[i].score);
//   }

//   // Generate QR code (version 6 supports ~100 chars, ECC Low)
//   QRCode qrcode;
//   uint8_t qrcodeData[qrcode_getBufferSize(6)];
//   qrcode_initText(&qrcode, qrcodeData, 6, ECC_LOW, url.c_str());

//   // Calculate scale and offsets to center on 128x64 display
//   // QR version 6 = 41x41 modules
//   uint8_t qr_size = qrcode.size;         // number of modules (e.g. 41)
//   uint8_t scale = SCREEN_HEIGHT / qr_size; // e.g. 64/41 = 1 pixel per module
//   if (scale < 1) scale = 1;

//   uint8_t rendered_width  = qr_size * scale;
//   uint8_t rendered_height = qr_size * scale;
//   uint8_t x_offset = (SCREEN_WIDTH  - rendered_width)  / 2;
//   uint8_t y_offset = (SCREEN_HEIGHT - rendered_height) / 2;

//   oled.clearDisplay();

//   // Render QR modules
//   for (uint8_t y = 0; y < qr_size; y++) {
//     for (uint8_t x = 0; x < qr_size; x++) {
//       if (qrcode_getModule(&qrcode, x, y)) {
//         // Fill a scale×scale block for each dark module
//         oled.fillRect(x_offset + x * scale, y_offset + y * scale, scale, scale,  SSD1306_WHITE);
//       }
//     }
//   }

//   oled.display();

//   // Set timer to return to idle after 10 seconds
//   qr_active = true;
//   qr_end_time_ms = millis() + QR_DISPLAY_DURATION_MS;
// }

// *************************************
// Helper Functions
// *************************************

AnimationObject* DisplayInterface::queue_animation(
  LedType led_type,
  AnimationCategory animation_type,
  int mole_id,
  unsigned long start_time_ms,
  unsigned long duration_ms,
  unsigned short current_hp,
  unsigned short max_hp,
  AnimationObject* animation_to_return_to,
  Colour colour_) {
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
  new_ani->colour = colour_;

  // Add new animation object to animation list
  animation_list.push_back(new_ani);

  return new_ani;
}

// Function removes all ring, linear and mole_indicator led animations for a mole
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
    delete animation_list.get(i);  // delete AnimationObject
  }

  animation_list.clear();

  //set all leds in the buffer to also be CRGB::Black

  for (int i = 0; i < number_of_leds; i++) {
    leds[i] = CRGB::Black;
  }
}

// Function converts user-enumerated Colour
// to FastLED enumerated CRGB
CRGB DisplayInterface::convert_to_crgb(Colour colour) {
  switch (colour) {
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
    case Colour::HealerMole:
      return CRGB::Blue;
    case Colour::NormalMole:
      return CRGB::Green;
    case Colour::Dim_Yellow:
      return CRGB(15, 15, 0);
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
  switch (led_type) {
    case LedType::Ring:
      return (mole_id - 1) * leds_per_ring;
    case LedType::Linear:
      return (total_moles * leds_per_ring) + (mole_id - 1) * leds_per_linear;
    case LedType::Indicator:
      return (total_moles * leds_per_ring) + (total_moles * leds_per_linear) + (mole_id - 1) * leds_per_mole_indicator;
    case LedType::Heart:
      return (total_moles * leds_per_ring) + (total_moles * leds_per_linear) + (total_moles * leds_per_mole_indicator);
    default:
      return -1;
  }
}



// *************************************
// Rendering Animations Helper Functions
// *************************************

// Function renders a colour to an animation's
// type of led at a specific mole id
void DisplayInterface::render_colour_to_led(AnimationObject* animation, Colour colour_) {

  int leds_per_led_type;

  switch (animation->led_type) {
    case LedType::Ring:
      leds_per_led_type = leds_per_ring;
      break;
    case LedType::Linear:
      leds_per_led_type = leds_per_linear;
      break;
    case LedType::Indicator:
      leds_per_led_type = leds_per_mole_indicator;
      break;
    case LedType::Heart:
      leds_per_led_type = leds_per_heart;
      break;
  }

  int start_index = convert_led_type_to_led_index(animation->led_type, animation->mole_id);
  CRGB colour = convert_to_crgb(colour_);

  for (int i = start_index; i < start_index + leds_per_led_type; i++) {
    leds[i] = colour;
  }
}

// Function is reponsible for processing the logic to advance
// leds in the led buffer using animation_list
void DisplayInterface::render_animation(AnimationObject* animation, unsigned long current_time_ms) {

  //for round transition animations, we may queue one row
  //pattern to occur after the next; in doing so, some animations' start time
  //will be in the future
  if (animation->start_time_ms > current_time_ms) {
    return;
  }

  AnimationCategory animation_type = animation->animation_type;

  if (animation_type == AnimationCategory::Timer) {
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
    int remaining_hp_percentage = floor(remaining_hp_fraction * 100.0);

    if (remaining_hp_percentage <= 100 && remaining_hp_percentage >= 70) {
      render_colour_to_led(animation, Colour::Green);
    } else if (remaining_hp_percentage <= 69 && remaining_hp_percentage >= 30) {
      render_colour_to_led(animation, Colour::Orange);
    } else if (remaining_hp_percentage <= 29 && remaining_hp_percentage >= 0) {
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
    int leds_to_turn_off = floor(fraction_elapsed * leds_per_ring);

    int start_led_index = convert_led_type_to_led_index(animation->led_type, animation->mole_id);
    int end_led_index = start_led_index + leds_per_ring - 1;

    // Turn OFF LEDs starting from the LAST LED backward
    for (int i = 0; i < leds_to_turn_off; i++) {
      int led_index = end_led_index - i;
      leds[led_index] = CRGB::Black;
    }

  } else if (animation_type == AnimationCategory::Solid) {

    if (animation->led_type == LedType::Linear) {

      int start_led_index = convert_led_type_to_led_index(animation->led_type, animation->mole_id);

      // Determine HP bar status
      int hp = animation->current_hp;
      int maxhp = animation->max_hp;

      // Clamp hp and maxhp values
      if (maxhp <= 0) maxhp = 1;
      if (hp < 0) hp = 0;
      if (hp > maxhp) hp = maxhp;

      // Calculate HP percentage
      float hp_percentage = (float)hp / (float)maxhp;

      // Determine color
      Colour hp_bar_colour;
      if (hp_percentage > 0.80f) {
        hp_bar_colour = Colour::Green;
      } else if (hp_percentage > 0.40f) {
        hp_bar_colour = Colour::Orange;
      } else {
        hp_bar_colour = Colour::Red;
      }


      // Flashing parameters
      const int FLASH_INTERVAL_MS = 100;
      bool is_on_cycle = true;

      // Flashing logic
      if (maxhp == 1 || (maxhp > 1 && hp == 1)) {
        unsigned long time_elapsed = current_time_ms - animation->start_time_ms;
        unsigned long cycle_position = time_elapsed / FLASH_INTERVAL_MS;
        is_on_cycle = (cycle_position % 2 == 0);
      }

      int lit_leds = 0;

      // Determine number of lit LEDs based on HP
      if (hp == 0) {
        lit_leds = 0;
      } else if (maxhp == 1) {
        lit_leds = leds_per_linear;
        hp_bar_colour = Colour::Green;
      } else {
        lit_leds = (int)ceilf(hp_percentage * (float)leds_per_linear);
        if (lit_leds < 1) lit_leds = 1;
        if (lit_leds > leds_per_linear) lit_leds = leds_per_linear;
      }

      // Convert colour to CRGB
      CRGB hp_colour = convert_to_crgb(hp_bar_colour);

      // Update LEDs based on lit_leds and flashing state
      for (int i = 0; i < leds_per_linear; i++) {
        if (i < lit_leds && is_on_cycle) {
          leds[start_led_index + i] = hp_colour;
        } else {
          leds[start_led_index + i] = CRGB::Black;
        }
      }
    } else if (animation->led_type == LedType::Ring) {
      render_colour_to_led(animation, animation->colour);
    } else if (animation->led_type == LedType::Indicator) {
      render_colour_to_led(animation, animation->colour);
    }

  } else if (animation_type == AnimationCategory::Blinking) {
    // flash interval CONSTANT (100ms)
    const int FLASH_INTERVAL_MS = 100;

    if (animation->led_type == LedType::Ring) {
      unsigned long time_elapsed = current_time_ms - animation->start_time_ms;

      unsigned long cycle_position = time_elapsed / FLASH_INTERVAL_MS;

      bool is_on_cycle = (cycle_position % 2 == 0);

      if (is_on_cycle) {
        render_colour_to_led(animation, animation->colour);
      } else {
        render_colour_to_led(animation, Colour::Black);
      }

    } else if (animation->led_type == LedType::Linear) {
      unsigned long time_elapsed = current_time_ms - animation->start_time_ms;

      unsigned long cycle_position = time_elapsed / FLASH_INTERVAL_MS;

      bool is_on_cycle = (cycle_position % 2 == 0);

      if (is_on_cycle) {
        render_colour_to_led(animation, animation->colour);
      } else {
        render_colour_to_led(animation, Colour::Black);
      }
    }  // else just in case
  } else if (animation_type == AnimationCategory::Wave) {
  }
}

// Function writes 4 raw segment values to the 7-seg display
void DisplayInterface::write4(uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3) {
  if (!sevenSegReady) return;

  sevenSeg.writeDigitRaw(0, d0);
  sevenSeg.writeDigitRaw(1, d1);
  sevenSeg.writeDigitRaw(3, d2);
  sevenSeg.writeDigitRaw(4, d3);
  sevenSeg.writeDisplay();
}
