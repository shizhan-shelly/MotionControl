// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "PlasmaCutDataHandler.h"

static std::map<SystemConfigFilter, std::string> SYSTEM_CONFIG_ITEM_ROW;

PlasmaCutDataHandler::PlasmaCutDataHandler() {}

PlasmaCutDataHandler::~PlasmaCutDataHandler() {}

bool PlasmaCutDataHandler::InitialDatabaseAccess(const std::string &db_file,
                                                 const std::string &db_key) {

  if (!sql_query_.Open(db_file)) {
    return false;
  }
  if (!sql_query_.Key(db_key)) {
    return false;
  }
  return true;
}

std::vector<std::map<SystemConfigFilter, std::string> >
    PlasmaCutDataHandler::GetSystemConfigItems(int vendor_id) {

  char sql[500];
  sprintf(sql, "SELECT * FROM SystemConfig WHERE SystemConfig.VENDOR_ID = %d", vendor_id);
  sql_query_.Prepare(sql);

  std::vector<std::map<SystemConfigFilter, std::string> > items;
  while (sql_query_.Read()) {
    std::map<SystemConfigFilter, std::string> item;
    item[VendorID] = sql_query_.GetStringValue(1);
    item[PlasmaPowerModel] = sql_query_.GetStringValue(2);
    item[GasBoxModel] = sql_query_.GetStringValue(3);
    item[TorchModel] = sql_query_.GetStringValue(4);
    item[Version] = sql_query_.GetStringValue(5);
    item[CuttingChartID] = sql_query_.GetStringValue(0);
    item[SelectedRecord] = sql_query_.GetStringValue(6);
    items.push_back(item);
  }
  return items;
}

std::vector<std::string> PlasmaCutDataHandler::GetVendorNames() {
  char sql[500];
  sprintf(sql, "SELECT NAME FROM Vendor");
  sql_query_.Prepare(sql);

  std::vector<std::string> vendor_name;
  while (sql_query_.Read()) {
    vendor_name.push_back(sql_query_.GetStringValue(0));
  }
  return vendor_name;
}

int PlasmaCutDataHandler::GetVendorID(const std::string &vendor_name) {
  char sql[500];
  sprintf(sql, "SELECT ID FROM Vendor WHERE Vendor.NAME = '%s'", vendor_name);
  sql_query_.Prepare(sql);
  if (sql_query_.Read()) {
    return sql_query_.GetIntValue(0);
  }
  return -1;
}

std::map<std::string, std::string> PlasmaCutDataHandler::GetSystemConfigKeywordField() {
  char sql[500];
  sprintf(sql, "SELECT FIELD_NAME FROM SystemConfigAttribute WHERE KEYWORD_FLAG = 1");
  sql_query_.Prepare(sql);

  std::map<std::string, std::string> field_name;
  while (sql_query_.Read()) {
    field_name.insert(std::pair<std::string, std::string>(sql_query_.GetStringValue(0), ""));
  }
  return field_name;
}

std::vector<std::string> PlasmaCutDataHandler::GetFieldValues(const std::string &field_name) {
  char sql[500];
  sprintf(sql, "SELECT DISTINCT %s FROM SystemConfig WHERE VENDOR_ID = %d", field_name.c_str(), 1);
  sql_query_.Prepare(sql);

  std::vector<std::string> field_values;
  while (sql_query_.Read()) {
    field_values.push_back(sql_query_.GetStringValue(0));
  }
  return field_values;
}
