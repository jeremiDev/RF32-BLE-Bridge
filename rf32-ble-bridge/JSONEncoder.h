#ifndef JSON_ENCODER_H
#define JSON_ENCODER_H

#include <ArduinoJson.h>
#include "Models/DataModels.h"

class JSONEncoder {
public:
  JSONEncoder();

  String encodeOperationSuccess(const char* id, const JsonObject& data);
  String encodeOperationFailure(const char* id, const ExceptionEntity& exception, const JsonObject& data);

  // Objects encoders
  String encodeRadioConfigurationEntity(const RadioConfigurationEntity& radioConfigurationEntity, StaticJsonDocument<256>& doc);
  String encodeModeEntity(const ModeEntity& modeEntity, StaticJsonDocument<256>& doc);
  String encodeStatusEntity(const StatusEntity& statusEntity, StaticJsonDocument<256>& doc);
  String encodeDeviceCommandEntity(const DeviceCommandEntity& deviceCommandEntity, StaticJsonDocument<256>& doc);
};

#endif