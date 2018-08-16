// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef DATABASE_PLASMACUTTECHNOLOGY_SYNCHANDLER_H__
#define DATABASE_PLASMACUTTECHNOLOGY_SYNCHANDLER_H__

#include <map>
#include <string>

class SyncHandler {
 public:
  virtual ~SyncHandler() {}

  virtual std::map<std::string, std::string> UpdateCNCParameterFromCutChart() = 0;
  virtual std::map<std::string, std::string> UpdateTHCParameterFromCutChart() = 0;
  virtual std::map<std::string, std::string> UpdatePPSParameterFromCutChart() = 0;

 protected:
  std::map<std::string, std::string> cnc_data_;
  std::map<std::string, std::string> thc_data_;
  std::map<std::string, std::string> pps_data_;

};

#define DECLARE_SYNCHANDLER_CLASS(VENDOR) \
  class VENDOR##SyncHandler: public SyncHandler { \
   public: \
    virtual std::map<std::string, std::string> UpdateCNCParameterFromCutChart(); \
    virtual std::map<std::string, std::string> UpdateTHCParameterFromCutChart(); \
    virtual std::map<std::string, std::string> UpdatePPSParameterFromCutChart(); \
  }; \

DECLARE_SYNCHANDLER_CLASS(Kjellberg)
DECLARE_SYNCHANDLER_CLASS(Hypertherm)
DECLARE_SYNCHANDLER_CLASS(Liuhe)

#endif // DATABASE_PLASMACUTTECHNOLOGY_SYNCHANDLER_H__
