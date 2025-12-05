#ifndef JSON_DECODER_H
#define JSON_DECODER_H

#include <ArduinoJson.h>
#include "Models/DataModels.h"

class JSONDecoder {
public:
  JSONDecoder();

  DecodeEntityStatus decodeOperationEntity(StaticJsonDocument<256>& doc, const char* jsonStr, OperationEntity& decodeEntityStatus);
  DecodeEntityStatus decodeRadioConfigurationEntity(StaticJsonDocument<256>& doc, const JsonObject& jsonObject, RadioConfigurationEntity& radioConfigurationEntity);
  DecodeEntityStatus decodeDeviceCommandEntity(StaticJsonDocument<256>& doc, const JsonObject& jsonObject, DeviceCommandEntity& deviceCommandEntity);
  DecodeEntityStatus decodeModeEntity(StaticJsonDocument<256>& doc, const JsonObject& jsonObject, ModeEntity& modeEntity);
};

#endif
