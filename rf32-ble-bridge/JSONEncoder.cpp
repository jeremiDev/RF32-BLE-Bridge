#include "JSONEncoder.h"

#include "Models/Constants.h"
JSONEncoder::JSONEncoder() {}

String JSONEncoder::encodeOperationSuccess(const char* id, const JsonObject& data) {
  StaticJsonDocument<256> doc;
  doc["id"] = id;
  doc["status"] = OPERATION_RESULT_SUCCESS;
  doc["mode"] = OPERATION_RESULT_MODE_RESULT;
  JsonObject dataObj = doc.createNestedObject("data");
  dataObj.set(data);

  String jsonStr;
  serializeJson(doc, jsonStr);
  return jsonStr;
}

String JSONEncoder::encodeOperationFailure(const char* id, const ExceptionEntity& exception, const JsonObject& data) {
  StaticJsonDocument<256> doc;
  doc["id"] = id;
  doc["status"] = OPERATION_RESULT_EXCEPTION;
  doc["mode"] = OPERATION_RESULT_MODE_RESULT;

  JsonObject dataObj = doc.createNestedObject("data");
  dataObj.set(data);

  JsonObject exceptionObj = doc.createNestedObject("exception");
  exceptionObj["code"] = exception.code;
  exceptionObj["type"] = exception.type;
  exceptionObj["description"] = exception.description;

  String jsonStr;
  serializeJson(doc, jsonStr);
  return jsonStr;
}

String JSONEncoder::encodeRadioConfigurationEntity(const RadioConfigurationEntity& radioConfigurationEntity, StaticJsonDocument<256>& doc) {
  doc["mhz"] = radioConfigurationEntity.mhz;
  doc["modulation"] = radioConfigurationEntity.modulation;
  doc["rxBw"] = radioConfigurationEntity.rxBw;
  doc["dRateKbps"] = radioConfigurationEntity.dRateKbps;
  doc["syncMode"] = radioConfigurationEntity.syncMode;
  doc["pktFormat"] = radioConfigurationEntity.pktFormat;
  doc["crc"] = radioConfigurationEntity.crc;
  doc["pa"] = radioConfigurationEntity.pa;
  String jsonStr;
  size_t result = serializeJson(doc, jsonStr);
  if (result == 0) {
    return "";
  } else {
    return jsonStr;
  }
}

String JSONEncoder::encodeModeEntity(const ModeEntity& modeEntity, StaticJsonDocument<256>& doc) {
  doc["mode"] = modeEntity.mode;
  String jsonStr;
  size_t result = serializeJson(doc, jsonStr);
  if (result == 0) {
    return "";
  } else {
    return jsonStr;
  }
}

String JSONEncoder::encodeStatusEntity(const StatusEntity& statusEntity, StaticJsonDocument<256>& doc) {
  doc["status"] = statusEntity.status;
  doc["version"] = statusEntity.version;
  doc["build"] = statusEntity.build;
  doc["uptime_ms"] = statusEntity.uptime_ms;
  String jsonStr;
  size_t result = serializeJson(doc, jsonStr);
  if (result == 0) {
    return "";
  } else {
    return jsonStr;
  }
}

String JSONEncoder::encodeDeviceCommandEntity(const DeviceCommandEntity& deviceCommandEntity, StaticJsonDocument<256>& doc) {
  doc["value"] = deviceCommandEntity.value;
  doc["bitlen"] = deviceCommandEntity.bitlen;
  doc["pulseUs"] = deviceCommandEntity.pulseUs;
  String jsonStr;
  size_t result = serializeJson(doc, jsonStr);
  if (result == 0) {
    return "";
  } else {
    return jsonStr;
  }
}