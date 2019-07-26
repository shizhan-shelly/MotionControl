// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef MODBUS_CLIENTHANDLERMANAGER_H__
#define MODBUS_CLIENTHANDLERMANAGER_H__

#include <map>

class ClientHandler;

class ClientHandlerManager {
 public:
  ~ClientHandlerManager();

  void RegisterClientHandler(ClientHandler *handler);

  ClientHandler *GetClientHandler(int slave_id) const;

 private:
  std::map<int, ClientHandler *> handlers_;

}; // class ClientHandlerManager

#endif // MODBUS_CLIENTHANDLERMANAGER_H__
