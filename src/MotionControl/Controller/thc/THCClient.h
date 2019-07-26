// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef CONTROLLER_THC_THCCLIENT_H__
#define CONTROLLER_THC_THCCLIENT_H__

#include "Base/Runnable.h"

class ClientHandlerManager;

class THCClient : public Runnable {
 public:
  THCClient();
  virtual ~THCClient();

  void SetClientHandlerManager(ClientHandlerManager *handler_manager);

  virtual void Run();

  bool SetupConnect();

  // Coil.(0X)
  bool DirectlyArc(bool status);
  bool PositionArc(bool status);
  bool AutoTHC(bool status);
  bool TorchUp(bool status);
  bool TorchDown(bool status);
  bool THCHome(bool status);
  bool PositionCheck(bool status);
  bool ArcOnCheck(bool status);
  bool OutputCheck(bool status, unsigned short port_num);

  // Input Bit.(1X)
  bool GetArcVoltageFeedback(bool &status);
  bool GetCollisionAlarm(bool &status);
  bool GetPierceFinish(bool &status);

  // Register.(4X)
  bool GetServoTHCMode(unsigned int &thc_mode);
  bool SetServoTHCMode(unsigned int thc_mode);
  bool GetServoArcOnMode(unsigned int &arc_on_mode);
  bool SetServoArcOnMode(unsigned int arc_on_mode);
  bool GetServoPosHSDownDis(float &distance);
  bool SetServoPosHSDownDis(float distance);
  bool GetServoIgnitionHeight(float &ignition_height);
  bool SetServoIgnitionHeight(float ignition_height);
  bool GetServoPierceHeight(float &pierce_height);
  bool SetServoPierceHeight(float pierce_height);
  bool GetServoCutHeight(float &cut_height);
  bool SetServoCutHeight(float cut_height);
  bool GetServoTorchUpHeightAfterM08(float &height);
  bool SetServoTorchUpHeightAfterM08(float height);
  bool GetServoAccelerate(float &servo_acc);
  bool SetServoAccelerate(float servo_acc);
  bool GetServoPulse(float &servo_pulse);
  bool SetServoPulse(float servo_pulse);
  bool GetServoLimitSpeed(float &servo_limit_speed);
  bool SetServoLimitSpeed(float servo_limit_speed);
  bool GetServoForbidTHC(unsigned int &forbid_thc);
  bool SetServoForbidTHC(unsigned int forbid_thc);
  bool GetServoSoftLimitEnable(unsigned int &soft_limit_enable);
  bool SetServoSoftLimitEnable(unsigned int soft_limit_enable);
  bool GetServoSoftLimitNegative(float &soft_limit_negative);
  bool SetServoSoftLimitNegative(float soft_limit_negative);
  bool GetDCPosHSDownTime(float &time);
  bool SetDCPosHSDownTime(float time);
  bool GetDCPositionUpTime(float &time);
  bool SetDCPositionUpTime(float time);
  bool GetDCPierceUpTime(float &time);
  bool SetDCPierceUpTime(float time);
  bool GetDCPierceDownTime(float &time);
  bool SetDCPierceDownTime(float time);
  bool GetDCRegualteSpeedTime(float &time);
  bool SetDCRegualteSpeedTime(float time);
  bool GetTHCMotor(unsigned int &thc_motor);
  bool SetTHCMotor(unsigned int thc_motor);

