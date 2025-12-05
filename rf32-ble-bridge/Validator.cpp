// RF32 BLE Bridge
// Copyright © 2025, Jeremiasz Grzesiuk (JeremiDev)
// MIT License

#include "Validator.h"
#include <Models/Constants.h>
#include <Models/ExceptionCodes.h>

Validator::Validator() {}

bool Validator::validFreqBand(double mhz) {
  return (mhz >= 300.0 && mhz <= 348.0) || (mhz >= 387.0 && mhz <= 464.0) || (mhz >= 779.0 && mhz <= 928.0);
}

ValidationEntityStatus Validator::validateConfig(const RadioConfigurationEntity& config) {
  constexpr const char* objectName = "RadioConfigurationEntity";

  if (config.mhz <= 0) {
    return ValidationEntityStatus{ false, 1, objectName, "mhz must be >0" };
  }

  if (!validFreqBand(config.mhz)) {
    return ValidationEntityStatus{ false, 2, objectName, "mhz out of allowed bands" };
  }

  if (config.rxBw <= 0) {
    return ValidationEntityStatus{ false, 3, objectName, "rxBw must be >0" };
  }

  if (config.dRateKbps <= 0) {
    return ValidationEntityStatus{ false, 4, objectName, "dRateKbps must be >0" };
  }

  if (config.syncMode < 0 || config.syncMode > 7) {
    return ValidationEntityStatus{ false, 5, objectName, "syncMode must be 0-7" };
  }

  if (config.pktFormat < 0 || config.pktFormat > 3) {
    return ValidationEntityStatus{ false, 6, objectName, "pktFormat must be 0-3" };
  }

  if (config.crc < 0 || config.crc > 1) {
    return ValidationEntityStatus{ false, 7, objectName, "crc must be 0-1" };
  }

  if (config.pa < 0 || config.pa > 10) {
    return ValidationEntityStatus{ false, 8, objectName, "pa must be 0-10" };
  }

  return ValidationEntityStatus{ true, 0, objectName, "" };
}

ValidationEntityStatus Validator::validateDeviceCommand(const DeviceCommandEntity& command) {
  constexpr const char* objectName = "DeviceCommandEntity";

  if (command.pulseUs < 0) {
    return ValidationEntityStatus{ false, 1, objectName, "pulseUs must be >0" };
  }

  if (command.bitlen < 0) {
    return ValidationEntityStatus{ false, 2, objectName, "bitlen must be >0" };
  }

  if (command.value < 0) {
    return ValidationEntityStatus{ false, 3, objectName, "value must be >0" };
  }

  return ValidationEntityStatus{ true, 0, objectName, "" };
}

ValidationEntityStatus Validator::validateMode(const ModeEntity& mode) {
  constexpr const char* objectName = "ModeEntity";

  if (String(mode.mode) != "TX" && String(mode.mode) != "RX") {
    String errorMessage = "mode must be TX or RX, got ";
    errorMessage += mode.mode;
    return ValidationEntityStatus{ false, 1, objectName, errorMessage };
  }

  return ValidationEntityStatus{ true, 0, objectName, "" };
}