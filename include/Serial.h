#include "Global.h"


/// шлем данные в порт //////////////////////////////////////////////
void SerialSend() {
  //Serial.print(millis() / 1000);
  //  Serial.print("PID ");
  //  Serial.print(Setpoint);
  //  Serial.print(" ");
  //  Serial.print(Input);
  //  Serial.print(" ");
  //  Serial.print(Output);
  //  Serial.print(" ");
  //  Serial.print(myPID.GetKp());
  //  Serial.print(" ");
  //  Serial.print(myPID.GetKi());
  //  Serial.print(" ");
  //  Serial.print(myPID.GetKd());
  //  Serial.print(" ");
  //  if (myPID.GetMode() == AUTOMATIC) Serial.print("Automatic");
  //  else Serial.print("Manual");
  //  Serial.print(" ");
  //  if (myPID.GetDirection() == DIRECT) Serial.println("Direct");
  //  else Serial.println("Reverse");

  delay(5);
  Serial.print("~Mink/set ");
  Serial.print(U_tem);
  Serial.print("^~Mink/outpwr ");
  Serial.print(Output / 10);
  Serial.print("^~Mink/t1 ");
  Serial.print(Input);
  Serial.print("^~Mink/hum ");
  Serial.println(hum);

  //Serial.print("^~Mink/alarm ");
  //Serial.print(digitalRead(alarm_pin));
  //Serial.print("^~Mink/extheat ");

  //Serial.print(digitalRead(extend_heater_pin));
  //Serial.print("^~Mink/fan ");
  //Serial.print(digitalRead(fan_pin));

  //Serial.print("^~Mink/door ");
  //Serial.println(!digitalRead(door_pin));
}
