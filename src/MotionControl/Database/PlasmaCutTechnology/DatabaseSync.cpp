// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "DatabaseSync.h"

#include "SyncHandler.h"

DatabaseSync::DatabaseSync() : sync_handler_(NULL) {}

DatabaseSync::~DatabaseSync() {
  if (sync_handler_) {
    delete sync_handler_;
    sync_handler_ = NULL;
  }
}

void DatabaseSync::RegisterSyncHandler(SyncHandler *sync_handler) {
  if (sync_handler) {
    sync_handler_ = sync_handler;
  }
}

bool DatabaseSync::CNCSync() {
  sync_handler_->UpdateCNCParameterFromCutChart();
  return true;
}

bool DatabaseSync::THCSync() {
  sync_handler_->UpdateTHCParameterFromCutChart();
  return true;
}

bool DatabaseSync::PlasmaPowerSync() {
  sync_handler_->UpdatePPSParameterFromCutChart();
  return true;
}
