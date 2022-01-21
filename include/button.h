#include "Global.h"

//чтение запись в епром ///////////////////////////////////////////////
 float EEPROM_float_read(int addr) {    //чтение из епром
  byte raw[4];
  for (byte i = 0; i < 4; i++) raw[i] = EEPROM.read(addr + i);
  float &num = (float&)raw;
  return num;
 }
 void EEPROM_float_write(int addr, float num) {   // запись в  епром
  if (EEPROM_float_read(addr) != num) { //если сохраняемое отличается
    byte raw[4];
    (float&)raw = num;
    for (byte i = 0; i < 4; i++) EEPROM.write(addr + i, raw[i]);
  }
  EEPROM.commit();
 }  
 
 
///////////////////////////////////////////////////////////////////////////
void button_read() {//функция проверки нажатия кнопки
  button_minus = digitalRead(button_minus_pin); //запоминаем значение кнопки
  button_plus = digitalRead(button_plus_pin); //запоминаем значение кнопки
  button_enter = digitalRead(button_enter_pin); //запоминаем значение кнопки
  if (!button_minus || !button_plus || !button_enter);
  wdt_reset();
}

//установка влажности вручную/////////////////////////////////////////////////////

void hum_setup() {
  delay(del); 
  
  button_read();
  lcd.setCursor(0, 0);
  lcd.print("hum SET ");   //выводим на экран
  delay(1000);             //ждём секунду
  lcd.clear();             //очищаем экран
  int x = 0;
  while (1) {
    x++;
    if (x > interval) break;
    button_read();
    
    EEPROM_float_read(12 + U_hum);   //чтение из епром из 12 ячейки значение переменной u_hum
    
    if (!button_enter) {
      delay(del);
      lcd.clear(); //очищаем экран
      break;
    }
    
    if (!button_plus) {
      x = 0;
      EEPROM_float_write(12, U_hum += 1);   //если была нажата кнопка плюс пишем в памятьзначение переменной +1
      if (U_hum >= 100) {     //проверяем, если выше 100,
        EEPROM_float_write(12, 100);  //пишем в память 100
      }
      lcd.clear();          //очищаем экран
    }
    
    if (!button_minus) {
      x = 0;
      EEPROM_float_write(12, U_hum -= 1);  //если была нажата кнопка минус пишем в памятьзначение переменной -1
      if (U_hum <= 0) {     //проверяем, если ниже 0,
        EEPROM_float_write(12, 0);  //пишем в память 0
      }
      lcd.clear();        //очищаем экран
    }
    
    EEPROM_float_read(12 + U_hum);    //чтение из епром из 12 ячейки значение переменной u_hum
    //EEPROM.commit();
    lcd.setCursor(0, 0);
    lcd.print("hum SET ");
    if (U_hum < 100)lcd.print(U_hum, 0);
    //if (U_hum > 0)lcd.print(U_hum);
    lcd.setCursor(1, 1);
    lcd.print("minus NEXT plus");
    delay(del);
  }
}

//установка температуры вручную/////////////////////////////////////////////////////

void U_temp_setup() {
  delay(del);
  
  button_read();
  lcd.setCursor(0, 0);
  lcd.print("tem SET " );
  delay(1000);
  lcd.clear();
  int x = 0;
  while (1) {
    x++;
    if (x > interval) break;
    button_read();
    //EEPROM_float_read(4) != U_temp;
    EEPROM_float_read(8 + U_tem);
    if (!button_enter) {
      delay(del);
      lcd.clear(); //очищаем экран
      break;
    }
    
    if (!button_plus) {
      x = 0;
      EEPROM_float_write(8, U_tem += .1);
      if (U_tem >= 40) {     //проверяем, если выше 13,
        EEPROM_float_write(8, 40);  //пишем в память 13
      }
      lcd.clear();
    }
    
    if (!button_minus) {
      x = 0;
      EEPROM_float_write(8, U_tem -= .1);
      if (U_tem <= 30) {     //проверяем, если ниже 0,
        EEPROM_float_write(8, 30);  //пишем в память 0
      }
      lcd.clear();
    }
    
    EEPROM_float_read(8 + U_tem);
    lcd.setCursor(0, 0);
    lcd.print("tem SET " );
    if (U_tem < 40)lcd.print(U_tem, 1);
    //if (U_tem  > 0)lcd.print(U_tem, 1 );
    lcd.setCursor(1, 1);
    lcd.print("minus NEXT plus");
    delay(del);
  }
}

 
//устанавливаем поворот///////////////////////////////////////////////
 
void turn_setup() {        
  //int turnPeriod;

  delay(del);
  button_read();
  lcd.setCursor(4, 0);
  lcd.print("turn SET");
  delay(1000);
  lcd.clear();
  int x = 0;
  while (1) {
    x++;
    if (x > interval) {
      break;
    }
    button_read();
    EEPROM_float_read(16 + turnPeriod);
    if (!button_enter) {
      delay(del);
      lcd.clear(); //очищаем экран
      break;
    }
    if (!button_plus) {
      x = 0;
      EEPROM_float_write(16, turnPeriod += 1);
      if (turnPeriod >= 13) {     //проверяем, если выше 13,
        EEPROM_float_write(16, 13);  //пишем в память 13
      }
      lcd.clear();
    }
    if (!button_minus) {
      x = 0;
      EEPROM_float_write(16, turnPeriod -= 1);
      if (turnPeriod <= 0) {     //проверяем, если ниже 0,
        EEPROM_float_write(16, 0);  //пишем в память 0
      }
      lcd.clear();
    }
    EEPROM_float_read(16 + turnPeriod);
    lcd.setCursor(0, 0);
    lcd.print("PERIOD = ");
    if (turnPeriod < 13)lcd.print(turnPeriod);
    if (turnPeriod > 12) lcd.print("RND");
    lcd.setCursor(1, 1);
    lcd.print("minus NEXT plus");
    delay(del);
  }
 
}


