// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "SQLiteAccess.h"

#include "../../sqlcipher/inc/sqlite3.h"

static const std::string DATABASE_ACCESS_KEY = "123456";

SQLiteAccess::SQLiteAccess() : database_(NULL) {}

SQLiteAccess::~SQLiteAccess() {
  Close();
}

bool SQLiteAccess::Open(const std::string &db_file) {
  int rc = sqlite3_open(db_file.c_str(), &database_);
  return rc == SQLITE_OK;
}

bool SQLiteAccess::Key(const std::string &db_key) {
  std::string key = db_key.empty() ? DATABASE_ACCESS_KEY : db_key;
  int rc = sqlite3_key(database_, key.c_str(), key.size());
  return rc == SQLITE_OK;
}

void SQLiteAccess::Close() {
  if (database_) {
    sqlite3_close(database_);
    database_ = NULL;
  }
}

bool SQLiteAccess::BeginTransaction() {
  char *errmsg = NULL;
  int rc = sqlite3_exec(database_, "BEGIN TRANSACTION;", NULL, NULL, &errmsg);
  return rc == SQLITE_OK;
}

bool SQLiteAccess::CommitTransaction() {
  char *errmsg = NULL;
  int rc = sqlite3_exec(database_, "COMMIT TRANSACTION;", NULL, NULL, &errmsg);
  return rc == SQLITE_OK;
}

bool SQLiteAccess::RollbackTransaction() {
  char * errmsg = NULL;
  int rc = sqlite3_exec(database_, "ROLLBACK TRANSACTION;", NULL, NULL, &errmsg);
  return rc == SQLITE_OK;
}

std::string SQLiteAccess::GetLastErrorMsg() {
#ifdef UNICODE
  return (char *)sqlite3_errmsg16(database_);
#else
  return sqlite3_errmsg(database_);
#endif
}
