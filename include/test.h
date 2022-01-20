//#include <ArduinoJson.h>
//#include <SD.h>
//#include <SPI.h>
//#include "Global.h"

// Наша конфигурационная структура.
//
// Никогда не используйте JsonDocument для хранения конфигурации!
// JsonDocument * не * постоянное хранилище; это всего лишь временное хранилище
// используется на этапе сериализации. Видеть:
// https://arduinojson.org/v6/faq/why-must-i-create-a-separate-config-object/
/*struct Config {
  char ssid[64];
  char Password[64];
  int port;
  
};

jsonConfig = "/config.json";  // <- Библиотека SD использует имена файлов формата 8.3
Config config;                         // <- глобальный объект конфигурации

// Загружает конфигурацию из файла
void loadConfiguration(const char *filename, Config &config) { 
  // Открыть файл для чтения
  File file = LittleFS.open(filename, "w");

  // Выделить временный JsonDocument
  // Не забудьте изменить емкость в соответствии с вашими требованиями.
  // Используйте arduinojson.org/v6/assistant для вычисления емкости.
  StaticJsonDocument<512> doc;

  // Десериализовать документ JSON
  DeserializationError error = deserializeJson(doc, file);
  if (error)
    Serial.println(F("Failed to read file, using default configuration"));

  // Скопируйте значения из JsonDocument в конфигурацию
  config.port = doc["port"] | 2731;
  ssid = doc["ssid"] | ssid ,(config.ssid);
  //strlcpy(config.hostname,                  // <- назначения
           //doc["hostname"] | "example.com",  // <- источник
          // sizeof(config.hostname));         // <- вместимость пункта назначения

  // Закройте файл (любопытно, что деструктор File не закрывает файл)
  file.close();
}

// Сохраняет конфигурацию в файл
void saveConfiguration(const char *filename, const Config &config) {
  // Удалите существующий файл, иначе конфигурация будет добавлена ​​к файлу.
  LittleFS.remove(filename);

  // Открыть файл для записи
  File file = LittleFS.open(filename, "w");
  if (!file) {
    Serial.println(F("Failed to create file"));
    return;
  }

  // Выделить временный JsonDocument
  // Не забудьте изменить емкость в соответствии с вашими требованиями.
  // Используйте arduinojson.org/assistant для вычисления емкости.
  StaticJsonDocument<256> doc;

  // Установите значения в документе
  doc["ssid"] = ssid;
  doc["Password"] = config.Password;
  doc["port"] = config.port;

  // Сериализовать JSON в файл
  if (serializeJson(doc, file) == 0) {
    Serial.println(F("Failed to write to file"));
  }

  // Закройте файл
  file.close();
}

// Печатает содержимое файла на серийный номер
void printFile(const char *filename) {
  // Открыть файл для чтения
  File file = LittleFS.open(filename, "w");
  if (!file) {
    Serial.println(F("Failed to read file"));
    return;
  }

  // Извлеките каждый символ по одному
  while (file.available()) {
    Serial.print((char)file.read());
  }
  Serial.println();

  // Закройте файл
  file.close();
}*/
/*const String writeFile(const String& filename, const String& str) {
    String path = filepath(filename);
    auto file = LittleFS.open(path, "w");
    if (!file) {
        return "failed";
    }
    file.print(str);
    file.close();
    return "sucсess";
}
const String readFile(const String& filename, size_t max_size) {
    String path = filepath(filename);
    auto file = LittleFS.open(path, "r");
    if (!file) {
        return "failed";
    }
    size_t size = file.size();
    if (size > max_size) {
        file.close();
        return "large";
    }
    String temp = file.readString();
    file.close();
    return temp;
}
const String filepath(const String& filename) {
    return filename.startsWith("/") ? filename : "/" + filename;
}

void globalVarsSync() {
    settingsFlashJson = readFile(F("settings.json"), 4096);
    settingsFlashJson.replace("\r\n", "");
}

void saveSettingsFlashJson() {
    writeFile(F("settings.json"), settingsFlashJson);
}*/