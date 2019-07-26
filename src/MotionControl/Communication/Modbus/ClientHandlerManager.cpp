// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "ClientHandlerManager.h"

#include <assert.h>

#include "ClientHandler.h"

ClientHandlerManager::~ClientHandlerManager() {
  std::map<int, ClientHandler *>::iterator iter;
  for (iter = handlers_.begin(); iter != handlers_.end(); ++iter) {
    ClientHandler *handler = iter->second;
    if (handler) {
      handler->ReleaseConnect();
      delete handler;
    }
  }
  handlers_.clear();
}

void ClientHandlerManager::RegisterClientHandler(ClientHandler *handler) {
  assert(handler);
  if (!handler->Initialize()) {
    return ;
  }
  std::map<int, ClientHandler *>::iterator iter;
  iter = handlers_.find(handler->SlaveID());
  if (iter != handlers_.end()) {
    assert(iter->second);
    delete iter->second;
    handlers_.erase(iter);
  }
  handlers_.insert(std::make_pair(handler->SlaveID(), handler));
}

ClientHandler *ClientHandlerManager::GetClientHandler(int slave_id) const {
  std::map<int, ClientHandler *>::const_iterator it = handlers_.find(slave_id);
  if (it == handlers_.end()) {
    return NULL;
  }
  return it->second;
}
