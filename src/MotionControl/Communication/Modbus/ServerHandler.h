// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef MODBUS_SERVERHANDLER_H__
#define MODBUS_SERVERHANDLER_H__

typedef struct _modbus modbus_t;

struct _modbus_mapping_t;
typedef struct _modbus_mapping_t modbus_mapping_t;

/**
 * @brief ServerHandler
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
class ServerHandler {
 public:
  ServerHandler();
  ~ServerHandler();

  bool Initialize();

  // Parse the modbus query from Modbus Server thread.
  // @return: 0: continue to receive next new query
  //          1: ready to reply for correct query
  //         -1: quit the server thread for error query
  int ParseQuery(modbus_t *ctx, unsigned char *query);

  // Transfer the modbus response to Modbus Server thread.
  modbus_mapping_t *GetModbusMapping() const;

 private:
  // ServerHandler will maintain this pointer.
  modbus_mapping_t *mb_mapping_;

  bool AllocateMapping();

  void InitialMapping();

  int ReadCoil(modbus_t *ctx, unsigned char *query);
  int WriteSingleCoil(modbus_t *ctx, unsigned char *query);
  int WriteMultipleCoil(modbus_t *ctx, unsigned char *query);
  int ReadInputBit(modbus_t *ctx, unsigned char *query);
  int ReadInputRegister(modbus_t *ctx, unsigned char *query);
  int ReadRegister(modbus_t *ctx, unsigned char *query);
  int WriteSingleRegister(modbus_t *ctx, unsigned char *query);
  int WriteMultipleRegister(modbus_t *ctx, unsigned char *query);

  // Execute the control command from Modbus client.
  void ExecuteControllerCommand(unsigned short device_address, bool old_status,
      bool new_status);

}; // class ServerHandler

#endif // MODBUS_SERVERHANDLER_H__
