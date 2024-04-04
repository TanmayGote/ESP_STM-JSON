#include <ArduinoJson.h>
#include "Wire.h"
#include <MPU6050_light.h>
#include <BluetoothSerial.h>

MPU6050 mpu(Wire);
byte status = mpu.begin();
long timer = 0;
char formattedString[11];
String jsonString = "";

String str = " ";
DynamicJsonDocument doc(1024);

#define resetpin 15

void setup() {

  Serial.begin(38400);
  Serial1.begin(38400, SERIAL_8N1, 18, 19);
  Serial2.begin(38400);
  Wire.begin();
  byte status = mpu.begin();
  while (status != 0) {}
  mpu.calcOffsets();
  mpu.calcOffsets(true, true);
}

void loop() {
  mpu.update();
  // doc["Loc"] = (int)mpu.getAngleZ();
  if ((millis() - timer) > 10) {
    // Cast MPU6050 values to integers
    float Val = mpu.getAngleZ();
    int Z = static_cast<int>(Val);
    sprintf(formattedString, "%04d", Z);
    doc["Z"] = formattedString;
  }

  timer = millis();
  
  serializeJson(doc, jsonString);
  // Serial2.print(jsonString);
  Serial1.print(jsonString);
  Serial.println(jsonString);
  // Serial.println(jsonString.length());
  doc.clear();
  Serial1.flush();
  // Serial2.flush();
  delay(10);
}
