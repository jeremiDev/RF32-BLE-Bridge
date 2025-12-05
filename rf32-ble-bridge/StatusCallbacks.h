// RF32 BLE Bridge
// Copyright © 2025, Jeremiasz Grzesiuk (JeremiDev)
// MIT License

#ifndef STATUS_CALLBACKS_H
#define STATUS_CALLBACKS_H

#include <NimBLEDevice.h>
#include "Models/DataModels.h"
#include "StatusModule.h"
#include "JSONDecoder.h"
#include "JSONEncoder.h"

class StatusCallbacks : public NimBLECharacteristicCallbacks {
public:
  StatusCallbacks(StatusModule* statusModule,
                  JSONDecoder jsonDecoder,
                  JSONEncoder jsonEncoder)
    : _jsonDecoder(jsonDecoder),
      _jsonEncoder(jsonEncoder) {
    _statusModule = statusModule;
  }

  void onRead(NimBLECharacteristic* pCharacteristic, NimBLEConnInfo& connInfo) override;

private:
  StatusModule* _statusModule;
  JSONDecoder _jsonDecoder;
  JSONEncoder _jsonEncoder;
};

#endif