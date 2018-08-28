// Copyright 2018 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#ifndef MODBUS_MODBUSMAPPINGDEF_H__
#define MODBUS_MODBUSMAPPINGDEF_H__

// Modbus device: 0X
const unsigned short BITS_ADDRESS = 0x0;
const unsigned short BITS_NB = 0x64;

const unsigned short DIRECTLY_ARC   = BITS_ADDRESS + 1;
const unsigned short POSITION_ARC   = BITS_ADDRESS + 2;
const unsigned short AUTO_THC       = BITS_ADDRESS + 3;
const unsigned short TORCH_UP       = BITS_ADDRESS + 4;
const unsigned short TORCH_DOWN     = BITS_ADDRESS + 5;
const unsigned short THC_HOME       = BITS_ADDRESS + 6;
const unsigned short POSITION_CHECK = BITS_ADDRESS + 7;
const unsigned short ARC_ON_CHECK   = BITS_ADDRESS + 8;
// On or Off one output port. Addr: 9 ~ 12
const unsigned short OUTPUT_CHECK   = BITS_ADDRESS + 9;

// Modbus device: 1X
const unsigned short INPUT_BITS_ADDRESS = 0x0;
const unsigned short INPUT_BITS_NB = 0x64;

const unsigned short ARC_VOLTAGE_FEEDBACK = INPUT_BITS_ADDRESS + 1;
const unsigned short COLLISION_ALARM      = INPUT_BITS_ADDRESS + 2;
const unsigned short PIERCE_FINISH        = INPUT_BITS_ADDRESS + 3;

// Modbus device: 3X
const unsigned short INPUT_REGISTERS_ADDRESS = 0x0;
const unsigned short INPUT_REGISTERS_NB = 0x64;

const unsigned short EXCEPTION_STATUS        = INPUT_REGISTERS_ADDRESS + 10;
const unsigned short CURRENT_STATUS          = INPUT_REGISTERS_ADDRESS + 12;
const unsigned short WARNING_STATUS          = INPUT_REGISTERS_ADDRESS + 14;
const unsigned short CURRENT_ARC_VOLTAGE     = INPUT_REGISTERS_ADDRESS + 16;
const unsigned short INPUT_PORT_STATUS       = INPUT_REGISTERS_ADDRESS + 18;
const unsigned short OUTPUT_PORT_STATUS      = INPUT_REGISTERS_ADDRESS + 20;
const unsigned short CURRENT_SPEED           = INPUT_REGISTERS_ADDRESS + 22;
const unsigned short CURRENT_POSITION        = INPUT_REGISTERS_ADDRESS + 26;
const unsigned short STEEL_PLATE_HEIGHT      = INPUT_REGISTERS_ADDRESS + 30;

// Modbus device: 4X
const unsigned short REGISTERS_ADDRESS = 0x0;
const unsigned short REGISTERS_NB = 0x1F72;

