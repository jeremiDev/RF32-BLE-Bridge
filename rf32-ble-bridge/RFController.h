#ifndef RF_CONTROLLER_H
#define RF_CONTROLLER_H

#include <ELECHOUSE_CC1101_SRC_DRV.h>
#include <RCSwitch.h>
#include "Models/DataModels.h"
#include "Models/Constants.h"
#include "DeviceController.h"

class RFController : public DeviceController {
public:
  RFController();
  bool setup() override;
  void loop() override;

  void applyConfig(const RadioConfigurationEntity& radioConfiguration) override;
  RadioConfigurationEntity getRadioConfiguration() override;

  void setMode(RadioMode m) override;
  RadioMode getMode() override;

  void sendCommand(const DeviceCommandEntity& c) override;
  void setDeviceCommandCallback(DeviceCommandCallback callback) override;
  void executePendingCommand();

private:
  RCSwitch _rcSwitch;
  RadioMode _radioMode;
  RadioConfigurationEntity _radioConfiguration;
  DeviceCommandCallback _deviceCommandCallback;

  DeviceCommandEntity _pendingCommand;
  bool _commandNeedsToBeSent = false;
  bool _wasInRxMode = false;
};

#endif