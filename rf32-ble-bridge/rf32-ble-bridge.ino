#include <NimBLEDevice.h>
#include <ArduinoJson.h>
#include <ctype.h>

#include "App.h"

static App* app;

void setup() {
  Serial.begin(115200);
  delay(800);

  Serial.println("--------------------------------");
  Serial.println("Starting...");

  app = new App();
  app->setup();

  Serial.println("--------------------------------");
  Serial.println(String(APP_NAME) + " ready.");
  Serial.println("Version: " + String(FW_VERSION));
  Serial.println("Build: " + String(__DATE__) + " " + String(__TIME__));
  Serial.println("--------------------------------");
}

void loop() {
  app->loop();
  delay(2);
}
