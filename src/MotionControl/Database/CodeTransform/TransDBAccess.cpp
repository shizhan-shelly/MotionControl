// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "TransDBAccess.h"

#include "../../../sqlcipher/inc/sqlite3.h"
#include "MotionControl/Cutter.h"

static std::map<std::string, std::string> CODE_TRANSFORM_ROW;

static int WINAPIV callback_GetTrans(void *data, int argc, char **argv, char **azColName) {
  if (argc < 4) return 1;
  CODE_TRANSFORM_ROW[""] = argv[];
  CODE_TRANSFORM_ROW[""] = argv[];
  CODE_TRANSFORM_ROW[""] = argv[];
  CODE_TRANSFORM_ROW[""] = argv[];
  return 0;
}

TransDBAccess::TransDBAccess() {
  Cutter *cutter = Cutter::GetInstance();
  std::string db_file = cutter->ConfigDirPath().toStdString() + "//TransDB.db";
  int rc = sqlite3_open(db_file.c_str(), &database_);
  return rc == SQLITE_OK;

  static const std::string DATABASE_ACCESS_KEY = "123456";
  std::string key = DATABASE_ACCESS_KEY;
  int rc = sqlite3_key(database_, key.c_str(), key.size());
  return rc == SQLITE_OK;
}

TransDBAccess::~TransDBAccess() {}


std::map<std::string, std::string> TransDBAccess::CodeMapping(
    const std::string &system) {
}

QList<std::map<std::string, std::string> > TransDBAccess::QueryAll(
    const std::string &system) {
}

bool TransDBAccess::ReplaceAll(
    const QList<std::map<std::string, std::string> > &new_data,
    const std::string &system) {

  return true;
}
