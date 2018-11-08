// Copyright 2016 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include <assert.h>

#include "DatabaseAccess.h"

#include "SqlCipher/inc/sqlite3.h"

static std::vector<std::string> TABLE_COLUMN;

static std::map<CuttingData, std::string> CUTTING_DATA_ROW;

typedef std::pair<CuttingData, std::string> pair_t;

static const pair_t cutting_data[] = {
  pair_t(Cathode,            "CATHODE"),
  pair_t(GasGuide,           "GAS_GUIDE"),
  pair_t(Nozzle,             "NOZZLE"),
  pair_t(NozzleCap,          "NOZZLE_CAP"),
  pair_t(SwirlGasCap,        "SWIRL_GAS_CAP"),
  pair_t(ProtectionCap,      "PROTECTION_CAP"),
  pair_t(CoolingTube,        "COOLING_TUBE"),
  pair_t(SwirlGasNozzle,     "SWIRL_GAS_NOZZLE"),
  pair_t(PlasmaGas1,         "PLASMA_GAS1"),
  pair_t(PlasmaGas2,         "PLASMA_GAS2"),
  pair_t(PlasmaGas3,         "PLASMA_GAS3"),
  pair_t(SwirlGas1,          "SWIRL_GAS1"),
  pair_t(SwirlGas2,          "SWIRL_GAS2"),
  pair_t(IgnitionGas,        "IGNITION_GAS"),
  pair_t(PlasmaGas1Pressure, "PLASMA_GAS1_KPA"),
  pair_t(PlasmaGas2Pressure, "PLASMA_GAS2_KPA"),
  pair_t(PlasmaGas3Pressure, "PLASMA_GAS3_KPA"),
  pair_t(SwirlGas1Pressure,  "SWIRL_GAS1_KPA"),
  pair_t(SwirlGas2Pressure,  "SWIRL_GAS2_KPA"),
  pair_t(CuttingPressure,    "CUTTING_PRESSURE"),
  pair_t(UpSlope,            "UP_SLOPE"),
  pair_t(DownSlope,          "DOWN_SLOPE"),
  pair_t(IgnitionHeight,     "IGNITION_HEIGHT"),
  pair_t(CuttingHeight,      "CUTTING_HEIGHT"),
  pair_t(PierceHeight,       "PIERCE_HEIGHT"),
  pair_t(PierceTime,         "PIERCE_TIME"),
  pair_t(CuttingVoltage,     "CUTTING_VOLTAGE"),
  pair_t(CuttingSpeedQuality,"CUTTING_SPEED_QUALITY"),
  pair_t(CuttingSpeedHole,   "CUTTING_SPEED_HOLE"),
  pair_t(KerfQuality,        "KERF_QUALITY"),
  pair_t(KerfHole,           "KERF_HOLE"),
  // Hypertherm
  pair_t(Feedrate,               "FEED_RATE"),
  pair_t(LeadInFeedrate,         "LEAD_IN_FEED_RATE"),
  pair_t(BaseKerf,               "BASE_KERF"),
  pair_t(Kerf,                   "KERF"),
  pair_t(DisableAHC,             "DISABLE_AHC"),
  pair_t(AsynchronousStop,       "ASYNCHRONOUS_STOP"),
  pair_t(CutChartType,           "TORCH_CONSUMABLE_TYPE"),
  pair_t(CutShieldGas,           "CUT_SHIELD_GAS"),
  pair_t(CuttingSurface,         "CUTTING_SURFACE"),
  pair_t(TransferHeightFactor,   "TRANSFER_HEIGHT_FACTOR"),
  pair_t(PierceHeightFactor,     "PIERCE_HEIGHT_FACTOR"),
  pair_t(PierceDelayTime,        "PIERCE_DELAY_TIME"),
  pair_t(CutHeight,              "CUT_HEIGHT"),
  pair_t(CutHeightDelay,         "CUT_HEIGHT_DELAY"),
  pair_t(ArcVol,                 "ARC_VOLTAGE"),
  pair_t(IHSDistance,            "IHS_DISTANCE"),
  pair_t(PreflowPlasmaPressure,  "PREFLOW_PLASMA_PRESSURE"),
  pair_t(PreflowShieldPressure,  "PREFLOW_SHIELD_PRESSURE"),
  pair_t(CutflowPlasmaPressure,  "CUTFLOW_PLASMA_PRESSURE"),
  pair_t(CutflowShieldPressure,  "CUTFLOW_SHIELD_PRESSURE"),

};

static const std::map<CuttingData, std::string> CUTTING_DATA_MAP(cutting_data,
    cutting_data + sizeof(cutting_data) / sizeof(cutting_data[0]));

static int WINAPIV callback_BaseModel(void *data, int argc, char **argv, char **azColName) {
  if (argc != 1) return 1;
  BaseModel *pData = (BaseModel *)data;
  sprintf(pData->name, "%s", argv[0] ? argv[0] : "");
  return 0;
}

static int WINAPIV callback_Table(void *data, int argc, char **argv, char **azColName) {
  if (argc != 1) return 1;
  TABLE_COLUMN.push_back(argv[0] ? argv[0] : "");
  return 0;
}

static int WINAPIV callback_IDModel(void *data, int argc, char **argv, char **azColName) {
  if (argc != 1) return 1;
  IDModel *pData = (IDModel *)data;
  pData->index_in_table = atoi(argv[0]);
  return 0;
}

static int WINAPIV callback_CuttingDataModel(void *data, int argc, char **argv, char **azColName) {
  if (argc != 1) return 1;
  CuttingDataModel *pData = (CuttingDataModel *)data;
  sprintf(pData->value, "%s", argv[0] ? argv[0] : "");
  return 0;
}

static int WINAPIV callback_GetCuttingData(void *data, int argc, char **argv, char **azColName) {
  if (argc < 30) return 1;
  CUTTING_DATA_ROW[CutShieldGas] = argv[9];
  CUTTING_DATA_ROW[Feedrate] = argv[13];
  CUTTING_DATA_ROW[LeadInFeedrate] = argv[14];
  CUTTING_DATA_ROW[Kerf] = argv[18];
  CUTTING_DATA_ROW[DisableAHC] = argv[19];
  CUTTING_DATA_ROW[AsynchronousStop] = argv[21];
  CUTTING_DATA_ROW[TransferHeightFactor] = argv[22];
  CUTTING_DATA_ROW[PierceHeightFactor] = argv[23];
  CUTTING_DATA_ROW[PierceDelayTime] = argv[24];
  CUTTING_DATA_ROW[CutHeight] = argv[26];
  CUTTING_DATA_ROW[CutHeightDelay] = argv[27];
  CUTTING_DATA_ROW[ArcVol] = argv[28];
  if (argc < 34) return 0;
  CUTTING_DATA_ROW[PreflowPlasmaPressure] = argv[30];
  CUTTING_DATA_ROW[PreflowShieldPressure] = argv[31];
  CUTTING_DATA_ROW[CutflowPlasmaPressure] = argv[32];
  CUTTING_DATA_ROW[CutflowShieldPressure] = argv[33];
  return 0;
}

static const std::string DATABASE_ACCESS_KEY = "F0885L";

DatabaseAccess::DatabaseAccess() : database_(NULL) {}

DatabaseAccess::~DatabaseAccess() {
  if (database_) {
    sqlite3_close(database_);
    database_ = NULL;
  }
}

