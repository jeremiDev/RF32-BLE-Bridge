// RF32 BLE Bridge
// Copyright © 2025, Jeremiasz Grzesiuk (JeremiDev)
// MIT License

#ifndef RECEIVE_RF_DATA_CALLBACKS_H
#define RECEIVE_RF_DATA_CALLBACKS_H


class ReceiveRfDataCallbacks : public NimBLECharacteristicCallbacks {
  void onSubscribe(NimBLECharacteristic* characteristic, NimBLEConnInfo& connInfo, uint16_t subValue) override {
    (void)characteristic;
    (void)connInfo;
  }
};

#endif