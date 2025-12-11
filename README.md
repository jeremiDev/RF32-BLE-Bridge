# RF32-BLE-Bridge
Arduino/ESP32 BLE-to-RF bridge that relays radio commands from a BLE device and from RF to BLE. Based on CC1101 transmitter / receiver

## 1) Goal of the project
Provide a lightweight bridge that lets a BLE central (e.g., phone/app/hub) interact with 315/433 MHz RF remotes and devices via an ESP32. The bridge:
- Receives RF codes and forwards them to the BLE central.
- Accepts BLE commands and transmits them over RF.
This is useful for integrating legacy RF devices (remotes, sensors, actuators) into modern BLE/IoT systems (e.g., a smart scoreboard controller).

## 2) Main characteristics
- **Platform**: ESP32 (Arduino) + CC1101 RF transceiver.
- **BLE stack**: NimBLE-Arduino (low memory footprint, GATT server).
- **RF handling**: SmartRC-CC1101 driver + rc-switch for OOK/ASK coding.
- **JSON protocol**: ArduinoJson-based encoder/decoder for requests and notifications.
- **Configurable radio**: Frequency, modulation, RxBW, data rate, sync mode, packet format, CRC, PA level.
- **Bidirectional flow**:
  - BLE Write → RF transmit (Send RF Data).
  - RF receive → BLE Notify (Receive RF Data).
- **GATT layout** (single service):
  - Status (READ)
  - Radio Configuration (READ/WRITE)
  - Mode (READ/WRITE; TX/RX)
  - Send RF Data (WRITE)
  - Receive RF Data (NOTIFY)
  - Operation Result (NOTIFY; success/exception)
- **Versioned device info**: Device name, firmware version exposed in logs and status.

## 3) Where are the constants
- Core constants and UUIDs: `rf32-ble-bridge/Models/Constants.h`
  - Device name (`NIMBLE_DEVICE_NAME`), firmware version (`FW_VERSION`), BLE service and characteristic UUIDs, CC1101 pin mapping.
- Exception codes and types: `rf32-ble-bridge/Models/ExceptionCodes.h`

## 4) Used architecture
- **Entry point**: `rf32-ble-bridge/rf32-ble-bridge.ino`
  - Initializes serial, constructs `App`, prints `APP_NAME`, `FW_VERSION`, build date/time.
- **Composition root**: `rf32-ble-bridge/App.{h,cpp}`
  - Wires modules: `RFController` (device side, radio) and `BLEController` (client side, BLE).
  - Sets up status, registers callback trampoline from RF → BLE.
  - Runs cooperative `loop()` calling RF then BLE controllers.
- **Abstractions**:
  - `DeviceController` (radio-side API): apply/get config, set/get mode, send command, callbacks.
  - `ClientController` (BLE-side API): setup/loop, operation result callbacks, device command callback.
- **Radio layer**: `rf32-ble-bridge/RFController.{h,cpp}`
  - Configures CC1101, manages TX/RX mode, uses rc-switch for encoding/decoding OOK/ASK.
  - Debounces TX via a pending send executed in `loop()`; notifies received frames upward.
- **BLE layer**: `rf32-ble-bridge/BLEController.{h,cpp}`
  - Creates GATT service and characteristics
    - Attaches characteristic-specific callbacks:
      - **Status**
        - Callback: `StatusCallbacks`
        - Access: READ-only
        - Returns: JSON `StatusEntity` (fields: status, version, build, uptime)
        - Purpose: Clients check readiness/health
      - **Radio Configuration**
        - Callback: `RadioConfigurationCallbacks`
        - Access:
          - READ: returns current `RadioConfigurationEntity`
          - WRITE: accepts JSON, validates via `Validator`, applies with `DeviceController::applyConfig`, emits an Operation Result
      - **Mode**
        - Callback: `ModeCallbacks`
        - Access:
          - READ: shows current mode (`TX`/`RX`)
          - WRITE: switches CC1101 mode via `DeviceController::setMode`, validates input, emits an Operation Result
      - **Send RF Data**
        - Callback: `SendRfDataCallbacks`
        - Access: WRITE-only
        - Accepts: JSON `DeviceCommandEntity` {value, bitlen, pulseUs}
        - Actions: validates, schedules TX (executed in `RFController::loop()`), responds with Operation Result
      - **Receive RF Data**
        - Callback: `ReceiveRfDataCallbacks`
        - Access: Notify-only
        - Action: pushes JSON `DeviceCommandEntity` when RF frames are captured in RX
        - Note: Clients must subscribe to receive notifications
      - **Operation Result**
        - Callback: `OperationResultCallbacks`
        - Access: Notify-only
        - Action: Sends per-write-operation outcome:
          - `id`
          - `status` (`SUCCESS`/`EXCEPTION`)
          - Optional: `data` or `exception`
  - Translates operations to/from JSON and triggers success/exception notifications.
- **Data & Validation**:
  - Models: `rf32-ble-bridge/Models/DataModels.h` (entities, enums, statuses).
  - Validation: `rf32-ble-bridge/Validator.{h,cpp}` (sanity checks, maps to `ExceptionCodes.h`).
  - JSON I/O: `rf32-ble-bridge/JSONEncoder.{h,cpp}`, `rf32-ble-bridge/JSONDecoder.{h,cpp}`.
- **Status tracking**: `rf32-ble-bridge/StatusModule.{h,cpp}` (current state, uptime/meta for status reads).
- **3rd‑party libraries (vendored)**: `libraries/`
  - `NimBLE-Arduino` (BLE), `ArduinoJson` (serialization), `SmartRC-CC1101-Driver-Lib` (CC1101), `rc-switch` (OOK/ASK).

