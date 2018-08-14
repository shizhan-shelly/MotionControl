// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef DATABASE_PLASMACUTTECHNOLOGY_CUTCHARTDEFINE_H__
#define DATABASE_PLASMACUTTECHNOLOGY_CUTCHARTDEFINE_H__

typedef enum _KjellbergCutData {
  Material = 0,
  Thickness,
  Current,
  Technology,

  CuttingSpeed,
  Kerf,
  IgnitionHeight,
  CuttingHeight,
  PierceHeight,
  PierceTime,
  CuttingVoltage,

  CoolingTube,
  Cathode,
  GasGuide,
  Nozzle,
  NozzleCap,
  SwirlGasCap,
  ProtectionCap,
  SwirlGasNozzle,
  SpecialPart,

  PlasmaGas1,
  PlasmaGas2,
  PlasmaGas3,
  SwirlGas1,
  SwirlGas2,
  IgnitionGas,
  GasCode,
  SpecialCode,
  PlasmaGas1Pressure,
  PlasmaGas2Pressure,
  PlasmaGas3Pressure,
  SwirlGas1Pressure,
  SwirlGas2Pressure,
  IgnitionGasPressure,
  CuttingPressure,
  AdditionalHeight,
  UpSlope,
  DownSlope,
  CuttingSpeedSpeed,
  CuttingSpeedMax,
  CuttingSpeedHole,
  KerfHole,
  RecordNumber,
  TechnologyRange,
  MarkingRecord,

} KjellbergCutData;

typedef enum _HyperthermCutData {
  TorchType,
  Material,
  SpecificMaterial,
  Current,
  GasType,
  CuttingSurface,
  Thickness,

  CuttingSpeed,
  Kerf,
  CutHeightDelay,
  CreepTime,
  CuttingHeight,
  IgnitionHeight,
  PierceHeight,
  PierceTime,
  CuttingVoltage,
  PlasmaManualPreflow,
  ShieldManualPreflow,
  PlasmaManualCutflow,
  ShieldManualCutflow,
  PlasmaAutoPreflow,
  ShieldAutoPreflow,
  PlasmaAutoCutflow,
  ShieldAutoCutflow,
  MixedGas1,
  MixedGas2,

  ShieldCap,
  Shield,
  NozzleRetainingCap,
  Nozzle,
  SwirlRing,
  Electrode,
  WaterTube,

} HyperthermCutData;

#endif // DATABASE_PLASMACUTTECHNOLOGY_CUTCHARTDEFINE_H__