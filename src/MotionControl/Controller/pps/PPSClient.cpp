// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "MotionControl/Controller/pps/PPSClient.h"

#include <assert.h>

#include "MotionControl/Communication/Modbus/ClientHandler.h"
#include "MotionControl/Communication/Modbus/ClientHandlerManager.h"

PPSClient::PPSClient() : Runnable()
                       , handler_manager_(NULL) {}

PPSClient::~PPSClient() {}

void PPSClient::SetClientHandlerManager(ClientHandlerManager *handler_manager) {
  assert(handler_manager);
  handler_manager_ = handler_manager;
}

void PPSClient::Run() {
  if (!SetupConnect()) {
    return ;
  }
  // Sample pps status and parameters.
}

bool PPSClient::SetupConnect() {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  if (!handler->Connect()) {
    return false;
  }
  return true;
}
