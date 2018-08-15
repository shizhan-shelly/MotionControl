// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef THCSYNCHANDLER_H__
#define THCSYNCHANDLER_H__

#include "SyncHandler.h"

class THCSyncHandler : public SyncHandler {
 public:
  std::map<std::string, std::string> UpdateTHCParameterFromCutChart() {
    sync_data_.clear();
    sync_data_.insert(std::make_pair("IgnitionHeight", ""));
    sync_data_.insert(std::make_pair("CuttingHeight", ""));
    sync_data_.insert(std::make_pair("PierceHeight", ""));
    sync_data_.insert(std::make_pair("PierceTime", ""));
    sync_data_.insert(std::make_pair("CuttingVoltage", ""));
    sync_data_.insert(std::make_pair("CutHeightDelay", ""));
    return sync_data_;
  }

}; // class THCSyncHandler

#endif // THCSYNCHANDLER_H__
