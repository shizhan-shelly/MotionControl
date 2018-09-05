// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "MasterClient.h"

#include <assert.h>

#include "ClientHandler.h"
#include "ModbusMappingDef.h"

MasterClient::MasterClient() : Runnable()
                             , connected_(false)
                             , handler_(nullptr) {}

MasterClient::~MasterClient() {}

void MasterClient::SetMasterClientHandler(ClientHandler *handler) {
  assert(handler);
  if (handler->Initialize()) {
    handler_ = handler;
  }
}

void MasterClient::Run() {
  if (!handler_) {
    return ;
  }
  if (!connected_) {
    if (SetupConnect()) {
      return ;
    }
  }
  while (connected_) {
    ConnectTest();
  }
}

bool MasterClient::SetupConnect() {
  connected_ = handler_->Connect();
  return connected_ && SlaveVersionVerify();
}

bool MasterClient::DirectlyArc(bool status) {
  return connected_ && handler_->WriteSingleCoil(DIRECTLY_ARC, status);
}

bool MasterClient::PositionArc(bool status) {
  return connected_ && handler_->WriteSingleCoil(POSITION_ARC, status);
}

bool MasterClient::AutoTHC(bool status) {
  return connected_ && handler_->WriteSingleCoil(AUTO_THC, status);
}

bool MasterClient::TorchUp(bool status) {
  return connected_ && handler_->WriteSingleCoil(TORCH_UP, status);
}

bool MasterClient::TorchDown(bool status) {
  return connected_ && handler_->WriteSingleCoil(TORCH_DOWN, status);
}

bool MasterClient::THCHome(bool status) {
  return connected_ && handler_->WriteSingleCoil(THC_HOME, status);
}

bool MasterClient::PositionCheck(bool status) {
  return connected_ && handler_->WriteSingleCoil(POSITION_CHECK, status);
}

bool MasterClient::ArcOnCheck(bool status) {
  return connected_ && handler_->WriteSingleCoil(ARC_ON_CHECK, status);
}

bool MasterClient::OutputCheck(bool status, unsigned short port_num) {
  return connected_ && handler_->WriteSingleCoil(OUTPUT_CHECK + port_num,
      status);

}

bool MasterClient::GetServoTHCMode(unsigned int &thc_mode) {
  return connected_ && handler_->ReadUint32Register(SERVO_THC_MODE, thc_mode);
}

bool MasterClient::SetServoTHCMode(unsigned int thc_mode) {
  return connected_ && handler_->WriteUint32Register(SERVO_THC_MODE, thc_mode);
}

bool MasterClient::GetServoArcOnMode(unsigned int &arc_on_mode) {
  return connected_ && handler_->ReadUint32Register(SERVO_ARC_ON_MODE, arc_on_mode);
}

bool MasterClient::SetServoArcOnMode(unsigned int arc_on_mode) {
  return connected_ && handler_->WriteUint32Register(SERVO_ARC_ON_MODE, arc_on_mode);
}

bool MasterClient::GetServoPosHSDownDis(float &distance) {
  return connected_ && handler_->ReadFloatRegister(SERVO_POS_HS_DWN_DIS, distance);
}

bool MasterClient::SetServoPosHSDownDis(float distance) {
  return connected_ && handler_->WriteFloatRegister(SERVO_POS_HS_DWN_DIS, distance);
}

bool MasterClient::GetServoIgnitionHeight(float &ignition_height) {
  return connected_ && handler_->ReadFloatRegister(SERVO_IGNITION_HEIGHT, ignition_height);
}

bool MasterClient::SetServoIgnitionHeight(float ignition_height) {
  return connected_ && handler_->WriteFloatRegister(SERVO_IGNITION_HEIGHT, ignition_height);
}

bool MasterClient::GetServoPierceHeight(float &pierce_height) {
  return connected_ && handler_->ReadFloatRegister(SERVO_PIERCE_HEIGHT, pierce_height);
}

bool MasterClient::SetServoPierceHeight(float pierce_height) {
  return connected_ && handler_->WriteFloatRegister(SERVO_PIERCE_HEIGHT, pierce_height);
}

bool MasterClient::GetServoCutHeight(float &cut_height) {
  return connected_ && handler_->ReadFloatRegister(SERVO_CUT_HEIGHT, cut_height);
}

bool MasterClient::SetServoCutHeight(float cut_height) {
  return connected_ && handler_->WriteFloatRegister(SERVO_CUT_HEIGHT, cut_height);
}

