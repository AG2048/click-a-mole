/* BEGIN OF TESTING LEDS SMALLER VERSION */

// #include "led_interface.h"

// using namespace std;


//         // DisplayInterface(
//         //     unsigned short leds_per_ring, 
//         //     unsigned short leds_per_linear, 
//         //     unsigned short leds_per_mole_indicator,
//         //     unsigned short leds_per_heart, 
//         //     unsigned short number_of_leds,
//         //     unsigned short rings_data_pin,
//         //     unsigned short hearts_data_pin
//         //     //missing 7-seg and oled display info (data pins, # of leds)
//         // ); 



//         // void DisplayInterface::start_mole(int mole_id, int max_hp, unsigned long duration_ms, const Colour colour)


// DisplayInterface display(3, 3, 1, 1, 70, 5, 1);
// // const Colour colours[] = { Colour::Green, Colour::Green, Colour::Green, Colour::Green, Colour::Green};


// void setup() {
//   Serial.begin(9600);
//   //display.begin();
//   display.start_mole(1, 5, 5000, Colour::Green);


//   //display.win_round();
//   //display.lose_round();
//   //display.end_mole(1, false, true);
// }

// void loop() {
//   display.process_timed_animations(millis());
//   //display.end_mole(1, true, false);
//   //display.decrease_mole_hp(1, 4, 5);


  
// }

/* END OF TESTING LEDS SMALLER VERSION */

/* BEGIN OF TESTING LEDS */

// #include "led_interface.h"

// DisplayInterface display( 35, 1, 1, 1, 350, 4, -1);
// int printed = 0;

// void setup() {
  
//   //display.begin();        // <-- DO THIS FIRST
//   Serial.begin(9600);
//   //display.update_oled_gameplay(1, 2, 10);
  

//    display.start_mole(0, 3, 10000, Colour::HealerMole);
//   // display.start_mole(2, 3, 8000, Colour::HealerMole);
//   // display.start_mole(3, 3, 8000, Colour::HealerMole);
//   // display.start_mole(4, 3, 8000, Colour::HealerMole);
//   // display.start_mole(5, 3, 8000, Colour::HealerMole);
//   // display.start_mole(6, 3, 8000, Colour::HealerMole);
//   // display.start_mole(7, 3, 8000, Colour::HealerMole);
//   // display.start_mole(8, 3, 8000, Colour::HealerMole);
//   // display.start_mole(9, 3, 8000, Colour::HealerMole);
//   Serial.println("SETUP TIME: ");
//   Serial.println(millis());
// }

// void loop() {

//   display.process_timed_animations(millis());

//   // if (millis() > 2000 && millis() < 2010){
//   //   //display.end_mole(1, true, false);
//   //   //display.decrease_mole_hp(1, 2, 3);
//   //    display.lose_game();
//   // }

//   if (millis() > 5000 && millis() < 5010){
//     display.decrease_mole_hp(0, 1, 3);
//   }


//   if (millis() > 7000 && millis() < 7010){
//     display.end_mole(0, false, true);
//   }

//   if (millis() > 7990 && millis() < 8000){
//     display.lose_game();

//   }




//   // if (display.isMoleAnimationDone(1) && printed == 0){
//   //   printed ++;
//   //   Serial.println("AFTER MOLE END: ");
//   //   Serial.println(millis());
//   // }

// }

/* END OF TESTING LEDS */

/* BEGIN OF TESTING ROTARY AND OLED */

// #include "led_interface.h"

// DisplayInterface display(1, 1, 1, 1, 1, 4, 1);
// int printed = 0;

// #define output_A 2
// #define output_B 3


// const int button_pin = 5;
// int last_button_reading  = HIGH;
// int prev_button_state    = HIGH;
// unsigned long last_debounce_ms = 0;
// const unsigned long DEBOUNCE_MS = 40;

// int accumulated_delta = 0;
// int final_score = 0;

// bool button_pressed() {               
//   int current_reading = digitalRead(button_pin);

//   if (current_reading != last_button_reading) {
//     last_debounce_ms    = millis();
//     last_button_reading = current_reading;
//   }

//   if ((millis() - last_debounce_ms) > DEBOUNCE_MS) {
//     if (prev_button_state == HIGH && current_reading == LOW) {
//       prev_button_state = current_reading;
//       Serial.println("Button Pressed");
//       return true;
//     }
//     prev_button_state = current_reading;
//   }
//   return false;
// }

// int read_encoder_delta() {
//   static int last_encoded = 0b11;

//   int A = digitalRead(output_A);
//   int B = digitalRead(output_B);
//   int encoded = (A << 1) | B;

//   int delta = 0;
//   int transition = (last_encoded << 2) | encoded;

//   switch (transition) {
//     case 0b1110: case 0b1000: case 0b0001: case 0b0111:
//       delta = 1;
//       break;
//     case 0b1101: case 0b0100: case 0b0010: case 0b1011:
//       delta = -1;
//       break;
//   }

//   last_encoded = encoded;
//   return delta;
// }

// void setup() {
  
//   pinMode(output_A,   INPUT_PULLUP);
//   pinMode(output_B,   INPUT_PULLUP);
//   pinMode(button_pin, INPUT_PULLUP);

//   Serial.begin(9600);
//   delay(1000);  // give Serial time to connect
//   Serial.println("Starting...");
  
//   display.begin();
//   Serial.println("Begin done");

//   //display.show_idle_oled_animation();
//   //display.show_leaderboard_qr();
//   //display.begin_leaderboard_entry(final_score);
//   //display.update_oled_gameplay(1, 2, 3);
//   //display.clear_display();
//   Serial.println("HI");


// }

// void loop() {

//   //display.process_timed_animations(millis());

  
//   //display.process_timed_animations(millis());
//   accumulated_delta += read_encoder_delta();

//   int delta_to_send = 0;
//   if (accumulated_delta >= 4) {
//     delta_to_send = 1;
//     accumulated_delta -= 4;
//   } else if (accumulated_delta <= -4) {
//     delta_to_send = -1;
//     accumulated_delta += 4;
//   }

//   bool btn = button_pressed();

//   if (delta_to_send != 0 || btn) {
//     bool entry_done = display.update_leaderboard_entry(delta_to_send, 0, btn);
//     if (entry_done) {
//       Serial.println("done");
//     }
//   }
// }

/* END OF TESTING ROTARY AND OLED */

/*END OF TESTING REFACTORED OLED AND ENCODER*/

#include "led_interface.h"

DisplayInterface display(1, 1, 1, 1, 1, 4, 1);
int final_score = 0;


void setup() {
  

  Serial.begin(9600);
  delay(1000);  // give Serial time to connect
  Serial.println("Starting...");
  
  display.begin();
  Serial.println("Begin done");

  display.show_idle_oled_animation();
  //display.show_leaderboard_qr();
  //display.begin_leaderboard_entry(final_score);
  //display.update_oled_gameplay(1, 2, 3);
  //display.clear_display();
  Serial.println("HI");


}

void loop() {

  display.process_timed_animations(millis());
  //display.encoder_to_leaderboard();

  }

/*END OF TESTING REFACTORED OLED AND ENCODER*/