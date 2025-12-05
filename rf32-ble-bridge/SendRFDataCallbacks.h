// RF32 BLE Bridge
// Copyright © 2025, Jeremiasz Grzesiuk (JeremiDev)
// MIT License

#ifndef SEND_RF_DATA_CALLBACKS_H
#define SEND_RF_DATA_CALLBACKS_H

#include "DeviceController.h"
#include "Validator.h"
#include <NimBLEDevice.h>
#include "Models/DataModels.h"
#include "Models/ExceptionCodes.h"
#include "JSONDecoder.h"
#include "JSONEncoder.h"


class SendRfDataCallbacks : public NimBLECharacteristicCallbacks {
public:
  SendRfDataCallbacks(OperationExceptionCallback operationExceptionCallback,
                      OperationSuccessCallback operationSuccessCallback,
                      DeviceController* deviceController,
                      Validator validator,
                      JSONDecoder jsonDecoder,
                      JSONEncoder jsonEncoder)
    : _operationExceptionCallback(operationExceptionCallback),
      _operationSuccessCallback(operationSuccessCallback),
      _deviceController(deviceController),
      _validator(validator),
      _jsonDecoder(jsonDecoder),
      _jsonEncoder(jsonEncoder) {}

  void onWrite(NimBLECharacteristic* pCharacteristic, NimBLEConnInfo& connInfo) override;

private:
  DeviceController* _deviceController;
  Validator _validator;
  OperationExceptionCallback _operationExceptionCallback;
  OperationSuccessCallback _operationSuccessCallback;
  JSONDecoder _jsonDecoder;
  JSONEncoder _jsonEncoder;
};

#endif