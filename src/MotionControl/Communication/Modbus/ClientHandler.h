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
  explicit ClientHandler(int slave_id);
  virtual ~ClientHandler();

  virtual bool Connect() = 0;

  void ReleaseConnect();

  bool Initialize();

  int SlaveID() const;

  bool ReadInputBit(unsigned short address, bool &status, bool sync = false, int (*callback)(modbus_t *) = nullptr);
  bool ReadShort16InputRegister(unsigned short address, unsigned short &value, bool sync = false, int (*callback)(modbus_t *) = nullptr);
  bool ReadUint32InputRegister(unsigned short address, unsigned int &value, bool sync = false, int (*callback)(modbus_t *) = nullptr);
  bool ReadFloatInputRegister(unsigned short address, float &value, bool sync = false, int (*callback)(modbus_t *) = nullptr);
  bool ReadDoubleInputRegister(unsigned short address, double &value, bool sync = false, int (*callback)(modbus_t *) = nullptr);
  bool WriteSingleCoil(unsigned short address, bool status, bool sync = false, int (*callback)(modbus_t *) = nullptr);
  bool WriteShort16Register(unsigned short address, unsigned short value, bool sync = false, int (*callback)(modbus_t *) = nullptr);
  bool WriteUint32Register(unsigned short address, unsigned int value, bool sync = false, int (*callback)(modbus_t *) = nullptr);
  bool WriteFloatRegister(unsigned short address, float value, bool sync = false, int (*callback)(modbus_t *) = nullptr);
  bool WriteDoubleRegister(unsigned short address, double value, bool sync = false, int (*callback)(modbus_t *) = nullptr);
  bool ReadCoil(unsigned short address, bool &status, bool sync = false, int (*callback)(modbus_t *) = nullptr);
  bool ReadShort16Register(unsigned short address, unsigned short &value, bool sync = false, int (*callback)(modbus_t *) = nullptr);
  bool ReadUint32Register(unsigned short address, unsigned int &value, bool sync = false, int (*callback)(modbus_t *) = nullptr);
  bool ReadFloatRegister(unsigned short address, float &value, bool sync = false, int (*callback)(modbus_t *) = nullptr);
  bool ReadDoubleRegister(unsigned short address, double &value, bool sync = false, int (*callback)(modbus_t *) = nullptr);

 protected:
  int slave_id_;
  modbus_t *ctx_;

 private:
  // ClientHandler will maintain this pointer.
  modbus_mapping_t *mb_mapping_;

  bool AllocateMapping();

  void InitialMapping();

}; // class ClientHandler

# endif // MODBUS_CLIENTHANDLER_H__
