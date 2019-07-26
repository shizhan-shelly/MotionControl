// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "MotionControl/Controller/thc/THCClient.h"

#include <assert.h>

#include "MotionControl/Communication/Modbus/ClientHandler.h"
#include "MotionControl/Communication/Modbus/ClientHandlerManager.h"
#include "MotionControl/Communication/Modbus/ModbusMappingDef.h"

THCClient::THCClient() : Runnable()
                       , handler_manager_(NULL) {}

THCClient::~THCClient() {}

void THCClient::SetClientHandlerManager(ClientHandlerManager *handler_manager) {
  assert(handler_manager);
  handler_manager_ = handler_manager;
}

void THCClient::Run() {
  if (!SetupConnect()) {
    return ;
  }
  ConnectTest();
}

bool THCClient::SetupConnect() {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  if (!handler->Connect()) {
    return false;
  }
  return SlaveVersionVerify();
}

bool THCClient::DirectlyArc(bool status) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteSingleCoil(DIRECTLY_ARC, status);
}

bool THCClient::PositionArc(bool status) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteSingleCoil(POSITION_ARC, status);
}

bool THCClient::AutoTHC(bool status) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteSingleCoil(AUTO_THC, status);
}

bool THCClient::TorchUp(bool status) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteSingleCoil(TORCH_UP, status);
}

bool THCClient::TorchDown(bool status) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteSingleCoil(TORCH_DOWN, status);
}

bool THCClient::THCHome(bool status) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteSingleCoil(THC_HOME, status);
}

bool THCClient::PositionCheck(bool status) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteSingleCoil(POSITION_CHECK, status);
}

bool THCClient::ArcOnCheck(bool status) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteSingleCoil(ARC_ON_CHECK, status);
}

bool THCClient::OutputCheck(bool status, unsigned short port_num) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteSingleCoil(OUTPUT_CHECK + port_num,
      status);

}

bool THCClient::GetArcVoltageFeedback(bool &status) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadInputBit(ARC_VOLTAGE_FEEDBACK, status);
}

bool THCClient::GetCollisionAlarm(bool &status) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadInputBit(COLLISION_ALARM, status);
}

bool THCClient::GetPierceFinish(bool &status) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadInputBit(PIERCE_FINISH, status);
}

bool THCClient::GetServoTHCMode(unsigned int &thc_mode) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadUint32Register(SERVO_THC_MODE, thc_mode);
}

bool THCClient::SetServoTHCMode(unsigned int thc_mode) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteUint32Register(SERVO_THC_MODE, thc_mode);
}

bool THCClient::GetServoArcOnMode(unsigned int &arc_on_mode) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadUint32Register(SERVO_ARC_ON_MODE, arc_on_mode);
}

bool THCClient::SetServoArcOnMode(unsigned int arc_on_mode) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteUint32Register(SERVO_ARC_ON_MODE, arc_on_mode);
}

bool THCClient::GetServoPosHSDownDis(float &distance) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadFloatRegister(SERVO_POS_HS_DWN_DIS, distance);
}

bool THCClient::SetServoPosHSDownDis(float distance) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteFloatRegister(SERVO_POS_HS_DWN_DIS, distance);
}

bool THCClient::GetServoIgnitionHeight(float &ignition_height) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadFloatRegister(SERVO_IGNITION_HEIGHT, ignition_height);
}

bool THCClient::SetServoIgnitionHeight(float ignition_height) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteFloatRegister(SERVO_IGNITION_HEIGHT, ignition_height);
}

bool THCClient::GetServoPierceHeight(float &pierce_height) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadFloatRegister(SERVO_PIERCE_HEIGHT, pierce_height);
}

bool THCClient::SetServoPierceHeight(float pierce_height) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteFloatRegister(SERVO_PIERCE_HEIGHT, pierce_height);
}

bool THCClient::GetServoCutHeight(float &cut_height) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadFloatRegister(SERVO_CUT_HEIGHT, cut_height);
}

bool THCClient::SetServoCutHeight(float cut_height) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteFloatRegister(SERVO_CUT_HEIGHT, cut_height);
}

bool THCClient::GetServoTorchUpHeightAfterM08(float &height) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadFloatRegister(SERVO_M08_TORCH_UP_HEIGHT, height);
}