bool DatabaseAccess::InitializeDatabaseAccess(const std::string &db_file,
                                              const std::string &db_key) {

  int rc = sqlite3_open(db_file.c_str(), &database_);
  if (rc != SQLITE_OK) {
    // TODO(Zhan Shi): 
    // printf("Fail to open the database: %s\n", sqlite3_errmsg(database_)) into Log file;
    return false;
  }
  std::string key = db_key.empty() ? DATABASE_ACCESS_KEY : db_key;
  rc = sqlite3_key(database_, key.c_str(), key.size());
  if (rc != SQLITE_OK) {
    // TODO(Zhan Shi): 
    // printf("error access key %s\n", sqlite3_errmsg(database_)) into Log file;
    return false;
  }
  return true;
}

void DatabaseAccess::LoadSmallContourParam() {
  std::vector<std::string> plasma_strs = SplitString(
      theApp.GetProfileString("SmallContour", "PlasmaPower"), ',');
  std::vector<std::string> gas_controller_strs = SplitString(
      theApp.GetProfileString("SmallContour", "GasController"), ',');
  std::vector<std::string> torch_strs = SplitString(
      theApp.GetProfileString("SmallContour", "Torch"), ',');

  plasma_id.clear();
  gas_controller_id.clear();
  torch_id.clear();
  for (size_t i = 0; i < plasma_strs.size(); i++) {
    plasma_id.push_back(atoi(plasma_strs[i]));
  }
  for (size_t i = 0; i < gas_controller_strs.size(); i++) {
    gas_controller_id.push_back(atoi(gas_controller_strs[i]));
  }
  for (size_t i = 0; i < torch_strs.size(); i++) {
    torch_id.push_back(atoi(torch_strs[i]));
  }
  vendor_id_ = theApp.GetProfileInt("SmallContour", "Vendor", 1);
  material_id_ = theApp.GetProfileInt("SmallContour", "Material", 1);
  cutting_technology_id_ = theApp.GetProfileInt("SmallContour", "CuttingTechnology", 1);
  thickness_ = theApp.GetProfileString("SmallContour", "Thickness");
  cutting_current_ = theApp.GetProfileString("SmallContour", "CuttingCurrent");
}

std::vector<std::string> DatabaseAccess::GetPlasmaPower() const {
  std::vector<std::string> rtn_values;
  for (size_t i = 0; i < plasma_id.size(); i++) {
    rtn_values.push_back(GetPlasmaModel(plasma_id[i], vendor_id_));
  }
  return rtn_values;
}

std::vector<std::string> DatabaseAccess::GetGasController() const {
  std::vector<std::string> rtn_values;
  for (size_t i = 0; i < gas_controller_id.size(); i++) {
    rtn_values.push_back(GetPartName(gas_controller_id[i], vendor_id_));
  }
  return rtn_values;
}

std::vector<std::string> DatabaseAccess::GetTorch() const {
  std::vector<std::string> rtn_values;
  for (size_t i = 0; i < torch_id.size(); i++) {
    rtn_values.push_back(GetPartName(torch_id[i], vendor_id_));
  }
  return rtn_values;
}

void DatabaseAccess::RefreshCuttingData(const std::vector<int> &plasma_power_ids,
                                        const std::vector<int> &gas_controller_ids,
                                        const std::vector<int> &torch_ids,
                                        int material_id,
                                        int cutting_technology_id,
                                        const std::string &thickness,
                                        const std::string &cutting_current) {

  if (plasma_power_ids.empty() || gas_controller_ids.empty() || torch_ids.empty()) {
    assert(false);
    return;
  }
  plasma_id = plasma_power_ids;
  gas_controller_id = gas_controller_ids;
  torch_id = torch_ids;
  material_id_ = material_id;
  cutting_technology_id_ = cutting_technology_id;
  thickness_ = thickness;
  cutting_current_ = cutting_current;

  // Get CuttingData.ID from CuttingIndex first.
  CuttingDataModel *data = (CuttingDataModel *)malloc(sizeof(CuttingDataModel));
  data->cutting_index = GetCuttingIndex();
  data->value = (char *)malloc(sizeof(char) * 100);
  // get follow cutting data from CuttingData.
  data->data_id = Cathode;
  GetCuttingData(data);
  data->data_id = GasGuide;
  GetCuttingData(data);
  data->data_id = Nozzle;
  GetCuttingData(data);
  data->data_id = NozzleCap;
  GetCuttingData(data);
  data->data_id = SwirlGasCap;
  GetCuttingData(data);
  data->data_id = ProtectionCap;
  GetCuttingData(data);
  data->data_id = CoolingTube;
  GetCuttingData(data);
  data->data_id = SwirlGasNozzle;
  GetCuttingData(data);
  data->data_id = PlasmaGas1;
  GetCuttingData(data);
  data->data_id = PlasmaGas2;
  GetCuttingData(data);
  data->data_id = PlasmaGas3;
  GetCuttingData(data);
  data->data_id = SwirlGas1;
  GetCuttingData(data);
  data->data_id = SwirlGas2;
  GetCuttingData(data);
  data->data_id = IgnitionGas;
  GetCuttingData(data);
  data->data_id = PlasmaGas1Pressure;
  GetCuttingData(data);
  data->data_id = PlasmaGas2Pressure;
  GetCuttingData(data);
  data->data_id = PlasmaGas3Pressure;
  GetCuttingData(data);
  data->data_id = SwirlGas1Pressure;
  GetCuttingData(data);
  data->data_id = SwirlGas2Pressure;
  GetCuttingData(data);
  data->data_id = CuttingPressure;
  GetCuttingData(data);
  data->data_id = UpSlope;
  GetCuttingData(data);
  data->data_id = DownSlope;
  GetCuttingData(data);
  data->data_id = IgnitionHeight;
  GetCuttingData(data);
  data->data_id = CuttingHeight;
  GetCuttingData(data);
  data->data_id = PierceHeight;
  GetCuttingData(data);
  data->data_id = PierceTime;
  GetCuttingData(data);
  data->data_id = CuttingVoltage;
  GetCuttingData(data);
  data->data_id = CuttingSpeedQuality;
  GetCuttingData(data);
  data->data_id = CuttingSpeedHole;
  GetCuttingData(data);
  data->data_id = KerfQuality;
  GetCuttingData(data);
  data->data_id = KerfHole;
  GetCuttingData(data);

  data->value = NULL;
  free(data->value);
  free(data);
  data = NULL;
}

int DatabaseAccess::GetCuttingIndex() {
  int rtn_value = 0;
  IDModel *data = (IDModel *)malloc(sizeof(IDModel));
  char *zErrMsg = NULL;
  char sql[500];
  sprintf(sql, "SELECT INDEX_ID FROM CuttingIndex \
                WHERE CuttingIndex.PLASMA_ID = %d \
                AND CuttingIndex.GAS_CONTROLLER_ID = %d \
                AND CuttingIndex.TORCH_ID = %d \
                GROUP BY PLASMA_ID, GAS_CONTROLLER_ID, TORCH_ID \
                HAVING VERSION = MAX(VERSION)\
                ORDER BY VERSION",
                plasma_id[0], gas_controller_id[0], torch_id[0]);

  int rc = sqlite3_exec(database_, sql, callback_IDModel, (void *)data, &zErrMsg);
  if (rc != SQLITE_OK) {
    // TODO(Zhan Shi): printf("SQL error: %s\n", zErrMsg) into Log file;
    sqlite3_free(zErrMsg);
  } else {
    rtn_value = data->index_in_table;
  }
  free(data);
  data = NULL;
  return rtn_value;
}

