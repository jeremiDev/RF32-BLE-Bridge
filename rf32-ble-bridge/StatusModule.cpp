#include "StatusModule.h"
#include <Arduino.h>
#include "Models/Constants.h"

StatusModule::StatusModule() {
}

void StatusModule::setup() {
  _status.status = "Launching";
  _status.version = FW_VERSION;
  _status.build = String(__DATE__) + " " + String(__TIME__);
  _status.uptime_ms = (uint32_t)millis();
}

void StatusModule::setStatus(const char* status) {
  _status.uptime_ms = (uint32_t)millis();
  _status.status = status;
}

StatusEntity StatusModule::getStatus() {
  _status.uptime_ms = (uint32_t)millis();
  return _status;
}