bool MasterClient::GetServoTorchUpHeightAfterM08(float &height) {
  return connected_ && handler_->ReadFloatRegister(SERVO_M08_TORCH_UP_HEIGHT, height);
}

bool MasterClient::SetServoTorchUpHeightAfterM08(float height) {
  return connected_ && handler_->WriteFloatRegister(SERVO_M08_TORCH_UP_HEIGHT, height);
}

bool MasterClient::GetServoAccelerate(float &servo_acc) {
  return connected_ && handler_->ReadFloatRegister(SERVO_ACCELERATE, servo_acc);
}

bool MasterClient::SetServoAccelerate(float servo_acc) {
  return connected_ && handler_->WriteFloatRegister(SERVO_ACCELERATE, servo_acc);
}

bool MasterClient::GetServoPulse(float &servo_pulse) {
  return connected_ && handler_->ReadFloatRegister(SERVO_PULSE, servo_pulse);
}

bool MasterClient::SetServoPulse(float servo_pulse) {
  return connected_ && handler_->WriteFloatRegister(SERVO_PULSE, servo_pulse);
}

bool MasterClient::GetServoLimitSpeed(float &servo_limit_speed) {
  return connected_ && handler_->ReadFloatRegister(SERVO_LIMIT_SPEED, servo_limit_speed);
}

bool MasterClient::SetServoLimitSpeed(float servo_limit_speed) {
  return connected_ && handler_->WriteFloatRegister(SERVO_LIMIT_SPEED, servo_limit_speed);
}

bool MasterClient::GetServoForbidTHC(unsigned int &forbid_thc) {
  return connected_ && handler_->ReadUint32Register(SERVO_FORBID_THC, forbid_thc);
}

bool MasterClient::SetServoForbidTHC(unsigned int forbid_thc) {
  return connected_ && handler_->WriteUint32Register(SERVO_FORBID_THC, forbid_thc);
}

bool MasterClient::GetServoSoftLimitEnable(unsigned int &soft_limit_enable) {
  return connected_ && handler_->ReadUint32Register(SERVO_SOFT_LIMIT_ENABLE, soft_limit_enable);
}

bool MasterClient::SetServoSoftLimitEnable(unsigned int soft_limit_enable) {
  return connected_ && handler_->WriteUint32Register(SERVO_SOFT_LIMIT_ENABLE, soft_limit_enable);
}

bool MasterClient::GetServoSoftLimitNegative(float &soft_limit_negative) {
  return connected_ && handler_->ReadFloatRegister(SERVO_SOFT_LIMIT_NEGATIVE, soft_limit_negative);
}

bool MasterClient::SetServoSoftLimitNegative(float soft_limit_negative) {
  return connected_ && handler_->WriteFloatRegister(SERVO_SOFT_LIMIT_NEGATIVE, soft_limit_negative);
}

bool MasterClient::GetDCPosHSDownTime(float &time) {
  return connected_ && handler_->ReadFloatRegister(DC_POS_HS_DWN_TIME, time);
}

bool MasterClient::SetDCPosHSDownTime(float time) {
  return connected_ && handler_->WriteFloatRegister(DC_POS_HS_DWN_TIME, time);
}

bool MasterClient::GetDCPositionUpTime(float &time) {
  return connected_ && handler_->ReadFloatRegister(DC_POSITION_UP_TIME, time);
}

bool MasterClient::SetDCPositionUpTime(float time) {
  return connected_ && handler_->WriteFloatRegister(DC_POSITION_UP_TIME, time);
}

bool MasterClient::GetDCPierceUpTime(float &time) {
  return connected_ && handler_->ReadFloatRegister(DC_PIERCE_UP_TIME, time);
}

bool MasterClient::SetDCPierceUpTime(float time) {
  return connected_ && handler_->WriteFloatRegister(DC_PIERCE_UP_TIME, time);
}

bool MasterClient::GetDCPierceDownTime(float &time) {
  return connected_ && handler_->ReadFloatRegister(DC_PIERCE_DOWN_TIME, time);
}

bool MasterClient::SetDCPierceDownTime(float time) {
  return connected_ && handler_->WriteFloatRegister(DC_PIERCE_DOWN_TIME, time);
}

bool MasterClient::GetDCRegualteSpeedTime(float &time) {
  return connected_ && handler_->ReadFloatRegister(DC_REGULATE_SPEED_TIME, time);
}

bool MasterClient::SetDCRegualteSpeedTime(float time) {
  return connected_ && handler_->WriteFloatRegister(DC_REGULATE_SPEED_TIME, time);
}

