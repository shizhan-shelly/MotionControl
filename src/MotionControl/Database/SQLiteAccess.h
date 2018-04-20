// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef DATABASE_SQLITEACCESS_H__
#define DATABASE_SQLITEACCESS_H__

#include <string>

struct sqlite3;

class SQLiteAccess {
 public:
  SQLiteAccess();
  virtual ~SQLiteAccess();

  bool InitializeAccess(const std::string &db_file,
                        const std::string &db_key);

 protected:
  sqlite3 *database_;

}; // class SQLiteAccess

#endif // DATABASE_SQLITEACCESS_H__
