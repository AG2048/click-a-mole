#include "led_interface.h"

using namespace std;


DisplayInterface display(3, 7, 0, 16, 4, -1);
const Colour colours[] = { Colour::Green, Colour::Green, Colour::Green, Colour::Green, Colour::Green};



void setup() {
  Serial.begin(9600);
  display.start_mole(1, 5, 5000, colours, 5);


  //display.win_round();
  //display.lose_round();
  //display.end_mole(1, false, true);
}

void loop() {
  display.process_timed_animations(millis());
  delay(1000);
  display.change_mole_hp(1, 1, 5);
  
}