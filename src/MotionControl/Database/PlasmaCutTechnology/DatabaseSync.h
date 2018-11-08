// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef DATABASE_PLASMACUTTECHNOLOGY_DATABASESYNC_H__
#define DATABASE_PLASMACUTTECHNOLOGY_DATABASESYNC_H__

#include "base/singleton/Singleton.h"

class SyncHandler;

class DatabaseSync : public Singleton {
  DECLARE_SINGLETON(DatabaseSync)

 public:
  void RegisterSyncHandler(SyncHandler *sync_handler);

  bool CNCSync();

  bool THCSync();

  bool PlasmaPowerSync();

 private:
  SyncHandler *sync_handler_;

  DatabaseSync();
  ~DatabaseSync();

}; // class DatabaseSync

#endif // DATABASE_PLASMACUTTECHNOLOGY_DATABASESYNC_H__
