#include <Wire.h>
#include <MPR121.h>
#include <SoftwareSerial.h>

SoftwareSerial toR4(0, 1); // RX pin is not used here, TX is pin 4

void setup() {
  Serial.begin(115200); // Debugging via Serial Monitor
  toR4.begin(9600);     // Send data to Arduino Uno R4

  if (!MPR121.begin(0x5C)) {
    Serial.println("MPR121 not found");
    while (1);
  }
  Serial.println("Touch Board Ready");
}

void loop() {
  MPR121.updateAll();
  for (int i = 0; i < 12; i++) {
    if (MPR121.isNewTouch(i)) {
      toR4.print("touch ");
      toR4.println(i);
    }
    if (MPR121.isNewRelease(i)) {
      toR4.print("release ");
      toR4.println(i);
    }
  }
  delay(10);
}
