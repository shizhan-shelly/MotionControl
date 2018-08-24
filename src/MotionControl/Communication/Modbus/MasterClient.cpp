// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "MasterClient.h"

#include <assert.h>

#include "../../../Modbus/modbus.h"
#include "ClientHandler.h"

MasterClient::MasterClient() : Runnable()
                             , ctx_(NULL)
                             , handler_(NULL) {}

MasterClient::~MasterClient() {
  modbus_close(ctx_);
  modbus_free(ctx_);
}

void MasterClient::SetMasterClientHandler(ClientHandler *handler) {
  assert(handler);
  if (handler->Initialize()) {
    handler_ = handler;
  }
}

void MasterClient::Run() {
}
