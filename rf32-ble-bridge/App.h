// RF32 BLE Bridge
// Copyright © 2025, Jeremiasz Grzesiuk (JeremiDev)
// MIT License

#ifndef APP_H
#define APP_H

#include "ClientController.h"
#include "DeviceController.h"
#include "StatusModule.h"
#include "RFController.h"
#include "JSONDecoder.h"
#include "JSONEncoder.h"
#include "Validator.h"
#include "BLEController.h"

class App {
public:
  App();
  void setup();
  void loop();

private:
  StatusModule _statusModule;

  DeviceController* _deviceController;
  ClientController* _clientController;

  JSONDecoder _jsonDecoder;
  JSONEncoder _jsonEncoder;
  Validator _validator;
};

#endif