void DatabaseAccess::GetCuttingData(CuttingDataModel *data) {
  std::map<CuttingData, std::string>::const_iterator iter =
      CUTTING_DATA_MAP.find(data->data_id);

  if (iter == CUTTING_DATA_MAP.end()) {
    return ;
  }
  char *zErrMsg = NULL;
  char sql[500];
  sprintf(sql, "SELECT %s FROM CuttingData \
                WHERE CuttingData.ID = %d \
                AND CuttingData.MATERIAL = %d \
                AND CuttingData.TECHNOLOGY = %d \
                AND CuttingData.THICKNESS = '%s' \
                AND CuttingData.CUTTING_CURRENT = '%s'",
                iter->second, data->cutting_index,
                material_id_, cutting_technology_id_,
                thickness_, cutting_current_);

  int rc = sqlite3_exec(database_, sql, callback_CuttingDataModel, (void *)data, &zErrMsg);
  if (rc != SQLITE_OK) {
    // TODO(Zhan Shi): printf("SQL error: %s\n", zErrMsg) into Log file;
    sqlite3_free(zErrMsg);
  } else {
    switch (data->data_id) {
     case Cathode:
      cathode_id_ = atoi(data->value);
      cathode_ = GetPartName(cathode_id_, vendor_id_);
      break;
     case GasGuide:
      gas_guide_id_ = atoi(data->value);
      gas_guide_ = GetPartName(gas_guide_id_, vendor_id_);
      break;
     case Nozzle:
      nozzle_id_ = atoi(data->value);
      nozzle_ = GetPartName(nozzle_id_, vendor_id_);
      break;
     case NozzleCap:
      nozzle_cap_id_ = atoi(data->value);
      nozzle_cap_ = GetPartName(nozzle_cap_id_, vendor_id_);
      break;
     case SwirlGasCap:
      swirl_gas_cap_id_ = atoi(data->value);
      swirl_gas_cap_ = GetPartName(swirl_gas_cap_id_, vendor_id_);
      break;
     case ProtectionCap:
      protection_cap_id_ = atoi(data->value);
      protection_cap_ = GetPartName(protection_cap_id_, vendor_id_);
      break;
     case CoolingTube:
      cooling_tube_id_ = atoi(data->value);
      cooling_tube_ = GetPartName(cooling_tube_id_, vendor_id_);
      break;
     case SwirlGasNozzle:
      swirl_gas_nozzle_id_ = atoi(data->value);
      swirl_gas_nozzle_ = GetPartName(swirl_gas_nozzle_id_, vendor_id_);
      break;
     case PlasmaGas1:
      plasma_gas1_id_ = atoi(data->value);
      plasma_gas1_ = GetGasName(plasma_gas1_id_);
      break;
     case PlasmaGas2:
      plasma_gas2_id_ = atoi(data->value);
      plasma_gas2_ = GetGasName(plasma_gas2_id_);
      break;
     case PlasmaGas3:
      plasma_gas3_id_ = atoi(data->value);
      plasma_gas3_ = GetGasName(plasma_gas3_id_);
      break;
     case SwirlGas1:
      swirl_gas1_id_ = atoi(data->value);
      swirl_gas1_ = GetGasName(swirl_gas1_id_);
      break;
     case SwirlGas2:
      swirl_gas2_id_ = atoi(data->value);
      swirl_gas2_ = GetGasName(swirl_gas2_id_);
      break;
     case IgnitionGas:
      ignition_gas_id_ = atoi(data->value);
      ignition_gas_ = GetGasName(ignition_gas_id_);
      break;
     case PlasmaGas1Pressure:
      plasma_gas1_pressure_ = data->value;
      break;
     case PlasmaGas2Pressure:
      plasma_gas2_pressure_ = data->value;
      break;
     case PlasmaGas3Pressure:
      plasma_gas3_pressure_ = data->value;
      break;
     case SwirlGas1Pressure:
      swirl_gas1_pressure_ = data->value;
      break;
     case SwirlGas2Pressure:
      swirl_gas2_pressure_ = data->value;
      break;
     case CuttingPressure:
      cutting_pressure_ = data->value;
      break;
     case UpSlope:
      up_slope_ = data->value;
      break;
     case DownSlope:
      down_slope_ = data->value;
      break;
     case IgnitionHeight:
      ignition_height_ = data->value;
      break;
     case CuttingHeight:
      cutting_height_ = data->value;
      break;
     case PierceHeight:
      pierce_height_ = data->value;
      break;
     case PierceTime:
      pierce_time_ = data->value;
      break;
     case CuttingVoltage:
      cutting_voltage_ = data->value;
      break;
     case CuttingSpeedQuality:
      cutting_speed_quality_ = data->value;
      break;
     case CuttingSpeedHole:
      cutting_speed_hole_ = data->value;
      break;
     case KerfQuality:
      kerf_quality_ = data->value;
      break;
     case KerfHole:
      kerf_hole_ = data->value;
      break;
     default:
      break;
    }
  }
}

void DatabaseAccess::UpdateCuttingData(const std::vector<int> &plasma_power_ids,
                                       const std::vector<int> &gas_controller_ids,
                                       const std::vector<int> &torch_ids,
                                       int material_id,
                                       int cutting_technology_id,
                                       const std::string &thickness,
                                       const std::string &cutting_current) {

  if (plasma_power_ids.empty() || gas_controller_ids.empty() || torch_ids.empty()) {
    assert(false);
    return;
  }
  plasma_id = plasma_power_ids;
  gas_controller_id = gas_controller_ids;
  torch_id = torch_ids;
  material_id_ = material_id;
  cutting_technology_id_ = cutting_technology_id;
  thickness_ = thickness;
  cutting_current_ = cutting_current;

  // Get CuttingData.ID from CuttingIndex first.
  CuttingDataModel *data = (CuttingDataModel *)malloc(sizeof(CuttingDataModel));
  data->cutting_index = GetCuttingIndex();
  data->value = (char *)malloc(sizeof(char) * 100);
  // modify follow cutting data from CuttingData.
  data->data_id = IgnitionHeight;
  sprintf(data->value, "%s", ignition_height_);
  ModifyCuttingData(data);
  data->data_id = CuttingHeight;
  sprintf(data->value, "%s", cutting_height_);
  ModifyCuttingData(data);
  data->data_id = PierceHeight;
  sprintf(data->value, "%s", pierce_height_);
  ModifyCuttingData(data);
  data->data_id = PierceTime;
  sprintf(data->value, "%s", pierce_time_);
  ModifyCuttingData(data);
  data->data_id = CuttingVoltage;
  sprintf(data->value, "%s", cutting_voltage_);
  ModifyCuttingData(data);
  data->data_id = CuttingSpeedQuality;
  sprintf(data->value, "%s", cutting_speed_quality_);
  ModifyCuttingData(data);
  data->data_id = CuttingSpeedHole;
  sprintf(data->value, "%s", cutting_speed_hole_);
  ModifyCuttingData(data);
  data->data_id = KerfQuality;
  sprintf(data->value, "%s", kerf_quality_);
  ModifyCuttingData(data);
  data->data_id = KerfHole;
  sprintf(data->value, "%s", kerf_hole_);
  ModifyCuttingData(data);

  data->value = NULL;
  free(data->value);
  free(data);
  data = NULL;
}

