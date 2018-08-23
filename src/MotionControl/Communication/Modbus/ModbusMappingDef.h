// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef MODBUS_MODBUSMAPPINGDEF_H__
#define MODBUS_MODBUSMAPPINGDEF_H__

// Modbus device: 0X
const unsigned short BITS_ADDRESS = 0x0;
const unsigned short BITS_NB = 0x64;

// Modbus device: 1X
const unsigned short INPUT_BITS_ADDRESS = 0x0;
const unsigned short INPUT_BITS_NB = 0x64;

// Modbus device: 3X
const unsigned short INPUT_REGISTERS_ADDRESS = 0x0;
const unsigned short INPUT_REGISTERS_NB = 0x64;

// Modbus device: 4X
const unsigned short REGISTERS_ADDRESS = 0x0;
const unsigned short REGISTERS_NB = 0x1F72;

#endif // MODBUS_MODBUSMAPPINGDEF_H__
