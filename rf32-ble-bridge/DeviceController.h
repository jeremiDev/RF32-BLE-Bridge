#ifndef DEVICE_CONTROLLER_H
#define DEVICE_CONTROLLER_H

#include <Arduino.h>
#include "Models/DataModels.h"
#include "Models/Constants.h"

// DeviceController is the abstract class for controller classes
// As device it means that the ESP32 is the device that is connected to the bridge (like smartphone) via BLE (Bluetooth Low Energy)
class DeviceController {
public:
  virtual ~DeviceController() {}

  virtual bool setup() = 0;
  virtual void loop() = 0;

  virtual void applyConfig(const RadioConfigurationEntity& radioConfiguration) = 0;
  virtual RadioConfigurationEntity getRadioConfiguration() = 0;

  virtual void setMode(RadioMode m) = 0;
  virtual RadioMode getMode() = 0;

  virtual void sendCommand(const DeviceCommandEntity& c) = 0;
  virtual void setDeviceCommandCallback(DeviceCommandCallback callback) = 0;
};

#endif