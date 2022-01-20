
#include <Arduino.h>
#include "Global.h"
#include "test.h"

  String processor(const String& var)
{
  //Serial.println(var); 
  if(var == "temp"){
    return String(temp);
  }
  else if(var == "humidity"){
    return String(hum);
  }
  
  return String();
}

void webstr() {
    
    LittleFS.begin();            //запуск памяти
    
    
    
    server.addHandler(&ws);

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){                 //загрузка страницы из памяти
    request->send(LittleFS, "/index.html", String(), false, processor);
    
  });
  server.serveStatic("/", LittleFS, "/");
  // Route to load style.css file
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "css/bezi.css", "text/css");
  });
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "css/index.css", "text/css");
  });
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "js/jquery-1.12.4.min.js", "application/javascript");
  });
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(LittleFS, "js/wb.panel.min.js", "application/javascript");
  });
  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){      //вывод температуры на страницу
    request->send_P(200, "text/plain", String(temp).c_str());
  });
  server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request){       //вывод влажности на страницу
    request->send_P(200, "text/plain", String(hum).c_str());
  });

  server.begin();                           // Инициализируем Web-сервер
  ftpSrv.begin("zz","zz");                 // Поднимаем FTP-сервер для удобства отладки работы HTML (логин: relay, пароль: relay)
  

}
 
String getContentType(String filename){                                 // Функция, возвращающая необходимый заголовок типа содержимого в зависимости от расширения файла
  if (filename.endsWith(".html")) return "text/html";                   // Если файл заканчивается на ".html", то возвращаем заголовок "text/html" и завершаем выполнение функции
  else if (filename.endsWith(".css")) return "text/css";                // Если файл заканчивается на ".css", то возвращаем заголовок "text/css" и завершаем выполнение функции
  else if (filename.endsWith(".js")) return "application/javascript";   // Если файл заканчивается на ".js", то возвращаем заголовок "application/javascript" и завершаем выполнение функции
  else if (filename.endsWith(".png")) return "image/png";               // Если файл заканчивается на ".png", то возвращаем заголовок "image/png" и завершаем выполнение функции
  else if (filename.endsWith(".jpg")) return "image/jpeg";              // Если файл заканчивается на ".jpg", то возвращаем заголовок "image/jpg" и завершаем выполнение функции
  else if (filename.endsWith(".gif")) return "image/gif";               // Если файл заканчивается на ".gif", то возвращаем заголовок "image/gif" и завершаем выполнение функции
  else if (filename.endsWith(".ico")) return "image/x-icon";            // Если файл заканчивается на ".ico", то возвращаем заголовок "image/x-icon" и завершаем выполнение функции
  return "text/plain";                                                  // Если ни один из типов файла не совпал, то считаем что содержимое файла текстовое, отдаем соответствующий заголовок и завершаем выполнение функции
}