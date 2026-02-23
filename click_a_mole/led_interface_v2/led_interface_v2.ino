#include "led_interface.h"

#define output_A 2
#define output_B 3

DisplayInterface display(9, 5, 1, 1, 16, 7, 1);

/*possible issues*/
/*
  1. fill_index doesn't reset; need a function to reset everything
  2. button might be LOW as pressed

*/

/*BUTTON VARIABLES*/
const int button_pin = 4; // this button is on the rotary encoder
int last_button_reading = LOW;
int prev_button_state = LOW;
unsigned long last_debounce_ms = 0;
const unsigned long DEBOUNCE_MS = 40;
/*END BUTTON VARIABLES*/

/*FINAL SCORE??*/
int final_score = 0;

/*HELPER FUNCTIONS*/

bool button_pressed(){
  int current_button_reading = digitalRead(button_pin);

  if (current_button_reading != last_button_reading){ // if button was pressed or released
    last_debounce_ms = millis();
    last_button_reading = current_button_reading;

  }

  if ((millis() - last_debounce_ms) > DEBOUNCE_MS){ // only use signal if its be stable for debounce_ms 
  
    // pressed down (low -> high)
    if (prev_button_state == LOW && current_button_reading == HIGH){
      prev_button_state = current_button_reading;
      return true; // button has been pressed
    }

    prev_button_state = current_button_reading;

  }

  return false;

} 

void setup() {
  pinMode(output_A, INPUT);
  pinMode(output_B, INPUT);
  pinMode(button_pin, INPUT);
  
  display.begin();        // <-- DO THIS FIRST

  Serial.begin(9600);
  Serial.println("start");

  last_button_reading = digitalRead(button_pin);
  prev_button_state = last_button_reading; // HIGH OR LOW, high is pressed down
  Serial.println("bye");

  display.show_idle_oled_animation();

  Serial.println("hi");
  // Call when transitioning into name-entry mode (e.g. after game ends)
  display.begin_leaderboard_entry(final_score);
}

void loop() {
  bool entry_done = display.update_leaderboard_entry(
    digitalRead(output_A),
    digitalRead(output_B),
    button_pressed()
  );

  if (entry_done){
    // Entry saved — transition to next game state here
    display.show_idle_oled_animation(); // placeholder for whatever's next
  }
}
