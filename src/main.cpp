//Термостат для инкубатора или PID регулятор на arduino
/// датчик температуры,влажности SI7021, LCD1602

#include <Arduino.h> 
//#include "main.h" 

  

#include "Global.h"
#include "web.h"
#include "humidat.h"
#include "button.h"
#include "menu.h"
#include "Serial.h"
#include "config.h"

void EEPROM_commit() {
  if (NeedCommit) {
    EEPROM.commit();
    NeedCommit = false;
  }
}

//DateTime now = rtc.now();

void setup() {
   Serial.begin(115200);   // Инициализируем вывод данных на серийный порт со скоростью 9600 бод
   
   #ifdef ESP8266
    Wire.begin(SDA, SCL);    // Инициализируем выход i2c
   #else
    Wire.begin();
   #endif
   
   if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }
   if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    
  }
   ESP.wdtEnable(WDTO_8S); //взводим сторожевой таймер на 8 секунд.
   
   EEPROM.begin(512);
   //sp = EEPROM_float_read(0);
   startDayUnixtime = EEPROM_float_read(4);
   memoryDay = EEPROM_float_read(4);
   U_tem = EEPROM_float_read(8);   //читаем установленную температуру из епром
   U_hum = EEPROM_float_read(12);   //читаем установленную влажность из епром
   turnPeriod = EEPROM_float_read(16);
   birdPrint = EEPROM_float_read(20);
   birdType = EEPROM_float_read(20);
   startDayUnixtime = EEPROM_float_read(4);
 

   Serial.println("Терморегулятор");

   lcd.init();             //инициализация дисплея
   lcd.backlight();        //включаем подсветку
   lcd.setCursor(4,0); //ставим курсор на 4 символ 1 строки
   lcd.print("INKUBATOP"); //выводим текст 
   // millis();
   //delay(50);
   //lcd.clear(); 
   pinMode(button_minus_pin, INPUT_PULLUP); //подтягиваем входы кнопок к плюсу встроенными резисторами
   pinMode(button_plus_pin, INPUT_PULLUP);
   pinMode(button_enter_pin, INPUT_PULLUP);
   pinMode(RELAY_PIN, OUTPUT);      //переводим порт нагрева в выход
   pinMode(humidifer_pin, OUTPUT);      //переводим порт реле влажности в выход 
   
   reg.setDirection(NORMAL);       // направление регулирования (NORMAL/REVERSE). ПО УМОЛЧАНИЮ СТОИТ NORMAL
   reg.setLimits(0, 255);          // пределы (ставим для 8 битного ШИМ). ПО УМОЛЧАНИЮ СТОЯТ 0 И 255
   //reg.setpoint;            // сообщаем регулятору температуру, которую он должен поддерживать
   reg.setpoint = U_tem;
   // в процессе работы можно менять коэффициенты
   reg.Kp = 5.2;
   reg.Ki += 0.5;
   reg.Kd = 0.1;
    
      
                    //подключитесь к локальной сети Wi-Fi
  WiFi.begin(ssid, password);
                    //проверьте, подключен ли Wi-Fi к сети Wi-Fi
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());
  lcd.setCursor(3,1); //ставим курсор на 4 символ 1 строки
  lcd.print(WiFi.localIP()); //выводим текст 
  delay(5000);
  lcd.clear();
  webstr();
  
}  

