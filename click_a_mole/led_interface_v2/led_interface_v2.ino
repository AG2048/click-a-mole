#include "led_interface.h"

DisplayInterface display(9, 5, 1, 1, 16, 4, 1);
using namespace std;

void setup() {
  Serial.begin(9600);
  display.show_score(10);
  //display.start_mole(1, 2, 5000, Colour::Green);
  //display.change_mole_hp(1, 1, 2);
  //display.process_timed_animations(millis());
}

void loop() { 
  //display.process_timed_animations(millis());


}