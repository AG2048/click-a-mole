#include "led_interface.h"

DisplayInterface display(8, 5, 1, 1, 16, 4, 1);
using namespace std;

void setup() {
  Serial.begin(9600);
  //display.start_mole(1, 5, 2000, Colour::Green);
}

void loop() {
  // delay(300);
  // display.change_mole_hp(1, 3, 5);
  // display.process_timed_animations(millis());

}