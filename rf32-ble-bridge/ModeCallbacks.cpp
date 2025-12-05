// RF32 BLE Bridge
// Copyright © 2025, Jeremiasz Grzesiuk (JeremiDev)
// MIT License

#include "ModeCallbacks.h"

void ModeCallbacks::onRead(NimBLECharacteristic* pCharacteristic, NimBLEConnInfo& connInfo) {
  (void)pCharacteristic;
  (void)connInfo;

  StaticJsonDocument<256> doc;

  ModeEntity modeEntity;
  modeEntity.mode = _deviceController->getMode() == RadioMode::TX ? "TX" : "RX";
  String jsonString = _jsonEncoder.encodeModeEntity(modeEntity, doc);
  pCharacteristic->setValue(jsonString);
  Serial.println("Mode read by central: " + jsonString);
}

void ModeCallbacks::onWrite(NimBLECharacteristic* pCharacteristic, NimBLEConnInfo& connInfo) {
  (void)pCharacteristic;
  (void)connInfo;

  std::string incoming = pCharacteristic->getValue();
  StaticJsonDocument<256> doc;

  OperationEntity operationEntity;
  ModeEntity modeEntity;

  //1. Decode the incoming to an operation entity
  DecodeEntityStatus decodeEntityStatus = _jsonDecoder.decodeOperationEntity(doc, incoming.c_str(), operationEntity);
  if (!decodeEntityStatus.success) {
    _operationExceptionCallback("UNKNOWN", ExceptionEntity(decodeEntityStatus.code, EXCEPTION_TYPE_BAD_JSON, decodeEntityStatus.errorMessage.c_str()), operationEntity.data);
    return;
  }
  const char* operationId = operationEntity.id ? operationEntity.id : "UNKNOWN";

  //2. Decode the data of the operation entity to a mode entity
  DecodeEntityStatus decodeModeEntityStatus = _jsonDecoder.decodeModeEntity(doc, operationEntity.data, modeEntity);
  if (!decodeModeEntityStatus.success) {
    _operationExceptionCallback(operationId, ExceptionEntity(decodeModeEntityStatus.code, EXCEPTION_TYPE_BAD_JSON, decodeModeEntityStatus.errorMessage.c_str()), operationEntity.data);
    return;
  }


  //3. Validate the mode
  ValidationEntityStatus validationEntityStatus = _validator.validateMode(modeEntity);
  if (!validationEntityStatus.success) {
    _operationExceptionCallback(operationId, ExceptionEntity(validationEntityStatus.code, EXCEPTION_TYPE_INVALID_ARG, validationEntityStatus.errorMessage.c_str()), operationEntity.data);
    return;
  }

  //4. Apply the mode to the device
  RadioMode mode = String(modeEntity.mode) == "TX" ? RadioMode::TX : RadioMode::RX;
  _deviceController->setMode(mode);

  //5. Send the success callback
  Serial.println("Mode write by central: " + String(incoming.c_str()));
  _operationSuccessCallback(operationId, operationEntity.data);
}
