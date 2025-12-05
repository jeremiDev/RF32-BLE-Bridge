#include "JSONDecoder.h"

JSONDecoder::JSONDecoder() {
}

DecodeEntityStatus JSONDecoder::decodeOperationEntity(StaticJsonDocument<256>& doc, const char* jsonStr, OperationEntity& operationEntity) {
  constexpr const char* objectName = "OperationEntity";

  DeserializationError err = deserializeJson(doc, jsonStr);
  if (err) {
    return DecodeEntityStatus{ false, 1, objectName, "Invalid JSON" };
  }

  JsonVariant idVar = doc["id"];
  if (idVar.isNull()) {
    return DecodeEntityStatus{ false, 2, objectName, "Missing id or id is not a string" };
  } else if (!idVar.is<const char*>()) {
    return DecodeEntityStatus{ false, 2, objectName, "Id is not a string" };
  }

  JsonVariant dataVar = doc["data"];
  if (dataVar.isNull()) {
    return DecodeEntityStatus{ false, 3, objectName, "Missing data or data is not a JSON object" };
  } else if (!dataVar.is<JsonObject>()) {
    return DecodeEntityStatus{ false, 3, objectName, "Data is not a JSON object" };
  }

  operationEntity.id = idVar.as<const char*>();
  operationEntity.data = dataVar.as<JsonObject>();

  return DecodeEntityStatus{ true, 0, objectName, "" };
}

DecodeEntityStatus JSONDecoder::decodeRadioConfigurationEntity(StaticJsonDocument<256>& doc, const JsonObject& jsonObject, RadioConfigurationEntity& radioConfigurationEntity) {
  constexpr const char* objectName = "RadioConfigurationEntity";

  JsonVariant mhzVar = jsonObject["mhz"];
  if (mhzVar.isNull()) {
    return DecodeEntityStatus{ false, 1, objectName, "Missing mhz or mhz is not a number" };
  } else if (!mhzVar.is<double>()) {
    return DecodeEntityStatus{ false, 1, objectName, "Mhz is not a number" };
  }

  JsonVariant modulationVar = jsonObject["modulation"];
  if (modulationVar.isNull()) {
    return DecodeEntityStatus{ false, 2, objectName, "Missing modulation or modulation is not a number" };
  } else if (!modulationVar.is<int>()) {
    return DecodeEntityStatus{ false, 2, objectName, "Modulation is not a number" };
  }

  JsonVariant rxBwVar = jsonObject["rxBw"];
  if (rxBwVar.isNull()) {
    return DecodeEntityStatus{ false, 3, objectName, "Missing rxBw or rxBw is not a number" };
  } else if (!rxBwVar.is<double>()) {
    return DecodeEntityStatus{ false, 3, objectName, "RxBw is not a number" };
  }

  JsonVariant dRateKbpsVar = jsonObject["dRateKbps"];
  if (dRateKbpsVar.isNull()) {
    return DecodeEntityStatus{ false, 4, objectName, "Missing dRateKbps or dRateKbps is not a number" };
  } else if (!dRateKbpsVar.is<double>()) {
    return DecodeEntityStatus{ false, 4, objectName, "DRateKbps is not a number" };
  }

  JsonVariant syncModeVar = jsonObject["syncMode"];
  if (syncModeVar.isNull()) {
    return DecodeEntityStatus{ false, 5, objectName, "Missing syncMode or syncMode is not a number" };
  } else if (!syncModeVar.is<int>()) {
    return DecodeEntityStatus{ false, 5, objectName, "SyncMode is not a number" };
  }

  JsonVariant pktFormatVar = jsonObject["pktFormat"];
  if (pktFormatVar.isNull()) {
    return DecodeEntityStatus{ false, 6, objectName, "Missing pktFormat or pktFormat is not a number" };
  } else if (!pktFormatVar.is<int>()) {
    return DecodeEntityStatus{ false, 6, objectName, "PktFormat is not a number" };
  }

  JsonVariant crcVar = jsonObject["crc"];
  if (crcVar.isNull()) {
    return DecodeEntityStatus{ false, 7, objectName, "Missing crc or crc is not a number" };
  } else if (!crcVar.is<int>()) {
    return DecodeEntityStatus{ false, 7, objectName, "Crc is not a number" };
  }

  JsonVariant paVar = jsonObject["pa"];
  if (paVar.isNull()) {
    return DecodeEntityStatus{ false, 8, objectName, "Missing pa or pa is not a number" };
  } else if (!paVar.is<int>()) {
    return DecodeEntityStatus{ false, 8, objectName, "Pa is not a number" };
  }

  radioConfigurationEntity.mhz = mhzVar.as<double>();
  radioConfigurationEntity.modulation = modulationVar.as<int>();
  radioConfigurationEntity.rxBw = rxBwVar.as<double>();
  radioConfigurationEntity.dRateKbps = dRateKbpsVar.as<double>();
  radioConfigurationEntity.syncMode = syncModeVar.as<int>();
  radioConfigurationEntity.pktFormat = pktFormatVar.as<int>();
  radioConfigurationEntity.crc = crcVar.as<int>();
  radioConfigurationEntity.pa = paVar.as<int>();

  return DecodeEntityStatus{ true, 0, objectName, "" };
}

DecodeEntityStatus JSONDecoder::decodeDeviceCommandEntity(StaticJsonDocument<256>& doc, const JsonObject& jsonObject, DeviceCommandEntity& deviceCommandEntity) {
  constexpr const char* objectName = "DeviceCommandEntity";

  JsonVariant valueVar = jsonObject["value"];
  if (valueVar.isNull()) {
    return DecodeEntityStatus{ false, 1, objectName, "Missing value or value is not a number" };
  } else if (!valueVar.is<uint32_t>()) {
    return DecodeEntityStatus{ false, 1, objectName, "Value is not a number" };
  }

  JsonVariant bitlenVar = jsonObject["bitlen"];
  if (bitlenVar.isNull()) {
    return DecodeEntityStatus{ false, 2, objectName, "Missing bitlen or bitlen is not a number" };
  } else if (!bitlenVar.is<uint32_t>()) {
    return DecodeEntityStatus{ false, 2, objectName, "Bitlen is not a number" };
  }

  JsonVariant pulseUsVar = jsonObject["pulseUs"];
  if (pulseUsVar.isNull()) {
    return DecodeEntityStatus{ false, 3, objectName, "Missing pulseUs or pulseUs is not a number" };
  } else if (!pulseUsVar.is<uint32_t>()) {
    return DecodeEntityStatus{ false, 3, objectName, "PulseUs is not a number" };
  }

  deviceCommandEntity.value = valueVar.as<uint32_t>();
  deviceCommandEntity.bitlen = bitlenVar.as<uint32_t>();
  deviceCommandEntity.pulseUs = pulseUsVar.as<uint32_t>();

  return DecodeEntityStatus{ true, 0, objectName, "" };
}

DecodeEntityStatus JSONDecoder::decodeModeEntity(StaticJsonDocument<256>& doc, const JsonObject& jsonObject, ModeEntity& modeEntity) {
  constexpr const char* objectName = "ModeEntity";

  JsonVariant modeVar = jsonObject["mode"];
  if (modeVar.isNull()) {
    return DecodeEntityStatus{ false, 1, objectName, "Missing mode or mode is not a string" };
  } else if (!modeVar.is<const char*>()) {
    return DecodeEntityStatus{ false, 1, objectName, "Mode is not a string" };
  }

  modeEntity.mode = modeVar.as<const char*>();

  return DecodeEntityStatus{ true, 0, objectName, "" };
}