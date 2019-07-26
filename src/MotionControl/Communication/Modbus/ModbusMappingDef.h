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

const unsigned short MODBUS_DEVICE_INFOR               = REGISTERS_ADDRESS + 8000;
const unsigned short CONNECT_FLAG                      = MODBUS_DEVICE_INFOR + 0;
const unsigned short CONNECT_TIME_OUT                  = MODBUS_DEVICE_INFOR + 2;
const unsigned short MASTER_MODEL                      = MODBUS_DEVICE_INFOR + 4;
const unsigned short MASTER_HARDWARE_VERSION           = MODBUS_DEVICE_INFOR + 6;
const unsigned short MASTER_SOFTWARE_VERSION           = MODBUS_DEVICE_INFOR + 8;
const unsigned short MASTER_VERSION_VERIFY             = MODBUS_DEVICE_INFOR + 10;
const unsigned short SLAVE_MODEL                       = MODBUS_DEVICE_INFOR + 12;
const unsigned short SLAVE_HARDWARE_VERSION            = MODBUS_DEVICE_INFOR + 14;
const unsigned short SLAVE_SOFTWARE_VERSION            = MODBUS_DEVICE_INFOR + 16;
const unsigned short SLAVE_VERSION_VERIFY              = MODBUS_DEVICE_INFOR + 18;

#endif // MODBUS_MODBUSMAPPINGDEF_H__
