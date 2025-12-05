#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <Arduino.h>
#include <Models/DataModels.h>

// Validator for logical validation of data inside the models
class Validator {
public:
  Validator();

  bool validFreqBand(double mhz);

  ValidationEntityStatus validateConfig(const RadioConfigurationEntity& config);
  ValidationEntityStatus validateDeviceCommand(const DeviceCommandEntity& command);
  ValidationEntityStatus validateMode(const ModeEntity& mode);
};

#endif