bool MasterClient::GetTHCMotor(unsigned int &thc_motor) {
  return connected_ && handler_->ReadUint32Register(THC_MOTOR, thc_motor);
}

bool MasterClient::SetTHCMotor(unsigned int thc_motor) {
  return connected_ && handler_->WriteUint32Register(THC_MOTOR, thc_motor);
}

bool MasterClient::GetPositionCheckDelay(float &pos_check_delay,
                                         unsigned int thc_motor) {

  return connected_ && handler_->ReadFloatRegister(
      thc_motor == 0 ? SERVO_POS_CHECK_DELAY : DC_POS_CHECK_DELAY,
      pos_check_delay);

}

bool MasterClient::SetPositionCheckDelay(float pos_check_delay,
                                         unsigned int thc_motor) {

  return connected_ && handler_->WriteFloatRegister(
      thc_motor == 0 ? SERVO_POS_CHECK_DELAY : DC_POS_CHECK_DELAY,
      pos_check_delay);

}

bool MasterClient::GetPierceTime(float &pierce_time,
                                 unsigned int thc_motor) {

  return connected_ && handler_->ReadFloatRegister(
      thc_motor == 0 ? SERVO_PIERCE_TIME : DC_PIERCE_TIME,
      pierce_time);

}

bool MasterClient::SetPierceTime(float pierce_time,
                                 unsigned int thc_motor) {

  return connected_ && handler_->WriteFloatRegister(
      thc_motor == 0 ? SERVO_PIERCE_TIME : DC_PIERCE_TIME,
      pierce_time);

}

bool MasterClient::GetCloseTHCTimeAfterM07(float &close_thc_time,
                                           unsigned int thc_motor) {

  return connected_ && handler_->ReadFloatRegister(
      thc_motor == 0 ? SERVO_CLOSE_THC_TIME_AFTER_M07 : DC_CLOSE_THC_TIME_AFTER_M07,
      close_thc_time);

}

bool MasterClient::SetCloseTHCTimeAfterM07(float close_thc_time,
                                           unsigned int thc_motor) {

  return connected_ && handler_->WriteFloatRegister(
      thc_motor == 0 ? SERVO_CLOSE_THC_TIME_AFTER_M07 : DC_CLOSE_THC_TIME_AFTER_M07,
      close_thc_time);

}

bool MasterClient::GetSensitivity(float &sensitivity,
                                  unsigned int thc_motor) {

  return connected_ && handler_->ReadFloatRegister(
      thc_motor == 0 ? SERVO_SENSITIVITY : DC_SENSITIVITY,
      sensitivity);

}

bool MasterClient::SetSensitivity(float sensitivity,
                                  unsigned int thc_motor) {

  return connected_ && handler_->WriteFloatRegister(
      thc_motor == 0 ? SERVO_SENSITIVITY : DC_SENSITIVITY,
      sensitivity);

}

bool MasterClient::GetMotorDirectionSwitch(unsigned int &motor_dir_switch,
                                           unsigned int thc_motor) {

  return connected_ && handler_->ReadUint32Register(
      thc_motor == 0 ? SERVO_MOTOR_DIR_SWITCH : DC_MOTOR_DIR_SWITCH,
      motor_dir_switch);

}

bool MasterClient::SetMotorDirectionSwitch(unsigned int motor_dir_switch,
                                           unsigned int thc_motor) {

  return connected_ && handler_->WriteUint32Register(
      thc_motor == 0 ? SERVO_MOTOR_DIR_SWITCH : DC_MOTOR_DIR_SWITCH,
      motor_dir_switch);

}

bool MasterClient::GetArcOnCheckTime(float &arc_on_check_time,
                                     unsigned int thc_motor) {

  return connected_ && handler_->ReadFloatRegister(
      thc_motor == 0 ? SERVO_ARC_ON_CHECK_TIME : DC_ARC_ON_CHECK_TIME,
      arc_on_check_time);

}

bool MasterClient::SetArcOnCheckTime(float arc_on_check_time,
                                     unsigned int thc_motor) {

  return connected_ && handler_->WriteFloatRegister(
      thc_motor == 0 ? SERVO_ARC_ON_CHECK_TIME : DC_ARC_ON_CHECK_TIME,
      arc_on_check_time);

}