bool THCClient::SetServoTorchUpHeightAfterM08(float height) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteFloatRegister(SERVO_M08_TORCH_UP_HEIGHT, height);
}

bool THCClient::GetServoAccelerate(float &servo_acc) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadFloatRegister(SERVO_ACCELERATE, servo_acc);
}

bool THCClient::SetServoAccelerate(float servo_acc) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteFloatRegister(SERVO_ACCELERATE, servo_acc);
}

bool THCClient::GetServoPulse(float &servo_pulse) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadFloatRegister(SERVO_PULSE, servo_pulse);
}

bool THCClient::SetServoPulse(float servo_pulse) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteFloatRegister(SERVO_PULSE, servo_pulse);
}

bool THCClient::GetServoLimitSpeed(float &servo_limit_speed) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadFloatRegister(SERVO_LIMIT_SPEED, servo_limit_speed);
}

bool THCClient::SetServoLimitSpeed(float servo_limit_speed) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteFloatRegister(SERVO_LIMIT_SPEED, servo_limit_speed);
}

bool THCClient::GetServoForbidTHC(unsigned int &forbid_thc) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadUint32Register(SERVO_FORBID_THC, forbid_thc);
}

bool THCClient::SetServoForbidTHC(unsigned int forbid_thc) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteUint32Register(SERVO_FORBID_THC, forbid_thc);
}

bool THCClient::GetServoSoftLimitEnable(unsigned int &soft_limit_enable) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadUint32Register(SERVO_SOFT_LIMIT_ENABLE, soft_limit_enable);
}

bool THCClient::SetServoSoftLimitEnable(unsigned int soft_limit_enable) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteUint32Register(SERVO_SOFT_LIMIT_ENABLE, soft_limit_enable);
}

bool THCClient::GetServoSoftLimitNegative(float &soft_limit_negative) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadFloatRegister(SERVO_SOFT_LIMIT_NEGATIVE, soft_limit_negative);
}

bool THCClient::SetServoSoftLimitNegative(float soft_limit_negative) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteFloatRegister(SERVO_SOFT_LIMIT_NEGATIVE, soft_limit_negative);
}

bool THCClient::GetDCPosHSDownTime(float &time) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadFloatRegister(DC_POS_HS_DWN_TIME, time);
}

bool THCClient::SetDCPosHSDownTime(float time) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteFloatRegister(DC_POS_HS_DWN_TIME, time);
}

bool THCClient::GetDCPositionUpTime(float &time) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadFloatRegister(DC_POSITION_UP_TIME, time);
}

bool THCClient::SetDCPositionUpTime(float time) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteFloatRegister(DC_POSITION_UP_TIME, time);
}

bool THCClient::GetDCPierceUpTime(float &time) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadFloatRegister(DC_PIERCE_UP_TIME, time);
}

bool THCClient::SetDCPierceUpTime(float time) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteFloatRegister(DC_PIERCE_UP_TIME, time);
}

bool THCClient::GetDCPierceDownTime(float &time) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadFloatRegister(DC_PIERCE_DOWN_TIME, time);
}

bool THCClient::SetDCPierceDownTime(float time) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteFloatRegister(DC_PIERCE_DOWN_TIME, time);
}

bool THCClient::GetDCRegualteSpeedTime(float &time) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadFloatRegister(DC_REGULATE_SPEED_TIME, time);
}

bool THCClient::SetDCRegualteSpeedTime(float time) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteFloatRegister(DC_REGULATE_SPEED_TIME, time);
}

bool THCClient::GetTHCMotor(unsigned int &thc_motor) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadUint32Register(THC_MOTOR, thc_motor);
}

bool THCClient::SetTHCMotor(unsigned int thc_motor) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteUint32Register(THC_MOTOR, thc_motor);
}

bool THCClient::GetPositionCheckDelay(float &pos_check_delay,
                                         unsigned int thc_motor) {

  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadFloatRegister(
      thc_motor == 0 ? SERVO_POS_CHECK_DELAY : DC_POS_CHECK_DELAY,
      pos_check_delay);

}

bool THCClient::SetPositionCheckDelay(float pos_check_delay,
                                         unsigned int thc_motor) {

  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteFloatRegister(
      thc_motor == 0 ? SERVO_POS_CHECK_DELAY : DC_POS_CHECK_DELAY,
      pos_check_delay);

}