void DatabaseAccess::ModifyCuttingData(CuttingDataModel *data) {
  std::map<CuttingData, std::string>::const_iterator iter =
      CUTTING_DATA_MAP.find(data->data_id);

  if (iter == CUTTING_DATA_MAP.end()) {
    return ;
  }
  char *zErrMsg = NULL;
  char sql[500];
  sprintf(sql, "UPDATE CuttingData \
                SET %s = '%s' \
                WHERE CuttingData.ID = %d \
                AND CuttingData.MATERIAL = %d \
                AND CuttingData.THICKNESS = %s \
                AND CuttingData.CUTTING_CURRENT = %s \
                AND CuttingData.TECHNOLOGY = %d",
                iter->second, data->value, data->cutting_index,
                material_id_, thickness_,
                cutting_current_, cutting_technology_id_);

  int rc = sqlite3_exec(database_, sql, NULL, (void *)data, &zErrMsg);
  if (rc != SQLITE_OK) {
    // TODO(Zhan Shi): printf("SQL error: %s\n", zErrMsg) into Log file;
    sqlite3_free(zErrMsg);
  }
}

void DatabaseAccess::CommitSmallContourParam() {
  theApp.WriteProfileString("SmallContour", "PlasmaPower",
      Compose(plasma_id, ','));

  theApp.WriteProfileString("SmallContour", "GasController",
      Compose(gas_controller_id, ','));

  theApp.WriteProfileString("SmallContour", "Torch",
      Compose(torch_id, ','));

  theApp.WriteProfileInt("SmallContour", "Vendor", vendor_id_);
  theApp.WriteProfileInt("SmallContour", "Material", material_id_);
  theApp.WriteProfileInt("SmallContour", "CuttingTechnology", cutting_technology_id_);
  theApp.WriteProfileString("SmallContour", "Thickness", thickness_);
  theApp.WriteProfileString("SmallContour", "CuttingCurrent", cutting_current_);
}

std::string DatabaseAccess::GetCutShieldGas(int gas_id) const {
  std::string rtn_value = "";
  char *zErrMsg = NULL;
  BaseModel *data = (BaseModel *)malloc(sizeof(BaseModel));
  data->id = gas_id;
  data->name = (char *)malloc(sizeof(char) * 100);
  char sql[500];
  sprintf(sql, "SELECT GAS_NAME FROM CutChartGas \
                WHERE CutChartGas.ID = %d",
                gas_id);

  int rc = sqlite3_exec(database_, sql, callback_BaseModel, (void *)data, &zErrMsg);
  if (rc != SQLITE_OK) {
    // TODO(Zhan Shi): printf("SQL error: %s\n", zErrMsg) into Log file;
    sqlite3_free(zErrMsg);
  } else {
    rtn_value = gas_id > 0 ? data->name : "";
  }
  data->name = NULL;
  free(data->name);
  free(data);
  data = NULL;
  return rtn_value;
}

std::string DatabaseAccess::GetPlasmaModel(int plasma_id, int vendor_id) const {
  std::string rtn_value = "";
  char *zErrMsg = NULL;
  BaseModel *data = (BaseModel *)malloc(sizeof(BaseModel));
  data->id = plasma_id;
  data->name = (char *)malloc(sizeof(char) * 100);
  char sql[500];
  sprintf(sql, "SELECT MODEL FROM Plasma \
                WHERE Plasma.ID = %d \
                AND Plasma.VENDOR_ID = %d",
                plasma_id, vendor_id);

  int rc = sqlite3_exec(database_, sql, callback_BaseModel, (void *)data, &zErrMsg);
  if (rc != SQLITE_OK) {
    // TODO(Zhan Shi): printf("SQL error: %s\n", zErrMsg) into Log file;
    sqlite3_free(zErrMsg);
  } else {
    rtn_value = plasma_id > 0 ? data->name : "";
  }
  data->name = NULL;
  free(data->name);
  free(data);
  data = NULL;
  return rtn_value;
}

std::string DatabaseAccess::GetPartName(int part_id, int vendor_id) const {
  std::string rtn_value = "";
  char *zErrMsg = NULL;
  BaseModel *data = (BaseModel *)malloc(sizeof(BaseModel));
  data->id = part_id;
  data->name = (char *)malloc(sizeof(char) * 100);
  char sql[500];
  sprintf(sql, "SELECT PART_NAME FROM Parts \
                WHERE Parts.ID = %d \
                AND Parts.VENDOR_ID = %d",
                part_id, vendor_id);

  int rc = sqlite3_exec(database_, sql, callback_BaseModel, (void *)data, &zErrMsg);
  if (rc != SQLITE_OK) {
    // TODO(Zhan Shi): printf("SQL error: %s\n", zErrMsg) into Log file;
    sqlite3_free(zErrMsg);
  } else {
    rtn_value = part_id > 0 ? data->name : "";
  }
  data->name = NULL;
  free(data->name);
  free(data);
  data = NULL;
  return rtn_value;
}

std::string DatabaseAccess::GetGasName(int gas_id) const {
  std::string rtn_value = "";
  char *zErrMsg = NULL;
  BaseModel *data = (BaseModel *)malloc(sizeof(BaseModel));
  data->id = gas_id;
  data->name = (char *)malloc(sizeof(char) * 100);
  char sql[500];
  sprintf(sql, "SELECT GAS_NAME FROM Gas \
                WHERE Gas.ID = %d",
                gas_id);

  int rc = sqlite3_exec(database_, sql, callback_BaseModel, (void *)data, &zErrMsg);
  if (rc != SQLITE_OK) {
    // TODO(Zhan Shi): printf("SQL error: %s\n", zErrMsg) into Log file;
    sqlite3_free(zErrMsg);
  } else {
    rtn_value = gas_id > 0 ? data->name : "";
  }
  data->name = NULL;
  free(data->name);
  free(data);
  data = NULL;
  return rtn_value;
}

std::string DatabaseAccess::GetMaterialName(int material_id) const {
  std::string rtn_value = "";
  char *zErrMsg = NULL;
  BaseModel *data = (BaseModel *)malloc(sizeof(BaseModel));
  data->id = material_id;
  data->name = (char *)malloc(sizeof(char) * 100);
  char sql[500];
  sprintf(sql, "SELECT NAME FROM Material \
                WHERE Material.ID = %d", material_id);

  int rc = sqlite3_exec(database_, sql, callback_BaseModel, (void *)data, &zErrMsg);
  if (rc != SQLITE_OK) {
    // TODO(Zhan Shi): printf("SQL error: %s\n", zErrMsg) into Log file;
    sqlite3_free(zErrMsg);
  } else {
    rtn_value = data->name;
  }
  data->name = NULL;
  free(data->name);
  free(data);
  data = NULL;
  return rtn_value;
}

std::string DatabaseAccess::GetCuttingTechnology(int cutting_technology_id) const {
  std::string rtn_value = "";
  char *zErrMsg = NULL;
  BaseModel *data = (BaseModel *)malloc(sizeof(BaseModel));
  data->id = cutting_technology_id;
  data->name = (char *)malloc(sizeof(char) * 100);
  char sql[500];
  sprintf(sql, "SELECT TECHNOLOGY FROM CutTechnology \
                WHERE CutTechnology.ID = %d", cutting_technology_id);

  int rc = sqlite3_exec(database_, sql, callback_BaseModel, (void *)data, &zErrMsg);
  if (rc != SQLITE_OK) {
    // TODO(Zhan Shi): printf("SQL error: %s\n", zErrMsg) into Log file;
    sqlite3_free(zErrMsg);
  } else {
    rtn_value = data->name;
  }
  data->name = NULL;
  free(data->name);
  free(data);
  data = NULL;
  return rtn_value;
}

