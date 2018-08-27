// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef MODBUS_MASTERCLIENT_H__
#define MODBUS_MASTERCLIENT_H__

#include "../../../Base/Runnable.h"

typedef struct _modbus modbus_t;

class ClientHandler;

class MasterClient : public Runnable {
 public:
  MasterClient();
  virtual ~MasterClient();

  void SetMasterClientHandler(ClientHandler *handler);

  void SetupConnect();

  virtual void Run();

 protected:
  virtual bool Connect() = 0;

  modbus_t *ctx_;

 private:
  ClientHandler *handler_;

}; // class MasterClient

#endif // MODBUS_MASTERCLIENT_H__
