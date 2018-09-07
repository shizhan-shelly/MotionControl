// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef MODBUS_DEVICEMODEL_H__
#define MODBUS_DEVICEMODEL_H__

typedef enum _DeviceModel {
  Undefine = 0x00000000,
  // Master
  F1628 = 0x01005029,
  F2000T = 0x01005031,
  F3000 = 0x00703000,
  F3100 = 0x00703001,
  F3200 = 0x00703002,
  F3300 = 0x00703006,
  F3500 = 0x00703010,
  F3610 = 0x00703011,
  F3500S = 0x00703012,
  F5000 = 0x00704000,
  F5100 = 0x00704001,
  F5200 = 0x00704002,
  F5300 = 0x00704006,
  F7300B = 0x00706004,
  F7600W = 0x00706005,
  F7600L = 0x00706006,

  // Slaver
  F2000 = 0x00702000,
  F2100T = 0x00702019,
  F2300T = 0x00702020,
  F2600T = 0x00702073,
  F1628 = 0x01005028,
  F1650 = 0x01005030,
  LH270A = 0x01012001,

} DeviceModel;

// Master Device Model:
typedef enum _MasterDeviceModel {
  Master_Undefine = 0x00000000,
  Master_F1628 = 0x01005029,
  Master_F2000T = 0x01005031,
  Master_F3000 = 0x00703000,
  Master_F3100 = 0x00703001,
  Master_F3200 = 0x00703002,
  Master_F3300 = 0x00703006,
  Master_F3500 = 0x00703010,
  Master_F3610 = 0x00703011,
  Master_F3500S = 0x00703012,
  Master_F5000 = 0x00704000,
  Master_F5100 = 0x00704001,
  Master_F5200 = 0x00704002,
  Master_F5300 = 0x00704006,
  Master_F7300B = 0x00706004,
  Master_F7600W = 0x00706005,
  Master_F7600L = 0x00706006,

} MasterDeviceMode;

// Slave Device Model:
typedef enum _SlaveDeviceModel {
  Slave_Undefine = 0x00000000,
  Slave_F2000 = 0x00702000,
  Slave_F2100T = 0x00702019,
  Slave_F2300T = 0x00702020,
  Slave_F2600T = 0x00702073,
  Slave_F1628 = 0x01005028,
  Slave_F1650 = 0x01005030,
  Slave_LH270A = 0x01012001,

} SlaveDeviceModel;

#endif // MODBUS_DEVICEMODEL_H__
