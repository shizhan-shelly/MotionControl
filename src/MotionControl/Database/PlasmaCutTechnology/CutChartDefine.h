// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef DATABASE_PLASMACUTTECHNOLOGY_CUTCHARTDEFINE_H__
#define DATABASE_PLASMACUTTECHNOLOGY_CUTCHARTDEFINE_H__

#include <map>

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
  CreepTime,
  CuttingHeight,
  IgnitionHeight,
  PierceHeight,
  PierceTime,
  CuttingVoltage,
  CutHeightDelay,
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

//////////////////////////////////////////////////////////////////////
typedef std::pair<int, std::string> pair_t;

static const pair_t hypertherm_thc[] = {
  pair_t(600, "CuttingVoltage"),
  pair_t(601, "PierceTime"),
  pair_t(602, "PierceHeightFactor"),
  pair_t(603, "CuttingHeight"),
  pair_t(604, "IgnitionHeightFactor"),
  pair_t(605, "CutHeightDelay"),
  pair_t(606, "KerfRedetectTime"),
  pair_t(607, "ModeSelect"),
  pair_t(608, "ArcCurrent"),
  pair_t(609, "IgnitionHeight"),
  pair_t(610, "PierceHeight"),
  pair_t(613, "AVCDelay"),
};

static const std::map<int, std::string> HYPERTHERM_THC(hypertherm_thc,
    hypertherm_thc + sizeof(hypertherm_thc) / sizeof(hypertherm_thc[0]));

#endif // DATABASE_PLASMACUTTECHNOLOGY_CUTCHARTDEFINE_H__