std::string DatabaseAccess::GetVendorName(int vendor_id) const {
  std::string rtn_value = "";
  char *zErrMsg = NULL;
  BaseModel *data = (BaseModel *)malloc(sizeof(BaseModel));
  data->id = vendor_id;
  data->name = (char *)malloc(sizeof(char) * 100);
  char sql[500];
  sprintf(sql, "SELECT NAME FROM Vendor \
                WHERE Vendor.ID = %d", vendor_id);

  int rc = sqlite3_exec(database_, sql, callback_BaseModel, (void *)data, &zErrMsg);
  if (rc != SQLITE_OK) {
    // TODO(Zhan Shi): printf("SQL error: %s\n", zErrMsg) into Log file;
    sqlite3_free(zErrMsg);
  } else {
    rtn_value = data->name;
  }
  data->name = NULL;
  free(data->name);
  free(data);
  data = NULL;
  return rtn_value;
}

int DatabaseAccess::GetVendorID(const std::string vendor_name) const {
  int rtn_value = 0;
  char *zErrMsg = NULL;
  IDModel *data = (IDModel *)malloc(sizeof(IDModel));
  char sql[500];
  sprintf(sql, "SELECT ID FROM Vendor \
                WHERE Vendor.NAME = '%s'",
                vendor_name);

  int rc = sqlite3_exec(database_, sql, callback_IDModel, (void *)data, &zErrMsg);
  if (rc != SQLITE_OK) {
    // TODO(Zhan Shi): printf("SQL error: %s\n", zErrMsg) into Log file;
    sqlite3_free(zErrMsg);
  } else {
    rtn_value = data->index_in_table;
  }
  free(data);
  data = NULL;
  return rtn_value;
}

int DatabaseAccess::GetGasID(const std::string gas_name) const {
  int rtn_value = 0;
  char *zErrMsg = NULL;
  IDModel *data = (IDModel *)malloc(sizeof(IDModel));
  char sql[500];
  sprintf(sql, "SELECT ID FROM Gas \
                WHERE Gas.GAS_NAME = '%s'",
                gas_name);

  int rc = sqlite3_exec(database_, sql, callback_IDModel, (void *)data, &zErrMsg);
  if (rc != SQLITE_OK) {
    // TODO(Zhan Shi): printf("SQL error: %s\n", zErrMsg) into Log file;
    sqlite3_free(zErrMsg);
  } else {
    rtn_value = data->index_in_table;
  }
  free(data);
  data = NULL;
  return rtn_value;
}

int DatabaseAccess::GetPartID(const std::string part_name) const {
  int rtn_value = 0;
  char *zErrMsg = NULL;
  IDModel *data = (IDModel *)malloc(sizeof(IDModel));
  char sql[500];
  sprintf(sql, "SELECT ID FROM Parts \
                WHERE Parts.PART_NAME = '%s' \
                AND Parts.VENDOR_ID = %d",
                part_name, vendor_id_);

  int rc = sqlite3_exec(database_, sql, callback_IDModel, (void *)data, &zErrMsg);
  if (rc != SQLITE_OK) {
    // TODO(Zhan Shi): printf("SQL error: %s\n", zErrMsg) into Log file;
    sqlite3_free(zErrMsg);
  } else {
    rtn_value = data->index_in_table;
  }
  free(data);
  data = NULL;
  return rtn_value;
}

int DatabaseAccess::GetPlasmaID(const std::string plasma_model) const {
  int rtn_value = 0;
  char *zErrMsg = NULL;
  IDModel *data = (IDModel *)malloc(sizeof(IDModel));
  char sql[500];
  sprintf(sql, "SELECT ID FROM Plasma \
                WHERE Plasma.MODEL = '%s' \
                AND Plasma.VENDOR_ID = %d",
                plasma_model, vendor_id_);

  int rc = sqlite3_exec(database_, sql, callback_IDModel, (void *)data, &zErrMsg);
  if (rc != SQLITE_OK) {
    // TODO(Zhan Shi): printf("SQL error: %s\n", zErrMsg) into Log file;
    sqlite3_free(zErrMsg);
  } else {
    rtn_value = data->index_in_table;
  }
  free(data);
  data = NULL;
  return rtn_value;
}

int DatabaseAccess::GetMaterialID(const std::string material_name) const {
  int rtn_value = 0;
  char *zErrMsg = NULL;
  IDModel *data = (IDModel *)malloc(sizeof(IDModel));
  char sql[500];
  sprintf(sql, "SELECT ID FROM Material \
                WHERE Material.NAME = '%s'",
                material_name);

  int rc = sqlite3_exec(database_, sql, callback_IDModel, (void *)data, &zErrMsg);
  if (rc != SQLITE_OK) {
    // TODO(Zhan Shi): printf("SQL error: %s\n", zErrMsg) into Log file;
    sqlite3_free(zErrMsg);
  } else {
    rtn_value = data->index_in_table;
  }
  free(data);
  data = NULL;
  return rtn_value;
}

int DatabaseAccess::GetCutTechnologyID(const std::string technology) const {
  int rtn_value = 0;
  char *zErrMsg = NULL;
  IDModel *data = (IDModel *)malloc(sizeof(IDModel));
  char sql[500];
  sprintf(sql, "SELECT ID FROM CutTechnology \
                WHERE CutTechnology.TECHNOLOGY = '%s'",
                technology);

  int rc = sqlite3_exec(database_, sql, callback_IDModel, (void *)data, &zErrMsg);
  if (rc != SQLITE_OK) {
    // TODO(Zhan Shi): printf("SQL error: %s\n", zErrMsg) into Log file;
    sqlite3_free(zErrMsg);
  } else {
    rtn_value = data->index_in_table;
  }
  free(data);
  data = NULL;
  return rtn_value;
}

std::vector<std::string> DatabaseAccess::GetGasNames() const {
  TABLE_COLUMN.clear();
  char *zErrMsg = NULL;
  char sql[500];
  sprintf(sql, "SELECT GAS_NAME FROM Gas");
  int rc = sqlite3_exec(database_, sql, callback_Table, NULL, &zErrMsg);
  if (rc != SQLITE_OK) {
    // TODO(Zhan Shi): printf("SQL error: %s\n", zErrMsg) into Log file;
    sqlite3_free(zErrMsg);
  }
  return TABLE_COLUMN;
}

std::vector<std::string> DatabaseAccess::GetVendorNames() const {
  TABLE_COLUMN.clear();
  char *zErrMsg = NULL;
  char sql[500];
  sprintf(sql, "SELECT NAME FROM Vendor");
  int rc = sqlite3_exec(database_, sql, callback_Table, NULL, &zErrMsg);
  if (rc != SQLITE_OK) {
    // TODO(Zhan Shi): printf("SQL error: %s\n", zErrMsg) into Log file;
    sqlite3_free(zErrMsg);
  }
  return TABLE_COLUMN;
}