  bool GetPositionCheckDelay(float &pos_check_delay, unsigned int thc_motor);
  bool SetPositionCheckDelay(float pos_check_delay, unsigned int thc_motor);
  bool GetPierceTime(float &pierce_time, unsigned int thc_motor);
  bool SetPierceTime(float pierce_time, unsigned int thc_motor);
  bool GetCloseTHCTimeAfterM07(float &close_thc_time, unsigned int thc_motor);
  bool SetCloseTHCTimeAfterM07(float close_thc_time, unsigned int thc_motor);
  bool GetSensitivity(float &sensitivity, unsigned int thc_motor);
  bool SetSensitivity(float sensitivity, unsigned int thc_motor);
  bool GetMotorDirectionSwitch(unsigned int &motor_dir_switch, unsigned int thc_motor);
  bool SetMotorDirectionSwitch(unsigned int motor_dir_switch, unsigned int thc_motor);
  bool GetArcOnCheckTime(float &arc_on_check_time, unsigned int thc_motor);
  bool SetArcOnCheckTime(float arc_on_check_time, unsigned int thc_motor);
  bool GetTorchUpDelayAfterM08(float &delay, unsigned int thc_motor);
  bool SetTorchUpDelayAfterM08(float delay, unsigned int thc_motor);
  bool GetCollisionCount(unsigned int &collision_count, unsigned int thc_motor);
  bool SetCollisionCount(unsigned int collision_count, unsigned int thc_motor);
  bool GetPresetArcVoltage(float &arc_voltage, unsigned int thc_motor);
  bool SetPresetArcVoltage(float arc_voltage, unsigned int thc_motor);
  bool GetOverArcVolProtectValue(float &protect_value, unsigned int thc_motor);
  bool SetOverArcVolProtectValue(float protect_value, unsigned int thc_motor);
  bool GetOverKerfArcVolThreshold(float &threshold, unsigned int thc_motor);
  bool SetOverKerfArcVolThreshold(float threshold, unsigned int thc_motor);
  bool GetAutoSpeed(float &auto_speed, unsigned int thc_motor);
  bool SetAutoSpeed(float auto_speed, unsigned int thc_motor);
  bool GetPositionLowSpeed(float &pos_ls_speed, unsigned int thc_motor);
  bool SetPositionLowSpeed(float pos_ls_speed, unsigned int thc_motor);
  bool GetManualSpeed(float &manual_speed, unsigned int thc_motor);
  bool SetManualSpeed(float manual_speed, unsigned int thc_motor);
  bool GetSystemUnit(unsigned int &system_unit);
  bool SetSystemUnit(unsigned int system_unit);
  bool GetSystemLanguage(unsigned int &system_language);
  bool SetSystemLanguage(unsigned int system_language);
  bool GetModbusBaud(unsigned int &modbus_baud);
  bool SetModbusBaud(unsigned int modbus_baud);
  bool GetModbusSlaveID(unsigned int &modbus_slave_id);
  bool SetModbusSlaveID(unsigned int modbus_slave_id);
  bool GetModbusParity(unsigned int &modbus_parity);
  bool SetModbusParity(unsigned int modbus_parity);
  bool GetBootHomeEnable(unsigned int &boot_home_enable);
  bool SetBootHomeEnable(unsigned int boot_home_enable);
  bool GetArcVolRateOfChangeCheck(unsigned int &arc_vol_rate_of_change_check);
  bool SetArcVolRateOfChangeCheck(unsigned int arc_vol_rate_of_change_check);
  bool GetDebugMode(unsigned int &debug_mode);
  bool SetDebugMode(unsigned int debug_mode);
  bool GetArcVolCorrectFactor(float &arc_vol_correct_factor);
  bool SetArcVolCorrectFactor(float arc_vol_correct_factor);
  bool GetArcVolCorrectBase(float &arc_vol_correct_base);
  bool SetArcVolCorrectBase(float arc_vol_correct_base);
  bool GetArcOkCheckMode(unsigned int &arc_ok_check_mode);
  bool SetArcOkCheckMode(unsigned int arc_ok_check_mode);
  bool GetScaleFactor(float &scale_factor);
  bool SetScaleFactor(float scale_factor);
  bool GetIntegralCoefficient(float &integral_coefficient);
  bool SetIntegralCoefficient(float integral_coefficient);
  bool GetDifferentialCoefficient(float &differential_coefficient);
  bool SetDifferentialCoefficient(float differential_coefficient);
  bool GetRegulateCycle(unsigned int &regulate_cycle);
  bool SetRegulateCycle(unsigned int regulate_cycle);
  bool GetVariableScaleFactor(float &variable_scale_factor);
  bool SetVariableScaleFactor(float variable_scale_factor);
  bool GetMaximumSensitivity(float &maximum_sensitivity);
  bool SetMaximumSensitivity(float maximum_sensitivity);
  bool GetPIDOutputDeadZoneRange(float &pid_output_dead_zone_range);
  bool SetPIDOutputDeadZoneRange(float pid_output_dead_zone_range);
  bool GetArcVolAdjustAccuracy(float &arc_vol_adjust_accuracy);
  bool SetArcVolAdjustAccuracy(float arc_vol_adjust_accuracy);
  bool GetCollisionSignalFilterTime(float &collision_signal_filter_time);
  bool SetCollisionSignalFilterTime(float collision_signal_filter_time);
  bool GetOutputFunc(unsigned int &func, unsigned short io_num);
  bool SetOutputFunc(unsigned int func, unsigned short io_num);
  bool GetOutputType(unsigned int &type, unsigned short io_num);
  bool SetOutputType(unsigned int type, unsigned short io_num);
  bool GetOutputPort(unsigned int &port, unsigned short io_num);
  bool SetOutputPort(unsigned int port, unsigned short io_num);
  bool GetOutputPortSN(unsigned int &sn, unsigned short io_num);
  bool SetOutputPortSN(unsigned int sn, unsigned short io_num);
  bool GetInputFunc(unsigned int &func, unsigned short io_num);
  bool SetInputFunc(unsigned int func, unsigned short io_num);
  bool GetInputType(unsigned int &type, unsigned short io_num);
  bool SetInputType(unsigned int type, unsigned short io_num);
  bool GetInputPort(unsigned int &port, unsigned short io_num);
  bool SetInputPort(unsigned int port, unsigned short io_num);
  bool GetInputPortSN(unsigned int &sn, unsigned short io_num);
  bool SetInputPortSN(unsigned int sn, unsigned short io_num);

