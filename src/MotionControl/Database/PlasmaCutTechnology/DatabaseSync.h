// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef DATABASE_PLASMACUTTECHNOLOGY_DATABASESYNC_H__
#define DATABASE_PLASMACUTTECHNOLOGY_DATABASESYNC_H__

class SyncHandler;

class DatabaseSync {
 public:
  DatabaseSync();
  ~DatabaseSync();

  void RegisterSyncHandler(SyncHandler *sync_handler);

  bool CNCSync();

  bool THCSync();

  bool PlasmaPowerSync();

 private:
  SyncHandler *sync_handler_;

}; // class DatabaseSync

#endif // DATABASE_PLASMACUTTECHNOLOGY_DATABASESYNC_H__