std::vector<std::string> DatabaseAccess::GetPartNames(int vendor_id) const {
  TABLE_COLUMN.clear();
  char *zErrMsg = NULL;
  char sql[500];
  sprintf(sql, "SELECT PART_NAME FROM Parts \
                WHERE Parts.VENDOR_ID = %d",
                vendor_id);

  int rc = sqlite3_exec(database_, sql, callback_Table, NULL, &zErrMsg);
  if (rc != SQLITE_OK) {
    // TODO(Zhan Shi): printf("SQL error: %s\n", zErrMsg) into Log file;
    sqlite3_free(zErrMsg);
  }
  return TABLE_COLUMN;
}

std::vector<std::string> DatabaseAccess::GetPlasmaModels(int vendor_id) const {
  TABLE_COLUMN.clear();
  char *zErrMsg = NULL;
  char sql[500];
  sprintf(sql, "SELECT MODEL FROM Plasma \
                WHERE Plasma.VENDOR_ID = %d",
                vendor_id);

  int rc = sqlite3_exec(database_, sql, callback_Table, NULL, &zErrMsg);
  if (rc != SQLITE_OK) {
    // TODO(Zhan Shi): printf("SQL error: %s\n", zErrMsg) into Log file;
    sqlite3_free(zErrMsg);
  }
  return TABLE_COLUMN;
}

std::vector<std::string> DatabaseAccess::GetGasBox(
    const std::vector<std::string> &plasma) const {

  TABLE_COLUMN.clear();
  char *zErrMsg = NULL;
  std::string sql_str = "select DISTINCT Parts.PART_NAME from CuttingIndex \
                     left join Plasma \
                     on CuttingIndex.PLASMA_ID = Plasma.ID \
                     left join Parts \
                     on CuttingIndex.GAS_CONTROLLER_ID = Parts.ID \
                     WHERE ";

  for (size_t i = 0; i < plasma.size(); i++) {
    std::string sub_str = _T("");
    sub_str.Format(_T("Plasma.MODEL like '%s'"), plasma[i]);
    sql_str += sub_str;
    if (i != plasma.size() - 1) {
      sql_str += " OR ";
    }
  }
  char sql[500];
  sprintf(sql, "%s", sql_str);
  int rc = sqlite3_exec(database_, sql, callback_Table, NULL, &zErrMsg);
  if (rc != SQLITE_OK) {
    // TODO(Zhan Shi): printf("SQL error: %s\n", zErrMsg) into Log file;
    sqlite3_free(zErrMsg);
  }
  return TABLE_COLUMN;
}

std::vector<std::string> DatabaseAccess::GetTorch(
    const std::vector<std::string> &plasma,
    const std::vector<std::string> &gas_box) const {

  TABLE_COLUMN.clear();
  char *zErrMsg = NULL;
  char sql[500];
  sprintf(sql, "select DISTINCT torch_parts.PART_NAME from CuttingIndex \
                left join Plasma \
                on CuttingIndex.PLASMA_ID = Plasma.ID \
                left join Parts as gas_parts \
                on CuttingIndex.GAS_CONTROLLER_ID = gas_parts.ID \
                left join Parts as torch_parts \
                on CuttingIndex.TORCH_ID = torch_parts.ID \
                where Plasma.MODEL like '%s' and gas_parts.PART_NAME like '%s'",
                plasma[0], gas_box[0]);

  int rc = sqlite3_exec(database_, sql, callback_Table, NULL, &zErrMsg);
  if (rc != SQLITE_OK) {
    // TODO(Zhan Shi): printf("SQL error: %s\n", zErrMsg) into Log file;
    sqlite3_free(zErrMsg);
  }
  return TABLE_COLUMN;
}

std::vector<std::string> DatabaseAccess::GetMaterial(
    const std::vector<std::string> &plasma,
    const std::vector<std::string> &gas_box,
    const std::vector<std::string> &torch) const {

  if (plasma.empty() || gas_box.empty() || torch.empty()) {
    return std::vector<std::string>();
  }
  std::vector<std::string> rtn_values;
  TABLE_COLUMN.clear();
  char *zErrMsg = NULL;
  char sql[1000];
  sprintf(sql, "SELECT DISTINCT MATERIAL FROM CuttingData \
                WHERE CuttingData.ID = \
                (SELECT CuttingIndex.INDEX_ID FROM CuttingIndex \
                 LEFT JOIN Plasma ON CuttingIndex.PLASMA_ID = Plasma.ID \
                 LEFT JOIN Parts AS Torch ON CuttingIndex.TORCH_ID = Torch.ID \
                 LEFT JOIN Parts AS Flow ON CuttingIndex.GAS_CONTROLLER_ID = Flow.ID \
                 WHERE Plasma.MODEL LIKE '%s' \
                 AND Flow.PART_NAME LIKE '%s' \
                 AND Torch.PART_NAME LIKE '%s' \
                 GROUP BY PLASMA_ID, GAS_CONTROLLER_ID, TORCH_ID \
                 HAVING VERSION = MAX(VERSION)\
                 ORDER BY VERSION \
                ) \
                ORDER BY MATERIAL ASC",
                plasma[0], gas_box[0], torch[0]);

  int rc = sqlite3_exec(database_, sql, callback_Table, NULL, &zErrMsg);
  if (rc != SQLITE_OK) {
    // TODO(Zhan Shi): printf("SQL error: %s\n", zErrMsg) into Log file;
    sqlite3_free(zErrMsg);
  } else {
    for (size_t i = 0; i < TABLE_COLUMN.size(); i++) {
      rtn_values.push_back(GetMaterialName(atoi(TABLE_COLUMN[i])));
    }
  }
  return rtn_values;
}

std::vector<std::string> DatabaseAccess::GetMaterial() const {
  std::vector<std::string> rtn_values;
  TABLE_COLUMN.clear();
  char *zErrMsg = NULL;
  char sql[1024];
  sprintf(sql, "SELECT DISTINCT MATERIAL FROM CuttingData \
                ORDER BY MATERIAL ASC");

  int rc = sqlite3_exec(database_, sql, callback_Table, NULL, &zErrMsg);
  if (rc != SQLITE_OK) {
    // TODO(Zhan Shi): printf("SQL error: %s\n", zErrMsg) into Log file;
    sqlite3_free(zErrMsg);
  } else {
    for (size_t i = 0; i < TABLE_COLUMN.size(); i++) {
      rtn_values.push_back(GetMaterialName(atoi(TABLE_COLUMN[i])));
    }
  }
  return rtn_values;
}

std::vector<std::string> DatabaseAccess::GetThickness(
    const std::string &material,
    const std::vector<std::string> &plasma,
    const std::vector<std::string> &gas_box,
    const std::vector<std::string> &torch) const {

  if (plasma.empty() || gas_box.empty() || torch.empty()) {
    return std::vector<std::string>();
  }
  TABLE_COLUMN.clear();
  char *zErrMsg = NULL;
  char sql[1000];
  sprintf(sql, "SELECT DISTINCT THICKNESS FROM CuttingData \
                WHERE CuttingData.ID = \
                (SELECT CuttingIndex.INDEX_ID FROM CuttingIndex \
                 LEFT JOIN Plasma ON CuttingIndex.PLASMA_ID = Plasma.ID \
                 LEFT JOIN Parts AS Torch ON CuttingIndex.TORCH_ID = Torch.ID \
                 LEFT JOIN Parts AS Flow ON CuttingIndex.GAS_CONTROLLER_ID = Flow.ID \
                 WHERE Plasma.MODEL LIKE '%s' \
                 AND Flow.PART_NAME LIKE '%s' \
                 AND Torch.PART_NAME LIKE '%s' \
                 GROUP BY PLASMA_ID, GAS_CONTROLLER_ID, TORCH_ID \
                 HAVING VERSION = MAX(VERSION)\
                 ORDER BY VERSION \
                ) \
                AND CuttingData.MATERIAL = %d \
                ORDER BY THICKNESS ASC",
                plasma[0], gas_box[0], torch[0], GetMaterialID(material));

  int rc = sqlite3_exec(database_, sql, callback_Table, NULL, &zErrMsg);
  if (rc != SQLITE_OK) {
    // TODO(Zhan Shi): printf("SQL error: %s\n", zErrMsg) into Log file;
    sqlite3_free(zErrMsg);
  }
  return TABLE_COLUMN;
}

