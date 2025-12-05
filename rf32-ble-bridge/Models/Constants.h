#ifndef CONSTANTS_H
#define CONSTANTS_H

// ---------------------------
// Constants
// ---------------------------

// -------------------- Pins --------------------
constexpr uint8_t PIN_CC1101_SCK = 18;
constexpr uint8_t PIN_CC1101_MISO = 19;
constexpr uint8_t PIN_CC1101_MOSI = 23;
constexpr uint8_t PIN_CC1101_CS = 5;
constexpr uint8_t PIN_CC1101_GDO0 = 4;

// -------------------- Constants --------------------
static const char* NIMBLE_DEVICE_NAME = "RF32-BLE-Bridge";
static const char* FW_VERSION = "1.1.0";
static const char* APP_NAME = "RF32 BLE Bridge";

// -------------------- BLE Constants --------------------
static const char* SERVICE_UUID = "6E400001-B5A3-F393-E0A9-E50A24DCCA9E";

// -------------------- Characteristic UUIDs --------------------
static const char* STATUS_CHARACTERISTIC_UUID = "6E400004-B5A3-F393-E0A9-E50E24DCCA9E";
static const char* RADIO_CONFIGURATION_CHARACTERISTIC_UUID = "6E400005-B5A3-F393-E0A9-E50E24DCCA9E";
static const char* MODE_CHARACTERISTIC_UUID = "6E400006-B5A3-F393-E0A9-E50E24DCCA9E";
static const char* RECEIVE_RF_DATA_CHARACTERISTIC_UUID = "6E400008-B5A3-F393-E0A9-E50E24DCCA9E";
static const char* SEND_RF_DATA_CHARACTERISTIC_UUID = "6E400009-B5A3-F393-E0A9-E50E24DCCA9E";

static const char* OPERATION_RESULT_CHARACTERISTIC_UUID = "6E400007-B5A3-F393-E0A9-E50E24DCCA9E";

// -------------------- Operation Result Types --------------------
static const char* OPERATION_RESULT_MODE_RESULT = "OPERATION_RESULT";
static const char* OPERATION_RESULT_SUCCESS = "SUCCESS";
static const char* OPERATION_RESULT_EXCEPTION = "EXCEPTION";


#endif