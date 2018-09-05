// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "ServerHandler.h"

#include "../../../Modbus/modbus.h"
#include "ModbusMappingDef.h"

ServerHandler::ServerHandler() : mb_mapping_(NULL) {}

ServerHandler::~ServerHandler() {
  modbus_mapping_free(mb_mapping_);
}

bool ServerHandler::Initialize() {
  if (!AllocateMapping()) {
    return false;
  }
  InitialMapping();
  return true;
}

bool ServerHandler::AllocateMapping() {
  mb_mapping_ = modbus_mapping_new(
      BITS_NB,
      INPUT_BITS_NB,
      REGISTERS_NB,
      INPUT_REGISTERS_NB);

  return mb_mapping_ != NULL;
}

void ServerHandler::InitialMapping() {
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

modbus_mapping_t *ServerHandler::GetModbusMapping() const {
  return mb_mapping_;
}

int ServerHandler::ParseQuery(modbus_t *ctx, unsigned char *query) {
  int modbus_header_length = modbus_get_header_length(ctx);
  unsigned char function_code = query[modbus_header_length];
  switch (function_code) {
   // 0X:
   case 0x01:
    return ReadCoil(ctx, query);
   case 0x05:
    return WriteSingleCoil(ctx, query);
   case 0x0f:
    return WriteMultipleCoil(ctx, query);
   // 1X:
   case 0x02:
    return ReadInputBit(ctx, query);
   // 3X:
   case 0x04:
    return ReadInputRegister(ctx, query);
   // 4X:
   case 0x03:
    return ReadRegister(ctx, query);
   case 0x06:
    return WriteSingleRegister(ctx, query);
   case 0x10:
    return WriteMultipleRegister(ctx, query);
   default:
    break;
  }
  return 0;
}

int ServerHandler::ReadCoil(modbus_t *ctx, unsigned char *query) { // 0x
  //  Read coil status. function code: 01H.
  return 1;
}

int ServerHandler::WriteSingleCoil(modbus_t *ctx, unsigned char *query) { // 0X
  // One coil has been set ON or OFF. function code: 05H.
  int modbus_header_length = modbus_get_header_length(ctx);
  unsigned short coil_addr = MODBUS_GET_INT16_FROM_INT8(query, modbus_header_length + 1);
  unsigned short coil_status = MODBUS_GET_INT16_FROM_INT8(query, modbus_header_length + 3);

  bool old_status = mb_mapping_->tab_bits[coil_addr];
  bool new_status = coil_status != 0;
  ExecuteControllerCommand(coil_addr, old_status, new_status);
  return 1;
}

int ServerHandler::WriteMultipleCoil(modbus_t *ctx, unsigned char *query) { // 0X
  // Several coils have been set ON or OFF. function code: 0FH.
  // TODO(zhan shi): Implement to write multiple coils.
  return 1;
}

int ServerHandler::ReadInputBit(modbus_t *ctx, unsigned char *query) { // 1X
  // function code: 02H.
  int modbus_header_length = modbus_get_header_length(ctx);
  unsigned short start_addr = MODBUS_GET_INT16_FROM_INT8(query, modbus_header_length + 1);
  unsigned short bit_no = MODBUS_GET_INT16_FROM_INT8(query, modbus_header_length + 3);
  // TODO(zhan shi): set the value of mb_mapping_->tab_input_bits[start_addr]
  return 1;
}

int ServerHandler::ReadInputRegister(modbus_t *ctx, unsigned char *query) { // 3X
  // function code: 04H.
  int modbus_header_length = modbus_get_header_length(ctx);
  unsigned short start_addr = MODBUS_GET_INT16_FROM_INT8(query, modbus_header_length + 1);
  unsigned short register_no = MODBUS_GET_INT16_FROM_INT8(query, modbus_header_length + 3);
  // TODO(zhan shi): set the value of mb_mapping_->tab_input_registers[]
  return 1;
}

int ServerHandler::ReadRegister(modbus_t *ctx, unsigned char *query) { // 4X
  // function code: 03H.
  int modbus_header_length = modbus_get_header_length(ctx);
  unsigned short start_addr = MODBUS_GET_INT16_FROM_INT8(query, modbus_header_length + 1);
  unsigned short register_no = MODBUS_GET_INT16_FROM_INT8(query, modbus_header_length + 3);
  // TODO(zhan shi): set the value of mb_mapping_->tab_registers[]
  return 1;
}

int ServerHandler::WriteSingleRegister(modbus_t *ctx, unsigned char *query) { // 4X
  // One register should be set a preset data. function code: 06H.
  // TODO(zhan shi):
  // Each value will be a data with 16 bits, which needs 2 bytes buffer space.
  return 1;
}

int ServerHandler::WriteMultipleRegister(modbus_t *ctx, unsigned char *query) { // 4X
  // Several registers should be set preset data. function code: 10H.
  // TODO(zhan shi):
  // Each value will be a data with 32 bits, which needs 4 bytes buffer space.
  int modbus_header_length = modbus_get_header_length(ctx);
  unsigned short start_addr = MODBUS_GET_INT16_FROM_INT8(query, modbus_header_length + 1);
  unsigned short register_no = MODBUS_GET_INT16_FROM_INT8(query, modbus_header_length + 3);
  unsigned char byte_count = query[modbus_header_length + 5];
  return 1;
}

void ServerHandler::ExecuteControllerCommand(unsigned short device_address,
    bool old_status, bool new_status) {
}
