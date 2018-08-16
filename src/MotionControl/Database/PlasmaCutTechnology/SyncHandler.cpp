// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "SyncHandler.h"

std::map<std::string, std::string> KjellbergSyncHandler::UpdateCNCParameterFromCutChart() {
  cnc_data_.clear();
  cnc_data_.insert(std::make_pair("CuttingSpeed", ""));
  cnc_data_.insert(std::make_pair("Kerf", ""));
  return cnc_data_;
}

std::map<std::string, std::string> KjellbergSyncHandler::UpdateTHCParameterFromCutChart() {
  thc_data_.clear();
  thc_data_.insert(std::make_pair("IgnitionHeight", ""));
  thc_data_.insert(std::make_pair("CuttingHeight", ""));
  thc_data_.insert(std::make_pair("PierceHeight", ""));
  thc_data_.insert(std::make_pair("PierceTime", ""));
  thc_data_.insert(std::make_pair("CuttingVoltage", ""));
  return thc_data_;
}


std::map<std::string, std::string> KjellbergSyncHandler::UpdatePPSParameterFromCutChart() {
  pps_data_.clear();
  pps_data_.insert(std::make_pair("PlasmaGas1", ""));
  pps_data_.insert(std::make_pair("PlasmaGas2", ""));
  pps_data_.insert(std::make_pair("PlasmaGas3", ""));
  pps_data_.insert(std::make_pair("SwirlGas1", ""));
  pps_data_.insert(std::make_pair("SwirlGas2", ""));
  pps_data_.insert(std::make_pair("IgnitionGas", ""));
  pps_data_.insert(std::make_pair("PlasmaGas1Pressure", ""));
  pps_data_.insert(std::make_pair("PlasmaGas2Pressure", ""));
  pps_data_.insert(std::make_pair("PlasmaGas3Pressure", ""));
  pps_data_.insert(std::make_pair("SwirlGas1Pressure", ""));
  pps_data_.insert(std::make_pair("SwirlGas2Pressure", ""));
  pps_data_.insert(std::make_pair("IgnitionGasPressure", ""));
  pps_data_.insert(std::make_pair("GasCode", ""));
  pps_data_.insert(std::make_pair("SpecialCode", ""));
  return pps_data_;
}

std::map<std::string, std::string> HyperthermSyncHandler::UpdateCNCParameterFromCutChart() {
  cnc_data_.clear();
  cnc_data_.insert(std::make_pair("CuttingSpeed", ""));
  cnc_data_.insert(std::make_pair("Kerf", ""));
  cnc_data_.insert(std::make_pair("CreepTime", ""));
  return cnc_data_;
}

std::map<std::string, std::string> HyperthermSyncHandler::UpdateTHCParameterFromCutChart() {
  thc_data_.clear();
  thc_data_.insert(std::make_pair("IgnitionHeight", ""));
  thc_data_.insert(std::make_pair("CuttingHeight", ""));
  thc_data_.insert(std::make_pair("PierceHeight", ""));
  thc_data_.insert(std::make_pair("PierceTime", ""));
  thc_data_.insert(std::make_pair("CuttingVoltage", ""));
  thc_data_.insert(std::make_pair("CutHeightDelay", ""));
  return thc_data_;
}


std::map<std::string, std::string> HyperthermSyncHandler::UpdatePPSParameterFromCutChart() {
  pps_data_.clear();
  pps_data_.insert(std::make_pair("PlasmaManualPreflow", ""));
  pps_data_.insert(std::make_pair("ShieldManualPreflow", ""));
  pps_data_.insert(std::make_pair("PlasmaManualCutflow", ""));
  pps_data_.insert(std::make_pair("ShieldManualCutflow", ""));
  pps_data_.insert(std::make_pair("PlasmaAutoPreflow", ""));
  pps_data_.insert(std::make_pair("ShieldAutoPreflow", ""));
  pps_data_.insert(std::make_pair("PlasmaAutoCutflow", ""));
  pps_data_.insert(std::make_pair("ShieldAutoCutflow", ""));
  pps_data_.insert(std::make_pair("MixedGas1", ""));
  pps_data_.insert(std::make_pair("MixedGas2", ""));
  return pps_data_;
}

std::map<std::string, std::string> LiuheSyncHandler::UpdateCNCParameterFromCutChart() {
  cnc_data_.clear();
  cnc_data_.insert(std::make_pair("CuttingSpeed", ""));
  cnc_data_.insert(std::make_pair("Kerf", ""));
  return cnc_data_;
}

std::map<std::string, std::string> LiuheSyncHandler::UpdateTHCParameterFromCutChart() {
  thc_data_.clear();
  thc_data_.insert(std::make_pair("IgnitionHeight", ""));
  thc_data_.insert(std::make_pair("CuttingHeight", ""));
  thc_data_.insert(std::make_pair("PierceHeight", ""));
  thc_data_.insert(std::make_pair("PierceTime", ""));
  thc_data_.insert(std::make_pair("CuttingVoltage", ""));
  return thc_data_;
}


std::map<std::string, std::string> LiuheSyncHandler::UpdatePPSParameterFromCutChart() {
  pps_data_.clear();
  pps_data_.insert(std::make_pair("", ""));
  pps_data_.insert(std::make_pair("", ""));
  return pps_data_;
}
