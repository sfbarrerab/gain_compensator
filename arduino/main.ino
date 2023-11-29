#include <Arduino_FreeRTOS.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  //Serial.setTimeout(1);
}

void loop() {
  // put your main code here, to run repeatedly: 
  while (!Serial.available());
  double x = Serial.readString().toInt();
  Serial.println(x + 1);
}
x