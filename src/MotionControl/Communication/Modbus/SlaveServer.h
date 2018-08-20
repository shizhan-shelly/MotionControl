// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef MODBUS_SLAVESERVER_H__
#define MODBUS_SLAVESERVER_H__

#include "../../../Base/Runnable.h"

typedef struct _modbus modbus_t;

class ServerHandler;

class SlaveServer : public Runnable {
 public:
  SlaveServer();
  virtual ~SlaveServer();

  void SetServerHandler(ServerHandler *handler);

  virtual void Run();

 protected:
  virtual bool Connect() = 0;

  modbus_t *ctx_;
  unsigned char *query_;

 private:
  bool connected_;
  ServerHandler *handler_;

}; // class SlaveServer

#endif // MODBUS_SLAVESERVER_H__
