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

int ServerHandler::ReadCoil(modbus_t *ctx, unsigned char *query) {
  return 1;
}

int ServerHandler::WriteSingleCoil(modbus_t *ctx, unsigned char *query) {
  return 1;
}

int ServerHandler::WriteMultipleCoil(modbus_t *ctx, unsigned char *query) {
  return 1;
}

int ServerHandler::ReadInputBit(modbus_t *ctx, unsigned char *query) {
  return 1;
}

int ServerHandler::ReadInputRegister(modbus_t *ctx, unsigned char *query) {
  return 1;
}

int ServerHandler::ReadRegister(modbus_t *ctx, unsigned char *query) {
  return 1;
}

int ServerHandler::WriteSingleRegister(modbus_t *ctx, unsigned char *query) {
  return 1;
}

int ServerHandler::WriteMultipleRegister(modbus_t *ctx, unsigned char *query) {
  return 1;
}