bool MasterClient::GetTorchUpDelayAfterM08(float &delay,
                                           unsigned int thc_motor) {

  return connected_ && handler_->ReadFloatRegister(
      thc_motor == 0 ? SERVO_M08_TORCH_UP_DELAY : DC_M08_TORCH_UP_DELAY,
      delay);

}

bool MasterClient::SetTorchUpDelayAfterM08(float delay,
                                           unsigned int thc_motor) {

  return connected_ && handler_->WriteFloatRegister(
      thc_motor == 0 ? SERVO_M08_TORCH_UP_DELAY : DC_M08_TORCH_UP_DELAY,
      delay);

}

bool MasterClient::GetCollisionCount(unsigned int &collision_count,
                                     unsigned int thc_motor) {

  return connected_ && handler_->ReadUint32Register(
      thc_motor == 0 ? SERVO_COLLISION_COUNT : DC_COLLISION_COUNT,
      collision_count);

}

bool MasterClient::SetCollisionCount(unsigned int collision_count,
                                     unsigned int thc_motor) {

  return connected_ && handler_->WriteUint32Register(
      thc_motor == 0 ? SERVO_COLLISION_COUNT : DC_COLLISION_COUNT,
      collision_count);

}

bool MasterClient::GetPresetArcVoltage(float &arc_voltage,
                                       unsigned int thc_motor) {

  return connected_ && handler_->ReadFloatRegister(
      thc_motor == 0 ? SERVO_PRESET_ARC_VOLTAGE : DC_PRESET_ARC_VOLTAGE,
      arc_voltage);

}

bool MasterClient::SetPresetArcVoltage(float arc_voltage,
                                       unsigned int thc_motor) {

  return connected_ && handler_->WriteFloatRegister(
      thc_motor == 0 ? SERVO_PRESET_ARC_VOLTAGE : DC_PRESET_ARC_VOLTAGE,
      arc_voltage);

}

bool MasterClient::GetOverArcVolProtectValue(float &protect_value,
                                             unsigned int thc_motor) {

  return connected_ && handler_->ReadFloatRegister(thc_motor == 0
      ? SERVO_OVER_ARC_VOL_PROTECT_VALUE : DC_OVER_ARC_VOL_PROTECT_VALUE,
      protect_value);

}

bool MasterClient::SetOverArcVolProtectValue(float protect_value,
                                             unsigned int thc_motor) {

  return connected_ && handler_->WriteFloatRegister(thc_motor == 0
      ? SERVO_OVER_ARC_VOL_PROTECT_VALUE : DC_OVER_ARC_VOL_PROTECT_VALUE,
      protect_value);

}

bool MasterClient::GetOverKerfArcVolThreshold(float &threshold,
                                              unsigned int thc_motor) {

  return connected_ && handler_->ReadFloatRegister(thc_motor == 0
      ? SERVO_OVER_KERF_ARC_VOL_THRESHOLD : DC_OVER_KERF_ARC_VOL_THRESHOLD,
      threshold);

}

bool MasterClient::SetOverKerfArcVolThreshold(float threshold,
                                              unsigned int thc_motor) {

  return connected_ && handler_->WriteFloatRegister(thc_motor == 0
      ? SERVO_OVER_KERF_ARC_VOL_THRESHOLD : DC_OVER_KERF_ARC_VOL_THRESHOLD,
      threshold);

}

bool MasterClient::GetAutoSpeed(float &auto_speed,
                                unsigned int thc_motor) {

  return connected_ && handler_->ReadFloatRegister(
      thc_motor == 0 ? SERVO_AUTO_SPEED : DC_AUTO_SPEED,
      auto_speed);

}

bool MasterClient::SetAutoSpeed(float auto_speed,
                                unsigned int thc_motor) {

  return connected_ && handler_->WriteFloatRegister(
      thc_motor == 0 ? SERVO_AUTO_SPEED : DC_AUTO_SPEED,
      auto_speed);

}

bool MasterClient::GetPositionLowSpeed(float &pos_ls_speed,
                                       unsigned int thc_motor) {

  return connected_ && handler_->ReadFloatRegister(
      thc_motor == 0 ? SERVO_POS_LS_SPEED : DC_POS_LS_SPEED,
      pos_ls_speed);

}

bool MasterClient::SetPositionLowSpeed(float pos_ls_speed,
                                       unsigned int thc_motor) {

  return connected_ && handler_->WriteFloatRegister(
      thc_motor == 0 ? SERVO_POS_LS_SPEED : DC_POS_LS_SPEED,
      pos_ls_speed);

}

