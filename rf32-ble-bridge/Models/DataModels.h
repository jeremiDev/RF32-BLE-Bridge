// RF32 BLE Bridge
// Copyright © 2025, Jeremiasz Grzesiuk (JeremiDev)
// MIT License

#ifndef DATA_MODELS_H
#define DATA_MODELS_H

#include <ArduinoJson.h>

// ---------------------------
// Enums
// ---------------------------

enum class RadioMode { TX,
                       RX };

// ---------------------------
// Data Models
// ---------------------------

// Radio Configuration Entity
struct RadioConfigurationEntity {
  //387MHz-464MHz, depending on the model
  double mhz = 433.92;  // MHz

  //Valid modulation values:
  //0 – 2-FSK
  //1 – GFSK
  //2 – ASK/OOK      (most cheap RF remotes)
  //3 – MSK
  //4 – ??? (reserved/rare)
  int modulation = 2;

  //Receiver bandwidth in kHz. Common values:
  //58  67  81  102  116  135  158  203  232  270  325  396  464  541  650
  double rxBw = 203.0;  // kHz

  //Datarate in kbps. Common values
  //1.2   2.4   4.8   10  38  50  100 250 500
  double dRateKbps = 2.4;

  //Synchronization mode values:
  //0 – No sync word (For raw OOK remotes)
  //1 – 15/16 sync word bits detected
  //2 – 16/16 sync word bits detected
  //3 – 30/32 sync word bits detected
  //4 – No preamble/sync (carrier sense)
  //5 – Carrier-sense above threshold
  //6 – Carrier-sense + 15/16 sync
  //7 – Carrier-sense + 16/16 sync
  int syncMode = 0;

  //Packet format settings:
  //0 – Normal FIFO mode
  //1 – Synchronous serial mode
  //2 – Random TX mode
  //3 – Asynchronous serial mode
  int pktFormat = 3;

  //CRC Options
  //Cyclic Redundancy Check
  //It is a method used to detect errors in transmitted data.
  //0 – No CRC
  //1 – CRC enabled
  int crc = 0;

  //PA (power amplifier) level index.
  //Library maps 0–10 to dBm:
  //0 = –30 dBm
  //1 = –20
  //2 = –15
  //3 = –10
  //4 = –6
  //5 = 0
  //6 = +5
  //7 = +7
  //8 = +10
  //9 = +12
  //10 = +12 (max)
  int pa = 9;
};

// Device Status Entity
struct StatusEntity {
  const char* status = "NOT_READY";
  const char* version = "...";
  String build = "...";
  uint32_t uptime_ms = 0;
};

// Mode Entity
struct ModeEntity {
  const char* mode = "TX";
};

// Exception Entity for write / save operations
struct ExceptionEntity {
  int code;
  const char* type;
  const char* description;
};

// Operation Result Entity for write / save operations
struct OperationResultEntity {
  const char* id;
  const char* status;
  const char* mode;
  const JsonObject* data;
  const ExceptionEntity* exception;
};

// Device Command Entity - used to send commands to the device from the client
struct DeviceCommandEntity {
  uint32_t value;
  uint32_t bitlen;
  uint32_t pulseUs;
};

// Operation Entity - generic operation wrapper that contains the id and the data
struct OperationEntity {
  const char* id;
  JsonObject data;
};

// JSON Decode statuses
struct DecodeEntityStatus {
  bool success;
  int code;
  String objectName;
  String errorMessage;
};

// JSON Encode statuses
struct EncodeEntityStatus {
  bool success;
  int code;
  String objectName;
  String errorMessage;
};

// Validation statuses
struct ValidationEntityStatus {
  bool success;
  int code;
  String objectName;
  String errorMessage;
};

// Callbacks for operation results - used to handle the results of the operations
typedef void (*OperationExceptionCallback)(const char* id, ExceptionEntity exception, JsonObject params);
typedef void (*OperationSuccessCallback)(const char* id, JsonObject data);

// Callbacks for device commands - used to handle the commands received from the client
typedef void (*DeviceCommandCallback)(const DeviceCommandEntity& command);

#endif