#ifndef SERVER_CALLBACKS_H
#define SERVER_CALLBACKS_H


class ServerCallbacks : public NimBLEServerCallbacks {
  void onConnect(NimBLEServer* server, NimBLEConnInfo& connInfo) override {
    (void)server;
    (void)connInfo;
    Serial.println("Central connected.");
  }

  void onDisconnect(NimBLEServer* server, NimBLEConnInfo& connInfo, int reason) override {
    (void)connInfo;
    Serial.printf("Central disconnected (reason %d)\n", reason);
    NimBLEDevice::startAdvertising();
  }
};

#endif