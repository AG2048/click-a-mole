// setup file for testing

#include "MoleController.h"
#include "MoleModule.h"

MoleController controller;

void setup() {
  Serial.begin(9600);

  Serial.println("Setup delay");
  Serial.println("Setup addModule");

  controller.init();

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

  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("Setup init");
  // delay(500);

  controller.startTimer();
  Serial.println("Setup complete");
}

int hp[8] = {0};
int buttons[8];
int i = 0;
void loop() {
  // if (i % 10 == 0) {
  //   Serial.println("-----");
  //   Serial.print("Loop: ");
  //   Serial.println(i);
  // }

  controller.updateAll();
  controller.readButtons(buttons);

  for (int j = 0; j < 8; j++) {
    if (i % 100 == 0) hp[j] = (hp[j] + 1) % 10;
    controller.setHp(j, hp[j], 10);
  }

  // if (buttons[0]) hp[0] = (hp[0] + 1) % 10;
  // if (buttons[1]) hp[1] = (hp[1] + 1) % 10;

  // if (i%200==0) hp[0] = (hp[0] + 1) % 10;
  // if (i%200==0) hp[1] = (hp[1] + 1) % 10;

  // controller.setHp(0, hp[0], 10);
  // controller.setHp(1, hp[1], 10);
  
  // if (i % 10 == 0) {
  //   Serial.print((hp[0]/10)*360);

  //   Serial.print("Buttons: ");
  //   Serial.print(buttons[0]);
  //   Serial.print(", ");
  //   Serial.println(buttons[1]);

  //   Serial.print("HP: ");
  //   Serial.print(hp[0]);
  //   Serial.print(", ");
  //   Serial.println(hp[1]); 
  // }

  i++;
  delay(5);
}