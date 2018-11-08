// Copyright 2016 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef DATABASE_DATABASEACCESS_H__
#define DATABASE_DATABASEACCESS_H__

#include <map>
#include <vector>

struct sqlite3;

typedef struct {
  int id;
  char *name;
} BaseModel;

typedef enum _CuttingData {
  Cathode,
  GasGuide,
  Nozzle,
  NozzleCap,
  SwirlGasCap,
  ProtectionCap,
  CoolingTube,
  SwirlGasNozzle,
  PlasmaGas1,
  PlasmaGas2,
  PlasmaGas3,
  SwirlGas1,
  SwirlGas2,
  IgnitionGas,
  PlasmaGas1Pressure,
  PlasmaGas2Pressure,
  PlasmaGas3Pressure,
  SwirlGas1Pressure,
  SwirlGas2Pressure,
  CuttingPressure,
  UpSlope,
  DownSlope,
  IgnitionHeight,
  CuttingHeight,
  PierceHeight,
  PierceTime,
  CuttingVoltage,
  CuttingSpeedQuality,
  CuttingSpeedHole,
  KerfQuality,
  KerfHole,
  // Hypertherm
  Feedrate,
  LeadInFeedrate,
  BaseKerf,
  Kerf,
  DisableAHC,
  AsynchronousStop,
  CutChartType,
  CutShieldGas,
  CuttingSurface,
  TransferHeightFactor,
  PierceHeightFactor,
  PierceDelayTime,
  CutHeight,
  CutHeightDelay,
  ArcVol,
  IHSDistance,
  PreflowPlasmaPressure,
  PreflowShieldPressure,
  CutflowPlasmaPressure,
  CutflowShieldPressure,

} CuttingData;

typedef struct {
  int cutting_index;
  CuttingData data_id;
  char *value;
} CuttingDataModel;

typedef struct {
  int index_in_table;
} IDModel;

class DatabaseAccess {
 public:
  DatabaseAccess();
  virtual ~DatabaseAccess();

  bool InitializeDatabaseAccess(const std::string &db_file,
                                const std::string &db_key);

  // Load the custom parameters from user parameter file.
  void LoadSmallContourParam();
  // Save the db data into user parameter file.
  void CommitSmallContourParam();

  std::vector<std::string> GetPlasmaPower() const;
  std::vector<std::string> GetGasController() const;
  std::vector<std::string> GetTorch() const;

  // According to plasma power id, gas controller id, torch id,
  // material id, cutting technology id, thickness, cutting current,
  // get current cutting data. 
  void RefreshCuttingData(const std::vector<int> &plasma_power_ids,
                          const std::vector<int> &gas_controller_ids,
                          const std::vector<int> &torch_ids,
                          int material_id,
                          int cutting_technology_id,
                          const std::string &thickness,
                          const std::string &cutting_current);

  // According to plasma power id, gas controller id, torch id,
  // material id, cutting technology id, thickness, cutting current,
  // modify corresponding cutting data.
  void UpdateCuttingData(const std::vector<int> &plasma_power_ids,
                         const std::vector<int> &gas_controller_ids,
                         const std::vector<int> &torch_ids,
                         int material_id,
                         int cutting_technology_id,
                         const std::string &thickness,
                         const std::string &cutting_current);

  //Get Palasma / Chield gas name from CutChartGas.
  std::string GetCutShieldGas(int gas_id) const;
  // Accoring to Plasma.ID and Plasma.VENDOR_ID,
  // get Plasma.MODEL.
  std::string GetPlasmaModel(int plasma_id, int vendor_id) const;
  // According to Parts.ID and current vendor_id_,
  // get Parts.PART_NAME.
  std::string GetPartName(int part_id, int vendor_id) const;
  // According to Gas.ID, get Gas.GAS_NAME.
  std::string GetGasName(int gas_id) const;
  // According to Material.ID, get Material.NAME.
  std::string GetMaterialName(int material_id) const;
  // According to CutTechnology.ID, get CutTechnology.TECHNOLOGY.
  std::string GetCuttingTechnology(int cutting_technology_id) const;
  // According to Vendor.ID, get Vendor.NAME.
  std::string GetVendorName(int vendor_id) const;
  // Get the ID.
  int GetVendorID(const std::string vendor_name) const;
  int GetGasID(const std::string gas_name) const;
  int GetPartID(const std::string part_name) const;
  int GetPlasmaID(const std::string plasma_model) const;
  int GetMaterialID(const std::string material_name) const;
  int GetCutTechnologyID(const std::string technology) const;

  // Get all Gas Names in Gas table.
  std::vector<std::string> GetGasNames() const;
  // Get all Vendor Names in Vendor table.
  std::vector<std::string> GetVendorNames() const;
  // According to special vendor id,
  // Get all Part Names in Parts table.
  std::vector<std::string> GetPartNames(int vendor_id) const;
  // According to special vendor id,
  // get all plasma power models in Plasma table.
  std::vector<std::string> GetPlasmaModels(int vendor_id) const;
  // According to several plasma selected,
  // get corresponding gas box in Parts table.
  std::vector<std::string> GetGasBox(const std::vector<std::string> &plasma) const;
  // According to several groups of plasma and gas box selected,
  // get corresponding torch in Parts table.
  std::vector<std::string> GetTorch(const std::vector<std::string> &plasma,
                                const std::vector<std::string> &gas_box) const;