std::vector<std::string> DatabaseAccess::GetThickness(
    const std::string &material) const {

  TABLE_COLUMN.clear();
  char *zErrMsg = NULL;
  char sql[1024];
  sprintf(sql, "SELECT DISTINCT THICKNESS FROM CuttingData \
                WHERE CuttingData.MATERIAL = %d \
                ORDER BY THICKNESS ASC",
                GetMaterialID(material));

  int rc = sqlite3_exec(database_, sql, callback_Table, NULL, &zErrMsg);
  if (rc != SQLITE_OK) {
    // TODO(Zhan Shi): printf("SQL error: %s\n", zErrMsg) into Log file;
    sqlite3_free(zErrMsg);
  }
  return TABLE_COLUMN;
}

std::vector<std::string> DatabaseAccess::GetCuttingCurrent(
    const std::string &material,
    const std::string &thickness,
    const std::vector<std::string> &plasma,
    const std::vector<std::string> &gas_box,
    const std::vector<std::string> &torch) const {

  if (plasma.empty() || gas_box.empty() || torch.empty()) {
    return std::vector<std::string>();
  }
  TABLE_COLUMN.clear();
  char *zErrMsg = NULL;
  char sql[1000];
  sprintf(sql, "SELECT DISTINCT CUTTING_CURRENT FROM CuttingData \
                WHERE CuttingData.ID = \
                (SELECT CuttingIndex.INDEX_ID FROM CuttingIndex \
                 LEFT JOIN Plasma ON CuttingIndex.PLASMA_ID = Plasma.ID \
                 LEFT JOIN Parts AS Torch ON CuttingIndex.TORCH_ID = Torch.ID \
                 LEFT JOIN Parts AS Flow ON CuttingIndex.GAS_CONTROLLER_ID = Flow.ID \
                 WHERE Plasma.MODEL LIKE '%s' \
                 AND Flow.PART_NAME LIKE '%s' \
                 AND Torch.PART_NAME LIKE '%s' \
                 GROUP BY PLASMA_ID, GAS_CONTROLLER_ID, TORCH_ID \
                 HAVING VERSION = MAX(VERSION)\
                 ORDER BY VERSION \
                ) \
                AND CuttingData.MATERIAL = %d \
                AND CuttingData.THICKNESS = '%s' \
                ORDER BY CUTTING_CURRENT ASC",
                plasma[0], gas_box[0], torch[0],
                GetMaterialID(material), thickness);

  int rc = sqlite3_exec(database_, sql, callback_Table, NULL, &zErrMsg);
  if (rc != SQLITE_OK) {
    // TODO(Zhan Shi): printf("SQL error: %s\n", zErrMsg) into Log file;
    sqlite3_free(zErrMsg);
  }
  return TABLE_COLUMN;
}

std::vector<std::string> DatabaseAccess::GetCuttingCurrent(
    const std::string &material,
    const std::string &thickness) const {

  TABLE_COLUMN.clear();
  char *zErrMsg = NULL;
  char sql[1024];
  sprintf(sql, "SELECT DISTINCT CUTTING_CURRENT FROM CuttingData \
                WHERE CuttingData.MATERIAL = %d \
                AND CuttingData.THICKNESS = '%s' \
                ORDER BY CUTTING_CURRENT ASC",
                GetMaterialID(material), thickness);

  int rc = sqlite3_exec(database_, sql, callback_Table, NULL, &zErrMsg);
  if (rc != SQLITE_OK) {
    // TODO(Zhan Shi): printf("SQL error: %s\n", zErrMsg) into Log file;
    sqlite3_free(zErrMsg);
  }
  return TABLE_COLUMN;
}

std::vector<std::string> DatabaseAccess::GetCuttingTechnology(
    const std::string &material,
    const std::string &thickness,
    const std::string &cutting_current,
    const std::vector<std::string> &plasma,
    const std::vector<std::string> &gas_box,
    const std::vector<std::string> &torch) const {

  if (plasma.empty() || gas_box.empty() || torch.empty()) {
    return std::vector<std::string>();
  }
  std::vector<std::string> rtn_values;
  TABLE_COLUMN.clear();
  char *zErrMsg = NULL;
  char sql[1000];
  sprintf(sql, "SELECT DISTINCT TECHNOLOGY FROM CuttingData \
                WHERE CuttingData.ID = \
                (SELECT CuttingIndex.INDEX_ID FROM CuttingIndex \
                 LEFT JOIN Plasma ON CuttingIndex.PLASMA_ID = Plasma.ID \
                 LEFT JOIN Parts AS Torch ON CuttingIndex.TORCH_ID = Torch.ID \
                 LEFT JOIN Parts AS Flow ON CuttingIndex.GAS_CONTROLLER_ID = Flow.ID \
                 WHERE Plasma.MODEL LIKE '%s' \
                 AND Flow.PART_NAME LIKE '%s' \
                 AND Torch.PART_NAME LIKE '%s' \
                 GROUP BY PLASMA_ID, GAS_CONTROLLER_ID, TORCH_ID \
                 HAVING VERSION = MAX(VERSION)\
                 ORDER BY VERSION \
                ) \
                AND CuttingData.MATERIAL = %d \
                AND CuttingData.THICKNESS = '%s' \
                AND CuttingData.CUTTING_CURRENT = '%s' \
                ORDER BY TECHNOLOGY ASC",
                plasma[0], gas_box[0], torch[0],
                GetMaterialID(material), thickness, cutting_current);

  int rc = sqlite3_exec(database_, sql, callback_Table, NULL, &zErrMsg);
  if (rc != SQLITE_OK) {
    // TODO(Zhan Shi): printf("SQL error: %s\n", zErrMsg) into Log file;
    sqlite3_free(zErrMsg);
  } else {
    for (size_t i = 0; i < TABLE_COLUMN.size(); i++) {
      rtn_values.push_back(GetCuttingTechnology(atoi(TABLE_COLUMN[i])));
    }
  }
  return rtn_values;
}

std::vector<std::string> DatabaseAccess::GetProcessClassify(
    const std::string &material,
    const std::string &thickness,
    const std::string &cutting_current) const {

  TABLE_COLUMN.clear();
  char *zErrMsg = NULL;
  char sql[1024];
  sprintf(sql, "SELECT DISTINCT PROCESS_CLASSIFY FROM CuttingData \
                WHERE CuttingData.MATERIAL = %d \
                AND CuttingData.THICKNESS = '%s' \
                AND CuttingData.CUTTING_CURRENT = '%s' \
                ORDER BY PROCESS_CLASSIFY ASC",
                GetMaterialID(material), thickness, cutting_current);

  int rc = sqlite3_exec(database_, sql, callback_Table, NULL, &zErrMsg);
  if (rc != SQLITE_OK) {
    // TODO(Zhan Shi): printf("SQL error: %s\n", zErrMsg) into Log file;
    sqlite3_free(zErrMsg);
  }
  return TABLE_COLUMN;
}

