// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef POWERSYNCHANDLER_H__
#define POWERSYNCHANDLER_H__

#include "SyncHandler.h"

class PowerSyncHandler : public SyncHandler {
 public:
  virtual ~PowerSyncHandler();

  virtual std::map<std::string, std::string> UpdateParameterFromCutChart();

}; // class PowerSyncHandler

#endif // POWERSYNCHANDLER_H__