const unsigned short CONNECT_TEST                      = REGISTERS_ADDRESS + 0;
const unsigned short SERVO_POS_CHECK_DELAY             = REGISTERS_ADDRESS + 50;
const unsigned short SERVO_POS_HS_DWN_DIS              = REGISTERS_ADDRESS + 52;
const unsigned short SERVO_IGNITION_HEIGHT             = REGISTERS_ADDRESS + 54;
const unsigned short SERVO_PIERCE_HEIGHT               = REGISTERS_ADDRESS + 56;
const unsigned short SERVO_PIERCE_TIME                 = REGISTERS_ADDRESS + 58;
const unsigned short SERVO_CLOSE_THC_TIME_AFTER_M07    = REGISTERS_ADDRESS + 60;
const unsigned short SERVO_CUT_HEIGHT                  = REGISTERS_ADDRESS + 62;
const unsigned short SERVO_PRESET_ARC_VOLTAGE          = REGISTERS_ADDRESS + 64;
const unsigned short SERVO_OVER_ARC_VOL_PROTECT_VALUE  = REGISTERS_ADDRESS + 66;
const unsigned short SERVO_OVER_KERF_ARC_VOL_THRESHOLD = REGISTERS_ADDRESS + 68;
const unsigned short SERVO_M08_TORCH_UP_HEIGHT         = REGISTERS_ADDRESS + 70;
const unsigned short SERVO_SENSITIVITY                 = REGISTERS_ADDRESS + 72;
const unsigned short SERVO_MANUAL_SPEED                = REGISTERS_ADDRESS + 74;
const unsigned short SERVO_POS_LS_SPEED                = REGISTERS_ADDRESS + 76;
const unsigned short SERVO_ACCELERATE                  = REGISTERS_ADDRESS + 78;
const unsigned short SERVO_PULSE                       = REGISTERS_ADDRESS + 80;
const unsigned short SERVO_THC_MODE                    = REGISTERS_ADDRESS + 82;
const unsigned short SERVO_LIMIT_SPEED                 = REGISTERS_ADDRESS + 84;
const unsigned short SERVO_MOTOR_DIR_SWITCH            = REGISTERS_ADDRESS + 86;
const unsigned short SERVO_ARC_ON_CHECK_TIME           = REGISTERS_ADDRESS + 88;
const unsigned short SERVO_COLLISION_COUNT             = REGISTERS_ADDRESS + 92;
const unsigned short SERVO_M08_TORCH_UP_DELAY          = REGISTERS_ADDRESS + 94;
const unsigned short SERVO_ARC_ON_MODE                 = REGISTERS_ADDRESS + 96;
const unsigned short SERVO_AUTO_SPEED                  = REGISTERS_ADDRESS + 98;
const unsigned short SERVO_FORBID_THC                  = REGISTERS_ADDRESS + 100;
const unsigned short SERVO_SOFT_LIMIT_ENABLE           = REGISTERS_ADDRESS + 120;
const unsigned short SERVO_SOFT_LIMIT_NEGATIVE         = REGISTERS_ADDRESS + 122;
const unsigned short DC_POS_CHECK_DELAY                = REGISTERS_ADDRESS + 200;
const unsigned short DC_POS_HS_DWN_TIME                = REGISTERS_ADDRESS + 202;
const unsigned short DC_POSITION_UP_TIME               = REGISTERS_ADDRESS + 204;
const unsigned short DC_PIERCE_TIME                    = REGISTERS_ADDRESS + 206;
const unsigned short DC_PIERCE_UP_TIME                 = REGISTERS_ADDRESS + 208;
const unsigned short DC_PIERCE_DOWN_TIME               = REGISTERS_ADDRESS + 210;
const unsigned short DC_CLOSE_THC_TIME_AFTER_M07       = REGISTERS_ADDRESS + 212;
const unsigned short DC_PRESET_ARC_VOLTAGE             = REGISTERS_ADDRESS + 214;
const unsigned short DC_OVER_ARC_VOL_PROTECT_VALUE     = REGISTERS_ADDRESS + 216;
const unsigned short DC_OVER_KERF_ARC_VOL_THRESHOLD    = REGISTERS_ADDRESS + 218;
const unsigned short DC_M08_TORCH_UP_DELAY             = REGISTERS_ADDRESS + 220;
const unsigned short DC_SENSITIVITY                    = REGISTERS_ADDRESS + 222;
const unsigned short DC_MANUAL_SPEED                   = REGISTERS_ADDRESS + 224;
const unsigned short DC_POS_LS_SPEED                   = REGISTERS_ADDRESS + 226;
const unsigned short DC_REGULATE_SPEED_TIME            = REGISTERS_ADDRESS + 228;
const unsigned short DC_MOTOR_DIR_SWITCH               = REGISTERS_ADDRESS + 232;
const unsigned short DC_ARC_ON_CHECK_TIME              = REGISTERS_ADDRESS + 234;
const unsigned short DC_COLLISION_COUNT                = REGISTERS_ADDRESS + 238;
const unsigned short DC_AUTO_SPEED                     = REGISTERS_ADDRESS + 240;
const unsigned short THC_MOTOR                         = REGISTERS_ADDRESS + 400;
const unsigned short SYSTEM_UNIT                       = REGISTERS_ADDRESS + 402;
const unsigned short SYSTEM_LANGUAGE                   = REGISTERS_ADDRESS + 404;
const unsigned short AV_CORRECT_FACTOR                 = REGISTERS_ADDRESS + 406;
const unsigned short MODBUS_BAUD                       = REGISTERS_ADDRESS + 408;
const unsigned short MODBUS_SLAVE_ID                   = REGISTERS_ADDRESS + 410;
const unsigned short MODBUS_PARITY                     = REGISTERS_ADDRESS + 412;
const unsigned short BOOT_HOME_ENABLE                  = REGISTERS_ADDRESS + 414;
const unsigned short AV_RATE_OF_CHANGE_CHECK           = REGISTERS_ADDRESS + 416;
const unsigned short DEBUG_MODE                        = REGISTERS_ADDRESS + 418;
const unsigned short AV_CORRECT_BASE                   = REGISTERS_ADDRESS + 420;
const unsigned short ARC_OK_CHECK_MODE                 = REGISTERS_ADDRESS + 422;
const unsigned short SCALE_FACTOR                      = REGISTERS_ADDRESS + 102;
const unsigned short INTEGRAL_COEFFICIENT              = REGISTERS_ADDRESS + 104;
const unsigned short DIFFERENTIAL_COEFFICIENT          = REGISTERS_ADDRESS + 106;
const unsigned short REGULATE_CYCLE                    = REGISTERS_ADDRESS + 108;
const unsigned short VARIABLE_SCALE_FACTOR             = REGISTERS_ADDRESS + 110;
const unsigned short MAXIMUM_SENSITIVITY               = REGISTERS_ADDRESS + 112;
const unsigned short PID_OUTPUT_DEAD_ZONE_RANGE        = REGISTERS_ADDRESS + 114;
const unsigned short ARC_VOL_ADJUST_ACCURACY           = REGISTERS_ADDRESS + 116;
const unsigned short COLLISION_SIGNAL_FILTER_TIME      = REGISTERS_ADDRESS + 118;
const unsigned short OUTPUT_FUNC_BASE                  = REGISTERS_ADDRESS + 600;
const unsigned short OUTPUT_NONC_BASE                  = REGISTERS_ADDRESS + 602;
const unsigned short OUTPUT_PORT_BASE                  = REGISTERS_ADDRESS + 604;
const unsigned short OUTPUT_PORT_SN_BASE               = REGISTERS_ADDRESS + 606;
const unsigned short INPUT_FUNC_BASE                   = REGISTERS_ADDRESS + 800;
const unsigned short INPUT_NONC_BASE                   = REGISTERS_ADDRESS + 802;
const unsigned short INPUT_PORT_BASE                   = REGISTERS_ADDRESS + 804;
const unsigned short INPUT_PORT_SN_BASE                = REGISTERS_ADDRESS + 806;

const unsigned short MODBUS_DEVICE_INFOR               = REGISTERS_ADDRESS + 8000;
const unsigned short CONNECT_FLAG                      = MODBUS_DEVICE_INFOR + 0;
const unsigned short CONNECT_TIME_OUT                  = MODBUS_DEVICE_INFOR + 2;
const unsigned short MASTER_MODEL                      = MODBUS_DEVICE_INFOR + 4;
const unsigned short MASTER_HARDWARE_VERSION           = MODBUS_DEVICE_INFOR + 6;
const unsigned short MASTER_SOFTWARE_VERSION           = MODBUS_DEVICE_INFOR + 8;
const unsigned short MASTER_VERSION_VERIFY             = MODBUS_DEVICE_INFOR + 10;
const unsigned short SLAVE_MODEL                       = MODBUS_DEVICE_INFOR + 12;
const unsigned short SLAVE_HARDWARE_VERSION            = MODBUS_DEVICE_INFOR + 14;
const unsigned short SLAVE_SOFTWARE_VERSION            = MODBUS_DEVICE_INFOR + 16;
const unsigned short SLAVE_VERSION_VERIFY              = MODBUS_DEVICE_INFOR + 18;

#endif // MODBUS_MODBUSMAPPINGDEF_H__
