// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef MODBUS_DEVICEMODEL_H__
#define MODBUS_DEVICEMODEL_H__

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
  Master_F5000 = 0x00704000,
  Master_F5100 = 0x00704001,
  Master_F5200 = 0x00704002,
  Master_F5300 = 0x00704006,

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

} SlaveDeviceModel;

#endif // MODBUS_DEVICEMODEL_H__