bool MasterClient::GetManualSpeed(float &manual_speed,
                                  unsigned int thc_motor) {

  return connected_ && handler_->ReadFloatRegister(
      thc_motor == 0 ? SERVO_MANUAL_SPEED : DC_MANUAL_SPEED,
      manual_speed);

}

bool MasterClient::SetManualSpeed(float manual_speed,
                                  unsigned int thc_motor) {

  return connected_ && handler_->WriteFloatRegister(
      thc_motor == 0 ? SERVO_MANUAL_SPEED : DC_MANUAL_SPEED,
      manual_speed);

}

bool MasterClient::GetSystemUnit(unsigned int &system_unit) {
  return connected_ && handler_->ReadUint32Register(SYSTEM_UNIT, system_unit);
}

bool MasterClient::SetSystemUnit(unsigned int system_unit) {
  return connected_ && handler_->WriteUint32Register(SYSTEM_UNIT, system_unit);
}

bool MasterClient::GetSystemLanguage(unsigned int &system_language) {
  return connected_ && handler_->ReadUint32Register(SYSTEM_LANGUAGE, system_language);
}

bool MasterClient::SetSystemLanguage(unsigned int system_language) {
  return connected_ && handler_->WriteUint32Register(SYSTEM_LANGUAGE, system_language);
}

bool MasterClient::GetModbusBaud(unsigned int &modbus_baud) {
  return connected_ && handler_->ReadUint32Register(MODBUS_BAUD, modbus_baud);
}

bool MasterClient::SetModbusBaud(unsigned int modbus_baud) {
  return connected_ && handler_->WriteUint32Register(MODBUS_BAUD, modbus_baud);
}

bool MasterClient::GetModbusSlaveID(unsigned int &modbus_slave_id) {
  return connected_ && handler_->ReadUint32Register(MODBUS_SLAVE_ID, modbus_slave_id);
}

bool MasterClient::SetModbusSlaveID(unsigned int modbus_slave_id) {
  return connected_ && handler_->WriteUint32Register(MODBUS_SLAVE_ID, modbus_slave_id);
}

bool MasterClient::GetModbusParity(unsigned int &modbus_parity) {
  return connected_ && handler_->ReadUint32Register(MODBUS_PARITY, modbus_parity);
}

bool MasterClient::SetModbusParity(unsigned int modbus_parity) {
  return connected_ && handler_->WriteUint32Register(MODBUS_PARITY, modbus_parity);
}

bool MasterClient::GetBootHomeEnable(unsigned int &boot_home_enable) {
  return connected_ && handler_->ReadUint32Register(BOOT_HOME_ENABLE, boot_home_enable);
}

bool MasterClient::SetBootHomeEnable(unsigned int boot_home_enable) {
  return connected_ && handler_->WriteUint32Register(BOOT_HOME_ENABLE, boot_home_enable);
}

bool MasterClient::GetArcVolRateOfChangeCheck(unsigned int &arc_vol_rate_of_change_check) {
  return connected_ && handler_->ReadUint32Register(AV_RATE_OF_CHANGE_CHECK, arc_vol_rate_of_change_check);
}

bool MasterClient::SetArcVolRateOfChangeCheck(unsigned int arc_vol_rate_of_change_check) {
  return connected_ && handler_->WriteUint32Register(AV_RATE_OF_CHANGE_CHECK, arc_vol_rate_of_change_check);
}

bool MasterClient::GetDebugMode(unsigned int &debug_mode) {
  return connected_ && handler_->ReadUint32Register(DEBUG_MODE,
      debug_mode);

}

bool MasterClient::SetDebugMode(unsigned int debug_mode) {
  return connected_ && handler_->WriteUint32Register(DEBUG_MODE,
      debug_mode);

}

bool MasterClient::GetArcVolCorrectFactor(float &arc_vol_correct_factor) {
  return connected_ && handler_->ReadFloatRegister(AV_CORRECT_FACTOR,
      arc_vol_correct_factor);

}

bool MasterClient::SetArcVolCorrectFactor(float arc_vol_correct_factor) {
  return connected_ && handler_->WriteFloatRegister(AV_CORRECT_FACTOR,
      arc_vol_correct_factor);

}

bool MasterClient::GetArcVolCorrectBase(float &arc_vol_correct_base) {
  return connected_ && handler_->ReadFloatRegister(AV_CORRECT_BASE,
      arc_vol_correct_base);

}

bool MasterClient::SetArcVolCorrectBase(float arc_vol_correct_base) {
  return connected_ && handler_->WriteFloatRegister(AV_CORRECT_BASE,
      arc_vol_correct_base);

}

