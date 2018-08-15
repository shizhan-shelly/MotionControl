// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef DATABASE_PLASMACUTTECHNOLOGY_SYNCHANDLER_H__
#define DATABASE_PLASMACUTTECHNOLOGY_SYNCHANDLER_H__

#include <map>

class SyncHandler {
 public:
  virtual ~SyncHandler() {}

  virtual std::map<std::string, std::string> UpdateParameterFromCutChart() = 0;

 protected:
  std::map<std::string, std::string> sync_data_;

};

#endif // DATABASE_PLASMACUTTECHNOLOGY_SYNCHANDLER_H__
