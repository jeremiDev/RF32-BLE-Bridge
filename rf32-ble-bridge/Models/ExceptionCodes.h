#ifndef EXCEPTIONS_CODES_H
#define EXCEPTIONS_CODES_H

// ---------------------------
// Exception Codes
// ---------------------------

// Start a 100 and increment uniquely per error site

constexpr int E_JSON_BAD = 1000;
constexpr int E_CMD_MISSING = 1001;
constexpr int E_CMD_UNSUPPORTED = 1002;
constexpr int E_INCOMING_EMPTY = 1003;
constexpr int E_INVALID_ARG = 1004;

constexpr int E_CFG_BUSY_LISTENING = 1100;
constexpr int E_CFG_MHZ_BAND = 1101;
constexpr int E_CFG_RXBW_INVALID = 1102;
constexpr int E_CFG_INT_MODULATION = 1103;
constexpr int E_CFG_INT_SYNCMODE = 1104;
constexpr int E_CFG_INT_PKTFORMAT = 1105;
constexpr int E_CFG_INT_CRC = 1106;
constexpr int E_CFG_DRATE_INVALID = 1107;
constexpr int E_CFG_PA_INVALID = 1108;
constexpr int E_CFG_SYNCMODE_INVALID = 1109;
constexpr int E_CFG_PKTFORMAT_INVALID = 1110;
constexpr int E_CFG_CRC_INVALID = 1111;

constexpr int E_LISTEN_ALREADY = 1200;
constexpr int E_LISTEN_DENIED_NO_NOTIF = 1201;
constexpr int E_LISTEN_TIMEOUT_ARG = 1202;

constexpr int E_SEND_BUSY = 1300;
constexpr int E_SEND_PARAMS_MISSING = 1301;
constexpr int E_SEND_BITLEN_INVALID = 1302;
constexpr int E_SEND_DELAY_INVALID = 1303;

// -------------------- Exception Types --------------------
static const char* EXCEPTION_TYPE_INVALID_ARG = "INVALID_ARG";
static const char* EXCEPTION_TYPE_BAD_JSON = "BAD_JSON";


#endif