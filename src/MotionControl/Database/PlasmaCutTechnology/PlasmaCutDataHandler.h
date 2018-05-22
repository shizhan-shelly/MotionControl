// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef TESTDBACCESS_H__
#define TESTDBACCESS_H__

#include <map>
#include <vector>

#include "base/singleton/Singleton.h"
#include "SystemConfigDefine.h"
#include "../SQLiteCommand.h"
#include "../SQLiteQuery.h"

class PlasmaCutDataHandler : public Singleton {
  DECLARE_SINGLETON(PlasmaCutDataHandler)

 public:
  bool InitialDatabaseAccess(const std::string &db_file,
                             const std::string &db_key);

  std::vector<std::map<SystemConfigFilter, std::string> > GetSystemConfigItems(
      int vendor_id);

  std::vector<std::string> GetVendorNames();

  int GetVendorID(const std::string &vendor_name);

  // Get all system config table's filed name, its translation
  std::vector<std::pair<std::string, std::string> > GetSystemConfigField();

  // Get system config table's keyword filed name, its translation
  std::vector<std::pair<std::string, std::string> > GetSystemConfigKeywordField();

  // according to the field_name, get the values from system config table.
  std::vector<std::string> GetSystemConfigFieldValues(
      int vendor_id,
      const std::string &field_name);

  std::vector<std::vector<std::pair<std::string, std::string> > > GetSystemConfigRecord(
      int vendor_id,
      const std::vector<std::pair<std::string, std::string> > &keyword_field);

 private:
  PlasmaCutDataHandler();
  ~PlasmaCutDataHandler();

  SQLiteQuery sql_query_;


}; //class PlasmaCutDataHandler

#endif // TESTDBACCESS_H__