void loop() {
   ftpSrv.handleFTP();    //ftp сервер работа
   
   DateTime now = rtc.now();
   currentTime_day = (now.unixtime() / 86400L);
   
   
   
   
   int bird;       // выбор птицы
   int r_array[2][4][4] = {
    {{2, 382, 650, 1}, {12, 377, 540, 1}, {18, 374, 480, 1}, {20, 371, 855, 0}},  // chick
    {{6, 379, 560, 1}, {12, 376, 530, 1}, {26, 373, 520, 1}, {30, 370, 855, 0}},  // turkey
  };
   
   EEPROM_float_read(8 + U_tem);
   button_read();
  if (!button_enter) {
    delay(del);
    lcd.clear();
    menu();
    lcd.clear();
  }
  if (!button_minus) {
    delay(del);
    lcd.clear();
   // alarmDelay = millis();    // задержка аварии по нажатии кнопки Минус
  }
  if (!button_plus) {
    delay(del);
    lcd.clear();
    digitalWrite(turn_pin, !digitalRead(turn_pin));       // включаем/выключаем реле поворота по кнопке Плюс
  }
  if (!button_plus && !button_plus) {
    delay(del);
    lcd.clear();
    // bottomView = !bottomView;       // переключаем режим показа нижней строки.
  }
  
  if (millis() > serialTime * 5) {
    
    serialTime += 500;
  }
  

  EEPROM_float_read(20 + bird);
  for (int d = 3; d >= 0; d--) {
    if (currentDay < r_array[bird][d][0]) {
      U_tem = float(r_array[bird][d][1] / 10.0);
      U_hum = float(r_array[bird][d][2] / 10.0);
      needTurn = r_array[bird][d][3];
    }
  }
  
   
  temp = sensor.GY21_Temperature();
  hum = sensor.GY21_Humidity();
  reg.input = temp;
  Input = temp;
  
  EEPROM_float_read(4 + startDayUnixtime);
  currentDay = (currentTime_day - startDayUnixtime);
  //EEPROM_float_read(20 + birdPrint);
  //birdSelect();
  lcd.setCursor(0, 0);
  lcd.print("T=");
  lcd.print(Input, 1);
  lcd.setCursor(6, 0);
  lcd.print("H");
  lcd.print(hum, 0);
  lcd.print("D");
    //if (currentDay > 100) lcd.print("99");
  lcd.print(currentDay);      // текущий день инкубации  else
  lcd.setCursor(0, 1);  
  lcd.print("T=");
  lcd.print(U_tem, 1);
  lcd.setCursor(6, 1);  
  lcd.print("H");
  lcd.print(U_hum, 0);
  lcd.setCursor(10, 1);
  lcd.print( birdPrint);
  //lcd.print(reg.getResultTimer());
  //lcd.print("mS "); 
  //lcd.print("%  ");    
  //lcd.setCursor(14, 0);
  //lcd.print("P");
  //lcd.print(map(reg.getResultTimer(), 0, WindowSize, 0, 100));


 //////////////////////////////////////////////////////////
  ws.cleanupClients();                                                 // Обработчик HTTP-событий (отлавливает HTTP-запросы к устройству и обрабатывает их в соответствии с выше описанным алгоритмом)
  ftpSrv.handleFTP();                                                 // Обработчик FTP-соединений 
  humidifer();
  turn(needTurn);
  SerialSend();
 ///////////////////////////////PID_pin/////////////////////////
  // getResultTimer возвращает значение для управляющего устройства
  // (после вызова можно получать это значение как regulator.output)
  // обновление происходит по встроенному таймеру на millis()
  analogWrite(12, reg.getResultTimer());  // отправляем на мосфет
  //turn(needTurn);

  ESP.wdtFeed();
  // .getResultTimer() по сути возвращает regulator.output
}
  //////////////////////////////////////////////////////

String RELAY_PIN_switch() {                                                 // Функция переключения реле 
  byte state;
  if (digitalRead(RELAY_PIN))                                               // Если на пине реле высокий уровень   
    state = 0;                                                          //  то запоминаем, что его надо поменять на низкий
  else                                                                  // иначе
    state = 1;                                                          //  запоминаем, что надо поменять на высокий
  digitalWrite(RELAY_PIN, state);                                           // меняем значение на пине подключения реле
  return String(state);                                                 // возвращаем результат, преобразовав число в строку
}

String RELAY_PIN_status() {                                                 // Функция для определения текущего статуса реле 
  byte state;
  if (digitalRead(RELAY_PIN))                                               // Если на пине реле высокий уровень   
    state = 1;                                                          //  то запоминаем его как единицу
  else                                                                  // иначе
    state = 0;                                                          //  запоминаем его как ноль
  return String(state);                                                 // возвращаем результат, преобразовав число в строку
}