bool MasterClient::GetArcOkCheckMode(unsigned int &arc_ok_check_mode) {
  return connected_ && handler_->ReadUint32Register(ARC_OK_CHECK_MODE,
      arc_ok_check_mode);

}

bool MasterClient::SetArcOkCheckMode(unsigned int arc_ok_check_mode) {
  return connected_ && handler_->WriteUint32Register(ARC_OK_CHECK_MODE,
      arc_ok_check_mode);

}

bool MasterClient::GetScaleFactor(float &scale_factor) {
  return connected_ && handler_->ReadFloatRegister(SCALE_FACTOR,
      scale_factor);

}

bool MasterClient::SetScaleFactor(float scale_factor) {
  return connected_ && handler_->WriteFloatRegister(SCALE_FACTOR,
      scale_factor);

}

bool MasterClient::GetIntegralCoefficient(float &integral_coefficient) {
  return connected_ && handler_->ReadFloatRegister(INTEGRAL_COEFFICIENT,
      integral_coefficient);

}

bool MasterClient::SetIntegralCoefficient(float integral_coefficient) {
  return connected_ && handler_->WriteFloatRegister(INTEGRAL_COEFFICIENT,
      integral_coefficient);

}

bool MasterClient::GetDifferentialCoefficient(float &differential_coefficient) {
  return connected_ && handler_->ReadFloatRegister(DIFFERENTIAL_COEFFICIENT,
      differential_coefficient);

}

bool MasterClient::SetDifferentialCoefficient(float differential_coefficient) {
  return connected_ && handler_->WriteFloatRegister(DIFFERENTIAL_COEFFICIENT,
      differential_coefficient);

}

bool MasterClient::GetRegulateCycle(unsigned int &regulate_cycle) {
  return connected_ && handler_->ReadUint32Register(REGULATE_CYCLE,
      regulate_cycle);

}

bool MasterClient::SetRegulateCycle(unsigned int regulate_cycle) {
  return connected_ && handler_->WriteUint32Register(REGULATE_CYCLE,
      regulate_cycle);

}

bool MasterClient::GetVariableScaleFactor(float &variable_scale_factor) {
  return connected_ && handler_->ReadFloatRegister(VARIABLE_SCALE_FACTOR,
      variable_scale_factor);

}

bool MasterClient::SetVariableScaleFactor(float variable_scale_factor) {
  return connected_ && handler_->WriteFloatRegister(VARIABLE_SCALE_FACTOR,
      variable_scale_factor);

}

bool MasterClient::GetMaximumSensitivity(float &maximum_sensitivity) {
  return connected_ && handler_->ReadFloatRegister(MAXIMUM_SENSITIVITY,
      maximum_sensitivity);

}

bool MasterClient::SetMaximumSensitivity(float maximum_sensitivity) {
  return connected_ && handler_->WriteFloatRegister(MAXIMUM_SENSITIVITY,
      maximum_sensitivity);

}

bool MasterClient::GetPIDOutputDeadZoneRange(float &pid_output_dead_zone_range) {
  return connected_ && handler_->ReadFloatRegister(PID_OUTPUT_DEAD_ZONE_RANGE,
      pid_output_dead_zone_range);

}

bool MasterClient::SetPIDOutputDeadZoneRange(float pid_output_dead_zone_range) {
  return connected_ && handler_->WriteFloatRegister(PID_OUTPUT_DEAD_ZONE_RANGE,
      pid_output_dead_zone_range);
}

bool MasterClient::GetArcVolAdjustAccuracy(float &arc_vol_adjust_accuracy) {
  return connected_ && handler_->ReadFloatRegister(ARC_VOL_ADJUST_ACCURACY,
      arc_vol_adjust_accuracy);

}

bool MasterClient::SetArcVolAdjustAccuracy(float arc_vol_adjust_accuracy) {
  return connected_ && handler_->WriteFloatRegister(ARC_VOL_ADJUST_ACCURACY,
      arc_vol_adjust_accuracy);

}

bool MasterClient::GetCollisionSignalFilterTime(float &collision_signal_filter_time) {
  return connected_ && handler_->ReadFloatRegister(COLLISION_SIGNAL_FILTER_TIME,
      collision_signal_filter_time);

}

bool MasterClient::SetCollisionSignalFilterTime(float collision_signal_filter_time) {
  return connected_ && handler_->WriteFloatRegister(COLLISION_SIGNAL_FILTER_TIME,
      collision_signal_filter_time);

}

