#include <arduino.h>
#include "motor.h"

static int res = 8; // 解像度8bit
static float limiter = 3.3 / 5.0; //( 3.3V / 5.0V)
static int lim = pow(2, res) * limiter; //ledcWriteの上限

void initMotor(int pin1, int pin2) {
  //channel, 周波数, 解像度8bit
  ledcSetup(0, 12800, res);
  ledcSetup(1, 12800, res);
  ledcAttachPin(pin1, 0);
  ledcAttachPin(pin2, 1);
  ledcWrite(0, 0);
  ledcWrite(1, 0);
  Serial.println("initMotor");
  Serial.print(pin1);
  Serial.print(",");
  Serial.println(pin2);
  Serial.print("limiter: ");
  Serial.print((int)(limiter * 100.0) % 100);
  Serial.println("%");
}

void mOutInt(int level) {
  //下限・上限セット
  if (level > lim) {
    level = lim;
  } else if (level < -lim) {
    level = -lim;
  }
  if (level > 0) {
    ledcWrite(0, level);
    ledcWrite(1, 0);
  } else {
    ledcWrite(0, 0);
    ledcWrite(1, -level);
  }
}
void mOutF(float level) {
  int intlevel = (int)(level * (float)res);
  mOutInt(intlevel);
}
