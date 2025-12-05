// RF32 BLE Bridge
// Copyright © 2025, Jeremiasz Grzesiuk (JeremiDev)
// MIT License

#ifndef CLIENT_CONTROLLER_H
#define CLIENT_CONTROLLER_H

#include <Arduino.h>
#include "Models/DataModels.h"
#include <ArduinoJson.h>

// ClientController is the abstract class for all client controllers
// It is used to handle the client side of the application
// As client it means that the  device (not controller, like smartphone) connected to the ESP32 via BLE
class ClientController {
public:
  virtual ~ClientController() {}

  virtual bool setup() = 0;
  virtual void loop() = 0;

  virtual void operationExceptionCallback(const char* id, ExceptionEntity exception, JsonObject params) = 0;
  virtual void operationSuccessCallback(const char* id, JsonObject data) = 0;

  virtual void deviceCommandCallback(const DeviceCommandEntity& command) = 0;
};

#endif