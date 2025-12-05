// RF32 BLE Bridge
// Copyright © 2025, Jeremiasz Grzesiuk (JeremiDev)
// MIT License

#include "App.h"

App::App() {
}

void App::setup() {
  Serial.println("App setup starting...");

  // Prepare implementations
  _deviceController = new RFController();
  _clientController = new BLEController(&_statusModule, _deviceController, _validator, _jsonDecoder, _jsonEncoder);

  // Setup
  _statusModule.setup();
  _clientController->setup();
  _deviceController->setDeviceCommandCallback(BLEController::deviceCommandCallbackTrampoline);

  if (!_deviceController->setup()) {
    _statusModule.setStatus("Error: RF Controller not initialized");
    while (true) { delay(500); }
  }

  // Finish setup
  _statusModule.setStatus("Ready");
  Serial.println("App setup complete");
}

void App::loop() {
  _deviceController->loop();
  _clientController->loop();
  delay(3);
}