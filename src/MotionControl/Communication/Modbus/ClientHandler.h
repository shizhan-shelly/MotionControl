// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef MODBUS_CLIENTHANDLER_H__
#define MODBUS_CLIENTHANDLER_H__

typedef struct _modbus modbus_t;

struct _modbus_mapping_t;
typedef struct _modbus_mapping_t modbus_mapping_t;

/**
 * @brief ClientHandler
 * This class is not thread-safe.
 * 1, Allocate a mapping segment for data transfer, initialize the read-only
 * data buffer mapping from plc.
 * 2, Process modbus received query, parse this packet for different function
 * code.
 * 3, For read query in the packet, scan the D value in the plc and copy into
 * the mapping buffer for modbus server thread.
 * 4, For write query in the packet, translate the remote controller's command
 * or motion data from client, set the M status and D value in plc.
 * 5, In the program end, destroy this data transfer mapping buffer.
 *
 */
class ClientHandler {
 public:
  ClientHandler();
  ~ClientHandler();

  bool Initialize();

 private:
  // ClientHandler will maintain this pointer.
  modbus_mapping_t *mb_mapping_;

  bool AllocateMapping();

  void InitialMapping();

}; // class ClientHandler

# endif // MODBUS_CLIENTHANDLER_H__