//выбираем из памяти птицу///////////////////////////////////////
void birdSelect() {
  //int birdType;
  EEPROM_float_read(20 + birdType);
  lcd.setCursor(0, 0);
  lcd.print("BIRD - ");
  switch (birdType) {
    case 0:
      //lcd.print("CHICK");  // курица
      birdPrint = "CHICK";
      break;
    
    case 1:
      //lcd.print("TURKEY"); // индюк
      birdPrint = "TURKEY";
      break;
  }
}

//выбираем птицу /////////////////////////////////////////////////////////
void bird_setup() {
  //int birdType;
  lcd.clear();
  delay(del);
  button_read();
  //birdSelect();
  lcd.setCursor(4, 0);
  lcd.print("bird SET");
  delay(1000);
  lcd.clear();
  int x = 0;
  while (1) {
    x++;
    if (x > interval) {
      break;
    }
    button_read();
    EEPROM_float_read(20 + birdType);
    if (!button_enter) {
      delay(del);
      lcd.clear(); //очищаем экран
      break;
    }
    if (!button_plus) {
      x = 0;
      if (birdType >= 1)      //проверяем, если выше или равно 5,
        EEPROM_float_write(20, 0);  //пишем в память 0
      else EEPROM_float_write(20, birdType += 1);
      lcd.clear();
    }
    if (!button_minus) {
      x = 0;
      if (birdType <= 0)      //проверяем, если ниже или равно 0,
        EEPROM_float_write(20, 1);  //пишем в память 1
      else EEPROM_float_write(20, birdType -= 1);
      lcd.clear();
    }
    birdSelect();
    
    lcd.setCursor(6, 0);
    lcd.print(birdPrint);
    lcd.setCursor(1, 1);
    lcd.print("minus NEXT plus");
    delay(del);
  }
}
 
// записываем в память день начала инкубации в юникс-формате//////////
void startInk() {
  //unsigned int currentTime_day;
  //unsigned int memoryDay;
  //DateTime rtc = rtc.now();
  //currentTime_day = (now.unixtime() / 86400L);
  //memoryDay = EEPROM_float_read(1);

  delay(del);
  button_read();
  lcd.setCursor(0, 0);
  lcd.print("START INK");
  delay(1000);
  lcd.clear();
  int x = 0;
  while (1) {
    x++;
    if (x > interval) break;
    button_read();
    EEPROM_float_read(4 +  memoryDay);
    
    if (!button_enter) {
      delay(del);
      lcd.clear(); //очищаем экран
      break;
    }
    if (!button_minus) {
      EEPROM_float_write(4, memoryDay += 1);
      lcd.clear();
    }
    if (!button_plus) {
      EEPROM_float_write(4, memoryDay -= 1);
      lcd.clear();
    } 
    EEPROM_float_read(4 + memoryDay);
    lcd.setCursor(5, 0);
    lcd.print("DAY = ");
    lcd.print(currentTime_day - memoryDay);
    lcd.setCursor(2, 1);
    lcd.print("ZERO START +1");
    delay(del);
  }
}

//управляем поворотом/////////////////////////////////////////////////////
void turn(boolean needTurn) {
  //int turnPeriod;                //период поворота лотков в часах
  int turnCommand;
  EEPROM_float_read(16 + turnPeriod);
  
  lcd.setCursor(12, 0);
  lcd.print("R");
  if (turnPeriod == 0)
  { lcd.print("OFF");
    return;           //если нулевой период поворота, то не поворачиваем яйца.
  }
  if (turnPeriod < 13) turnCommand = turnPeriod;
  else if (turnPeriod > 12 && turnFlag == 0) { //если произошел поворот (сброшен флаг) и значение в памяти 13, то
    turnCommand = random(1, 6);        //берем случайное значение часов 1-6
    turnFlag = 1;                     //защелкиваем флаг вычисления случайных значений до следующего поворота
  }
  currentTime = millis() / 1000;


  lcd.print((loopTime - currentTime + turnCommand * 3600UL) / 60UL);
  lcd.print("m");

  if (needTurn == true) {
    if (currentTime > (loopTime + turnCommand * 3600UL)) {  // 3600000 сравниваем текущий таймер с переменной loopTime + период поворота в часах.
      digitalWrite(turn_pin, !digitalRead(turn_pin));       // включаем/выключаем реле поворота
      loopTime = currentTime;    // в loopTime записываем новое значение
      turnFlag = 0;    //сбрасываем флаг поворота
    }
    //lcd.print((loopTime - currentTime + turnCommand * 3600UL) / 60UL);
    //lcd.print(" ");
  }
}


//пищалка////////////////////////////////////////////////////////////////////////
void beeper(int duration) {
  tone(beeper_pin, 2000, duration);
}