bool THCClient::GetPierceTime(float &pierce_time,
                                 unsigned int thc_motor) {

  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadFloatRegister(
      thc_motor == 0 ? SERVO_PIERCE_TIME : DC_PIERCE_TIME,
      pierce_time);

}

bool THCClient::SetPierceTime(float pierce_time,
                                 unsigned int thc_motor) {

  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteFloatRegister(
      thc_motor == 0 ? SERVO_PIERCE_TIME : DC_PIERCE_TIME,
      pierce_time);

}

bool THCClient::GetCloseTHCTimeAfterM07(float &close_thc_time,
                                           unsigned int thc_motor) {

  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadFloatRegister(
      thc_motor == 0 ? SERVO_CLOSE_THC_TIME_AFTER_M07 : DC_CLOSE_THC_TIME_AFTER_M07,
      close_thc_time);

}

bool THCClient::SetCloseTHCTimeAfterM07(float close_thc_time,
                                           unsigned int thc_motor) {

  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteFloatRegister(
      thc_motor == 0 ? SERVO_CLOSE_THC_TIME_AFTER_M07 : DC_CLOSE_THC_TIME_AFTER_M07,
      close_thc_time);

}

bool THCClient::GetSensitivity(float &sensitivity,
                                  unsigned int thc_motor) {

  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadFloatRegister(
      thc_motor == 0 ? SERVO_SENSITIVITY : DC_SENSITIVITY,
      sensitivity);

}

bool THCClient::SetSensitivity(float sensitivity,
                                  unsigned int thc_motor) {

  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteFloatRegister(
      thc_motor == 0 ? SERVO_SENSITIVITY : DC_SENSITIVITY,
      sensitivity);

}

bool THCClient::GetMotorDirectionSwitch(unsigned int &motor_dir_switch,
                                           unsigned int thc_motor) {

  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadUint32Register(
      thc_motor == 0 ? SERVO_MOTOR_DIR_SWITCH : DC_MOTOR_DIR_SWITCH,
      motor_dir_switch);

}

bool THCClient::SetMotorDirectionSwitch(unsigned int motor_dir_switch,
                                           unsigned int thc_motor) {

  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteUint32Register(
      thc_motor == 0 ? SERVO_MOTOR_DIR_SWITCH : DC_MOTOR_DIR_SWITCH,
      motor_dir_switch);

}

bool THCClient::GetArcOnCheckTime(float &arc_on_check_time,
                                     unsigned int thc_motor) {

  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadFloatRegister(
      thc_motor == 0 ? SERVO_ARC_ON_CHECK_TIME : DC_ARC_ON_CHECK_TIME,
      arc_on_check_time);

}

bool THCClient::SetArcOnCheckTime(float arc_on_check_time,
                                     unsigned int thc_motor) {

  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteFloatRegister(
      thc_motor == 0 ? SERVO_ARC_ON_CHECK_TIME : DC_ARC_ON_CHECK_TIME,
      arc_on_check_time);

}

bool THCClient::GetTorchUpDelayAfterM08(float &delay,
                                           unsigned int thc_motor) {

  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadFloatRegister(
      thc_motor == 0 ? SERVO_M08_TORCH_UP_DELAY : DC_M08_TORCH_UP_DELAY,
      delay);

}

bool THCClient::SetTorchUpDelayAfterM08(float delay,
                                           unsigned int thc_motor) {

  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteFloatRegister(
      thc_motor == 0 ? SERVO_M08_TORCH_UP_DELAY : DC_M08_TORCH_UP_DELAY,
      delay);

}

bool THCClient::GetCollisionCount(unsigned int &collision_count,
                                     unsigned int thc_motor) {

  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadUint32Register(
      thc_motor == 0 ? SERVO_COLLISION_COUNT : DC_COLLISION_COUNT,
      collision_count);

}

bool THCClient::SetCollisionCount(unsigned int collision_count,
                                     unsigned int thc_motor) {

  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteUint32Register(
      thc_motor == 0 ? SERVO_COLLISION_COUNT : DC_COLLISION_COUNT,
      collision_count);

}

bool THCClient::GetPresetArcVoltage(float &arc_voltage,
                                       unsigned int thc_motor) {

  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadFloatRegister(
      thc_motor == 0 ? SERVO_PRESET_ARC_VOLTAGE : DC_PRESET_ARC_VOLTAGE,
      arc_voltage);

}

