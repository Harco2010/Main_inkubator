#pragma once
#include <Arduino.h>
#include "Global.h"

//управляем влажностью///////////////////////////////////////////////////////////////
void humidifer() {
  //float humidity;
  unsigned long humMillis = 0;
  unsigned long curMillis = millis();
    //if (curMillis - humMillis >= humStep) {
    //  humMillis = curMillis;
  //    //humidity = sht1x.readHumidity();
   // }
  if (U_hum > hum) digitalWrite(humidifer_pin, HIGH); //сравниваем измеренную влажность с заданной
  if (U_hum < hum + h_histeresis) digitalWrite(humidifer_pin, LOW);
} 