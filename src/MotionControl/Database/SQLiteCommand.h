// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef DATABASE_SQLITECOMMAND_H__
#define DATABASE_SQLITECOMMAND_H__

#include "SQLiteAccess.h"

struct sqlite3_stmt;

class SQLiteCommand : public SQLiteAccess {
 public:
  SQLiteCommand();
  ~SQLiteCommand();

  void Clear();

  bool Prepare(const std::string &query);

  bool Execute();

  bool BindParam(int index, const unsigned char *blob_buf);

  bool BindParam(int index, const int value);

  bool BindParam(int index, const double value);

  bool BindParam(int index, const char *value);

 private:
  sqlite3_stmt *stmt_;

}; // class SQLiteCommand

#endif // DATABASE_SQLITECOMMAND_H__
