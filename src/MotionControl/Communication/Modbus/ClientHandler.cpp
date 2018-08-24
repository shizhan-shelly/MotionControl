// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "ClientHandler.h"

#include "ModbusMappingDef.h"
#include "../../../Modbus/modbus.h"

ClientHandler::ClientHandler() : mb_mapping_(NULL) {}

ClientHandler::~ClientHandler() {
  modbus_mapping_free(mb_mapping_);
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
