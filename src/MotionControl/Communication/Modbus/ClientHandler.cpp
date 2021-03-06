// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "ClientHandler.h"

#include "ModbusMappingDef.h"
#include "../../../Modbus/modbus.h"

ClientHandler::ClientHandler(int slave_id) : slave_id_(slave_id)
                                           , ctx_(NULL)
                                           , mb_mapping_(NULL) {}

ClientHandler::~ClientHandler() {
  modbus_mapping_free(mb_mapping_);
}

void ClientHandler::ReleaseConnect() {
  modbus_close(ctx_);
  modbus_free(ctx_);
}

int ClientHandler::SlaveID() const {
  return slave_id_;
}

bool ClientHandler::Initialize() {
  if (!AllocateMapping()) {
    return false;
  }
  InitialMapping();
  return true;
}

bool ClientHandler::AllocateMapping() {
  mb_mapping_ = modbus_mapping_new(
      BITS_NB,
      INPUT_BITS_NB,
      REGISTERS_NB,
      INPUT_REGISTERS_NB);

  return mb_mapping_ != NULL;
}

void ClientHandler::InitialMapping() {
  /** INPUT STATUS **/
  unsigned char only_read_status[] = {0x00};
  modbus_set_bits_from_bytes(mb_mapping_->tab_input_bits,
                             INPUT_BITS_ADDRESS, INPUT_BITS_NB,
                             only_read_status);

  /** INPUT REGISTERS **/
  for (unsigned short i=0; i < INPUT_REGISTERS_NB; i++) {
    mb_mapping_->tab_input_registers[INPUT_REGISTERS_ADDRESS + i] = 0x0000;
  }

  /** REGISTERS **/
  for (unsigned short i=0; i < REGISTERS_NB; i++) {
    mb_mapping_->tab_registers[REGISTERS_ADDRESS + i] = 0x0000;
  }
}

bool ClientHandler::ReadInputBit(unsigned short address,
                                 bool &status, bool sync,
                                 int (*callback)(modbus_t *)) {

  // function code: 02H.
  //MutexLocker locker(&mutex_);
  int rc = modbus_read_input_bits(ctx_, address, 1,
      mb_mapping_->tab_input_bits + address);

  if (rc == 1) {
    status = mb_mapping_->tab_input_bits[address] == 1;
  }
  return rc == 1;
}

bool ClientHandler::ReadShort16InputRegister(unsigned short address,
                                             unsigned short &value, bool sync,
                                             int (*callback)(modbus_t *)) {

  // Function code: 0x04
  //MutexLocker locker(&mutex_);
  int rc = modbus_read_input_registers(ctx_, address, 1,
      mb_mapping_->tab_input_registers + address);

  if (rc == 1) {
    value = mb_mapping_->tab_input_registers[address];
  }
  return rc == 1;
}

bool ClientHandler::ReadUint32InputRegister(unsigned short address,
                                            unsigned int &value, bool sync,
                                            int (*callback)(modbus_t *)) {

  // Function code: 0x04
  //MutexLocker locker(&mutex_);
  int rc = modbus_read_input_registers(ctx_, address, 2,
      mb_mapping_->tab_input_registers + address);

  if (rc == 2) {
    value = (mb_mapping_->tab_input_registers[address + 1] << 16) +
        mb_mapping_->tab_input_registers[address];

  }
  return rc == 2;
}

bool ClientHandler::ReadFloatInputRegister(unsigned short address,
                                           float &value, bool sync,
                                           int (*callback)(modbus_t *)) {

  // Function code: 0x04
  //MutexLocker locker(&mutex_);
  int rc = modbus_read_input_registers(ctx_, address, 2,
      mb_mapping_->tab_input_registers + address);

  if (rc == 2) {
    value = modbus_get_float(mb_mapping_->tab_input_registers + address);
  }
  return rc == 2;
}

bool ClientHandler::ReadDoubleInputRegister(unsigned short address,
                                            double &value, bool sync,
                                            int (*callback)(modbus_t *)) {

  // Function code: 0x04H
  //MutexLocker locker(&mutex_);
  int rc = modbus_read_input_registers(ctx_, address, 4,
      mb_mapping_->tab_input_registers + address);

  if (rc == 4) {
    memcpy(&value, mb_mapping_->tab_input_registers + address, sizeof(double));
  }
  return rc == 4;
}

