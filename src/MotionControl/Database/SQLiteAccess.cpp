// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "SQLiteAccess.h"

#include "../../sqlcipher/inc/sqlite3.h"

static const std::string DATABASE_ACCESS_KEY = "123456";

SQLiteAccess::SQLiteAccess() : database_(NULL) {}

SQLiteAccess::~SQLiteAccess() {
  if (database_) {
    sqlite3_close(database_);
    database_ = NULL;
  }
}

bool SQLiteAccess::InitializeAccess(const std::string &db_file,
                                    const std::string &db_key) {

  int rc = sqlite3_open(db_file.c_str(), &database_);
  if (rc != SQLITE_OK) {
    return false;
  }
  std::string key = db_key.empty() ? DATABASE_ACCESS_KEY : db_key;
  rc = sqlite3_key(database_, key.c_str(), key.size());
  if (rc != SQLITE_OK) {
    return false;
  }
  return true;
}
