// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "DatabaseSync.h"

#include "SyncHandler.h"

DatabaseSync::DatabaseSync() : sync_handler_(NULL) {}

DatabaseSync::~DatabaseSync() {
  if (sync_handler_) {
    delete sync_handler_;
  }
}

void DatabaseSync::RegisterSyncHandler(SyncHandler *sync_handler) {
  if (sync_handler_) {
    delete sync_handler_;
  }
  sync_handler_ = sync_handler;
}

bool DatabaseSync::CNCSync() {
  std::map<std::string, std::string> sync_data =
      sync_handler_->UpdateParameterFromCutChart();

  return true;
}

bool DatabaseSync::THCSync() {
  std::map<std::string, std::string> sync_data =
      sync_handler_->UpdateParameterFromCutChart();

  return true;
}

bool DatabaseSync::PlasmaPowerSync() {
  std::map<std::string, std::string> sync_data =
      sync_handler_->UpdateParameterFromCutChart();

  return true;
}