bool THCClient::SetPresetArcVoltage(float arc_voltage,
                                       unsigned int thc_motor) {

  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteFloatRegister(
      thc_motor == 0 ? SERVO_PRESET_ARC_VOLTAGE : DC_PRESET_ARC_VOLTAGE,
      arc_voltage);

}

bool THCClient::GetOverArcVolProtectValue(float &protect_value,
                                             unsigned int thc_motor) {

  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadFloatRegister(thc_motor == 0
      ? SERVO_OVER_ARC_VOL_PROTECT_VALUE : DC_OVER_ARC_VOL_PROTECT_VALUE,
      protect_value);

}

bool THCClient::SetOverArcVolProtectValue(float protect_value,
                                             unsigned int thc_motor) {

  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteFloatRegister(thc_motor == 0
      ? SERVO_OVER_ARC_VOL_PROTECT_VALUE : DC_OVER_ARC_VOL_PROTECT_VALUE,
      protect_value);

}

bool THCClient::GetOverKerfArcVolThreshold(float &threshold,
                                              unsigned int thc_motor) {

  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadFloatRegister(thc_motor == 0
      ? SERVO_OVER_KERF_ARC_VOL_THRESHOLD : DC_OVER_KERF_ARC_VOL_THRESHOLD,
      threshold);

}

bool THCClient::SetOverKerfArcVolThreshold(float threshold,
                                              unsigned int thc_motor) {

  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteFloatRegister(thc_motor == 0
      ? SERVO_OVER_KERF_ARC_VOL_THRESHOLD : DC_OVER_KERF_ARC_VOL_THRESHOLD,
      threshold);

}

bool THCClient::GetAutoSpeed(float &auto_speed,
                                unsigned int thc_motor) {

  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadFloatRegister(
      thc_motor == 0 ? SERVO_AUTO_SPEED : DC_AUTO_SPEED,
      auto_speed);

}

bool THCClient::SetAutoSpeed(float auto_speed,
                                unsigned int thc_motor) {

  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteFloatRegister(
      thc_motor == 0 ? SERVO_AUTO_SPEED : DC_AUTO_SPEED,
      auto_speed);

}

bool THCClient::GetPositionLowSpeed(float &pos_ls_speed,
                                       unsigned int thc_motor) {

  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadFloatRegister(
      thc_motor == 0 ? SERVO_POS_LS_SPEED : DC_POS_LS_SPEED,
      pos_ls_speed);

}

bool THCClient::SetPositionLowSpeed(float pos_ls_speed,
                                       unsigned int thc_motor) {

  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteFloatRegister(
      thc_motor == 0 ? SERVO_POS_LS_SPEED : DC_POS_LS_SPEED,
      pos_ls_speed);

}

bool THCClient::GetManualSpeed(float &manual_speed,
                                  unsigned int thc_motor) {

  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadFloatRegister(
      thc_motor == 0 ? SERVO_MANUAL_SPEED : DC_MANUAL_SPEED,
      manual_speed);

}

bool THCClient::SetManualSpeed(float manual_speed,
                                  unsigned int thc_motor) {

  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteFloatRegister(
      thc_motor == 0 ? SERVO_MANUAL_SPEED : DC_MANUAL_SPEED,
      manual_speed);

}

bool THCClient::GetSystemUnit(unsigned int &system_unit) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadUint32Register(SYSTEM_UNIT, system_unit);
}

bool THCClient::SetSystemUnit(unsigned int system_unit) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteUint32Register(SYSTEM_UNIT, system_unit);
}

bool THCClient::GetSystemLanguage(unsigned int &system_language) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadUint32Register(SYSTEM_LANGUAGE, system_language);
}

bool THCClient::SetSystemLanguage(unsigned int system_language) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteUint32Register(SYSTEM_LANGUAGE, system_language);
}

bool THCClient::GetModbusBaud(unsigned int &modbus_baud) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadUint32Register(MODBUS_BAUD, modbus_baud);
}

bool THCClient::SetModbusBaud(unsigned int modbus_baud) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteUint32Register(MODBUS_BAUD, modbus_baud);
}

bool THCClient::GetModbusSlaveID(unsigned int &modbus_slave_id) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadUint32Register(MODBUS_SLAVE_ID, modbus_slave_id);
}

