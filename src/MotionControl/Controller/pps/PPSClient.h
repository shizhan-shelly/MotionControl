// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef CONTROLLER_PPS_PPSCLIENT_H__
#define CONTROLLER_PPS_PPSCLIENT_H__

#include "Base/Runnable.h"

class ClientHandlerManager;

class PPSClient : public Runnable {
 public:
  PPSClient();
  virtual ~PPSClient();

  void SetClientHandlerManager(ClientHandlerManager *handler_manager);

  virtual void Run();

  bool SetupConnect();

 private:
  ClientHandlerManager *handler_manager_;

}; // class PPSClient

#endif // CONTROLLER_PPS_PPSCLIENT_H__
