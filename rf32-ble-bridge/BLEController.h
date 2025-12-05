#ifndef BLE_CONTROLLER_H
#define BLE_CONTROLLER_H

#include <NimBLEDevice.h>
#include "ClientController.h"
#include "StatusModule.h"
#include "DeviceController.h"
#include "Validator.h"
#include "JSONDecoder.h"
#include "JSONEncoder.h"
#include "Constants.h"

class BLEController : public ClientController {
public:
  BLEController(StatusModule* statusModule,
                DeviceController* deviceController,
                Validator validator,
                JSONDecoder jsonDecoder,
                JSONEncoder jsonEncoder) {
    _bleControllerInstance = this;
    _deviceController = deviceController;
    _statusModule = statusModule;
  };
  bool setup() override;
  void loop() override;

  void operationExceptionCallback(const char* id, ExceptionEntity exception, JsonObject params) override;
  void operationSuccessCallback(const char* id, JsonObject data) override;

  void deviceCommandCallback(const DeviceCommandEntity& command) override;

  static void exceptionCallbackTrampoline(const char* id, ExceptionEntity exception, JsonObject params);
  static void successCallbackTrampoline(const char* id, JsonObject data);

  static void deviceCommandCallbackTrampoline(const DeviceCommandEntity& command);

private:

  static BLEController* _bleControllerInstance;

  // Items
  StatusModule* _statusModule;
  DeviceController* _deviceController;
  Validator _validator;
  JSONDecoder _jsonDecoder;
  JSONEncoder _jsonEncoder;


  // BLE Server
  NimBLEServer* _server;
  NimBLEService* _service;
  NimBLECharacteristic* _operationResultCharacteristic;
  NimBLECharacteristic* _receiveRfDataCharacteristic;
  NimBLECharacteristic* _statusCharacteristic;
  NimBLECharacteristic* _radioConfigurationCharacteristic;
  NimBLECharacteristic* _modeCharacteristic;
  NimBLECharacteristic* _sendRfDataCharacteristic;
};



#endif