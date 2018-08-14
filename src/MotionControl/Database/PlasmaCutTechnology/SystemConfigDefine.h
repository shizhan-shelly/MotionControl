// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef DATABASE_PLASMACUTTECHNOLOGY_SYSTEMCONFIGDEFINE_H__
#define DATABASE_PLASMACUTTECHNOLOGY_SYSTEMCONFIGDEFINE_H__

typedef enum _PlasmaPowerVendor {
  Kjellberg = 1,
  Hypertherm,
  LiuHe,

} PlasmaPowerVendor;

typedef enum _SystemConfigFilter {
  VendorID = 0,
  PlasmaPowerModel,
  GasBoxModel,
  TorchModel,
  Version,
  CutChartID,
  SelectedRecord,

} SystemConfigFilter;

#endif // DATABASE_PLASMACUTTECHNOLOGY_SYSTEMCONFIGDEFINE_H__
