// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef DATABASE_SQLITEQUERY_H__
#define DATABASE_SQLITEQUERY_H__

#include "SQLiteAccess.h"

struct sqlite3_stmt;

class SQLiteQuery : public SQLiteAccess {
 public:
  SQLiteQuery();
  ~SQLiteQuery();

  void Clear();

  bool Prepare(const std::string &query);

  // Read a row of data from database. SQL statement has been prepared for read.
  bool Read();

  int ColumnCount() const;

  std::string GetColumnName(int col) const;

  int GetColumnType(int col) const;

  std::string GetStringValue(int col) const;

  int GetIntValue(int col) const;

  long GetInt64Value(int col) const;

  double GetDoubleValue(int col) const;

  const char* GetBlobValue(int col, int &bytes) const;

 private:
  sqlite3_stmt *stmt_;

}; // class SQLiteQuery

#endif // DATABASE_SQLITEQUERY_H__
