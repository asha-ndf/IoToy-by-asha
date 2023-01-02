#include <arduino.h>
#include "modes.h"
#include "motor.h"

void mode_0(int i);
void mode_1(int i);
void mode_2(int i);
void mode_3(int i);
void mode_4(int i);
static int mymode = 0;
void subProcess(void * pvParameters) {
  while (1) {
    Serial.print("MODE:");

    Serial.println(mymode);
    for (int i = 0; i < 10000; i++) {
      //modeをRAM参照からレジスタ参照へ移行
      mymode = nowmode;
      if (mymode == 1) {
        mode_1(i);
      } else if (mymode == 2) {
        mode_2(i);
      } else if (mymode == 3) {
        mode_3(i);
      } else if (mymode == 4) {
        mode_4(i);
      } else if (mymode == 0) {
        mode_0(i);
      } else {
        mode_0(i);
      }
      if (i % 1000 == 0) {
        Serial.print(".");
      }
      delay(1);
    }
    Serial.println("");

  }
}


void mode_0(int i) {
  mOutF(0.0);
}

void mode_1(int i) {
  mOutF(1.0);
}

void mode_2(int i) {
  mOutF(-1.0);
}

void mode_3(int i) {
  int t = i % 1000;
  if (t < 480) {
    mOutF(1.0);
  } else if (t < 500) {
    mOutF(0.0);
  } else if (t < 980) {
    mOutF(-1.0);
  } else {
    mOutF(0.0);
  }
}

void mode_4(int i) {

}
