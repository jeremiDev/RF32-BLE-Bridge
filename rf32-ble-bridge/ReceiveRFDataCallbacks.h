#ifndef RECEIVE_RF_DATA_CALLBACKS_H
#define RECEIVE_RF_DATA_CALLBACKS_H


class ReceiveRfDataCallbacks : public NimBLECharacteristicCallbacks {
  void onSubscribe(NimBLECharacteristic* characteristic, NimBLEConnInfo& connInfo, uint16_t subValue) override {
    (void)characteristic;
    (void)connInfo;
  }
};

#endif