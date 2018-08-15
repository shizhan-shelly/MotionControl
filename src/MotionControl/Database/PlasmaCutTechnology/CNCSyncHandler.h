// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef DATABASE_PLASMACUTTECHNOLOGY_CNCSYNCHANDLER_H__
#define DATABASE_PLASMACUTTECHNOLOGY_CNCSYNCHANDLER_H__

#include "SyncHandler.h"

class CNCSyncHandler : public SyncHandler {
 public:
   std::map<std::string, std::string> UpdateParameterFromCutChart() {
     sync_data_.clear();
     sync_data_.insert(std::make_pair("CuttingSpeed", ""));
     sync_data_.insert(std::make_pair("Kerf", ""));
     return sync_data_;
   }

}; // class CNCSyncHandler

#endif // DATABASE_PLASMACUTTECHNOLOGY_CNCSYNCHANDLER_H_
