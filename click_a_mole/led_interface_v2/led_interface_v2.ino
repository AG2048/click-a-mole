#include "led_interface.h"

DisplayInterface display(9, 5, 1, 1, 16, 4, 1);

void setup() {
  display.begin();        // <-- DO THIS FIRST

  Serial.begin(9600);

  display.show_idle_oled_animation();
}

void loop() {
  //display.process_timed_animations(millis());
}
