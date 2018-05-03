// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "SQLiteQuery.h"

#include <assert.h>

#include "../../sqlcipher/inc/sqlite3.h"

SQLiteQuery::SQLiteQuery() : stmt_(NULL) {}

SQLiteQuery::~SQLiteQuery() {
  Clear();
}

void SQLiteQuery::Clear() {
  if (stmt_) {
    sqlite3_finalize(stmt_);
    stmt_ = NULL;
  }
}

bool SQLiteQuery::Prepare(const std::string &query) {
#ifdef UNICODE
  int rc = sqlite3_prepare16_v2(database_, query.c_str(), -1, &stmt_, NULL);
#else
  int rc = sqlite3_prepare_v2(database_, query.c_str(), -1, &stmt_, NULL);
#endif
  return rc == SQLITE_OK;
}

bool SQLiteQuery::Read() {
  assert(stmt_);
  return sqlite3_step(stmt_) == SQLITE_ROW;
}

int SQLiteQuery::ColumnCount() const {
  return sqlite3_column_count(stmt_);
}

std::string SQLiteQuery::GetColumnName(int col) const {
#ifdef UNICODE
  return (char *)sqlite3_column_name16(stmt_, col);
#else
  return (char *)sqlite3_column_name(stmt_, col);
#endif
}

int SQLiteQuery::GetColumnType(int col) const {
  return sqlite3_column_type(stmt_, col);
}

std::string SQLiteQuery::GetStringValue(int col) const {
#ifdef  UNICODE
  return (char *)sqlite3_column_text16(stmt_, col);
#else
  return (char *)sqlite3_column_text(stmt_, col);
#endif
}

int SQLiteQuery::GetIntValue(int col) const {
  return sqlite3_column_int(stmt_, col);
}

long SQLiteQuery::GetInt64Value(int col) const {
  return sqlite3_column_int64(stmt_, col);
}

double SQLiteQuery::GetDoubleValue(int col) const {
  return sqlite3_column_double(stmt_, col);
}

const char* SQLiteQuery::GetBlobValue(int col, int &bytes) const {
  bytes = sqlite3_column_bytes(stmt_, col);
  return (const char *)sqlite3_column_blob(stmt_, col);
}