  bool GetConnectFlag(unsigned int &connect_flag);
  bool SetConnectFlag(unsigned int connect_flag);
  bool GetConnectTimeOut(unsigned int &connect_time_out);
  bool SetConnectTimeOut(unsigned int connect_time_out);
  bool SetMasterModel(unsigned int master_model);
  bool GetMasterHardwareVersion(unsigned int &master_hardware_version);
  bool SetMasterHardwareVersion(unsigned int master_hardware_version);
  bool GetMasterSoftwareVersion(unsigned int &master_software_version);
  bool SetMasterSoftwareVersion(unsigned int master_software_version);
  bool SetMasterVersionVerify(unsigned int master_version_verify);
  bool GetSlaveModel(unsigned int &slave_model);
  bool GetSlaveHardwareVersion(unsigned int &slave_hardware_version);
  bool SetSlaveHardwareVersion(unsigned int slave_hardware_version);
  bool GetSlaveSoftwareVersion(unsigned int &slave_software_version);
  bool SetSlaveSoftwareVersion(unsigned int slave_software_version);
  bool GetSlaveVersionVerify(unsigned int &slave_version_verify);

  // Input Register.(3X)
  bool GetInputPortStatus(unsigned int &status);
  bool GetOutputPortStatus(unsigned int &status);
  bool GetCurStatus(unsigned int &status);
  bool GetWarningStatus(unsigned int &status);
  bool GetCurArcVoltage(float &cur_arc_voltage);
  bool GetCurPosition(double &cur_position);
  bool GetCurSpeed(double &cur_speed);
  bool GetSteelPlateHeight(double &steel_plate_height);

 private:
  ClientHandlerManager *handler_manager_;

  bool ConnectTest();

  bool SlaveVersionVerify();

}; // class THCClient

#endif // CONTROLLER_THC_THCCLIENT_H__
