// RF32 BLE Bridge
// Copyright © 2025, Jeremiasz Grzesiuk (JeremiDev)
// MIT License

#include "RFController.h"

RFController::RFController() {
  _radioMode = RadioMode::TX;
}

bool RFController::setup() {
  Serial.println("RF Controller setup starting...");
  // Configure CC1101 Pins
  ELECHOUSE_cc1101.setSpiPin(PIN_CC1101_SCK, PIN_CC1101_MISO, PIN_CC1101_MOSI, PIN_CC1101_CS);

  // Initialize Driver
  ELECHOUSE_cc1101.Init();

  // Check connection
  if (!ELECHOUSE_cc1101.getCC1101()) {
    Serial.println("Error: CC1101 not responding, check wiring and power.");
    return false;
  } else {
    Serial.println("CC1101 initialized successfully");
  }

  // Set configuration default values
  _radioConfiguration = RadioConfigurationEntity(
    433.92,
    2,
    203.0,
    2.4,
    0,
    3,
    0,
    8);
  applyConfig(_radioConfiguration);

  // Set default mode to TX
  _radioMode = RadioMode::RX;
  setMode(RadioMode::TX);

  Serial.println("RF Controller setup complete");
  return true;
}

void RFController::loop() {
  if (_radioMode == RadioMode::RX) {
    if (_rcSwitch.available()) {
      unsigned long value = _rcSwitch.getReceivedValue();
      unsigned int bitlen = _rcSwitch.getReceivedBitlength();
      unsigned int pulseUs = _rcSwitch.getReceivedDelay();

      DeviceCommandEntity deviceCommandEntity = DeviceCommandEntity(value, bitlen, pulseUs);
      Serial.println("Received RF Data: Value: " + String(deviceCommandEntity.value) + " Bitlen: " + String(deviceCommandEntity.bitlen) + " PulseUs: " + String(deviceCommandEntity.pulseUs));

      _deviceCommandCallback(deviceCommandEntity);

      _rcSwitch.resetAvailable();
    }
  } else {
    //This approach is required by stability of sending library - do not execute it outside of loop
    executePendingCommand();
  }
}

void RFController::executePendingCommand() {
  if (_radioMode == RadioMode::TX && _commandNeedsToBeSent) {
    Serial.println("Sending command: Value: " + String(_pendingCommand.value) + " Bitlen: " + String(_pendingCommand.bitlen) + " PulseUs: " + String(_pendingCommand.pulseUs) + "....");

    _rcSwitch.setProtocol(1);
    _rcSwitch.setPulseLength(_pendingCommand.pulseUs);
    _rcSwitch.send(_pendingCommand.value, _pendingCommand.bitlen);

    // Go back to RX mode if we were in RX mode before sending the command
    if (_wasInRxMode) {
      setMode(RadioMode::RX);
    }

    _commandNeedsToBeSent = false;
  }
}

void RFController::applyConfig(const RadioConfigurationEntity& radioConfiguration) {
  Serial.println("Applying RF Configuration: MHz: " + String(radioConfiguration.mhz) + " Modulation: " + String(radioConfiguration.modulation) + " RxBw: " + String(radioConfiguration.rxBw) + " DRateKbps: " + String(radioConfiguration.dRateKbps) + " SyncMode: " + String(radioConfiguration.syncMode) + " PktFormat: " + String(radioConfiguration.pktFormat) + " Crc: " + String(radioConfiguration.crc) + " Pa: " + String(radioConfiguration.pa));
  ELECHOUSE_cc1101.setMHZ(radioConfiguration.mhz);
  ELECHOUSE_cc1101.setModulation(radioConfiguration.modulation);
  ELECHOUSE_cc1101.setRxBW(radioConfiguration.rxBw);
  ELECHOUSE_cc1101.setDRate(radioConfiguration.dRateKbps);
  ELECHOUSE_cc1101.setSyncMode(radioConfiguration.syncMode);
  ELECHOUSE_cc1101.setPktFormat(radioConfiguration.pktFormat);
  ELECHOUSE_cc1101.setGDO0(0x0D);
  ELECHOUSE_cc1101.setCrc(radioConfiguration.crc);
  ELECHOUSE_cc1101.setPA(radioConfiguration.pa);
  _radioConfiguration = radioConfiguration;
}

RadioConfigurationEntity RFController::getRadioConfiguration() {
  return _radioConfiguration;
}

void RFController::setMode(RadioMode m) {
  if (m == _radioMode) return;
  _radioMode = m;

  if (m == RadioMode::TX) {
    pinMode(PIN_CC1101_GDO0, OUTPUT);
    ELECHOUSE_cc1101.SetTx();

    _rcSwitch.enableTransmit(PIN_CC1101_GDO0);

    Serial.println("RF Controller set mode to TX");

  } else {
    pinMode(PIN_CC1101_GDO0, INPUT);
    ELECHOUSE_cc1101.SetRx();

    _rcSwitch.enableReceive(PIN_CC1101_GDO0);
    _rcSwitch.disableTransmit();

    Serial.println("RF Controller set mode to RX");
  }
  delay(50);
}

RadioMode RFController::getMode() {
  return _radioMode;
}

void RFController::sendCommand(const DeviceCommandEntity& c) {
  if (_radioMode == RadioMode::RX) {
    _wasInRxMode = true;
  }
  setMode(RadioMode::TX);

  _pendingCommand = c;
  _commandNeedsToBeSent = true;
}

void RFController::setDeviceCommandCallback(DeviceCommandCallback callback) {
  Serial.println("Setting Device Command Callback");
  _deviceCommandCallback = callback;
}