bool THCClient::SetModbusSlaveID(unsigned int modbus_slave_id) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteUint32Register(MODBUS_SLAVE_ID, modbus_slave_id);
}

bool THCClient::GetModbusParity(unsigned int &modbus_parity) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadUint32Register(MODBUS_PARITY, modbus_parity);
}

bool THCClient::SetModbusParity(unsigned int modbus_parity) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteUint32Register(MODBUS_PARITY, modbus_parity);
}

bool THCClient::GetBootHomeEnable(unsigned int &boot_home_enable) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadUint32Register(BOOT_HOME_ENABLE, boot_home_enable);
}

bool THCClient::SetBootHomeEnable(unsigned int boot_home_enable) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteUint32Register(BOOT_HOME_ENABLE, boot_home_enable);
}

bool THCClient::GetArcVolRateOfChangeCheck(unsigned int &arc_vol_rate_of_change_check) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadUint32Register(AV_RATE_OF_CHANGE_CHECK, arc_vol_rate_of_change_check);
}

bool THCClient::SetArcVolRateOfChangeCheck(unsigned int arc_vol_rate_of_change_check) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteUint32Register(AV_RATE_OF_CHANGE_CHECK, arc_vol_rate_of_change_check);
}

bool THCClient::GetDebugMode(unsigned int &debug_mode) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadUint32Register(DEBUG_MODE,
      debug_mode);

}

bool THCClient::SetDebugMode(unsigned int debug_mode) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteUint32Register(DEBUG_MODE,
      debug_mode);

}

bool THCClient::GetArcVolCorrectFactor(float &arc_vol_correct_factor) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadFloatRegister(AV_CORRECT_FACTOR,
      arc_vol_correct_factor);

}

bool THCClient::SetArcVolCorrectFactor(float arc_vol_correct_factor) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteFloatRegister(AV_CORRECT_FACTOR,
      arc_vol_correct_factor);

}

bool THCClient::GetArcVolCorrectBase(float &arc_vol_correct_base) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadFloatRegister(AV_CORRECT_BASE,
      arc_vol_correct_base);

}

bool THCClient::SetArcVolCorrectBase(float arc_vol_correct_base) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteFloatRegister(AV_CORRECT_BASE,
      arc_vol_correct_base);

}

bool THCClient::GetArcOkCheckMode(unsigned int &arc_ok_check_mode) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadUint32Register(ARC_OK_CHECK_MODE,
      arc_ok_check_mode);

}

bool THCClient::SetArcOkCheckMode(unsigned int arc_ok_check_mode) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteUint32Register(ARC_OK_CHECK_MODE,
      arc_ok_check_mode);

}

bool THCClient::GetScaleFactor(float &scale_factor) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadFloatRegister(SCALE_FACTOR,
      scale_factor);

}

bool THCClient::SetScaleFactor(float scale_factor) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteFloatRegister(SCALE_FACTOR,
      scale_factor);

}

bool THCClient::GetIntegralCoefficient(float &integral_coefficient) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadFloatRegister(INTEGRAL_COEFFICIENT,
      integral_coefficient);

}

bool THCClient::SetIntegralCoefficient(float integral_coefficient) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteFloatRegister(INTEGRAL_COEFFICIENT,
      integral_coefficient);

}

bool THCClient::GetDifferentialCoefficient(float &differential_coefficient) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadFloatRegister(DIFFERENTIAL_COEFFICIENT,
      differential_coefficient);

}

bool THCClient::SetDifferentialCoefficient(float differential_coefficient) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteFloatRegister(DIFFERENTIAL_COEFFICIENT,
      differential_coefficient);

}

bool THCClient::GetRegulateCycle(unsigned int &regulate_cycle) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadUint32Register(REGULATE_CYCLE,
      regulate_cycle);

}

bool THCClient::SetRegulateCycle(unsigned int regulate_cycle) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteUint32Register(REGULATE_CYCLE,
      regulate_cycle);

}

bool THCClient::GetVariableScaleFactor(float &variable_scale_factor) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadFloatRegister(VARIABLE_SCALE_FACTOR,
      variable_scale_factor);

}

bool THCClient::SetVariableScaleFactor(float variable_scale_factor) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteFloatRegister(VARIABLE_SCALE_FACTOR,
      variable_scale_factor);

}

bool THCClient::GetMaximumSensitivity(float &maximum_sensitivity) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadFloatRegister(MAXIMUM_SENSITIVITY,
      maximum_sensitivity);

}

