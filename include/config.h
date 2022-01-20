 #include "Global.h"

/*void saveConfig(String fileName, String strings) {
  File configFile = LittleFS.open(fileName, "w");
  configFile.print(strings);
  configFile.close();
} */

 //
String jsonWrite(String &json, String name, float volume) {
 char json[] = "{\"sensor\":\"gps\",\"time\":1351824120,\"data\":[48.756080,2.302038]\"startDay\",}";

 DynamicJsonDocument doc(1024);
 deserializeJson(doc, json);

 const char* sensor             = doc["sensor"];
 long time                      = doc["time"];
 double latitude                = doc["data"][0];
 double longitude               = doc["data"][1];
 unsigned int startDayUnixtime  = doc["data"];
 
 serializeJson(doc, json);
 return json;
} 
String readFile(String fileName, size_t len) {
 DynamicJsonDocument doc(1024);

 doc["sensor"] = "gps";
 doc["time"]   = 1351824120;
 doc["data"][0] = 48.756080;
 doc["data"][1] = 2.302038;
 doc["data"]   = 0;

 serializeJson(doc, Serial);
 // This prints:
 // {"sensor":"gps","time":1351824120,"data":[48.756080,2.302038]}
} 
 

 
 // Загрузка данных сохраненных в файл  config.json
/*String jsonWrite(String &json, String name, float volume) {
  DynamicJsonDocument root(3072);
  deserializeJson(root, json);
  root[name]= volume;
  json = "";
  serializeJson(root, json);
  return json;
}
void saveConfig(String fileName, String strings) {
  File configFile = LittleFS.open(fileName, "w");
  configFile.print(strings);
  configFile.close();
}
String readFile(String fileName, size_t len) {
  File configFile = LittleFS.open(fileName, "r");
  DEBUG_PRINT("\nFile: %s | size: %i\n", fileName.c_str(), configFile.size());
  String cSetup = configFile.readString();
  configFile.close();
  return cSetup;
}*/

//configSetupJson = readFile("/configSetup.json", 1024);

//jsonWrite(configSetup, "defaultFloat", defFloat);

//saveConfig("/configSetup.json", configSetup);

// Наша структура конфигурации.
//
// Никогда не используйте документ Json для хранения конфигурации!
// Документ Json не является постоянным хранилищем; это всего лишь временное хранилище
//используется на этапе сериализации. Видеть:
// https://arduinojson.org/v6/faq/why-must-i-create-a-separate-config-object/

/*struct Config {
  char hostname[32];
  int port;
};

const char *filename = "/config.txt";  // <- Библиотека SD использует 8.3 имен файлов
Config config;                         // <- объект глобальной конфигурации
// Загружает конфигурацию из файла
void loadConfiguration(const char *filename, Config &config) {
  // Открыть файл для чтения
  File config = LittleFS.open("/config.txt"," w ");

  // Выделите временный документ Json
  // Не забудьте изменить емкость в соответствии с вашими требованиями.
  // Использовать arduinojson.org/v6/assistant для вычисления емкости.
  StaticJsonDocument<512> doc;

  // Десериализовать документ JSON
  DeserializationError error = deserializeJson(doc, "!!NOT JSON!!");
  if (error)
    Serial.println(F("Failed to read file, using default configuration"));

  // Скопируйте значения из документа Json в конфигурацию
  config.port = doc["port"] | 2731;
  strlcpy(config.hostname,                  // <- место назначения
          doc["hostname"] | "example.com",  // <- source
          sizeof(config.hostname));         // <- destination's capacity

  // Close the file (Curiously, File's destructor doesn't close the file)
  file.close();
}

// Saves the configuration to a file
void saveConfiguration(const char *filename, const Config &config) {
  // Delete existing file, otherwise the configuration is appended to the file
  SD.remove(filename);

  // Open file for writing
  File file = SD.open(filename, FILE_WRITE);
  if (!file) {
    Serial.println(F("Failed to create file"));
    return;
  }

  // Allocate a temporary JsonDocument
  // Don't forget to change the capacity to match your requirements.
  // Use arduinojson.org/assistant to compute the capacity.
  StaticJsonDocument<256> doc;

  // Set the values in the document
  doc["hostname"] = config.hostname;
  doc["port"] = config.port;

  // Serialize JSON to file
  if (serializeJson(doc, file) == 0) {
    Serial.println(F("Failed to write to file"));
  }

  // Close the file
  file.close();
}

// Prints the content of a file to the Serial
void printFile(const char *filename) {
  // Open file for reading
  File file = SD.open(filename);
  if (!file) {
    Serial.println(F("Failed to read file"));
    return;
  }

  // Extract each characters by one by one
  while (file.available()) {
    Serial.print((char)file.read());
  }
  Serial.println();

  // Close the file
  file.close();
}*/
