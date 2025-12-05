#include "RadioConfigurationCallbacks.h"

void RadioConfigurationCallbacks::onRead(NimBLECharacteristic* pCharacteristic, NimBLEConnInfo& connInfo) {
  (void)pCharacteristic;
  (void)connInfo;
  StaticJsonDocument<256> doc;

  String jsonString = _jsonEncoder.encodeRadioConfigurationEntity(_deviceController->getRadioConfiguration(), doc);
  pCharacteristic->setValue(jsonString);
  Serial.println("Radio Configuration read by central: " + jsonString);
}

void RadioConfigurationCallbacks::onWrite(NimBLECharacteristic* pCharacteristic, NimBLEConnInfo& connInfo) {
  (void)pCharacteristic;
  (void)connInfo;

  std::string incoming = pCharacteristic->getValue();
  StaticJsonDocument<256> doc;

  OperationEntity operationEntity;
  RadioConfigurationEntity radioConfigurationEntity;

  //1. Decode the incoming to an operation entity
  DecodeEntityStatus decodeEntityStatus = _jsonDecoder.decodeOperationEntity(doc, incoming.c_str(), operationEntity);
  if (!decodeEntityStatus.success) {
    _operationExceptionCallback("UNKNOWN",
                                ExceptionEntity(decodeEntityStatus.code, EXCEPTION_TYPE_BAD_JSON, decodeEntityStatus.errorMessage.c_str()),
                                operationEntity.data);
    return;
  }
  const char* operationId = operationEntity.id ? operationEntity.id : "UNKNOWN";

  //2. Decode the data of the operation entity to a radio configuration entity
  DecodeEntityStatus decodeRadioConfigurationEntityStatus = _jsonDecoder.decodeRadioConfigurationEntity(doc,
                                                                                                        operationEntity.data,
                                                                                                        radioConfigurationEntity);
  if (!decodeRadioConfigurationEntityStatus.success) {
    _operationExceptionCallback(operationId,
                                ExceptionEntity(decodeRadioConfigurationEntityStatus.code, EXCEPTION_TYPE_BAD_JSON, decodeRadioConfigurationEntityStatus.errorMessage.c_str()),
                                operationEntity.data);
    return;
  }

  //3. Validate the radio configuration
  ValidationEntityStatus validationEntityStatus = _validator.validateConfig(radioConfigurationEntity);
  if (!validationEntityStatus.success) {
    _operationExceptionCallback(operationId,
                                ExceptionEntity(validationEntityStatus.code, EXCEPTION_TYPE_INVALID_ARG, validationEntityStatus.errorMessage.c_str()),
                                operationEntity.data);
    return;
  }

  //4. Apply the radio configuration to the device
  _deviceController->applyConfig(radioConfigurationEntity);

  //5. Send the success callback
  Serial.println("Radio Configuration updated characteristic: " + String(incoming.c_str()));
  _operationSuccessCallback(operationId, operationEntity.data);
}