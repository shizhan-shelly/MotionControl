// Copyright 2019 Fangling Software Co., Ltd. All Rights Reserved.
// Author: shizhan-shelly@hotmail.com (Zhan Shi)

#include "MotionControl/Widgets/devicediagnose/pps/liuhe/LH270ADiagnose.h"

#include <QtGui/QButtonGroup>

//#include "cutter/controller/pps/liuhe/LH270APPSDev.h"
//#include "cutter/OCutter.h"
#include "ui_LH270ADiagnose.h"
//#include "device/pps/liuhe/LiuheModbusAddr.h"
//#include "nmlclient/NmlClient.h"

namespace cutter {

LH270ADiagnose::LH270ADiagnose(QWidget *parent)
    : QWidget(parent)
    , station_id_(0) {

  ui_ = new Ui::LH270ADiagnose;
  ui_->setupUi(this);
  setStyleSheet("QPushButton, QLabel, QComboBox, QLineEdit { font-size: 11pt;\
                 font-family:SimSun }");

  initialDiagnoseWidget();
}

LH270ADiagnose::~LH270ADiagnose() {
  delete ui_;
}

void LH270ADiagnose::initialDiagnoseWidget() {
  diagnose_btn_group_ = new QButtonGroup(this);
  diagnose_btn_group_->addButton(ui_->pps_infors_, 0);
  diagnose_btn_group_->addButton(ui_->pps_inputs_, 1);
  diagnose_btn_group_->addButton(ui_->pps_outputs_, 2);
  diagnose_btn_group_->addButton(ui_->gc_inputs_, 3);
  diagnose_btn_group_->addButton(ui_->gc_outputs_, 4);
  connect(diagnose_btn_group_, SIGNAL(buttonClicked(int)), this, SLOT(onSwitchMonitor(int)));

  pps_output_btn_group_ = new QButtonGroup(this);
  pps_output_btn_group_->addButton(ui_->pps_output_switch_1_, 0);
  pps_output_btn_group_->addButton(ui_->pps_output_switch_2_, 1);
  pps_output_btn_group_->addButton(ui_->pps_output_switch_3_, 2);
  pps_output_btn_group_->addButton(ui_->pps_output_switch_4_, 3);
  pps_output_btn_group_->addButton(ui_->pps_output_switch_5_, 4);
  pps_output_btn_group_->addButton(ui_->pps_output_switch_6_, 5);
  pps_output_btn_group_->addButton(ui_->pps_output_switch_7_, 6);
  pps_output_btn_group_->addButton(ui_->pps_output_switch_8_, 7);
  pps_output_btn_group_->addButton(ui_->pps_output_switch_9_, 8);
  pps_output_btn_group_->addButton(ui_->pps_output_switch_10_, 9);
  pps_output_btn_group_->addButton(ui_->pps_output_switch_11_, 10);
  connect(pps_output_btn_group_, SIGNAL(buttonClicked(int)), this, SLOT(onPPSOutputSwitch(int)));

  gc_output_btn_group_ = new QButtonGroup(this);
  gc_output_btn_group_->addButton(ui_->gc_output_switch_1_, 0);
  gc_output_btn_group_->addButton(ui_->gc_output_switch_2_, 1);
  gc_output_btn_group_->addButton(ui_->gc_output_switch_3_, 2);
  gc_output_btn_group_->addButton(ui_->gc_output_switch_4_, 3);
  gc_output_btn_group_->addButton(ui_->gc_output_switch_5_, 4);
  gc_output_btn_group_->addButton(ui_->gc_output_switch_6_, 5);
  gc_output_btn_group_->addButton(ui_->gc_output_switch_7_, 6);
  gc_output_btn_group_->addButton(ui_->gc_output_switch_8_, 7);
  gc_output_btn_group_->addButton(ui_->gc_output_switch_9_, 8);
  gc_output_btn_group_->addButton(ui_->gc_output_switch_10_, 9);
  gc_output_btn_group_->addButton(ui_->gc_output_switch_11_, 10);
  gc_output_btn_group_->addButton(ui_->gc_output_switch_12_, 11);
  gc_output_btn_group_->addButton(ui_->gc_output_switch_13_, 12);
  gc_output_btn_group_->addButton(ui_->gc_output_switch_14_, 13);
  gc_output_btn_group_->addButton(ui_->gc_output_switch_15_, 14);
  gc_output_btn_group_->addButton(ui_->gc_output_switch_16_, 15);
  gc_output_btn_group_->addButton(ui_->gc_output_switch_17_, 16);
  gc_output_btn_group_->addButton(ui_->gc_output_switch_18_, 17);
  gc_output_btn_group_->addButton(ui_->gc_output_switch_19_, 18);
  gc_output_btn_group_->addButton(ui_->gc_output_switch_20_, 19);
  connect(gc_output_btn_group_, SIGNAL(buttonClicked(int)), this, SLOT(onGCOutputSwitch(int)));
}

void LH270ADiagnose::setCurrentStation(int station_id) {
  station_id_ = station_id;
}

void LH270ADiagnose::Update() {
  if (ui_->stack_->currentWidget() == ui_->pps_inputs_page_) {
    UpdatePPSInputs();
  } else if (ui_->stack_->currentWidget() == ui_->pps_outputs_page_) {
    UpdatePPSOutputs();
  } else if (ui_->stack_->currentWidget() == ui_->gc_inputs_page_) {
    UpdateGCInputs();
  } else if (ui_->stack_->currentWidget() == ui_->gc_outputs_page_) {
    UpdateGCOutputs();
  } else {
    UpdatePPSInfors();
  }
}

void LH270ADiagnose::UpdatePPSInfors() {
  //Status_PPS status_pps = OCutter::GetInstance()->GetController()->dev_comm_->
  //    status_->station_manager_.stations_[station_id_].plasma_.pps_;

  //unsigned short chopper_A_set_current = status_pps.liuhe_.chopper_A_set_current_;
  //unsigned short chopper_B_set_current = status_pps.liuhe_.chopper_B_set_current_;
  //unsigned short chopper_A_PWM_duty = status_pps.liuhe_.chopper_A_PWM_duty_;
  //unsigned short chopper_B_PWM_duty = status_pps.liuhe_.chopper_B_PWM_duty_;
  //unsigned short cur_A_current = status_pps.liuhe_.cur_A_current_;
  //unsigned short cur_B_current = status_pps.liuhe_.cur_B_current_;
  //unsigned short cur_work_current = status_pps.liuhe_.cur_work_current_;
  //unsigned short transformer_temperature = status_pps.liuhe_.transformer_temperature_;
  //unsigned short chopper_A_temperature = status_pps.liuhe_.chopper_A_temperature_;
  //unsigned short chopper_B_temperature = status_pps.liuhe_.chopper_B_temperature_;
  //unsigned short coolant_temperature = status_pps.liuhe_.coolant_temperature_;
  //unsigned short line_voltage = status_pps.liuhe_.line_voltage_;
  //unsigned short coolant_flow = status_pps.liuhe_.coolant_flow_;
  //unsigned short cur_pps_current_setpoint = status_pps.liuhe_.cur_pps_current_setpoint_;
  //unsigned short cur_pps_state_code = status_pps.liuhe_.cur_pps_state_code_;
  //unsigned short cur_pps_fault_code = status_pps.liuhe_.cur_pps_fault_code_;
  //unsigned short preflow_plasma_gas_pressure = status_pps.liuhe_.preflow_plasma_gas_pressure_;
  //unsigned short preflow_shield_gas_pressure = status_pps.liuhe_.preflow_shield_gas_pressure_;
  //unsigned short cutflow_plasma_gas_pressure = status_pps.liuhe_.cutflow_plasma_gas_pressure_;
  //unsigned short cutflow_shield_gas_pressure = status_pps.liuhe_.cutflow_shield_gas_pressure_;
  //unsigned short plasma_gas_type = status_pps.liuhe_.plasma_gas_type_;
  //unsigned short shield_gas_type = status_pps.liuhe_.shield_gas_type_;

  //unsigned short pps_hardware_version = status_pps.liuhe_.pps_hardware_version_;
  //unsigned short gc_hardware_version = status_pps.liuhe_.gc_hardware_version_;
  //unsigned short pps_software_version = status_pps.liuhe_.pps_software_version_;
  //unsigned short gc_software_version = status_pps.liuhe_.gc_software_version_;

  //ui_->chopper_A_set_current_->setText(QString::number(chopper_A_set_current));
  //ui_->chopper_B_set_current_->setText(QString::number(chopper_B_set_current));
  //ui_->chopper_A_PWM_duty_->setText(QString::number(chopper_A_PWM_duty));
  //ui_->chopper_B_PWM_duty_->setText(QString::number(chopper_B_PWM_duty));
  //ui_->cur_A_current_->setText(QString::number(cur_A_current));
  //ui_->cur_B_current_->setText(QString::number(cur_B_current));
  //ui_->cur_work_current_->setText(QString::number(cur_work_current));
  //ui_->line_voltage_->setText(QString::number(line_voltage));
  //ui_->coolant_flow_->setText(QString::number(coolant_flow));
  //ui_->current_setpoint_->setText(QString::number(cur_pps_current_setpoint));
  //ui_->cur_state_code_->setText(QString::number(cur_pps_state_code));
  //ui_->cur_fault_code_->setText(QString::number(cur_pps_fault_code));
  //ui_->preflow_plasma_gas_pressure_->setText(QString::number(preflow_plasma_gas_pressure));
  //ui_->preflow_shield_gas_pressure_->setText(QString::number(preflow_shield_gas_pressure));
  //ui_->cutflow_plasma_gas_pressure_->setText(QString::number(cutflow_plasma_gas_pressure));
  //ui_->cutflow_shield_gas_pressure_->setText(QString::number(cutflow_shield_gas_pressure));
  //ui_->plasma_gas_type_->setText(LH270APPSDev::GasType(plasma_gas_type).c_str());
  //ui_->shield_gas_type_->setText(LH270APPSDev::GasType(shield_gas_type).c_str());
  //ui_->transformer_temp_->setText(OCutter::GetInstance()->GetPPSInfor()->GetPPSInfor(
  //    "Temperature", LH270APPSDev::Temperature(transformer_temperature), "value").c_str());
  //ui_->chopper_A_temp_->setText(OCutter::GetInstance()->GetPPSInfor()->GetPPSInfor(
  //    "Temperature", LH270APPSDev::Temperature(chopper_A_temperature), "value").c_str());
  //ui_->chopper_B_temp_->setText(OCutter::GetInstance()->GetPPSInfor()->GetPPSInfor(
  //    "Temperature", LH270APPSDev::Temperature(chopper_B_temperature), "value").c_str());
  //ui_->coolant_temp_->setText(OCutter::GetInstance()->GetPPSInfor()->GetPPSInfor(
  //    "Temperature", LH270APPSDev::Temperature(coolant_temperature), "value").c_str());

  //ui_->pps_hardware_version_->setText(QString::number(pps_hardware_version));
  //ui_->gc_hardware_version_->setText(QString::number(gc_hardware_version));
  //ui_->pps_software_version_->setText(QString::number(pps_software_version));
  //ui_->gc_software_version_->setText(QString::number(gc_software_version));

  //ui_->state_code_description_->setText(OCutter::GetInstance()->GetPPSInfor()->GetPPSInfor(
  //    "StateCode", LH270APPSDev::StateCode(status_pps.liuhe_.cur_pps_state_code_),
  //    "description").c_str());

  //ui_->state_code_implication_->setText(OCutter::GetInstance()->GetPPSInfor()->GetPPSInfor(
  //    "StateCode", LH270APPSDev::StateCode(status_pps.liuhe_.cur_pps_state_code_),
  //    "implication").c_str());

  //ui_->fault_code_description_->setText(OCutter::GetInstance()->GetPPSInfor()->GetPPSInfor(
  //    "FaultCode", LH270APPSDev::FaultCode(status_pps.liuhe_.cur_pps_fault_code_),
  //    "description").c_str());

  //ui_->fault_code_implication_->setText(OCutter::GetInstance()->GetPPSInfor()->GetPPSInfor(
  //    "FaultCode", LH270APPSDev::FaultCode(status_pps.liuhe_.cur_pps_fault_code_),
  //    "implication").c_str());

  //ui_->fault_code_resolve_->setText(OCutter::GetInstance()->GetPPSInfor()->GetPPSInfor(
  //    "FaultCode", LH270APPSDev::FaultCode(status_pps.liuhe_.cur_pps_fault_code_),
  //    "resolve").c_str());

}

void LH270ADiagnose::UpdatePPSInputs() {
  //Status_PPS status_pps = OCutter::GetInstance()->GetController()->dev_comm_->
  //    status_->station_manager_.stations_[station_id_].plasma_.pps_;

  //ui_->pps_input_1_->setPixmap(status_pps.liuhe_.pps_input_[0] == 1 ?
  //    QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  //ui_->pps_input_2_->setPixmap(status_pps.liuhe_.pps_input_[1] == 1 ?
  //    QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  //ui_->pps_input_3_->setPixmap(status_pps.liuhe_.pps_input_[2] == 1 ?
  //    QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  //ui_->pps_input_4_->setPixmap(status_pps.liuhe_.pps_input_[3] == 1 ?
  //    QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  //ui_->pps_input_5_->setPixmap(status_pps.liuhe_.pps_input_[4] == 1 ?
  //    QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  //ui_->pps_input_6_->setPixmap(status_pps.liuhe_.pps_input_[5] == 1 ?
  //    QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  //ui_->pps_input_7_->setPixmap(status_pps.liuhe_.pps_input_[6] == 1 ?
  //    QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

}

void LH270ADiagnose::UpdatePPSOutputs() {
  //Status_PPS status_pps = OCutter::GetInstance()->GetController()->dev_comm_->
  //    status_->station_manager_.stations_[station_id_].plasma_.pps_;

  //ui_->pps_output_switch_1_->setIcon(status_pps.liuhe_.pps_output_[0] == 1 ?
  //    QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  //ui_->pps_output_switch_2_->setIcon(status_pps.liuhe_.pps_output_[1] == 1 ?
  //    QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  //ui_->pps_output_switch_3_->setIcon(status_pps.liuhe_.pps_output_[2] == 1 ?
  //    QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  //ui_->pps_output_switch_4_->setIcon(status_pps.liuhe_.pps_output_[3] == 1 ?
  //    QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  //ui_->pps_output_switch_5_->setIcon(status_pps.liuhe_.pps_output_[4] == 1 ?
  //    QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  //ui_->pps_output_switch_6_->setIcon(status_pps.liuhe_.pps_output_[5] == 1 ?
  //    QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  //ui_->pps_output_switch_7_->setIcon(status_pps.liuhe_.pps_output_[6] == 1 ?
  //    QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  //ui_->pps_output_switch_8_->setIcon(status_pps.liuhe_.pps_output_[7] == 1 ?
  //    QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  //ui_->pps_output_switch_9_->setIcon(status_pps.liuhe_.pps_output_[8] == 1 ?
  //    QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  //ui_->pps_output_switch_10_->setIcon(status_pps.liuhe_.pps_output_[9] == 1 ?
  //    QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  //ui_->pps_output_switch_11_->setIcon(status_pps.liuhe_.pps_output_[10] == 1 ?
  //    QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

}

void LH270ADiagnose::UpdateGCInputs() {
  //Status_PPS status_pps = OCutter::GetInstance()->GetController()->dev_comm_->
  //    status_->station_manager_.stations_[station_id_].plasma_.pps_;

  //ui_->gc_input_1_->setPixmap(status_pps.liuhe_.gc_input_[0] == 1 ?
  //    QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  //ui_->gc_input_2_->setPixmap(status_pps.liuhe_.gc_input_[1] == 1 ?
  //    QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  //ui_->gc_input_3_->setPixmap(status_pps.liuhe_.gc_input_[2] == 1 ?
  //    QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  //ui_->gc_input_4_->setPixmap(status_pps.liuhe_.gc_input_[3] == 1 ?
  //    QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  //ui_->gc_input_5_->setPixmap(status_pps.liuhe_.gc_input_[4] == 1 ?
  //    QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  //ui_->gc_input_6_->setPixmap(status_pps.liuhe_.gc_input_[5] == 1 ?
  //    QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  //ui_->gc_input_7_->setPixmap(status_pps.liuhe_.gc_input_[6] == 1 ?
  //    QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  //ui_->gc_input_8_->setPixmap(status_pps.liuhe_.gc_input_[7] == 1 ?
  //    QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  //ui_->gc_input_9_->setPixmap(status_pps.liuhe_.gc_input_[8] == 1 ?
  //    QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  //ui_->gc_input_10_->setPixmap(status_pps.liuhe_.gc_input_[9] == 1 ?
  //    QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  //ui_->gc_input_11_->setPixmap(status_pps.liuhe_.gc_input_[10] == 1 ?
  //    QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  //ui_->gc_input_12_->setPixmap(status_pps.liuhe_.gc_input_[11] == 1 ?
  //    QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  //ui_->gc_input_13_->setPixmap(status_pps.liuhe_.gc_input_[12] == 1 ?
  //    QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

}

void LH270ADiagnose::UpdateGCOutputs() {
  //Status_PPS status_pps = OCutter::GetInstance()->GetController()->dev_comm_->
  //    status_->station_manager_.stations_[station_id_].plasma_.pps_;

  //ui_->gc_output_switch_1_->setIcon(status_pps.liuhe_.gc_output_[0] == 1 ?
  //    QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  //ui_->gc_output_switch_2_->setIcon(status_pps.liuhe_.gc_output_[1] == 1 ?
  //    QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  //ui_->gc_output_switch_3_->setIcon(status_pps.liuhe_.gc_output_[2] == 1 ?
  //    QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  //ui_->gc_output_switch_4_->setIcon(status_pps.liuhe_.gc_output_[3] == 1 ?
  //    QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  //ui_->gc_output_switch_5_->setIcon(status_pps.liuhe_.gc_output_[4] == 1 ?
  //    QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  //ui_->gc_output_switch_6_->setIcon(status_pps.liuhe_.gc_output_[5] == 1 ?
  //    QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  //ui_->gc_output_switch_7_->setIcon(status_pps.liuhe_.gc_output_[6] == 1 ?
  //    QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  //ui_->gc_output_switch_8_->setIcon(status_pps.liuhe_.gc_output_[7] == 1 ?
  //    QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  //ui_->gc_output_switch_9_->setIcon(status_pps.liuhe_.gc_output_[8] == 1 ?
  //    QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  //ui_->gc_output_switch_10_->setIcon(status_pps.liuhe_.gc_output_[9] == 1 ?
  //    QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  //ui_->gc_output_switch_11_->setIcon(status_pps.liuhe_.gc_output_[10] == 1 ?
  //    QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  //ui_->gc_output_switch_12_->setIcon(status_pps.liuhe_.gc_output_[11] == 1 ?
  //    QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  //ui_->gc_output_switch_13_->setIcon(status_pps.liuhe_.gc_output_[12] == 1 ?
  //    QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  //ui_->gc_output_switch_14_->setIcon(status_pps.liuhe_.gc_output_[13] == 1 ?
  //    QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  //ui_->gc_output_switch_15_->setIcon(status_pps.liuhe_.gc_output_[14] == 1 ?
  //    QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  //ui_->gc_output_switch_16_->setIcon(status_pps.liuhe_.gc_output_[15] == 1 ?
  //    QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  //ui_->gc_output_switch_17_->setIcon(status_pps.liuhe_.gc_output_[16] == 1 ?
  //    QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  //ui_->gc_output_switch_18_->setIcon(status_pps.liuhe_.gc_output_[17] == 1 ?
  //    QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  //ui_->gc_output_switch_19_->setIcon(status_pps.liuhe_.gc_output_[18] == 1 ?
  //    QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

  //ui_->gc_output_switch_20_->setIcon(status_pps.liuhe_.gc_output_[19] == 1 ?
  //    QPixmap(":/widget/resource/open.png") : QPixmap(":/widget/resource/closed.png"));

}

void LH270ADiagnose::onSwitchMonitor(int monitor_id) {
  switch (monitor_id) {
   case 0:
    ui_->stack_->setCurrentWidget(ui_->pps_infors_page_);
    break;
   case 1:
    ui_->stack_->setCurrentWidget(ui_->pps_inputs_page_);
    break;
   case 2:
    ui_->stack_->setCurrentWidget(ui_->pps_outputs_page_);
    break;
   case 3:
    ui_->stack_->setCurrentWidget(ui_->gc_inputs_page_);
    break;
   case 4:
    ui_->stack_->setCurrentWidget(ui_->gc_outputs_page_);
    break;
   default:
    break;
  }
}

void LH270ADiagnose::onPPSOutputSwitch(int index) {
  //OCutter *cutter = cutter::OCutter::GetInstance();
  //std::map<int, PPSClient *> pps_dev = cutter->pps_factory_.GetPPSDev();
  //std::map<int, PPSClient *>::const_iterator it = pps_dev.find(station_id_);
  //if (it != pps_dev.end()) {
  //  Status_PPS status_pps = OCutter::GetInstance()->GetController()->dev_comm_->
  //      status_->station_manager_.stations_[station_id_].plasma_.pps_;

  //  bool checked = status_pps.liuhe_.pps_output_[index] == 1;
  //  it->second->SendCommandToPPS(LIUHE_PPS_OUTPUT_ADDR + index, !checked);
  //}
}

void LH270ADiagnose::onGCOutputSwitch(int index) {
  //OCutter *cutter = cutter::OCutter::GetInstance();
  //std::map<int, PPSClient *> pps_dev = cutter->pps_factory_.GetPPSDev();
  //std::map<int, PPSClient *>::const_iterator it = pps_dev.find(station_id_);
  //if (it != pps_dev.end()) {
  //  Status_PPS status_pps = OCutter::GetInstance()->GetController()->dev_comm_->
  //      status_->station_manager_.stations_[station_id_].plasma_.pps_;

  //  bool checked = status_pps.liuhe_.gc_output_[index] == 1;
  //  it->second->SendCommandToPPS(LIUHE_GC_OUTPUT_ADDR + index, !checked);
  //}
}

} // namespace cutter
