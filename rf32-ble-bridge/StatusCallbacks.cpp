// RF32 BLE Bridge
// Copyright © 2025, Jeremiasz Grzesiuk (JeremiDev)
// MIT License

#include "StatusCallbacks.h"

void StatusCallbacks::onRead(NimBLECharacteristic* pCharacteristic, NimBLEConnInfo& connInfo) {
  (void)pCharacteristic;
  (void)connInfo;

  StaticJsonDocument<256> doc;
  StatusEntity statusEntity = _statusModule->getStatus();
  String jsonString = _jsonEncoder.encodeStatusEntity(statusEntity, doc);
  pCharacteristic->setValue(jsonString);
  Serial.println("Status read by central: " + jsonString);
}