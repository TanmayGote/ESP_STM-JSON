#include "Wire.h"
#include <MPU6050_light.h>

MPU6050 mpu(Wire);
unsigned long timer = 0;
double z;
String tosend = "";
void setup() {
  Serial.begin(9600);
  Serial2.begin(38400);
  Wire.begin();
  
  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while(status!=0){ }
  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);
  mpu.calcOffsets();
  Serial.println("Done!\n");
}

void loop() {
  mpu.update();
  
    if((millis()-timer)>10){
    Serial.print("\tZ : ");
    z = mpu.getAngleZ();
    timer = millis();  
    Serial.println(z);
    tosend = (String)z;
    Serial2.println(tosend);
  }
}