bool THCClient::SetMaximumSensitivity(float maximum_sensitivity) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteFloatRegister(MAXIMUM_SENSITIVITY,
      maximum_sensitivity);

}

bool THCClient::GetPIDOutputDeadZoneRange(float &pid_output_dead_zone_range) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadFloatRegister(PID_OUTPUT_DEAD_ZONE_RANGE,
      pid_output_dead_zone_range);

}

bool THCClient::SetPIDOutputDeadZoneRange(float pid_output_dead_zone_range) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteFloatRegister(PID_OUTPUT_DEAD_ZONE_RANGE,
      pid_output_dead_zone_range);
}

bool THCClient::GetArcVolAdjustAccuracy(float &arc_vol_adjust_accuracy) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadFloatRegister(ARC_VOL_ADJUST_ACCURACY,
      arc_vol_adjust_accuracy);

}

bool THCClient::SetArcVolAdjustAccuracy(float arc_vol_adjust_accuracy) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteFloatRegister(ARC_VOL_ADJUST_ACCURACY,
      arc_vol_adjust_accuracy);

}

bool THCClient::GetCollisionSignalFilterTime(float &collision_signal_filter_time) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadFloatRegister(COLLISION_SIGNAL_FILTER_TIME,
      collision_signal_filter_time);

}

bool THCClient::SetCollisionSignalFilterTime(float collision_signal_filter_time) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteFloatRegister(COLLISION_SIGNAL_FILTER_TIME,
      collision_signal_filter_time);

}

bool THCClient::GetOutputFunc(unsigned int &func, unsigned short io_num) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadUint32Register(
      OUTPUT_FUNC_BASE + io_num * 8, func);

}

bool THCClient::SetOutputFunc(unsigned int func, unsigned short io_num) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteUint32Register(
      OUTPUT_FUNC_BASE + io_num * 8 , func);

}

bool THCClient::GetOutputType(unsigned int &type, unsigned short io_num) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadUint32Register(
      OUTPUT_NONC_BASE + io_num * 8, type);

}

bool THCClient::SetOutputType(unsigned int type, unsigned short io_num) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteUint32Register(
      OUTPUT_NONC_BASE + io_num * 8 , type);

}

bool THCClient::GetOutputPort(unsigned int &port, unsigned short io_num) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadUint32Register(
      OUTPUT_PORT_BASE + io_num * 8, port);

}

bool THCClient::SetOutputPort(unsigned int port, unsigned short io_num) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteUint32Register(
      OUTPUT_PORT_BASE + io_num * 8 , port);

}

bool THCClient::GetOutputPortSN(unsigned int &sn, unsigned short io_num) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadUint32Register(
      OUTPUT_PORT_SN_BASE + io_num * 8, sn);

}

bool THCClient::SetOutputPortSN(unsigned int sn, unsigned short io_num) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteUint32Register(
      OUTPUT_PORT_SN_BASE + io_num * 8 , sn);

}

bool THCClient::GetInputFunc(unsigned int &func, unsigned short io_num) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadUint32Register(
      INPUT_FUNC_BASE + io_num * 8, func);

}

bool THCClient::SetInputFunc(unsigned int func, unsigned short io_num) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteUint32Register(
      INPUT_FUNC_BASE + io_num * 8 , func);

}

bool THCClient::GetInputType(unsigned int &type, unsigned short io_num) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadUint32Register(
      INPUT_NONC_BASE + io_num * 8, type);

}

bool THCClient::SetInputType(unsigned int type, unsigned short io_num) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteUint32Register(
      INPUT_NONC_BASE + io_num * 8 , type);

}

bool THCClient::GetInputPort(unsigned int &port, unsigned short io_num) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadUint32Register(
      INPUT_PORT_BASE + io_num * 8, port);

}

bool THCClient::SetInputPort(unsigned int port, unsigned short io_num) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteUint32Register(
      INPUT_PORT_BASE + io_num * 8 , port);

}

bool THCClient::GetInputPortSN(unsigned int &sn, unsigned short io_num) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadUint32Register(
      INPUT_PORT_SN_BASE + io_num * 8, sn);

}

bool THCClient::SetInputPortSN(unsigned int sn, unsigned short io_num) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteUint32Register(
      INPUT_PORT_SN_BASE + io_num * 8 , sn);

}

