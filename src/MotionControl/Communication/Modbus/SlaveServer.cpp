// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "SlaveServer.h"

#include <assert.h>

#include "../../../Modbus/modbus.h"
#include "ServerHandler.h"

SlaveServer::SlaveServer() : Runnable()
                           , ctx_(NULL)
                           , query_(NULL)
                           , connected_(false)
                           , handler_(NULL) {}

SlaveServer::~SlaveServer() {
  if (query_) {
    free(query_);
    query_ = NULL;
  }
  modbus_close(ctx_);
  modbus_free(ctx_);
}

void SlaveServer::SetServerHandler(ServerHandler *handler) {
  assert(handler);
  if (handler->Initialize()) {
    handler_ = handler;
  }
}

void SlaveServer::Run() {
  if (!handler_) {
    return ;
  }
  if (!connected_) {
    if (Connect()) {
      connected_ = true;
    }
  }
  int rc;
  while (connected_) {
    do {
      rc = modbus_receive(ctx_, query_); /* Filtered queries return 0 */
    } while (rc == 0);

     /* The connection is not closed on errors which require on reply such as bad CRC in RTU. */
    if (rc == -1 && errno != EMBBADCRC) {
      continue;
    }
    int parse_flag = handler_->ParseQuery(ctx_, query_);
    if (parse_flag == 1) {
      modbus_mapping_t *mb_mapping_ = handler_->GetModbusMapping();
      modbus_reply(ctx_, query_, rc, mb_mapping_);
    }
  }
}
