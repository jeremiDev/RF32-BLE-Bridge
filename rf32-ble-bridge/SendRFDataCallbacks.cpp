#include "SendRFDataCallbacks.h"

void SendRfDataCallbacks::onWrite(NimBLECharacteristic* pCharacteristic, NimBLEConnInfo& connInfo) {
  (void)pCharacteristic;
  (void)connInfo;
  std::string incoming = pCharacteristic->getValue();
  StaticJsonDocument<256> doc;

  OperationEntity operationEntity;
  DeviceCommandEntity deviceCommandEntity;

  //1. Decode command
  DecodeEntityStatus decodeEntityStatus = _jsonDecoder.decodeOperationEntity(doc, incoming.c_str(), operationEntity);
  if (!decodeEntityStatus.success) {
    _operationExceptionCallback("UNKNOWN",
                                ExceptionEntity(decodeEntityStatus.code, EXCEPTION_TYPE_BAD_JSON, decodeEntityStatus.errorMessage.c_str()),
                                operationEntity.data);
    return;
  }
  const char* operationId = operationEntity.id ? operationEntity.id : "UNKNOWN";

  //2. Decode object
  DecodeEntityStatus decodeDeviceCommandEntityStatus = _jsonDecoder.decodeDeviceCommandEntity(doc, operationEntity.data, deviceCommandEntity);
  if (!decodeDeviceCommandEntityStatus.success) {
    _operationExceptionCallback(operationId,
                                ExceptionEntity(decodeDeviceCommandEntityStatus.code, EXCEPTION_TYPE_BAD_JSON, decodeDeviceCommandEntityStatus.errorMessage.c_str()),
                                operationEntity.data);
    return;
  }


  //3. Validate object
  ValidationEntityStatus validationEntityStatus = _validator.validateDeviceCommand(deviceCommandEntity);
  if (!validationEntityStatus.success) {
    _operationExceptionCallback(operationId,
                                ExceptionEntity(validationEntityStatus.code, EXCEPTION_TYPE_INVALID_ARG, validationEntityStatus.errorMessage.c_str()),
                                operationEntity.data);
    return;
  }

  _deviceController->sendCommand(deviceCommandEntity);
  _operationSuccessCallback(operationId, operationEntity.data);
  Serial.println("Send RF Data write by central: " + String(incoming.c_str()));
}