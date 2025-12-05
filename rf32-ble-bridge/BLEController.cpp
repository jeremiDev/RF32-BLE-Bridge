// RF32 BLE Bridge
// Copyright © 2025, Jeremiasz Grzesiuk (JeremiDev)
// MIT License

#include "BLEController.h"
#include "ServerCallbacks.h"
#include "OperationResultCallbacks.h"
#include "ReceiveRfDataCallbacks.h"
#include "StatusCallbacks.h"
#include "RadioConfigurationCallbacks.h"
#include "ModeCallbacks.h"
#include "SendRfDataCallbacks.h"
#include "Constants.h"

BLEController* BLEController::_bleControllerInstance = nullptr;

bool BLEController::setup() {
  Serial.println("BLE Controller setup starting...");
  // BLE setup
  NimBLEDevice::init(NIMBLE_DEVICE_NAME);
  _server = NimBLEDevice::createServer();
  _server->setCallbacks(new ServerCallbacks());

  _service = _server->createService(SERVICE_UUID);
  Serial.println("BLE Controller service created");

  // 1. Operation Result Characteristic
  _operationResultCharacteristic = _service->createCharacteristic(
    OPERATION_RESULT_CHARACTERISTIC_UUID,
    NIMBLE_PROPERTY::NOTIFY);
  _operationResultCharacteristic->setCallbacks(new OperationResultCallbacks());
  Serial.println("BLE Controller operation result characteristic created");

  // 2. Receive RF Data Characteristic
  _receiveRfDataCharacteristic = _service->createCharacteristic(
    RECEIVE_RF_DATA_CHARACTERISTIC_UUID,
    NIMBLE_PROPERTY::NOTIFY);
  _receiveRfDataCharacteristic->setCallbacks(new ReceiveRfDataCallbacks());
  Serial.println("BLE Controller receive RF data characteristic created");

  // 3. Status Characteristic
  _statusCharacteristic = _service->createCharacteristic(
    STATUS_CHARACTERISTIC_UUID,
    NIMBLE_PROPERTY::READ);
  _statusCharacteristic->setCallbacks(new StatusCallbacks(_statusModule, _jsonDecoder, _jsonEncoder));
  Serial.println("BLE Controller status characteristic created");

  // 4. Radio Configuration Characteristic
  _radioConfigurationCharacteristic = _service->createCharacteristic(
    RADIO_CONFIGURATION_CHARACTERISTIC_UUID,
    NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::WRITE);
  _radioConfigurationCharacteristic->setCallbacks(new RadioConfigurationCallbacks(
    BLEController::exceptionCallbackTrampoline,
    BLEController::successCallbackTrampoline,
    _deviceController,
    _validator,
    _jsonDecoder,
    _jsonEncoder));
  Serial.println("BLE Controller radio configuration characteristic created");

  // 5. Mode Characteristic
  _modeCharacteristic = _service->createCharacteristic(
    MODE_CHARACTERISTIC_UUID,
    NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::WRITE);
  _modeCharacteristic->setCallbacks(new ModeCallbacks(
    BLEController::exceptionCallbackTrampoline,
    BLEController::successCallbackTrampoline,
    _deviceController,
    _validator,
    _jsonDecoder,
    _jsonEncoder));
  Serial.println("BLE Controller mode characteristic created");

  // 6. Send RF Data Characteristic
  _sendRfDataCharacteristic = _service->createCharacteristic(
    SEND_RF_DATA_CHARACTERISTIC_UUID,
    NIMBLE_PROPERTY::WRITE);
  _sendRfDataCharacteristic->setCallbacks(new SendRfDataCallbacks(
    BLEController::exceptionCallbackTrampoline,
    BLEController::successCallbackTrampoline,
    _deviceController,
    _validator,
    _jsonDecoder,
    _jsonEncoder));
  Serial.println("BLE Controller send RF data characteristic created");

  // Start the service
  _service->start();
  Serial.println("BLE Controller service started");

  // Advertise the service and characteristics
  NimBLEAdvertising* advertising = NimBLEDevice::getAdvertising();
  advertising->addServiceUUID(SERVICE_UUID);
  advertising->addServiceUUID(STATUS_CHARACTERISTIC_UUID);
  advertising->addServiceUUID(RADIO_CONFIGURATION_CHARACTERISTIC_UUID);
  advertising->addServiceUUID(MODE_CHARACTERISTIC_UUID);
  advertising->addServiceUUID(RECEIVE_RF_DATA_CHARACTERISTIC_UUID);
  advertising->addServiceUUID(SEND_RF_DATA_CHARACTERISTIC_UUID);
  advertising->addServiceUUID(OPERATION_RESULT_CHARACTERISTIC_UUID);
  Serial.println("BLE Controller advertising service and characteristics added");

  advertising->start();
  Serial.println("BLE Controller setup complete");

  return true;
}

void BLEController::loop() {
  // Implement loop
}

void BLEController::operationExceptionCallback(const char* id, ExceptionEntity exception, JsonObject params) {
  Serial.println("Operation Exception Callback: " + String(id) + " " + String(exception.code) + " " + String(exception.type) + " " + String(exception.description));

  String jsonString = _jsonEncoder.encodeOperationFailure(id, exception, params);
  Serial.println("Operation Exception Callback JSON: " + String(jsonString));

  _operationResultCharacteristic->setValue(jsonString);
  _operationResultCharacteristic->notify();
}

void BLEController::operationSuccessCallback(const char* id, JsonObject data) {
  Serial.println("Operation Success Callback: " + String(id));

  _operationResultCharacteristic->setValue(_jsonEncoder.encodeOperationSuccess(id, data));
  _operationResultCharacteristic->notify();
}

void BLEController::deviceCommandCallback(const DeviceCommandEntity& command) {
  StaticJsonDocument<256> doc;
  String jsonString = _jsonEncoder.encodeDeviceCommandEntity(command, doc);
  _receiveRfDataCharacteristic->setValue(jsonString);
  _receiveRfDataCharacteristic->notify();
  Serial.println("Device RF Data Command Callback JSON: " + jsonString);
}

// Trampoline for operation exception callbacks
void BLEController::exceptionCallbackTrampoline(const char* id, ExceptionEntity exception, JsonObject params) {
  if (_bleControllerInstance != nullptr) {
    _bleControllerInstance->operationExceptionCallback(id, exception, params);
  }
}

void BLEController::successCallbackTrampoline(const char* id, JsonObject data) {
  if (_bleControllerInstance != nullptr) {
    _bleControllerInstance->operationSuccessCallback(id, data);
  }
}

// Trampoline for device command callbacks
void BLEController::deviceCommandCallbackTrampoline(const DeviceCommandEntity& command) {
  if (_bleControllerInstance != nullptr) {
    _bleControllerInstance->deviceCommandCallback(command);
  } else {
    Serial.println("BLE Controller instance is null in device command callback trampoline");
  }
}