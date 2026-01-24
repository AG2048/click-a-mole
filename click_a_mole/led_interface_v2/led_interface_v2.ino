#include "led_interface.h"

DisplayInterface display(9, 5, 1, 1, 16, 4, 1);

void setup() {
  display.begin();        // <-- DO THIS FIRST
  display.show_score(10);
}

void loop() {
  display.process_timed_animations(millis());
}