bool THCClient::GetConnectFlag(unsigned int &connect_flag) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadUint32Register(
      CONNECT_FLAG, connect_flag);

}

bool THCClient::SetConnectFlag(unsigned int connect_flag) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteUint32Register(
      CONNECT_FLAG, connect_flag);

}

bool THCClient::GetConnectTimeOut(unsigned int &connect_time_out) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadUint32Register(
      CONNECT_TIME_OUT, connect_time_out);

}

bool THCClient::SetConnectTimeOut(unsigned int connect_time_out) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteUint32Register(
      CONNECT_TIME_OUT, connect_time_out);

}

bool THCClient::SetMasterModel(unsigned int master_model) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteUint32Register(
      MASTER_MODEL, master_model);

}

bool THCClient::GetMasterHardwareVersion(unsigned int &master_hardware_version) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadUint32Register(
      MASTER_HARDWARE_VERSION, master_hardware_version);

}

bool THCClient::SetMasterHardwareVersion(unsigned int master_hardware_version) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteUint32Register(
      MASTER_HARDWARE_VERSION, master_hardware_version);

}

bool THCClient::GetMasterSoftwareVersion(unsigned int &master_software_version) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadUint32Register(
      MASTER_SOFTWARE_VERSION, master_software_version);

}

bool THCClient::SetMasterSoftwareVersion(unsigned int master_software_version) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteUint32Register(
      MASTER_SOFTWARE_VERSION, master_software_version);

}

bool THCClient::SetMasterVersionVerify(unsigned int master_version_verify) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteUint32Register(
      MASTER_VERSION_VERIFY, master_version_verify);

}

bool THCClient::GetSlaveModel(unsigned int &slave_model) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadUint32Register(
      SLAVE_MODEL, slave_model);

}

bool THCClient::GetSlaveHardwareVersion(unsigned int &slave_hardware_version) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadUint32Register(
      SLAVE_HARDWARE_VERSION, slave_hardware_version);

}

bool THCClient::SetSlaveHardwareVersion(unsigned int slave_hardware_version) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteUint32Register(
      SLAVE_HARDWARE_VERSION, slave_hardware_version);

}

bool THCClient::GetSlaveSoftwareVersion(unsigned int &slave_software_version) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadUint32Register(
      SLAVE_SOFTWARE_VERSION, slave_software_version);

}

bool THCClient::SetSlaveSoftwareVersion(unsigned int slave_software_version) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteUint32Register(
      SLAVE_SOFTWARE_VERSION, slave_software_version);

}

bool THCClient::GetSlaveVersionVerify(unsigned int &slave_version_verify) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadUint32Register(
      SLAVE_VERSION_VERIFY, slave_version_verify);

}

bool THCClient::GetInputPortStatus(unsigned int &status) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadUint32InputRegister(
      INPUT_PORT_STATUS, status);

}

bool THCClient::GetOutputPortStatus(unsigned int &status) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadUint32InputRegister(
      OUTPUT_PORT_STATUS, status);

}

bool THCClient::GetCurStatus(unsigned int &status) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadUint32InputRegister(
      CURRENT_STATUS, status);

}

bool THCClient::GetWarningStatus(unsigned int &status) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadUint32InputRegister(
      WARNING_STATUS, status);

}

bool THCClient::GetCurArcVoltage(float &cur_arc_voltage) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadFloatInputRegister(
      CURRENT_ARC_VOLTAGE, cur_arc_voltage);

}

bool THCClient::GetCurPosition(double &cur_position) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadDoubleInputRegister(
      CURRENT_POSITION, cur_position);

}

bool THCClient::GetCurSpeed(double &cur_speed) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadDoubleInputRegister(
      CURRENT_SPEED, cur_speed);

}

bool THCClient::GetSteelPlateHeight(double &steel_plate_height) {
  assert(handler_manager_);
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->ReadDoubleInputRegister(
      STEEL_PLATE_HEIGHT, steel_plate_height);

}

bool THCClient::ConnectTest() {
  assert(handler_manager_);
  static unsigned int connect_count = 0;
  connect_count++;
  ClientHandler *handler = handler_manager_->GetClientHandler(1);
  return handler->WriteUint32Register(CONNECT_TEST, connect_count);
}

bool THCClient::SlaveVersionVerify() {
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