void DatabaseAccess::SetHyperthermAllProfileCuttingData(
    CuttingData cutting_data,
    const std::string &cutting_data_value,
    int material_id,
    const std::string &thickness,
    const std::string &cutting_current,
    const std::string &process_classify) {

  std::map<CuttingData, std::string>::const_iterator iter =
      CUTTING_DATA_MAP.find(cutting_data);

  if (iter == CUTTING_DATA_MAP.end()) {
    return ;
  }
  CuttingDataModel *data = (CuttingDataModel *)malloc(sizeof(CuttingDataModel));
  data->cutting_index = 1;
  data->value = (char *)malloc(sizeof(char) * 100);
  data->data_id = cutting_data;
  sprintf(data->value, "%s", cutting_data_value);
  char *zErrMsg = NULL;
  char sql[500];
  sprintf(sql, "UPDATE CuttingData \
                SET %s = '%s' \
                WHERE CuttingData.ID = %d \
                AND CuttingData.MATERIAL = %d \
                AND CuttingData.THICKNESS = %s \
                AND CuttingData.CUTTING_CURRENT = %s \
                AND CuttingData.PROCESS_CLASSIFY = '%s' \
                AND CuttingData.PROFILE_TYPE = 0",
                iter->second, data->value, data->cutting_index,
                material_id, thickness,
                cutting_current, process_classify);

  int rc = sqlite3_exec(database_, sql, NULL, (void *)data, &zErrMsg);
  if (rc != SQLITE_OK) {
    // TODO(Zhan Shi): printf("SQL error: %s\n", zErrMsg) into Log file;
    sqlite3_free(zErrMsg);
  }
  data->value = NULL;
  free(data->value);
  free(data);
  data = NULL;
}

std::vector<std::string> DatabaseAccess::GetHyperthermInteriorProfileDiameter(
    int material_id,
    const std::string &thickness,
    const std::string &cutting_current,
    const std::string &process_classify) const {

  TABLE_COLUMN.clear();
  char *zErrMsg = NULL;
  char sql[1024];
  sprintf(sql, "SELECT DISTINCT DIAMETER FROM CuttingData \
                WHERE CuttingData.ID = %d \
                AND CuttingData.MATERIAL = %d \
                AND CuttingData.THICKNESS = '%s' \
                AND CuttingData.CUTTING_CURRENT = '%s' \
                AND CuttingData.PROCESS_CLASSIFY = '%s' \
                AND CuttingData.PROFILE_TYPE = 1 \
                ORDER BY DIAMETER ASC",
                1, material_id, thickness, cutting_current, process_classify);

  int rc = sqlite3_exec(database_, sql, callback_Table, NULL, &zErrMsg);
  if (rc != SQLITE_OK) {
    // TODO(Zhan Shi): printf("SQL error: %s\n", zErrMsg) into Log file;
    sqlite3_free(zErrMsg);
  }
  return TABLE_COLUMN;
}

void DatabaseAccess::SetHyperthermInteriorProfileCuttingData(
    CuttingData cutting_data,
    const std::string &cutting_data_value,
    double cur_diameter,
    int material_id,
    const std::string &thickness,
    const std::string &cutting_current,
    const std::string &process_classify) {

  std::map<CuttingData, std::string>::const_iterator iter =
      CUTTING_DATA_MAP.find(cutting_data);

  if (iter == CUTTING_DATA_MAP.end()) {
    return ;
  }
  CuttingDataModel *data = (CuttingDataModel *)malloc(sizeof(CuttingDataModel));
  data->cutting_index = 1;
  data->value = (char *)malloc(sizeof(char) * 100);
  data->data_id = cutting_data;
  sprintf(data->value, "%s", cutting_data_value);
  char *zErrMsg = NULL;
  char sql[500];
  sprintf(sql, "UPDATE CuttingData \
                SET %s = '%s' \
                WHERE CuttingData.ID = %d \
                AND CuttingData.MATERIAL = %d \
                AND CuttingData.THICKNESS = %s \
                AND CuttingData.CUTTING_CURRENT = %s \
                AND CuttingData.PROCESS_CLASSIFY = '%s' \
                AND CuttingData.PROFILE_TYPE = 1 \
                AND CuttingData.DIAMETER = '%.1f'",
                iter->second, data->value, data->cutting_index,
                material_id, thickness,
                cutting_current, process_classify, cur_diameter);

  int rc = sqlite3_exec(database_, sql, NULL, (void *)data, &zErrMsg);
  if (rc != SQLITE_OK) {
    // TODO(Zhan Shi): printf("SQL error: %s\n", zErrMsg) into Log file;
    sqlite3_free(zErrMsg);
  }
  data->value = NULL;
  free(data->value);
  free(data);
  data = NULL;
}

std::vector<std::string> DatabaseAccess::SplitString(std::string string,
                                                 char separate) {
  if (string.IsEmpty()) {
    return std::vector<std::string>();
  }
  std::string str_proc = string;
  std::vector<std::string> split_strs;
  int pos = 0;
  while (pos != -1) {
    pos = str_proc.Find(separate);
    if (pos == -1) {
      split_strs.push_back(str_proc);
      break;
    }
    split_strs.push_back(str_proc.Mid(0, pos));
    str_proc = str_proc.Mid(pos + 1);
  }
  return split_strs;
}

std::string DatabaseAccess::Compose(const std::vector<int> &ids,
                                char separate) {

  std::string rtn_values = "";
  for (size_t i = 0; i < ids.size(); i++) {
    std::string id = _T("");
    id.Format(_T("%d"), ids[i]);
    rtn_values += id;
    if (i != ids.size() - 1) {
      rtn_values += separate;
    }
  }
  return rtn_values;
}

std::map<CuttingData, std::string> DatabaseAccess::GetHyperthermCuttingData(
    int profile_type,
    std::string diameter,
    int material_id,
    const std::string &thickness,
    const std::string &cutting_current,
    const std::string &process_classify) const {

  CUTTING_DATA_ROW.clear();
  int cutting_index = 1;
  char *zErrMsg = NULL;
  char sql[500];
  sprintf(sql, "SELECT * FROM CuttingData \
                WHERE CuttingData.ID = %d \
                AND CuttingData.MATERIAL = %d \
                AND CuttingData.THICKNESS = '%s' \
                AND CuttingData.CUTTING_CURRENT = '%s' \
                AND CuttingData.PROCESS_CLASSIFY = '%s' \
                AND CuttingData.PROFILE_TYPE = %d \
                AND CuttingData.DIAMETER = '%s'",
                cutting_index, material_id, thickness, cutting_current,
                process_classify, profile_type, diameter);

  int rc = sqlite3_exec(database_, sql, callback_GetCuttingData, NULL, &zErrMsg);
  if (rc != SQLITE_OK) {
    // TODO(Zhan Shi): printf("SQL error: %s\n", zErrMsg) into Log file;
    sqlite3_free(zErrMsg);
  }
  return CUTTING_DATA_ROW;
}