bool MasterClient::GetOutputFunc(unsigned int &func, unsigned short io_num) {
  return connected_ && handler_->ReadUint32Register(
      OUTPUT_FUNC_BASE + io_num * 8, func);

}

bool MasterClient::SetOutputFunc(unsigned int func, unsigned short io_num) {
  return connected_ && handler_->WriteUint32Register(
      OUTPUT_FUNC_BASE + io_num * 8 , func);

}

bool MasterClient::GetOutputType(unsigned int &type, unsigned short io_num) {
  return connected_ && handler_->ReadUint32Register(
      OUTPUT_NONC_BASE + io_num * 8, type);

}

bool MasterClient::SetOutputType(unsigned int type, unsigned short io_num) {
  return connected_ && handler_->WriteUint32Register(
      OUTPUT_NONC_BASE + io_num * 8 , type);

}

bool MasterClient::GetOutputPort(unsigned int &port, unsigned short io_num) {
  return connected_ && handler_->ReadUint32Register(
      OUTPUT_PORT_BASE + io_num * 8, port);

}

bool MasterClient::SetOutputPort(unsigned int port, unsigned short io_num) {
  return connected_ && handler_->WriteUint32Register(
      OUTPUT_PORT_BASE + io_num * 8 , port);

}

bool MasterClient::GetOutputPortSN(unsigned int &sn, unsigned short io_num) {
  return connected_ && handler_->ReadUint32Register(
      OUTPUT_PORT_SN_BASE + io_num * 8, sn);

}

bool MasterClient::SetOutputPortSN(unsigned int sn, unsigned short io_num) {
  return connected_ && handler_->WriteUint32Register(
      OUTPUT_PORT_SN_BASE + io_num * 8 , sn);

}

bool MasterClient::GetInputFunc(unsigned int &func, unsigned short io_num) {
  return connected_ && handler_->ReadUint32Register(
      INPUT_FUNC_BASE + io_num * 8, func);

}

bool MasterClient::SetInputFunc(unsigned int func, unsigned short io_num) {
  return connected_ && handler_->WriteUint32Register(
      INPUT_FUNC_BASE + io_num * 8 , func);

}

bool MasterClient::GetInputType(unsigned int &type, unsigned short io_num) {
  return connected_ && handler_->ReadUint32Register(
      INPUT_NONC_BASE + io_num * 8, type);

}

bool MasterClient::SetInputType(unsigned int type, unsigned short io_num) {
  return connected_ && handler_->WriteUint32Register(
      INPUT_NONC_BASE + io_num * 8 , type);

}

bool MasterClient::GetInputPort(unsigned int &port, unsigned short io_num) {
  return connected_ && handler_->ReadUint32Register(
      INPUT_PORT_BASE + io_num * 8, port);

}

bool MasterClient::SetInputPort(unsigned int port, unsigned short io_num) {
  return connected_ && handler_->WriteUint32Register(
      INPUT_PORT_BASE + io_num * 8 , port);

}

bool MasterClient::GetInputPortSN(unsigned int &sn, unsigned short io_num) {
  return connected_ && handler_->ReadUint32Register(
      INPUT_PORT_SN_BASE + io_num * 8, sn);

}

bool MasterClient::SetInputPortSN(unsigned int sn, unsigned short io_num){
  return connected_ && handler_->WriteUint32Register(
      INPUT_PORT_SN_BASE + io_num * 8 , sn);

}

bool MasterClient::GetConnectFlag(unsigned int &connect_flag) {
  return connected_ && handler_->ReadUint32Register(
      CONNECT_FLAG, connect_flag);

}

bool MasterClient::SetConnectFlag(unsigned int connect_flag) {
  return connected_ && handler_->WriteUint32Register(
      CONNECT_FLAG, connect_flag);

}

bool MasterClient::GetConnectTimeOut(unsigned int &connect_time_out) {
  return connected_ && handler_->ReadUint32Register(
      CONNECT_TIME_OUT, connect_time_out);

}

bool MasterClient::SetConnectTimeOut(unsigned int connect_time_out) {
  return connected_ && handler_->WriteUint32Register(
      CONNECT_TIME_OUT, connect_time_out);

}

bool MasterClient::SetMasterModel(unsigned int master_model) {
  return connected_ && handler_->WriteUint32Register(
      MASTER_MODEL, master_model);

}

bool MasterClient::GetMasterHardwareVersion(unsigned int &master_hardware_version) {
  return connected_ && handler_->ReadUint32Register(
      MASTER_HARDWARE_VERSION, master_hardware_version);

}