  // According to current plasma power, gas box and torch selected,
  // get corresponding material in cutting data table.
  std::vector<std::string> GetMaterial(const std::vector<std::string> &plasma,
                                   const std::vector<std::string> &gas_box,
                                   const std::vector<std::string> &torch) const;

  std::vector<std::string> GetMaterial() const;

  // According to current material selected in one excel table,
  // get several thickness in cutting data table.
  std::vector<std::string> GetThickness(const std::string &material,
                                    const std::vector<std::string> &plasma,
                                    const std::vector<std::string> &gas_box,
                                    const std::vector<std::string> &torch) const;

  std::vector<std::string> GetThickness(const std::string &material) const;

  // According to current material and thickness selected in one excel table,
  // get cutting current in cutting data table.
  std::vector<std::string> GetCuttingCurrent(const std::string &material,
                                         const std::string &thickness,
                                         const std::vector<std::string> &plasma,
                                         const std::vector<std::string> &gas_box,
                                         const std::vector<std::string> &torch) const;

  std::vector<std::string> GetCuttingCurrent(const std::string &material,
                                         const std::string &thickness) const;

  // According to current material and thickness selected in one excel table,
  // get cutting current in cutting data table.
  std::vector<std::string> GetCuttingTechnology(const std::string &material,
                                            const std::string &thickness,
                                            const std::string &cutting_current,
                                            const std::vector<std::string> &plasma,
                                            const std::vector<std::string> &gas_box,
                                            const std::vector<std::string> &torch) const;

  std::vector<std::string> GetProcessClassify(const std::string &material,
                                          const std::string &thickness,
                                          const std::string &cutting_current) const;

  std::map<CuttingData, std::string> GetHyperthermCuttingData(
      int profile_type,
      std::string diameter,
      int material_id,
      const std::string &thickness,
      const std::string &cutting_current,
      const std::string &process_classify) const;

  void SetHyperthermAllProfileCuttingData(
      CuttingData cutting_data,
      const std::string &cutting_data_value,
      int material_id,
      const std::string &thickness,
      const std::string &cutting_current,
      const std::string &process_classify);

  void SetHyperthermInteriorProfileCuttingData(
      CuttingData cutting_data,
      const std::string &cutting_data_value,
      double cur_diameter,
      int material_id,
      const std::string &thickness,
      const std::string &cutting_current,
      const std::string &process_classify);

  std::vector<std::string> GetHyperthermInteriorProfileDiameter(
      int material_id,
      const std::string &thickness,
      const std::string &cutting_current,
      const std::string &process_classify) const;

  std::vector<int> plasma_id;
  std::vector<int> gas_controller_id;
  std::vector<int> torch_id;
  int material_id_;
  int cutting_technology_id_;
  std::string thickness_;
  std::string cutting_current_;

  std::string cathode_;
  int cathode_id_;
  std::string gas_guide_;
  int gas_guide_id_;
  std::string nozzle_;
  int nozzle_id_;
  std::string nozzle_cap_;
  int nozzle_cap_id_;
  std::string swirl_gas_cap_;
  int swirl_gas_cap_id_;
  std::string protection_cap_;
  int protection_cap_id_;
  std::string cooling_tube_;
  int cooling_tube_id_;
  std::string swirl_gas_nozzle_;
  int swirl_gas_nozzle_id_;
  std::string plasma_gas1_;
  int plasma_gas1_id_;
  std::string plasma_gas2_;
  int plasma_gas2_id_;
  std::string plasma_gas3_;
  int plasma_gas3_id_;
  std::string swirl_gas1_;
  int swirl_gas1_id_;
  std::string swirl_gas2_;
  int swirl_gas2_id_;
  std::string ignition_gas_;
  int ignition_gas_id_;
  std::string plasma_gas1_pressure_;
  std::string plasma_gas2_pressure_;
  std::string plasma_gas3_pressure_;
  std::string swirl_gas1_pressure_;
  std::string swirl_gas2_pressure_;
  std::string cutting_pressure_;
  std::string up_slope_;
  std::string down_slope_;
  std::string ignition_height_;
  std::string cutting_height_;
  std::string pierce_height_;
  std::string pierce_time_;
  std::string cutting_voltage_;
  std::string cutting_speed_quality_;
  std::string cutting_speed_hole_;
  std::string kerf_quality_;
  std::string kerf_hole_;

  int vendor_id_;

 private:
  std::vector<std::string> SplitString(std::string string, char separate);
  std::string Compose(const std::vector<int> &ids, char separate);
  int GetCuttingIndex();
  void GetCuttingData(CuttingDataModel *data);
  void ModifyCuttingData(CuttingDataModel *data);

  sqlite3 *database_;

};

#endif // DATABASE_DATABASEACCESS_H__