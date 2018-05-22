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

std::vector<std::pair<std::string, std::string> > PlasmaCutDataHandler::GetSystemConfigField() {
  char sql[500];
  sprintf(sql, "SELECT DISTINCT FIELD_NAME FROM SystemConfigAttribute");
  sql_query_.Prepare(sql);

  std::vector<std::pair<std::string, std::string> > field_name;
  while (sql_query_.Read()) {
    field_name.push_back(std::make_pair(sql_query_.GetStringValue(0), ""));
  }
  return field_name;
}

std::vector<std::pair<std::string, std::string> > PlasmaCutDataHandler::GetSystemConfigKeywordField() {
  char sql[500];
  sprintf(sql, "SELECT FIELD_NAME FROM SystemConfigAttribute WHERE KEYWORD_FLAG = 1");
  sql_query_.Prepare(sql);

  std::vector<std::pair<std::string, std::string> > field_name;
  while (sql_query_.Read()) {
    field_name.push_back(std::make_pair(sql_query_.GetStringValue(0), ""));
  }
  return field_name;
}

std::vector<std::string> PlasmaCutDataHandler::GetSystemConfigFieldValues(
    int vendor_id,
    const std::string &field_name) {

  char sql[500];
  sprintf(sql, "SELECT DISTINCT %s FROM SystemConfig WHERE VENDOR_ID = %d",
      field_name.c_str(), vendor_id);

  sql_query_.Prepare(sql);

  std::vector<std::string> field_values;
  while (sql_query_.Read()) {
    field_values.push_back(sql_query_.GetStringValue(0));
  }
  return field_values;
}

std::vector<std::vector<std::pair<std::string, std::string> > > PlasmaCutDataHandler::GetSystemConfigRecord(
    int vendor_id,
    const std::vector<std::pair<std::string, std::string> > &keyword_field) {

  char pre_sql[500];
  sprintf(pre_sql, "SELECT * FROM SystemConfig WHERE VENDOR_ID = %d ", vendor_id);
  std::string sql = pre_sql;
  for (size_t i = 0; i < keyword_field.size(); i++) {
    char child_sql[500];
    sprintf(child_sql, "AND %s = '%s'", keyword_field[i].first.c_str(), keyword_field[i].second.c_str());
    sql.append(child_sql);
  }
  sql_query_.Prepare(sql);

  std::vector<std::pair<std::string, std::string> > field_values;
  std::vector<std::vector<std::pair<std::string, std::string> > > record_values;
  while (sql_query_.Read()) {
    for (int i = 0; i < sql_query_.ColumnCount(); i++) {
      field_values.push_back(std::make_pair(sql_query_.GetColumnName(i),
          sql_query_.GetStringValue(i)));

    }
    record_values.push_back(field_values);
  }
  return record_values;
}
