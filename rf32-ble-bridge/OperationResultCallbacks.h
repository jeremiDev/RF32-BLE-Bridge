#ifndef OPERATION_RESULT_CALLBACKS_H
#define OPERATION_RESULT_CALLBACKS_H


class OperationResultCallbacks : public NimBLECharacteristicCallbacks {
  void onSubscribe(NimBLECharacteristic* characteristic, NimBLEConnInfo& connInfo, uint16_t subValue) override {
    (void)characteristic;
    (void)connInfo;
  }
};

#endif