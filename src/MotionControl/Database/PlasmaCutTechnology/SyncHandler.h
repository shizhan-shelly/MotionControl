// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef DATABASE_PLASMACUTTECHNOLOGY_SYNCHANDLER_H__
#define DATABASE_PLASMACUTTECHNOLOGY_SYNCHANDLER_H__

#include <map>
#include <string>

class SyncHandler {
 public:
  virtual ~SyncHandler() {}

  virtual void UpdateCNCParameterFromCutChart() = 0;
  virtual void UpdateTHCParameterFromCutChart() = 0;
  virtual void UpdatePPSParameterFromCutChart() = 0;

  virtual void ModifyParameterFromGCode(const std::map<int, std::string> &code_map) = 0;

  std::map<std::string, std::string> cnc_data_;
  std::map<std::string, std::string> thc_data_;
  std::map<std::string, std::string> pps_data_;

};

#define DECLARE_SYNCHANDLER_CLASS(VENDOR) \
  class VENDOR##SyncHandler: public SyncHandler { \
   public: \
    virtual void UpdateCNCParameterFromCutChart(); \
    virtual void UpdateTHCParameterFromCutChart(); \
    virtual void UpdatePPSParameterFromCutChart(); \
    virtual void ModifyParameterFromGCode(const std::map<int, std::string> &code_map); \
  }; \

DECLARE_SYNCHANDLER_CLASS(Kjellberg)
DECLARE_SYNCHANDLER_CLASS(Hypertherm)
DECLARE_SYNCHANDLER_CLASS(Liuhe)

#endif // DATABASE_PLASMACUTTECHNOLOGY_SYNCHANDLER_H__