bool ClientHandler::WriteSingleCoil(unsigned short address,
                                    bool status, bool sync,
                                    int (*callback)(modbus_t *)) {

  // One coil has been set ON or OFF. function code: 05H.
  //MutexLocker locker(&mutex_);
  return modbus_write_bit(ctx_, address, status ? 1 : 0) == 1;
}

bool ClientHandler::WriteShort16Register(unsigned short address,
                                         unsigned short value, bool sync,
                                         int (*callback)(modbus_t *)) {

  // Several registers should be set preset data. function code: 10H.
  //MutexLocker locker(&mutex_);
  mb_mapping_->tab_registers[address] = value;
  return modbus_write_registers(ctx_, address, 1,
      mb_mapping_->tab_registers + address) == 1;

}

bool ClientHandler::WriteUint32Register(unsigned short address,
                                        unsigned int value, bool sync,
                                        int (*callback)(modbus_t *)) {

  // Several registers should be set preset data. function code: 10H.
  //MutexLocker locker(&mutex_);
  mb_mapping_->tab_registers[address] = value & 0xFFFF;
  mb_mapping_->tab_registers[address + 1] = value >> 16;
  return modbus_write_registers(ctx_, address, 2,
      mb_mapping_->tab_registers + address) == 2;

}

bool ClientHandler::WriteFloatRegister(unsigned short address,
                                       float value, bool sync,
                                       int (*callback)(modbus_t *)) {

  // Several registers should be set preset data. function code: 10H.
  //MutexLocker locker(&mutex_);
  modbus_set_float(value, mb_mapping_->tab_registers + address);
  return modbus_write_registers(ctx_, address, 2,
      mb_mapping_->tab_registers + address) == 2;

}

bool ClientHandler::WriteDoubleRegister(unsigned short address,
                                        double value, bool sync,
                                        int (*callback)(modbus_t *)) {

  // Several registers should be set preset data. function code: 10H.
  //MutexLocker locker(&mutex_);
  memcpy(mb_mapping_->tab_registers + address, &value, 4 * sizeof(unsigned short));
  return modbus_write_registers(ctx_, address, 4,
      mb_mapping_->tab_registers + address) == 4;

}

bool ClientHandler::ReadCoil(unsigned short address,
                             bool &status, bool sync,
                             int (*callback)(modbus_t *)) {

  // function code: 01H.
  //MutexLocker locker(&mutex_);
  int rc = modbus_read_bits(ctx_, address, 1,
      mb_mapping_->tab_bits + address);

  if (rc == 1) {
    status = mb_mapping_->tab_bits[address] == 1;
  }
  return rc == 1;
}

bool ClientHandler::ReadShort16Register(unsigned short address,
                                        unsigned short &value, bool sync,
                                        int (*callback)(modbus_t *)) {

  // Read several registers. function code: 03H.
  //MutexLocker locker(&mutex_);
  int rc = modbus_read_registers(ctx_, address, 1,
      mb_mapping_->tab_registers + address);

  if (rc == 1) {
    value = mb_mapping_->tab_registers[address];
  }
  return rc == 1;
}

bool ClientHandler::ReadUint32Register(unsigned short address,
                                       unsigned int &value, bool sync,
                                       int (*callback)(modbus_t *)) {

  // Read several registers. function code: 03H.
  //MutexLocker locker(&mutex_);
  int rc = modbus_read_registers(ctx_, address, 2,
      mb_mapping_->tab_registers + address);

  if (rc == 2) {
    value = (mb_mapping_->tab_registers[address + 1] << 16) +
        mb_mapping_->tab_registers[address];

  }
  return rc == 2;
}

bool ClientHandler::ReadFloatRegister(unsigned short address,
                                      float &value, bool sync,
                                      int (*callback)(modbus_t *)) {

  // Read several registers. function code: 03H.
  //MutexLocker locker(&mutex_);
  int rc = modbus_read_registers(ctx_, address, 2,
      mb_mapping_->tab_registers + address);

  if (rc == 2) {
    value = modbus_get_float(mb_mapping_->tab_registers + address);
  }
  return rc == 2;
}

bool ClientHandler::ReadDoubleRegister(unsigned short address,
                                       double &value, bool sync,
                                       int (*callback)(modbus_t *)) {

  // Read several registers. function code: 03H.
  //MutexLocker locker(&mutex_);
  int rc = modbus_read_registers(ctx_, address, 4,
      mb_mapping_->tab_registers + address);

  if (rc == 4) {
    memcpy(&value, mb_mapping_->tab_registers + address, sizeof(double));
  }
  return rc == 4;
}
