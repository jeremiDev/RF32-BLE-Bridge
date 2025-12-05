#ifndef STATUS_H
#define STATUS_H

#include "Models/DataModels.h"

class StatusModule {
public:
  StatusModule();

  void setup();

  void setStatus(const char* status);
  StatusEntity getStatus();

private:
  StatusEntity _status;
};

#endif