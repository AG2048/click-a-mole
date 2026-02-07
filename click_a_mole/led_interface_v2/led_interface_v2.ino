#include "led_interface.h"

#define output_A 6
#define output_B 7

DisplayInterface display(9, 5, 1, 1, 16, 4, 1);

/*possible issues*/
/*
  1. fill_index doesn't reset; need a function to reset everything
  2. button might be LOW as pressed

*/

/*ROTARY ENCODER VARIABLES*/
int hovered_index = 0;
int current_A_state;
int prev_A_state;
int fill_index = 0;

char name_letters[4] = {'_', '_', '_', '\0'};
/*END OF ROTARY ENCODER VARIABLES*/

/*BUTTON VARIABLES*/
const int button_pin = 2; // this button is on the rotary encoder
int last_button_reading = LOW;
int prev_button_state = LOW;
unsigned long last_debounce_ms = 0;
const unsigned long DEBOUNCE_MS = 40;
/*END BUTTON VARIABLES*/

/*FINAL SCORE??*/
int final_score = 0;

/*HELPER FUNCTIONS*/

void redraw_entry_menu(){
  char hovered_letter = (char) ('A' + hovered_index);

  display.entering_names_to_leaderboard(hovered_letter, name_letters[0], name_letters[1], name_letters[2], final_score, fill_index, false);
}

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

  prev_A_state = digitalRead(output_A);

  last_button_reading = digitalRead(button_pin);
  prev_button_state = last_button_reading; // HIGH OR LOW, high is pressed down
}

void loop() {

  /*START ROTARY ENCODER*/
  current_A_state = digitalRead(output_A);

  if (current_A_state != prev_A_state){
    if (digitalRead(output_B) != current_A_state){
      
      // Clockwise
      if (hovered_index == 25){
        hovered_index = 0;
      } else {
        hovered_index ++;
      }

    } else {

      // Counterclockwise
      if (hovered_index == 0){
        hovered_index = 25;
      } else {
        hovered_index --;
      }
    }

    redraw_entry_menu();
    prev_A_state = current_A_state; 
  }

  /*END ROTARY ENCODER*/

  /*START BUTTON*/

  // when button is pressed, 
  // the letter thats currently selected should be saved

  if (button_pressed()){
    char hovered_letter = (char)('A' + hovered_index);
    name_letters[fill_index] = hovered_letter;

    if (fill_index < 2){ 
    // if the fill index is < 2, we can move to the next spot
      fill_index ++;
      redraw_entry_menu();
    } else {
      // save on the third push
      display.entering_names_to_leaderboard(hovered_letter, name_letters[0], name_letters[1], name_letters[2], final_score, fill_index, true);
    }
  }


  /*END BUTTON*/

}
