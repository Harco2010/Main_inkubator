#pragma once
#include <Arduino.h>
//===================Libraries===================================================================================================================================================
#include <GY21.h>                // датчик температуры,влажности SI7021
#include "Wire.h"
#include <GyverPID.h>            // библиотека ПИД
#include <LiquidCrystal_I2C.h>    // библиотека LCD1602
#include <ESP8266WiFi.h>        // Библиотека для создания Wi-Fi подключения (клиент или точка доступа)
#include <ESPAsyncWebServer.h>     // Библиотека для управления устройством по HTTP (например из браузера) 
#include "LittleFS.h"           // Библиотека для работы с файловой системой
#include <SimpleFTPServer.h>   // Библиотека для работы с LittleFS по FTP
#include <ArduinoJson.h>       // v.6.17.2
#include <FS.h>
#include <RTClib.h>
#include <EEPROM.h>
#include "EEPROM.h"
//#include <Sensirion.h>
//#include <avr/wdt.h>
//#include <GyverEncoder.h>
#include <Adafruit_I2CDevice.h>

  
//#include "test.h"
//#include "web.h"
//#define FileFS LittleFS 
//#ifdef WEBSOCKET_ENABLED
AsyncWebSocket ws("/ws");
AsyncEventSource events("/events");  
AsyncWebServer server(80);
RTC_DS3231 rtc;

//#endif
 
#ifdef ESP8266
 #define SCL 5 // D5 ON NODEMCU 
 #define SDA 4 // D6 ON NODEMCU
#endif

 //AsyncWebServer server;
 GY21 sensor;                                  // переменная для датчика SI7021
LiquidCrystal_I2C lcd(0x27, 16, 2);           // переменная для LCD1602

//////////////////////////////////////////
//#define portOutputRegister(port)    ((volatile uint32_t*) GPO)
//#define IO_REG_TYPE			uint32_t
#define beeper_pin 1                   //пищалка по аварии
#define button_plus_pin 9                          // вход энкодера
#define button_minus_pin 10
#define button_enter_pin 13            //пин кнопки "enter"
#define turn_pin 3                    // управление поворотом

boolean button_minus;                // статус нажатия кнопок
boolean button_plus;
boolean button_enter;
boolean needTurn = false;               // нужен ли поворот яиц?
boolean turnFlag = 0;              // флаг поворота для случайного периода

int del = 80;                     // переменная ожидания между выборами меню

unsigned int interval = 300;      // интервал сколько будет длиться цикл while, после чего перейдёт к следующему меню.(кол-во итераций)
unsigned int startDayUnixtime;          // хранящийся в памяти день старта программы в юникс-формате
unsigned int currentTime_day;           //текущий день в юникс-формате (сколько дней минуло с 1 января 1970)
unsigned int currentDay;                // текущий день в юникс-формате
unsigned long serialTime;            //это поможет нам знать, когда следует поговорить с обработчиком
unsigned long currentTime;            // задаем переменные для тайминга поворота
unsigned long loopTime;
unsigned int memoryDay;

String birdPrint = "CHICK";




#define TEMP_MAX 40.0                        // Приделы настройки термостата
#define TEMP_MIN 25.0

#define h_histeresis 1.0              // гистерезис влажности
#define but_enter_pin 10            //пин кнопки "enter"
const byte RELAY_PIN = 12;                        // выход на нагреватель
const byte humidifer_pin = 14;                        // выход на реле влажности

#define WindowSize 512                       // периуд, для симистора можно оставить, для
                                             // реле увеличить в ~10 раз
////////////////////////////////////////////// 

unsigned long windowStartTime;
double setpoint, Input, Output;
GyverPID reg(0.1, 0.05, 0.01, 10);          // коэф. П, коэф. И, коэф. Д, период дискретизации dt (мс)

// Определяем переменные wifi
const char* ssid     = "Utilit";
const char* password = "11051977";

FtpServer ftpSrv;                         // Определяем объект для работы с модулем по FTP (для отладки HTML)

const unsigned long humStep = 300UL; // Период опроса датчиков
float temp = 0.0;                        //переменная температуры для страницы
float hum = 0.0;                        //переменная влажности для страницы
float U_tem = 38;                  //переменная установленной температуры
float U_hum = 60;                     //переменная установленной влажности 
float sp = 20;
int adrr = 0;
int turnPeriod;
int birdType;
bool NeedCommit = false; //Флаг необходимости сохранения настроек в EEPROM


//String config = "{}"; 
//String settingsFlashJson = "{}";  //переменная в которой хранятся все настройки, находится в оперативной памяти и синхронизированна с flash памятью
//String paramsFlashJson = "{}";    //переменная в которой хранятся все параметры, находится в оперативной памяти и синхронизированна с flash памятью
//String paramsHeapJson = "{}";     //переменная в которой хранятся все параметры, находится в оперативной памяти только