bool MasterClient::SetMasterHardwareVersion(unsigned int master_hardware_version) {
  return connected_ && handler_->WriteUint32Register(
      MASTER_HARDWARE_VERSION, master_hardware_version);

}

bool MasterClient::GetMasterSoftwareVersion(unsigned int &master_software_version) {
  return connected_ && handler_->ReadUint32Register(
      MASTER_SOFTWARE_VERSION, master_software_version);

}

bool MasterClient::SetMasterSoftwareVersion(unsigned int master_software_version) {
  return connected_ && handler_->WriteUint32Register(
      MASTER_SOFTWARE_VERSION, master_software_version);

}

bool MasterClient::SetMasterVersionVerify(unsigned int master_version_verify) {
  return connected_ && handler_->WriteUint32Register(
      MASTER_VERSION_VERIFY, master_version_verify);

}

bool MasterClient::GetSlaveModel(unsigned int &slave_model) {
  return connected_ && handler_->ReadUint32Register(
      SLAVE_MODEL, slave_model);

}

bool MasterClient::GetSlaveHardwareVersion(unsigned int &slave_hardware_version) {
  return connected_ && handler_->ReadUint32Register(
      SLAVE_HARDWARE_VERSION, slave_hardware_version);

}

bool MasterClient::SetSlaveHardwareVersion(unsigned int slave_hardware_version) {
  return connected_ && handler_->WriteUint32Register(
      SLAVE_HARDWARE_VERSION, slave_hardware_version);

}

bool MasterClient::GetSlaveSoftwareVersion(unsigned int &slave_software_version) {
  return connected_ && handler_->ReadUint32Register(
      SLAVE_SOFTWARE_VERSION, slave_software_version);

}

bool MasterClient::SetSlaveSoftwareVersion(unsigned int slave_software_version) {
  return connected_ && handler_->WriteUint32Register(
      SLAVE_SOFTWARE_VERSION, slave_software_version);

}

bool MasterClient::GetSlaveVersionVerify(unsigned int &slave_version_verify) {
  return connected_ && handler_->ReadUint32Register(
      SLAVE_VERSION_VERIFY, slave_version_verify);

}

bool MasterClient::GetInputPortStatus(unsigned int &status) {
  return connected_ && handler_->ReadUint32InputRegister(
      INPUT_PORT_STATUS, status);

}

bool MasterClient::GetOutputPortStatus(unsigned int &status) {
  return connected_ && handler_->ReadUint32InputRegister(
      OUTPUT_PORT_STATUS, status);

}

bool MasterClient::GetCurStatus(unsigned int &status) {
  return connected_ && handler_->ReadUint32InputRegister(
      CURRENT_STATUS, status);

}

bool MasterClient::GetWarningStatus(unsigned int &status) {
  return connected_ && handler_->ReadUint32InputRegister(
      WARNING_STATUS, status);

}

bool MasterClient::GetCurArcVoltage(float &cur_arc_voltage) {
  return connected_ && handler_->ReadFloatInputRegister(
      CURRENT_ARC_VOLTAGE, cur_arc_voltage);

}

bool MasterClient::GetCurPosition(double &cur_position) {
  return connected_ && handler_->ReadDoubleInputRegister(
      CURRENT_POSITION, cur_position);

}

bool MasterClient::GetCurSpeed(double &cur_speed) {
  return connected_ && handler_->ReadDoubleInputRegister(
      CURRENT_SPEED, cur_speed);

}

bool MasterClient::GetSteelPlateHeight(double &steel_plate_height) {
  return connected_ && handler_->ReadDoubleInputRegister(
      STEEL_PLATE_HEIGHT, steel_plate_height);

}

bool MasterClient::ConnectTest() {
  static unsigned int connect_count = 0;
  connect_count++;
  return connected_ && handler_->WriteUint32Register(CONNECT_TEST, connect_count);
}

bool MasterClient::SlaveVersionVerify() {
  unsigned int slave_model;
  unsigned int slave_hardware_version;
  unsigned int slave_software_version;
  unsigned int slave_version_verify;
  return GetSlaveModel(slave_model) &&
      GetSlaveHardwareVersion(slave_hardware_version) &&
      GetSlaveSoftwareVersion(slave_software_version) &&
      GetSlaveVersionVerify(slave_version_verify) &&
      slave_version_verify == slave_model + slave_hardware_version + slave_software_version;

}
