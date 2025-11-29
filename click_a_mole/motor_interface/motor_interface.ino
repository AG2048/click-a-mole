// setup file for testing

#include "MoleController.h"
#include "MoleModule.h"

MoleController controller;

void setup() {
  Serial.begin(9600);
  delay(500);

  controller.addModule(
    new MoleModule(
      {22, &PORTA, (1 << PA0)},   // pul
      {23, &PORTA, (1 << PA1)},   // dir
      30,                         // button
      0                           // mux channel
    )
  );

  controller.addModule(
    new MoleModule(
      {24, &PORTA, (1 << PA2)},   // pul
      {25, &PORTA, (1 << PA3)},   // dir
      31,                         // button
      1                           // mux channel
    )
  );

  controller.init();
}

int hp[2] = {0, 0};
void loop() {
  controller.updateAll();

  int buttons[2];
  controller.readButtons(buttons);

  if (buttons[0]) hp[0] = (hp[0] + 1) % 10;
  if (buttons[1]) hp[1] = (hp[1] + 1) % 10;

  controller.setHp(0, hp[0], 10);
  controller.setHp(1, hp[1], 10);
}
